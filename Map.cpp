#include "Map.h"
Map::Map(std::string textPath, sf::Texture &wallTexture, sf::Texture &tileTexture) : wallSprite(wallTexture),tileSprite(tileTexture) {
	std::ifstream file(textPath);
	std::vector<std::string> map;
	std::string line;
	while (std::getline(file, line)) {
		map.push_back(line);
	}
	float sizeX = wallTexture.getSize().x;
	float sizeY = wallTexture.getSize().y;
	for (int i = 0;i < map.size();i++) {
		for (int j = 0;j < map[i].size();j++) {
			if ((map[i][j]) == 'W'){
				walls.push_back(sf::Vector2f(i*sizeX,j*sizeY));
			}
			else if ((map[i][j]) == 'T') {
				tiles.push_back(sf::Vector2f(i * sizeX, j * sizeY));
			}
			else if ((map[i][j]) == 'P') {
				tiles.push_back(sf::Vector2f(i * sizeX, j * sizeY));
				playerInitialPos = sf::Vector2f(i * sizeX, j * sizeY);
			}
		}
	}
	wallSprite.setOrigin(sf::Vector2f(wallTexture.getSize().x, wallTexture.getSize().y));
	tileSprite.setOrigin(sf::Vector2f(tileTexture.getSize().x, tileTexture.getSize().y));
}
sf::Vector2f Map::getPlayerInitialPosition() {
	return playerInitialPos;
}
void Map::draw(sf::RenderWindow &window) {
	for (int i = 0;i < walls.size();i++) {
		wallSprite.setPosition(walls[i]);
		window.draw(wallSprite);
	}
	for (int i = 0;i < tiles.size();i++) {
		tileSprite.setPosition(tiles[i]);
		window.draw(tileSprite);
	}
}
std::vector <sf::Vector2f> Map::getWalls() {
	return walls;
}
sf::Sprite Map::getWallSprite() {
	return wallSprite;
}