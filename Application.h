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
#include <SDL2pp/Renderer.hh>

class Application {
public:
	Application();
	~Application();
	int run();

private:
	static const std::string WINDOW_TITLE;

	SDL2pp::SDL sdl;
	SDL2pp::Window window;
	SDL2pp::Renderer renderer;
};



#endif /* APPLICATION_H_ */
