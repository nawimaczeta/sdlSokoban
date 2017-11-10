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

Application::Application() :
	sdl(SDL_INIT_VIDEO),
	window(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0),
	renderer(window, -1, SDL_RENDERER_ACCELERATED)
{}

Application::~Application() {

}

int Application::run() {
	Game game;


	SDL_Event sdlEvent;
	int x = window.GetWidth();
	int y = window.GetHeight();

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

		renderer.SetDrawColor(0x00, 0x00, 0x00, 0xff);
		renderer.Clear();
		renderer.SetDrawColor(0x00, 0x80, 0x80, 0xff);
		renderer.FillRect(10, 10, x - 10, y - 10);
		renderer.Present();


		SDL_Delay(1000 / 60);	// 60 FPS
	}

	return 1;
}
