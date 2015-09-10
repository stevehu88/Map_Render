/*
 * ColorManger.h
 *
 *  Created on: Sep 4, 2015
 *      Author: Steve Hu
 */

#ifndef COLORMANGER_H_
#define COLORMANGER_H_


void speedLevel2Color(const int SpeedLevel, agg::rgba8& color)
{
	switch(SpeedLevel){
		case 1:
			color = agg::rgba8(0,117,2,255); //red
			break;
		case 2:
			color = agg::rgba8(146,198,1,255); // green
			break;
		case 3:
			color = agg::rgba8(255,255,1, 255); // yellow
			break;
		case 4:
			color = agg::rgba8(255,156,1,255); // blue
			break;
		case 5:
			color = agg::rgba8(254,0,0,255);
			break;
		default:
			color = agg::rgba8(0,0,0,0);
	}
	return;
}



#endif /* COLORMANGER_H_ */
