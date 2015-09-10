/*
 * Segment.h
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#ifndef ROADSEGMENT_H_
#define ROADSEGMENT_H_
#include "Node.h"
#include "Segment.h"

class RoadSegment {
public:
	RoadSegment();
	RoadSegment(const Node& f_node,const Node& t_node,const int& speedLevel,const int& isOneWay,const double& offset, const double& strokeWidth);
	Segment convertToSegment(const Tile&)const;
	virtual ~RoadSegment();

	const Node& getFromNode() const {
		return from_node;
	}

	void setFromNode(const Node& fromNode) {
		from_node = fromNode;
	}

	const Node& getToNode() const {
		return to_node;
	}

	void setToNode(const Node& toNode) {
		to_node = toNode;
	}

	int getSpeedLevel() const {
		return speed_level;
	}

	void setSpeedLevel(int speedLevel) {
		speed_level = speedLevel;
	}

	double getOffset() const {
		return offset;
	}

	void setOffset(double offset) {
		this->offset = offset;
	}

	int getIsOneWay() const {
		return isOneWay;
	}

	void setIsOneWay(int isOneWay) {
		this->isOneWay = isOneWay;
	}

	double getStrokeWidth() const {
		return strokeWidth;
	}

	void setStrokeWidth(double strokeWidth) {
		this->strokeWidth = strokeWidth;
	}

private:
	Node from_node;
	Node to_node;
	int speed_level;
	int isOneWay;
	double offset;
	double strokeWidth;
};

#endif /* ROADSEGMENT_H_ */
