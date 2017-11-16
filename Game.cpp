/*
 * Game.cpp
 *
 *  Created on: Nov 9, 2017
 *      Author: li
 */

#include "Game.h"

#include <algorithm>

#include "Coords.h"
#include "Level.h"

Game::Game(LevelProvider & levelProvider) :
		levelProvider { levelProvider } {
}

/*! \brief Play the game
 *
 *  The function provides main game logic. It contains moving the player,
 *  moving other objects, collision detection and testing winning conditions
 *
 *  /param levelNumber Currently active level
 *  /param direction Direction to move a player
 *  /return New coordinates if the move is possible. coords otherwise
 */
void Game::play(unsigned levelNumber, Direction direction) {
	Level & level = levelProvider.getLevel(levelNumber);

	if (direction == Direction::NONE) return;

	// play if level is not won
	if (!level.getWon()) {
		if (checkMovePlayer(level, direction)) {
			/*
			 * if it is possible to move a player make a copy of the level.
			 * Modify the new copy only and finally store it in the level provider.
			 * Thus it would be possible to undo this move when an user asks for it.
			 */

			std::unique_ptr<Level> levelCopyPtr{new Level{level}};
			Level & levelCopy = *levelCopyPtr;
			movePlayer(levelCopy, direction);
			levelCopy.setWon(checkIfWin(levelCopy));
			levelProvider.addToUndoHistory(levelNumber, std::move(levelCopyPtr));
		}
	}
}

/*! \brief Check if a player can be moved in the given direction
 *
 *  The function tests if the player can be moved in given direction.
 *  It contains collision check.
 *
 *  /param level Reference to current Level object
 *  /param direction Direction to move a player
 *  /return true if the move is possible (no walls etc.)
 */
bool Game::checkMovePlayer(Level & level, Direction direction) {
	Coords playerPos = level.getPlayerPos();
	Coords newPlayerPos = moveCoords(level, playerPos, direction);
	bool res;

	if (playerPos == newPlayerPos) {
		// player is not moved
		return false;
	}

	// collisions check
	Item itemOnNewPos = level.getItem(newPlayerPos);
	switch (itemOnNewPos) {
	case Item::WALL:
		res = false;
		break;
	case Item::OBSTACLE:
	case Item::OBSTACLE_ON_TARGET:
		res = checkObstacleMove(level, newPlayerPos, direction);
		break;
	default:
		res = true;
	}

	return res;
}

/*! \brief Check if an obstacle can be moved in the given direction
 *
 *  The function tests if the obstacle can be moved in given direction.
 *  It contains collision check.
 *
 *  /param level Reference to current Level object
 *  /param coords Initial coordinates of the obstacle
 *  /param direction Direction to move an obstacle
 *  /return true if the move is possible (no walls etc.)
 */
bool Game::checkObstacleMove(Level & level, Coords coords, Direction direction) {
	Coords newObstaclePos{moveCoords(level, coords, direction)};
	bool res;

	if (newObstaclePos == coords) {
		// obstacle was not moved
		return false;
	}

	// collisions check
	Item itemOnNewPos{level.getItem(newObstaclePos)};
	switch (itemOnNewPos) {
	case Item::WALL:
	case Item::OBSTACLE:
	case Item::OBSTACLE_ON_TARGET:
		res = false;
		break;
	default:
		res = true;
	}

	return res;
}

/*! \brief Move the player in given direction
 *
 *  The function moves the player in given direction, checks for collisions
 *  and moves the obstacle if it is needed.
 *
 *  /param level Reference to current Level object
 *  /param direction Direction to move a player
 */
void Game::movePlayer(Level & level, Direction direction) {
	Coords playerPos = level.getPlayerPos();
	Coords newPlayerPos = moveCoords(level, playerPos, direction);
	bool playerMoveRequest;

	if (playerPos == newPlayerPos) {
		// player is not moved
		return;
	}

	// check collisions
	Item itemOnNewPos = level.getItem(newPlayerPos);
	Item newPlayerItemType = Item::PLAYER;		// PLAYER or PLAYER_ON_TARGET
	Item playerReplacement = Item::BLANK;		// BLANK or TARGET

	bool obstacleMoved = false;
	switch (itemOnNewPos) {
	case Item::WALL:
		playerMoveRequest = false;
		break;
	case Item::OBSTACLE:
		obstacleMoved = moveObstacle(level, newPlayerPos, direction);
		if (obstacleMoved) {
			playerMoveRequest = true;
		} else {
			playerMoveRequest = false;
		}
		break;
	case Item::OBSTACLE_ON_TARGET:
		obstacleMoved = moveObstacle(level, newPlayerPos, direction);
		if (obstacleMoved) {
			playerMoveRequest = true;
			newPlayerItemType = Item::PLAYER_ON_TARGET;
		} else {
			playerMoveRequest = false;
		}
		break;
	case Item::TARGET:
		newPlayerItemType = Item::PLAYER_ON_TARGET;
		playerMoveRequest = true;
		break;
	default:
		playerMoveRequest = true;
	}

	if (level.getItem(level.getPlayerPos()) == Item::PLAYER_ON_TARGET) {
		playerReplacement = Item::TARGET;
	}

	if (playerMoveRequest) {
		// update level map
		level.setItem(newPlayerPos, newPlayerItemType);
		level.setItem(level.getPlayerPos(), playerReplacement);
		level.setPlayerPos(newPlayerPos);
	};
}

/*! \brief Move the given coords in given direction
 *
 *  The function moves the cords in the given direction and checks if
 *  the new coords are still inside level's  borders.
 *
 *  /param level Reference to Level object
 *  /param coords Coordinates to be moved
 *  /param direction Direction to move
 *  /return New coordinates if the move is possible. coords otherwise
 */
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

bool Game::checkIfWin(Level & level) {
	if (level.getCountOfItem(Item::OBSTACLE) == 0) {
		return true;
	} else {
		return false;
	}
}
