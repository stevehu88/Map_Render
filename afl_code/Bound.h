/*
 * Bound.h
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#ifndef BOUND_H_
#define BOUND_H_

class Bound {
public:
	Bound();
	Bound(double n, double s, double e, double w);
	virtual ~Bound();

	double getEast() const {
		return east;
	}

	void setEast(double east) {
		this->east = east;
	}

	double getNorth() const {
		return north;
	}

	void setNorth(double north) {
		this->north = north;
	}

	double getSouth() const {
		return south;
	}

	void setSouth(double south) {
		this->south = south;
	}

	double getWest() const {
		return west;
	}

	void setWest(double west) {
		this->west = west;
	}

private:
	double north;
	double south;
	double east;
	double west;
};

#endif /* BOUND_H_ */
