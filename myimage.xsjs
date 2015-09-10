//**** Example for basic REQUEST RESPONSE handling
var paramName; var paramValue; var headerName; var headerValue; var contentType;
//Implementation of GET call
var x,y,z;
function handleGet() {
	
	var content = '';
	var conn = $.db.getConnection("myimage.s.logic.service::admin");
	var pstmt = conn.prepareStatement('CALL "I075903"."RENDER_TILE"(?,?,?)');
	pstmt.setInteger(1, z);
	pstmt.setInteger(2, x);
	pstmt.setInteger(3, y);
	pstmt.execute();
	var rs = pstmt.getResultSet();
	if(rs.next()){
		content = rs.getClob(1);
	}
	rs.close();
	pstmt.close();
	conn.commit();
	conn.close();
	content = $.util.codec.decodeBase64(content);
	$.response.status = $.net.http.OK;
	 return content;
}
//Implementation of POST call
function handlePost() {
	var bodyStr = $.request.body ? $.request.body.asString() : undefined;
	if ( bodyStr === undefined ){
		 $.response.status = $.net.http.INTERNAL_SERVER_ERROR;
		 return {"myResult":"Missing BODY"};
	}
	// Extract body insert data to DB and return results in JSON/other format
	$.response.status = $.net.http.CREATED;
    return {"myResult":"POST success"};
}
// Check Content type headers and parameters
function validateInput() {
	var i;
	for (i = 0; i < $.request.parameters.length; ++i) {
	    paramName = $.request.parameters[i].name;
	    paramValue = $.request.parameters[i].value;
	    if (paramName === 'x') {
	    	x = parseInt(paramValue, 10);
	    }
	    if (paramName === 'y') {
	    	y = parseInt(paramValue, 10);
	    }	    
	    if (paramName === 'z') {
	    	z = parseInt(paramValue, 10);
	    }
	}
	return true;
}
// Request process 
function processRequest(){
	if (validateInput()){
		try {
		    switch ( $.request.method ) {
		        //Handle your GET calls here
		        case $.net.http.GET:
		        	$.response.setBody(handleGet());
		            break;
		            //Handle your POST calls here
		        case $.net.http.POST:
		            $.response.setBody("Error");
		            break; 
		        //Handle your other methods: PUT, DELETE
		        default:
		            $.response.status = $.net.http.METHOD_NOT_ALLOWED;
		            $.response.setBody("Wrong request method");		        
		            break;
		    }
//		    $.response.contentType = 'plain/text';
		    $.response.contentType = 'image/png';
		    $.response.cacheControl = 'max-age=300';
		} catch (e) {
		    $.response.setBody("Failed to execute action: " + e.toString());
		}
	}
}
// Call request processing  
processRequest();
