/*
 * Game.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: li
 */

#include <iostream>

#include "Game.h"

Game::Game(LevelProvider & levelProvider) :
		levelProvider { levelProvider } {
}

bool Game::play(unsigned levelNumber, Direction direction) {
	Level & level = levelProvider.getLevel(levelNumber);

	movePlayer(level, direction);


	return false;
}

void Game::movePlayer(Level & level, Direction direction) {
	Coords player{level.getPlayerPos()};
	Coords size{level.getSize()};
	bool isMoved = false;

	switch (direction) {
	case Direction::UP:
		if (player.getY() > 0) {
			player.setY(player.getY() - 1);
			isMoved = true;
		}
		break;
	case Direction::DOWN:
		if (player.getY() < size.getY() - 1) {
			player.setY(player.getY() + 1);
			isMoved = true;
		}
		break;
	case Direction::LEFT:
		if (player.getX() > 0) {
			player.setX(player.getX() - 1);
			isMoved = true;
		}
		break;
	case Direction::RIGHT:
		if (player.getX() < size.getX() - 1) {
			player.setX(player.getX() + 1);
			isMoved = true;
		}
		break;
	default:
		break;
	}

	if (!isMoved) {
		return;
	}

	level.setItem(player, Item::PLAYER);
	level.setItem(level.getPlayerPos(), Item::BLANK);
	level.setPlayerPos(player);

//	Item itemOnNewPos{level.getItem(player)};
//	switch (itemOnNewPos) {
//	case Item::WALL:
//
//	}
}
