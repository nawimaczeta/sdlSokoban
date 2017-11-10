/*
 * Game.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: li
 */

#include <iostream>

#include "Game.h"

std::string level1{	"####\n"
					"# t#\n"
					"#  ###\n"
					"#Op  #\n"
					"#  o #\n"
					"#  ###\n"
					"####"};

Game::Game() : currentLevel{0}
{
	Level l{level1};
}

unsigned Game::loadLevel(std::string content) {
	//std::unique_ptr<Level> newLevel = new Level{level1};
	return 1;
}
