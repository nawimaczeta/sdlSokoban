/*
 * Game.h
 *
 *  Created on: Nov 9, 2017
 *      Author: li
 */

#ifndef GAME_H_
#define GAME_H_

#include <string>
#include <vector>
#include <memory>

#include "Level.h"

class Game {
public:
	Game();
	unsigned loadLevel(std::string content);

private:
	unsigned currentLevel;
	std::vector<std::unique_ptr<Level>> levels;
};



#endif /* GAME_H_ */
