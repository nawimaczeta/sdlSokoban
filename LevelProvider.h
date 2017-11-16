/*
 * LevelProvider.h
 *
 *  Created on: Nov 11, 2017
 *      Author: li
 */

#ifndef LEVELPROVIDER_H_
#define LEVELPROVIDER_H_

#include <vector>
#include <memory>

#include "Level.h"

// contains undo history and properties related to each level
class LevelContainer {
public:
	LevelContainer(std::unique_ptr<Level> level);
	Level & getLevel();		// return the last state of the level
	void addToUndoHistory(std::unique_ptr<Level> level);
	void restartLevel();
	void undo();
private:
	// level at index 0 is always original
	std::vector<std::unique_ptr<Level>> levels;
};

class LevelProvider {
public:
	void loadLevel(const std::string & content);
	unsigned getNumberOfLevels() const;
	Level & getLevel(unsigned index) const;
	void addToUndoHistory(unsigned index, std::unique_ptr<Level> level);
	void restartLevel(unsigned index);
	void undo(unsigned index);
private:
	std::vector<std::unique_ptr<LevelContainer>> levels;
};



#endif /* LEVELPROVIDER_H_ */
