/*
 * Tile.cpp
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#include "Tile.h"
#include <math.h>



Tile::Tile() {
	x = 0;
	y = 0;
	z = 0;
	imgWidth = 256;
	imgHeight = 256;
	bytes_per_pixel = 4;
}


Tile::Tile(int z, int x, int y) {
	// TODO Auto-generated constructor stub
	setX(x);
	setY(y);
	setZ(z);
	imgWidth = 256;
	imgHeight = 256;
	bytes_per_pixel = 4;
}


double tile2lon(int x, int z)
{
	return x / pow(2.0, z) * 360.0 - 180;
}

double tile2lat(int y, int z)
{
	double n = M_PI - 2.0 * M_PI * y / pow(2.0, z);
	return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

Bound Tile::getBounds() const
{
    double north = tile2lat(y, z);
    double south = tile2lat(y + 1, z);
    double west = tile2lon(x, z);
    double east = tile2lon(x + 1, z);
    return Bound(north, south, east, west);
}


double Tile::getLngDelta() const
{
	Bound bound = this->getBounds();
	return fabs(bound.getEast() - bound.getWest());
}

double Tile::getLatDelta() const
{
	Bound bound = this->getBounds();
	return fabs(bound.getNorth() - bound.getSouth());
}


unsigned Tile::getByteSize() const
{
	return imgWidth * imgHeight * bytes_per_pixel;
}
Tile::~Tile() {
	// TODO Auto-generated destructor stub
}
