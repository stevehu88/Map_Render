/*
 * PngImage.cpp
 *
 *  Created on: Aug 31, 2015
 *      Author: Steve Hu
 */


#include <string>
#include <sstream>
#include <iostream>

#include "PngImage.h"
#include "base64.h"

#include "agg2/agg_renderer_base.h"
#include "agg2/agg_pixfmt_rgba.h"

bool getPngImage(const agg::rendering_buffer& in_rbuf, png::image<png::rgba_pixel>& img)
{
	img = png::image<png::rgba_pixel>(256,256);

	agg::rendering_buffer rbuf(in_rbuf);

    agg::pixfmt_rgba32 pixf(rbuf);

    unsigned x,y;

    unsigned height =  pixf.height();
    unsigned width = pixf.width();

    for(y = 0; y < height; ++y)
    {
        for (x = 0; x < width; ++x)
        {
        	agg::rgba8 c = pixf.pixel(x,y);
        	img[y][x] = png::rgba_pixel(c.r,c.g,c.b,c.a);
        }
    }

    return true;
}


bool getBase64String(const agg::rendering_buffer rbuf, std::string& base64_str)
{
	png::image<png::rgba_pixel>  img;
	getPngImage(rbuf, img);
	std::ostringstream oss;
	img.write_stream(oss);

	oss.flush();
	std::string str = oss.str();

	base64_str = base64_encode(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
	return true;
}


