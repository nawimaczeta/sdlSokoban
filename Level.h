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
#include <SDL2pp/Renderer.hh>

#include "Matrix2D.h"
#include "Coords.h"

enum class Item {BLANK, PLAYER, OBSTACLE, TARGET, WALL, PLAYER_ON_TARGET, OBSTACLE_ON_TARGET};
enum class Direction {NONE, UP, DOWN, LEFT, RIGHT};

class Level {
public:
	static const unsigned SYMBOL_COUNT = 7;	// number of different items

	Level(const std::string & content);
	void loadFromString(const std::string & map);
	Coords getSize() const;
	Item getItem(unsigned x, unsigned y);
	bool play(Direction direction);

private:
	static const char SYMBOL_BLANK 				= ' ';
	static const char SYMBOL_PLAYER 			= 'p';
	static const char SYMBOL_WALL 				= '#';
	static const char SYMBOL_OBSTACLE 			= 'o';
	static const char SYMBOL_TARGET 			= 't';
	static const char SYMBOL_PLAYER_ON_TARGET 	= 'P';
	static const char SYMBOL_OBSTACLE_ON_TARGET	= 'O';

	std::unique_ptr<Matrix2D<Item>> boardMap;
	unsigned width;
	unsigned height;
	Coords player;
	unsigned obstaclesNumber;
	unsigned targetsNumber;

	Item symbol2Item(char symbol);

};



#endif /* LEVEL_H_ */
