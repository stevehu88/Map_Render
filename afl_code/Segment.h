/*
 * Segment.h
 *
 *  Created on: Sep 4, 2015
 *      Author: Steve Hu
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_
#include "Point.h"
#include "agg2/agg_color_rgba.h"

class Segment {
public:
	Segment();
	Segment(agg::rgba8 color,const Point& fromPoint,const Point& toPoint, double strokeWidth);
	Segment offset(double offPixel)const;
	virtual ~Segment();

	agg::rgba8 getColor() const {
		return color;
	}

	void setColor(agg::rgba8 color) {
		this->color = color;
	}

	const Point& getFromPoint() const {
		return fromPoint;
	}

	void setFromPoint(const Point& fromPoint) {
		this->fromPoint = fromPoint;
	}

	double getStrokeWidth() const {
		return strokeWidth;
	}

	void setStrokeWidth(double strokeWidth) {
		this->strokeWidth = strokeWidth;
	}

	const Point& getToPoint() const {
		return toPoint;
	}

	void setToPoint(const Point& toPoint) {
		this->toPoint = toPoint;
	}

private:
	Point fromPoint, toPoint;
	agg::rgba8 color;
	double strokeWidth;
};

#endif /* SEGMENT_H_ */
