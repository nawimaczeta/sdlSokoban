/*
 * Application.cpp
 *
 *  Created on: Oct 9, 2017
 *      Author: li
 */

#include <iostream>
#include <string>

#include "Application.h"
#include "Game.h"

const std::string Application::WINDOW_TITLE = "Game";
const std::string Application::FILENAME_BLANK = "textures/blank.png";
const std::string Application::FILENAME_PLAYER = "textures/player.png";
const std::string Application::FILENAME_OBSTACLE = "textures/obstacle.png";
const std::string Application::FILENAME_WALL = "textures/wall.png";
const std::string Application::FILENAME_TARGET = "textures/target.png";
const std::string Application::FILENAME_OBSTACLE_ON_TARGET = "textures/obstacle_on_target.png";

const std::string Application::LEVEL_1{
	"####\n"
	"# t#\n"
	"#  ###\n"
	"#Op  #\n"
	"#  o #\n"
	"#  ###\n"
	"####"};

Application::Application() :
		sdl(SDL_INIT_VIDEO),
		sdlWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0),
		game {levelProvider},
		drawer{sdlWindow, levelProvider},
		currentLevel { 0 }
{
	drawer.loadTexture(Item::BLANK, FILENAME_BLANK);
	drawer.loadTexture(Item::OBSTACLE, FILENAME_OBSTACLE);
	drawer.loadTexture(Item::OBSTACLE_ON_TARGET, FILENAME_OBSTACLE_ON_TARGET);
	drawer.loadTexture(Item::PLAYER, FILENAME_PLAYER);
	drawer.loadTexture(Item::PLAYER_ON_TARGET, FILENAME_PLAYER);
	drawer.loadTexture(Item::TARGET, FILENAME_TARGET);
	drawer.loadTexture(Item::WALL, FILENAME_WALL);

	levelProvider.loadLevel(LEVEL_1);
}

Application::~Application() {

}

int Application::run() {

	SDL_Event sdlEvent;

	while (true) {
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:
				return 0;
				break;
			case SDL_KEYDOWN:
				std::cout << "Key pressed: " << std::to_string(sdlEvent.key.keysym.sym) << "\n";
				break;
			}
		}
		drawer.drawLevel(currentLevel);
		SDL_Delay(1000 / 60);	// 60 FPS
	}

	return 1;
}
