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
				walls.push_back(sf::Vector2f(j*sizeX,i*sizeY));
			}
			else if ((map[i][j]) == 'T') {
				tiles.push_back(sf::Vector2f(j * sizeX, i * sizeY));
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
			else if ((map[i][j]) == 'P') {
				tiles.push_back(sf::Vector2f(j * sizeX, i * sizeY));
				playerInitialPos = sf::Vector2f(j * sizeX, i * sizeY);
			}
			else if (map[i][j] == 'C') {
				cobbInitialPos = sf::Vector2f(j * sizeX, i * sizeY);
				tiles.push_back(sf::Vector2f(j * sizeX, i * sizeY));
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
			else if (map[i][j] == 'w') {
			}
			else if (map[i][j] == 'G') {
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
			else if (map[i][j] == 'E') {
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
			else if (map[i][j] == 'F') {
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
			else if (map[i][j] == 'e') {
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
		}
	}
	wallSprite.setOrigin(sf::Vector2f(wallTexture.getSize().x/2, wallTexture.getSize().y/2));
	tileSprite.setOrigin(sf::Vector2f(tileTexture.getSize().x/2, tileTexture.getSize().y/2));
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
sf::Vector2f Map::getCobbInitialPosition() {
	return cobbInitialPos;
}
std::vector <sf::Vector2f> Map::getCobbsAllowablePositions() {
	return cobbsAllowablePositions;
}