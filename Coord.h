/*
 * Coord.h
 *
 *  Created on: Nov 10, 2017
 *      Author: li
 */

#ifndef COORD_H_
#define COORD_H_

class Coord {
public:
	Coord(unsigned x, unsigned y) : x{x}, y{y} {}
	Coord(const Coord & c) : x{c.x}, y{c.y} {}
private:
	unsigned x;
	unsigned y;
};



#endif /* COORD_H_ */
