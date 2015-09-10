/*
 * Bound.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#include "Bound.h"

Bound::Bound() {
	north = 0;
	south = 0;
	east = 0;
	west = 0;
}

Bound::Bound(double n, double s, double e, double w) {
	north = n;
	south = s;
	east = e;
	west = w;
}

Bound::~Bound() {
	// TODO Auto-generated destructor stub
}

