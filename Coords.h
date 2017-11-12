/*
 * Coords.h
 *
 *  Created on: Nov 10, 2017
 *      Author: li
 */

#ifndef COORDS_H_
#define COORDS_H_

class Coords {
public:
	Coords() : x{0}, y{0} {}
	Coords(unsigned x, unsigned y) : x{x}, y{y} {}
	Coords(const Coords & c) : x{c.x}, y{c.y} {}

	unsigned getX() const {return x;}
	unsigned getY() const {return y;}

	void setX(const unsigned x) {this->x = x;}
	void setY(const unsigned y) {this->y = y;}
	void set(const unsigned x, const unsigned y) {
		this->x = x;
		this->y = y;
	}
private:
	unsigned x;
	unsigned y;
};



#endif /* COORDS_H_ */
