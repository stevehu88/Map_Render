/*
 * Node.h
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#ifndef NODE_H_
#define NODE_H_

#include "Tile.h"
#include "Point.h"

class Node {
public:
	Node();
	Node(const double lng,const double lat);
	Point convert2Point(const Tile& tile) const;


	virtual ~Node();

	double getLat() const {
		return lat;
	}

	void setLat(double lat) {
		this->lat = lat;
	}

	double getLng() const {
		return lng;
	}

	void setLng(double lng) {
		this->lng = lng;
	}

private:
	double lat;
	double lng;

};

#endif /* NODE_H_ */
