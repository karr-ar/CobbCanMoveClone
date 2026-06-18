#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
class Map
{
public:
	Map(std::string textPath, sf::Texture &wallTexture, sf::Texture &tileTexture);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPlayerInitialPosition();
	std::vector <sf::Vector2f> getWalls();
	sf::Sprite getWallSprite();
	// update function and a boolean vector which will tell whether to draw a certain area or not based on how far the user is to it
private:
	std::vector <sf::Vector2f> walls;
	std::vector <sf::Vector2f> tiles;
	sf::Vector2f playerInitialPos;

	sf::Sprite wallSprite;
	sf::Sprite tileSprite;
};

