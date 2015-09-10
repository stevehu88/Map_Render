/*
 * Segment.cpp
 *
 *  Created on: Sep 4, 2015
 *      Author: Steve Hu
 */

#include "Segment.h"

Segment::Segment() {
	// TODO Auto-generated constructor stub
	this->strokeWidth = 2;
}

Segment::Segment(agg::rgba8 color,const Point& fromPoint,const Point& toPoint, double strokeWidth){
	this->color = color;
	this->fromPoint = fromPoint;
	this->toPoint = toPoint;
	this->strokeWidth = strokeWidth;
}

Segment Segment::offset(double m)const
{
    double dx = toPoint.getX() - fromPoint.getX();
    double dy = toPoint.getY() - fromPoint.getY();
    double d = sqrt(dx*dx + dy*dy);
    if(d == 0) {
          return Segment(this->getColor(), fromPoint, toPoint, this->getStrokeWidth());
    }
    else
    {
        double offx = -m * dy / d;
        double offy = m * dx / d;


        Point pn0(fromPoint.getX() + offx, fromPoint.getY() + offy);
        Point pn1(toPoint.getX() + offx, toPoint.getY() + offy);
        return Segment(this->getColor(),pn0, pn1, this->getStrokeWidth());
    }


}

Segment::~Segment() {
	// TODO Auto-generated destructor stub
}

