/*
 * Renderer.h
 *
 *  Created on: Aug 31, 2015
 *      Author: Steve Hu
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include "Tile.h"
#include "Edge.h"
#include <vector>
#include "agg2/agg_renderer_base.h"
#include "RoadSegment.h"


	enum
	{
	    frame_width = 256,
	    frame_height = 256,
		bytes_per_pixel = 4,
	};

	bool render(const Tile& tile,const std::vector<RoadSegment>& segments, agg::rendering_buffer& rbuf);
	bool getPngAsBase64(const Tile& tile,const std::vector<RoadSegment>& segments,std::string& base64_str);

#endif /* RENDERER_H_ */
