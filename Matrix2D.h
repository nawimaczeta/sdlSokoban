/*
 * Matrix2D.h
 *
 *  Created on: Nov 9, 2017
 *      Author: li
 */

#ifndef MATRIX2D_H_
#define MATRIX2D_H_

#include <vector>
#include <stdexcept>

template <typename T>
class Matrix2D {
public:
	Matrix2D(unsigned x, unsigned y) :
		sizeX(x), sizeY(y) {
		matrix.resize(sizeX * sizeY);
	}

	T get(unsigned x, unsigned y) const {
		if ((x >= sizeX) || (y >= sizeY)) throw std::out_of_range("Index out of range");
		return matrix.at(x + y * sizeY);
	}

	void set(unsigned x, unsigned y, T value) {
		if ((x >= sizeX) || (y >= sizeY)) throw std::out_of_range("Index out of range");
		matrix.insert(x + sizeY * y, value);
	}



private:
	unsigned sizeX;
	unsigned sizeY;

	std::vector<T> matrix;
};

#endif /* MATRIX2D_H_ */
