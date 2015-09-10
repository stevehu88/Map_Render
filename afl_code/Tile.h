/*
 * Tile.h
 *
 *  Created on: Aug 30, 2015
 *      Author: Steve Hu
 */

#ifndef TILE_H_
#define TILE_H_
#include "Bound.h"

class Tile {
public:
	Tile();
	Tile(int x, int y, int z);
    Bound getBounds() const;
	double getLngDelta() const;
	double getLatDelta() const;
	unsigned getByteSize() const;


	virtual ~Tile();

	int getX() const {
		return x;
	}

	void setX(int x) {
		this->x = x;
	}

	int getY() const {
		return y;
	}

	void setY(int y) {
		this->y = y;
	}

	int getZ() const {
		return z;
	}

	void setZ(int z) {
		this->z = z;
	}

	double getImgHeight() const {
		return imgHeight;
	}

	void setImgHeight(double imgHeight = 256) {
		this->imgHeight = imgHeight;
	}

	double getImgWidth() const {
		return imgWidth;
	}

	void setImgWidth(double imgWidth = 256) {
		this->imgWidth = imgWidth;
	}

	unsigned getBytesPerPixel() const {
		return bytes_per_pixel;
	}

	void setBytesPerPixel(unsigned bytesPerPixel) {
		bytes_per_pixel = bytesPerPixel;
	}

private:
	int x;
	int y;
	int z;
	unsigned imgWidth;
	unsigned imgHeight;
	unsigned bytes_per_pixel;
};

#endif /* TILE_H_ */
