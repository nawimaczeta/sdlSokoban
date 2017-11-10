/*
 * Level.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: li
 */

#include <iostream>
#include <sstream>
#include <map>

#include "Level.h"

Level::Level(std::string & content)// :
//		boardMap { nullptr }
{
	loadFromString(content);
}

bool Level::loadFromString(std::string & map) {
	char delimiter = '\n';
	std::stringstream ss { map };
	std::vector<std::string> lines;

	unsigned maxHight;
	unsigned maxWidth = 0;

	std::cout << map << "\n";

	for (std::string line; std::getline(ss, line, delimiter);) {
		lines.push_back(line);
		if (line.size() > maxWidth) {
			maxWidth = line.size();
		}
	}

	// fill lines with ' '. All of them should be equal maxWidth
	for (auto l : lines) {
		int missed;
		missed = maxWidth - l.size();

		// generate string with 'missed' number of spaces
		std::string s{""};
		for (int i = 0; i < missed; i++) {
			s += "U";
		}
		l += s;
	}

	maxHight = lines.size();

	std::unique_ptr<Matrix2D<Item>> map2d{new Matrix2D<Item>{maxWidth, maxHight}};
	for (int i = 0; i < maxWidth; i++) {
		for (int j = 0; j < maxHight; j++) {
//			map2d->set(i, j, )
		}
	}


	boardMap = std::move(map2d);

	std::cout << "W: " << std::to_string(maxWidth) << " H: "
			<< std::to_string(maxHight) << "\n";

	return true;
}

