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
#include <algorithm>

template <typename T>
class Matrix2D {
public:
	Matrix2D(unsigned x, unsigned y) :
		sizeX{x}, sizeY{y} {
		matrix.resize(sizeX * sizeY);
		std::cout << "matrix size: " << std::to_string((sizeX) * (sizeY)) << "\n";
	}

	Matrix2D(const Matrix2D & m ) :
		sizeX{m.sizeX}, sizeY{m.sizeY}, matrix{m.matrix}
		{
	}

	T get(unsigned x, unsigned y) const {
		if ((x >= sizeX) || (y >= sizeY)) {
			throw std::out_of_range(
				"Matrix2D::get Index out of range. Size is: x=" +
				std::to_string(sizeX) + " y=" + std::to_string(sizeY) +
				", requested cords: x=" + std::to_string(x) + " y=" +
				std::to_string(y) + " index: " + std::to_string((x % sizeX) + sizeY* y));
		}
		return matrix.at(xy2index(x, y));
	}

	void set(unsigned x, unsigned y, T value) {
		if ((x >= sizeX) || (y >= sizeY)) {
			throw std::out_of_range(
					"Matrix2D::set Index out of range. Size is: x=" +
					std::to_string(sizeX) + " y=" + std::to_string(sizeY) +
					", requested cords: x=" + std::to_string(x) + " y=" +
					std::to_string(y) + " index: " + std::to_string((x % sizeX) + sizeY* y));
		}
		matrix[xy2index(x, y)] = value;
	}

	unsigned getSizeX() const {
		return sizeX;
	}

	unsigned getSizeY() const {
		return sizeY;
	}

	unsigned getCountOfItems(T & item) {
		return std::count(
				std::begin(matrix),
				std::end(matrix),
				item);
	}



private:
	unsigned sizeX;
	unsigned sizeY;

	std::vector<T> matrix;
	unsigned xy2index(unsigned x, unsigned y) const {
		return (x + (sizeY - 1)* y);
	}
};

#endif /* MATRIX2D_H_ */
