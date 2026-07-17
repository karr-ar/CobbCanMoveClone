#include "Map.h"
Map::Map(std::string textPath, sf::Texture &wallTexture, sf::Texture &tileTexture , sf::Texture& wall2Texture , sf::Texture &grassTexture, sf::Texture& escalatorTexture) : wallSprite(wallTexture),
																					tileSprite(tileTexture),wall2Sprite(wall2Texture), grassSprite(grassTexture){
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
				wall2.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
			else if (map[i][j] == 'G') {
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
				tiles.push_back(sf::Vector2f(j * sizeX, i * sizeY));
				grass.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
			else if (map[i][j] == 'E') {
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
				escalator.push_back(Escalator(escalatorTexture, sf::Vector2f(j * sizeX, i * sizeY)));
			}
			else if (map[i][j] == 'F') {
			}
			else if (map[i][j] == 'e') {
				cobbsAllowablePositions.push_back(sf::Vector2f(j * sizeX, i * sizeY));
				secondTileType.push_back(sf::Vector2f(j * sizeX, i * sizeY));
			}
		}
	}
	wallSprite.setOrigin(sf::Vector2f(wallTexture.getSize().x/2, wallTexture.getSize().y/2));
	tileSprite.setOrigin(sf::Vector2f(tileTexture.getSize().x/2, tileTexture.getSize().y/2));
	wall2Sprite.setOrigin(sf::Vector2f(wall2Texture.getSize().x / 2, wall2Texture.getSize().y / 2));
	grassSprite.setOrigin(sf::Vector2f(grassTexture.getSize().x / 2, grassTexture.getSize().y / 2));
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
	for (int i = 0;i < wall2.size();i++) {
		wall2Sprite.setPosition(wall2[i]);
		window.draw(wall2Sprite);
	}
	for (int i = 0;i < grass.size();i++) {
		grassSprite.setPosition(grass[i]);
		window.draw(grassSprite);
	}
	for (int i = 0;i < secondTileType.size();i++) {
		wall2Sprite.setPosition(secondTileType[i]);  //for now using wall2Sprite
		window.draw(wall2Sprite);   
	}
}
std::vector <sf::Vector2f> Map::getWalls() {
	return walls ;
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
std::vector <sf::Vector2f> Map::getWalls2() {
	return wall2;
}
std::vector <Escalator> Map::getEscalator() {
	return escalator;
}