/*
 * Drawer.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: li
 */

#include <stdexcept>

#include "Drawer.h"

const std::string Drawer::BLANK_TEXTURE_FILE_NAME {"textures/blank.png"};

Drawer::Drawer(SDL2pp::Window & window, LevelProvider & levelProvider) :
		sdlWindow { window },
		sdlRenderer { window, -1, SDL_RENDERER_ACCELERATED },
		blankTexture { sdlRenderer, BLANK_TEXTURE_FILE_NAME },
		levelProvider { levelProvider } {
}

void Drawer::loadTexture(const Item item, const std::string & textureFileName) {
	SDL2pp::Texture texture{sdlRenderer, textureFileName};

	// check is the item has been in the map yet
	auto it = textureMap.find(item);
	if (it != textureMap.end()) {
		// element exists
		it->second = std::move(texture);
	} else {
		// new entry
		textureMap.insert(std::pair<Item, SDL2pp::Texture>(item, std::move(texture)));
	}
}

void Drawer::drawLevel(const unsigned levelNumber)  {
	const unsigned TEXTURE_SIZE = 80;

	sdlRenderer.SetDrawColor(128, 255, 0x00, 0xff);
	sdlRenderer.Clear();

	Coords mapSize = levelProvider.getLevelSize(levelNumber);
	for (unsigned i = 0; i < mapSize.getX(); i++) {
		for (unsigned j = 0; j < mapSize.getY(); j++) {
			Item item = levelProvider.getLevelItem(levelNumber, i, j);
			SDL2pp::Texture & texture = getTexture(item);

			sdlRenderer.Copy(
					texture,
					SDL2pp::NullOpt,
					SDL2pp::Rect{
				static_cast<int>(i * TEXTURE_SIZE),
				static_cast<int>(j * TEXTURE_SIZE),
				static_cast<int>(TEXTURE_SIZE),
				static_cast<int>(TEXTURE_SIZE)});

		}
	}

	sdlRenderer.Present();

}

SDL2pp::Texture & Drawer::getTexture(const Item item) {
	auto it = textureMap.find(item);
	if (it != textureMap.end()) {
		return it->second;
	} else {
		return blankTexture;
	}
}
