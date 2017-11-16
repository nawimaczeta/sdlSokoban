/*
 * LevelProvider.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: li
 */

#include <stdexcept>

#include "LevelProvider.h"

LevelContainer::LevelContainer(std::unique_ptr<Level> level) {
	levels.push_back(std::move(level));
}

Level & LevelContainer::getLevel() {
	Level & level = *levels.at(levels.size() - 1);
	return level;
}

void LevelContainer::addToUndoHistory(std::unique_ptr<Level> level) {
	levels.push_back(std::move(level));
}

/*! \brief Reset the level
 *
 *  The function removes all user's moves and leave only the first original
 *
 */
void LevelContainer::restartLevel() {
	std::unique_ptr<Level> firstLevelCopy{std::move(levels.at(0))};
	levels.clear();
	levels.push_back(std::move(firstLevelCopy));
}

/*! \brief Undo last user move
 *
 *  The function removes last user move
 *
 */
void LevelContainer::undo() {
	if (levels.size() > 1) {
		levels.erase(levels.end() - 1);
	}
}

void LevelProvider::loadLevel(const std::string & content) {
	std::unique_ptr<Level> lp{ new Level(content) };
	std::unique_ptr<LevelContainer> lc{new LevelContainer(std::move(lp))};
	levels.push_back(std::move(lc));
}

Level & LevelProvider::getLevel(unsigned index) const {
	LevelContainer & lc =  *levels.at(index);
	return lc.getLevel();
}

unsigned LevelProvider::getNumberOfLevels() const {
	return levels.size();
}

void LevelProvider::addToUndoHistory(unsigned index, std::unique_ptr<Level> level) {
	LevelContainer & lc = *levels.at(index);
	lc.addToUndoHistory(std::move(level));
}

void LevelProvider::restartLevel(unsigned index) {
	levels.at(index)->restartLevel();
}

void LevelProvider::undo(unsigned index) {
	levels.at(index)->undo();
}

