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

Level & LevelProvider::getLevel(unsigned index) const {
	return *levels.at(index);
}

unsigned LevelProvider::getNumberOfLevels() const {
	return levels.size();
}

