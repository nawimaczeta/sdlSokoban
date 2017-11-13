/*
 * Level.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: li
 */

#include <iostream>
#include <sstream>
#include <map>
#include <stdexcept>

#include "Level.h"

Level::Level(const std::string & content) :
		boardMap { nullptr },
		width { 0 },
		height { 0 },
		obstaclesNumber { 0 },
		targetsNumber { 0 } {
	loadFromString(content);
}

void Level::loadFromString(const std::string & map) {
	char delimiter = '\n';
	std::stringstream ss { map };
	std::vector<std::string> lines;

	height = 0;
	width = 0;

	std::cout << map << "\n";

	for (std::string line; std::getline(ss, line, delimiter);) {
		lines.push_back(line);
		if (line.size() > width) {
			width = line.size();
		}
	}

	// fill lines with ' '. All of them should be equal maxWidth
	for (auto & l : lines) {
		int missed;
		missed = width - l.size();

		// generate string with 'missed' number of spaces
		std::string s { "" };
		for (int i = 0; i < missed; i++) {
			s += SYMBOL_BLANK;
		}
		l += s;
	}

	height = lines.size();


	std::cout << "W: " << std::to_string(width) << " H: "
			<< std::to_string(height) << "\n";

	bool isPlayerFound = false;
	std::unique_ptr<Matrix2D<Item>> map2d { new Matrix2D<Item> { width, height } };
	for (unsigned i = 0; i < width; i++) {
		for (unsigned j = 0; j < height; j++) {
			char c = lines[j].at(i);

			// look for player
			if (c == SYMBOL_PLAYER || c == SYMBOL_PLAYER_ON_TARGET) {
				if (!isPlayerFound) {
					player.set(i, j);
					isPlayerFound = true;
				} else {
					throw std::range_error("Second player detected\n");
				}
			}
			// count targets and obstacles
			if (c == SYMBOL_OBSTACLE || c == SYMBOL_OBSTACLE_ON_TARGET) {
				obstaclesNumber++;
			}
			if (c == SYMBOL_TARGET || c == SYMBOL_OBSTACLE_ON_TARGET
					|| c == SYMBOL_PLAYER_ON_TARGET) {
				targetsNumber++;
			}

			Item item = symbol2Item(c);
			map2d->set(i, j, item);
		}
	}

	if (!isPlayerFound) {
		throw std::range_error { "Player not found\n" };
	}
	if (obstaclesNumber != targetsNumber) {
		throw std::range_error { "Number of obstacles != number of targets\n" };
	}
	if (targetsNumber == 0) {
		throw std::range_error { "No targets on map\n" };
	}

	std::cout <<
			"Player: " <<
			std::to_string(player.getX()) <<
			" " <<
			std::to_string(player.getY()) <<
			"\n";

	boardMap = std::move(map2d);
}

Coords Level::getSize() const {
	Coords c { width, height };
	return c;
}

Item Level::getItem(unsigned x, unsigned y) const {
	if (x > width || y > height) {
		throw std::out_of_range{"Coords out of range\n"};
	}

	return boardMap->get(x, y);
}

Item Level::getItem(Coords coords) const {
	return getItem(coords.getX(), coords.getY());
}

Coords Level::getPlayerPos() const {
	return player;
}

void Level::setItem(Coords pos, Item item) {
	boardMap->set(pos.getX(), pos.getY(), item);
}

void Level::setPlayerPos(Coords pos) {
	if (pos.getX() > width || pos.getY() > height) {
		throw std::out_of_range("Player pos");
	}

	player = pos;
}

Item Level::symbol2Item(char symbol) {
	Item item;

	switch (symbol) {
	case SYMBOL_BLANK:
		item = Item::BLANK;
		break;
	case SYMBOL_WALL:
		item = Item::WALL;
		break;
	case SYMBOL_PLAYER:
		item = Item::PLAYER;
		break;
	case SYMBOL_OBSTACLE:
		item = Item::OBSTACLE;
		break;
	case SYMBOL_TARGET:
		item = Item::TARGET;
		break;
	case SYMBOL_PLAYER_ON_TARGET:
		item = Item::PLAYER_ON_TARGET;
		break;
	case SYMBOL_OBSTACLE_ON_TARGET:
		item = Item::OBSTACLE_ON_TARGET;
		break;
	default:
		// error
		throw std::range_error { "Invalid symbol " + std::to_string(symbol) };
	}

	return item;
}
