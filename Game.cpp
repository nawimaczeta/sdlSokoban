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
	bool movePlayer = true;

	Level & level = levelProvider.getLevel(levelNumber);
	Coords playerPos = level.getPlayerPos();
	Coords newPlayerPos = moveCoords(level, playerPos, direction);

	if (playerPos == newPlayerPos) {
		// player is not moved
		return false;
	}

	// check collisions
	Item itemOnNewPos = level.getItem(newPlayerPos);
	Item newPlayerItemType = Item::PLAYER;		// PLAYER or PLAYER_ON_TARGET
	Item playerReplacement = Item::BLANK;		// BLANK or TARGET
	//Item player
	bool obstacleMoved = false;
	switch (itemOnNewPos) {
	case Item::WALL:
		movePlayer = false;
		break;
	case Item::OBSTACLE:
		obstacleMoved = moveObstacle(level, newPlayerPos, direction);
		if (obstacleMoved) {
			movePlayer = true;
		} else {
			movePlayer = false;
		}
		break;
	case Item::OBSTACLE_ON_TARGET:
		obstacleMoved = moveObstacle(level, newPlayerPos, direction);
		if (obstacleMoved) {
			movePlayer = true;
			newPlayerItemType = Item::PLAYER_ON_TARGET;
		} else {
			movePlayer = false;
		}
		break;
	case Item::TARGET:
		newPlayerItemType = Item::PLAYER_ON_TARGET;
		break;
	default:
		movePlayer = true;
	}

	if (level.getItem(level.getPlayerPos()) == Item::PLAYER_ON_TARGET) {
		playerReplacement = Item::TARGET;
	}

	if (movePlayer) {
		level.setItem(newPlayerPos, newPlayerItemType);

		level.setItem(level.getPlayerPos(), playerReplacement);
		level.setPlayerPos(newPlayerPos);
	}
	return false;
}

Coords Game::moveCoords(Level & level, Coords coords, Direction direction) {
	Coords size{level.getSize()};

	switch (direction) {
	case Direction::UP:
		if (coords.getY() > 0) {
			coords.setY(coords.getY() - 1);
		}
		break;
	case Direction::DOWN:
		if (coords.getY() < size.getY() - 1) {
			coords.setY(coords.getY() + 1);
		}
		break;
	case Direction::LEFT:
		if (coords.getX() > 0) {
			coords.setX(coords.getX() - 1);
		}
		break;
	case Direction::RIGHT:
		if (coords.getX() < size.getX() - 1) {
			coords.setX(coords.getX() + 1);
		}
		break;
	default:
		break;
	}

	return coords;
}

bool Game::moveObstacle(Level & level, Coords coords, Direction direction) {
	bool obstacleMove = false;
	Coords newObstaclePos = moveCoords(level, coords, direction);

	if (newObstaclePos == coords) {
		return false;
	}

	Item obstacle2Draw = Item::OBSTACLE;
	if (newObstaclePos != coords) {
		Item newObstalcePosItem = level.getItem(newObstaclePos);
		switch (newObstalcePosItem) {
		case Item::WALL:
		case Item::OBSTACLE:
		case Item::OBSTACLE_ON_TARGET:
			obstacleMove = false;
			break;
		case Item::TARGET:
			obstacle2Draw = Item::OBSTACLE_ON_TARGET;
			obstacleMove = true;
			break;
		default:
			obstacleMove = true;
		}

		if (obstacleMove) {
			level.setItem(newObstaclePos, obstacle2Draw);
		}
	}

	return obstacleMove;
}
