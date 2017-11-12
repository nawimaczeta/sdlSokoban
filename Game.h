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
	Game(const LevelProvider & levelProvider);



private:
	const LevelProvider & levelProvider;
};



#endif /* GAME_H_ */
