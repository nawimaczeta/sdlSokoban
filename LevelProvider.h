/*
 * LevelProvider.h
 *
 *  Created on: Nov 11, 2017
 *      Author: li
 */

#ifndef LEVELPROVIDER_H_
#define LEVELPROVIDER_H_

#include "Level.h"

class LevelProvider {
public:
	void loadLevel(const std::string & content);
	Item getLevelItem(const unsigned index, const unsigned x, const unsigned y);
	Coords getLevelSize(const unsigned index);
private:
	std::vector<std::unique_ptr<Level>> levels;
};



#endif /* LEVELPROVIDER_H_ */
