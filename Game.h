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
	Game(Game &&) = delete;
	Game& operator=(Game&&) = delete;

	void play(unsigned levelNumber, Direction direction);
private:
	LevelProvider & levelProvider;

	Coords moveCoords(Level & level, Coords coords, Direction direction);
	bool checkMovePlayer(Level & level, Direction direction);
	bool checkObstacleMove(Level & level, Coords coords, Direction direction);
	void movePlayer(Level & level, Direction direction);
	bool moveObstacle(Level & level, Coords coords, Direction direction);
	bool checkIfWin(Level & level);
};



#endif /* GAME_H_ */
