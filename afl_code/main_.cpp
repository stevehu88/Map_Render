/*
 * main_.cpp
 *
 *  Created on: Aug 31, 2015
 *      Author: Steve Hu
 */


#include "Renderer.h"
#include <iostream>
#include <cstdlib>

#include <stdlib.h>

int main()
{
	unsigned i = 0;
	for (i = 0; i < 1; i++)
	{
		Tile tile(14,13599,6672);
		std::vector<RoadSegment> segments;

		Node node1(118.81,31.64);
		Node node2(118.81,31.65);
		Node node3(118.82,31.64);


		segments.push_back(RoadSegment(node1, node2, 1, 0, 0, 2));
		segments.push_back(RoadSegment(node1, node3, 5, 0, 0, 2));
		std::string str;
		getPngAsBase64(tile, segments, str);

		std::cout << strlen(str.c_str()) << std::endl;

		std::cout << str << std::endl;

	}

	return 0;
}
