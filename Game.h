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

#include "LevelProvider.h"

class Game {
public:
	Game(LevelProvider & levelProvider);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool play(unsigned levelNumber, Direction direction);
	void movePlayer(Level & level, Direction direction);


private:
	LevelProvider & levelProvider;
};



#endif /* GAME_H_ */
