/*
 * Application.h
 *
 *  Created on: Oct 9, 2017
 *      Author: li
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>

#include "Game.h"
#include "Drawer.h"
#include "LevelProvider.h"

class Application {
public:
	Application();
	~Application();
	int run();

private:
	static const std::string WINDOW_TITLE;
	static const std::string FILENAME_BLANK;
	static const std::string FILENAME_PLAYER;
	static const std::string FILENAME_OBSTACLE;
	static const std::string FILENAME_WALL;
	static const std::string FILENAME_TARGET;
	static const std::string FILENAME_OBSTACLE_ON_TARGET;

	static const std::string LEVEL_1;
	static const std::string LEVEL_2;

	SDL2pp::SDL sdl;
	SDL2pp::Window sdlWindow;

	LevelProvider levelProvider;
	Game game;
	Drawer drawer;
	unsigned currentLevel;

	bool processInputs(Direction & direction);
};



#endif /* APPLICATION_H_ */
