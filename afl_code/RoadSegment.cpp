/*
 * Segment.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#include "RoadSegment.h"
#include "ColorManger.h"

RoadSegment::RoadSegment()
{
	this->speed_level = -1;
	this->offset = 0;
	this->isOneWay = 0;
	this->strokeWidth = 2;
}


RoadSegment::RoadSegment(const Node& f_node,const Node& t_node,const int& speedLevel,const int& isOneway, const double& offset, const double& strokeWidth)
{
	this->from_node = f_node;
	this->to_node = t_node;
	this->speed_level = speedLevel;
	this->isOneWay = isOneWay;
	this->offset = offset;
	this->strokeWidth = strokeWidth;
}

Segment RoadSegment::convertToSegment(const Tile& tile)const
{
	agg::rgba8 color;
	speedLevel2Color(this->speed_level, color);
	Point fPoint = this->from_node.convert2Point(tile);
	Point tPoint = this->to_node.convert2Point(tile);

	if(this->isOneWay)
	{
		return Segment(color, fPoint,tPoint, this->strokeWidth);
	}
	else
	{
		return Segment(color, fPoint,tPoint, this->strokeWidth).offset(this->offset);
	}


}

RoadSegment::~RoadSegment() {
	// TODO Auto-generated destructor stub
}

