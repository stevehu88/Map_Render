/*
 * Point.h
 *
 *  Created on: Sep 4, 2015
 *      Author: Steve Hu
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point();
	Point(double px, double py);
	virtual ~Point();

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

private:
	double x,y;
};

#endif /* POINT_H_ */
