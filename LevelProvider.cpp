/*
 * LevelProvider.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: li
 */

#include <stdexcept>

#include "LevelProvider.h"

void LevelProvider::loadLevel(const std::string & content) {
	std::unique_ptr<Level> lp{ new Level(content) };
	levels.push_back(std::move(lp));
}

Level & LevelProvider::getLevel(unsigned index) {
	return *levels.at(index);
}

Item LevelProvider::getLevelItem(const unsigned index, const unsigned x, const unsigned y) {
	if (index > levels.size()) {
		throw std::out_of_range("Level index " + std::to_string(index) +" out of range\n");
	}

	Coords levelSize = getLevelSize(index);
	if (x > levelSize.getX() || y > levelSize.getY()) {
		throw std::out_of_range{"Coords out of range\n"};
	}

	return levels.at(index)->getItem(x, y);
}

unsigned LevelProvider::getNumberOfLevels() const {
	return levels.size();
}

Coords LevelProvider::getLevelSize(const unsigned index) {
	if (index > levels.size()) {
		throw std::out_of_range("Level index " + std::to_string(index) +" out of range\n");
	}

	return levels.at(index)->getSize();
}

