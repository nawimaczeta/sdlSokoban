/*
 * Drawer.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: li
 */

#include <stdexcept>

#include "Drawer.h"

const std::string Drawer::EMPTY_TEXTURE_FILE_NAME {"textures/empty.png"};

Drawer::Drawer(SDL2pp::Window & window, LevelProvider & levelProvider) :
		sdlWindow { window },
		sdlRenderer { window, -1, SDL_RENDERER_ACCELERATED },
		emptyTexture { sdlRenderer, EMPTY_TEXTURE_FILE_NAME },
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
	Level & level = levelProvider.getLevel(levelNumber);
	Coords mapSize = level.getSize();

	unsigned screenX = static_cast<unsigned>(sdlRenderer.GetOutputWidth());
	unsigned screenY = static_cast<unsigned>(sdlRenderer.GetOutputHeight());

	unsigned mapSizePixelsX = mapSize.getX() * TEXTURE_SIZE;
	unsigned mapSizePixelsY = mapSize.getY() * TEXTURE_SIZE;
	if (mapSizePixelsX > screenX ||
			mapSizePixelsY > screenY) {
		throw std::runtime_error("Map size is too big " +
				std::to_string(mapSizePixelsX) + " " + std::to_string(mapSizePixelsY));
	}

	// get offsets. We want to place the map in the center
	unsigned xOffset = (screenX - mapSizePixelsX) / 2;
	unsigned yOffset = (screenY - mapSizePixelsY) / 2;

	sdlRenderer.SetDrawColor(0, 0, 0, 0xff).Clear();

	for (unsigned i = 0; i < mapSize.getX(); i++) {
		for (unsigned j = 0; j < mapSize.getY(); j++) {
			Item item = level.getItem(i, j);
			SDL2pp::Texture & texture = getTexture(item);

			sdlRenderer.Copy(
					texture,
					SDL2pp::NullOpt,
					SDL2pp::Rect{
				static_cast<int>(i * TEXTURE_SIZE + xOffset),
				static_cast<int>(j * TEXTURE_SIZE + yOffset),
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
		return emptyTexture;
	}
}
