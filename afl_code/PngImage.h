/*
 * PngImage.h
 *
 *  Created on: Aug 31, 2015
 *      Author: Steve Hu
 */

#ifndef PNGIMAGE_H_
#define PNGIMAGE_H_

#include "png++/png.hpp"
#include "agg2/agg_renderer_base.h"

	bool getPngImage(agg::rendering_buffer& rbuf, png::image<png::rgba_pixel>& img);
	bool getBase64String(const agg::rendering_buffer rbuf, std::string& base64_str);

#endif /* PNGIMAGE_H_ */
