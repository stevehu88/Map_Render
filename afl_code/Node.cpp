/*
 * Node.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#include "Node.h"

Node::Node() {
	this->lat = 0;
	this->lng = 0;
}

Node::Node(const double lng,const double lat) {
	this->lng = lng;
	this->lat = lat;

}

Point Node::convert2Point(const Tile& tile) const
{

	Bound bound = tile.getBounds();
	double west = bound.getWest();
	double north = bound.getNorth();

	double pixl_lng = (this->lng - west) / tile.getLngDelta() * tile.getImgWidth();
	double pixl_lat = (north- this->lat) / tile.getLatDelta() * tile.getImgHeight();

	return Point(pixl_lng, pixl_lat);
}


Node::~Node() {
	// TODO Auto-generated destructor stub
}

