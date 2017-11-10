/*
 * Level.h
 *
 *  Created on: Nov 10, 2017
 *      Author: li
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include <vector>
#include <memory>
#include <string>

#include "Matrix2D.h"

enum class Item {BLANK, PLAYER, OBSTACLE, TARGET, WALL, PLAYER_ON_TARGET, OBSTACLE_ON_TARGET};
enum class Direction {NONE, UP, DOWN, LEFT, RIGHT};

class Level {
public:
	Level(std::string & content);
	bool loadFromString(std::string & map);
	bool play(Direction direction);

private:
	std::unique_ptr<Matrix2D<Item>> boardMap;
};



#endif /* LEVEL_H_ */
