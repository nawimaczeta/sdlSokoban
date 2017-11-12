/*
 * Drawer.h
 *
 *  Created on: Nov 11, 2017
 *      Author: li
 */

#ifndef DRAWER_H_
#define DRAWER_H_

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2pp/SDL.hh>
#include <SDL2pp/Window.hh>
#include <SDL2pp/Renderer.hh>
#include <SDL2pp/Texture.hh>

#include "LevelProvider.h"


class Drawer {
public:
	Drawer(SDL2pp::Window & window, LevelProvider & levelProvider);

	Drawer(const Drawer&) = delete;
	Drawer& operator=(const Drawer&) = delete;

	void loadTexture(const Item item, const std::string & textureFileName);
	void drawLevel(const unsigned levelNumber);

private:
	static const std::string BLANK_TEXTURE_FILE_NAME;

	SDL2pp::Window &sdlWindow;
	SDL2pp::Renderer sdlRenderer;
	std::map<Item, SDL2pp::Texture> textureMap;
	SDL2pp::Texture blankTexture;

	LevelProvider & levelProvider;

	SDL2pp::Texture & getTexture(const Item item);
};



#endif /* DRAWER_H_ */
