/*
 * Renderer.cpp
 *
 *  Created on: Aug 31, 2015
 *      Author: Steve Hu
 */

#include "Renderer.h"
#include "agg2/agg_rendering_buffer.h"
#include "agg2/agg_pixfmt_rgba.h"
#include "agg2/agg_renderer_outline_aa.h"
#include "agg2/agg_rasterizer_outline_aa.h"
#include "agg2/agg_renderer_scanline.h"
#include "agg2/agg_rasterizer_scanline_aa.h"
#include "agg2/agg_scanline_p.h"
#include "agg2/agg_conv_stroke.h"
#include "agg2/agg_path_storage.h"

#include "PngImage.h"


bool render(const Tile& tile,const std::vector<RoadSegment>& segments,agg::rendering_buffer& rbuf)
{
	typedef agg::renderer_base<agg::pixfmt_rgba32> ren_base;
	typedef agg::renderer_outline_aa<ren_base> renderer_oaa;
	typedef agg::rasterizer_outline_aa<renderer_oaa> rasterizer_outline_aa;
	typedef agg::renderer_scanline_aa_solid<ren_base> renderer;

    agg::pixfmt_rgba32 pixf(rbuf);
    ren_base renb(pixf);

    renderer ren(renb);
    agg::rasterizer_scanline_aa<> ras;
    agg::scanline_p8 sl;

    unsigned i = 0;
    for (i=0; i < segments.size(); i++)
    {
    	RoadSegment rseg = segments[i];
    	Segment seg = rseg.convertToSegment(tile);


    	ren.color(seg.getColor());
    	agg::path_storage path;
    	path.move_to(seg.getFromPoint().getX(), seg.getFromPoint().getY());
    	path.line_to(seg.getToPoint().getX(), seg.getToPoint().getY());

    	agg::conv_stroke<agg::path_storage> stroke(path);
    	stroke.width(seg.getStrokeWidth());

        agg::line_cap_e  cap = agg::round_cap;
        agg::line_join_e join = agg::round_join;
        stroke.line_join(join);
        stroke.line_cap(cap);


    	ras.reset();
    	ras.add_path(stroke);
    	agg::render_scanlines(ras,sl,ren);
    }
	return true;
}



bool getPngAsBase64(const Tile& tile,const std::vector<RoadSegment>& segments,std::string& base64_str)
{
	agg::int8u* buffer = new agg::int8u[tile.getByteSize()];
	memset(buffer, 0 , tile.getByteSize());
	agg::rendering_buffer rbuf = agg::rendering_buffer(buffer,
			tile.getImgWidth(), tile.getImgHeight(), tile.getImgWidth() * tile.getBytesPerPixel());
	render(tile, segments, rbuf);
	getBase64String(rbuf, base64_str);
	delete [] buffer;
	return true;
}

