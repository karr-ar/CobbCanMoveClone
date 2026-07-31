#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Escalator.h"
class Map
{
public:
	Map(std::string textPath, sf::Texture &wallTexture, sf::Texture &tileTexture, sf::Texture& wall2Texture, sf::Texture &grassTexture , sf::Texture &escalatorTexture);
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPlayerInitialPosition();
	std::vector <sf::Vector2f> getWalls();
	sf::Sprite getWallSprite();
	sf::Vector2f getCobbInitialPosition();
	std::vector <sf::Vector2f> getCobbsAllowablePositions();
	std::vector <sf::Vector2f> getWalls2();
	std::vector <Escalator> getEscalator();
	// update function and a boolean vector which will tell whether to draw a certain area or not based on how far the user is to it

	sf::Vector2f getFurnacePos();

private:
	std::vector <sf::Vector2f> walls;
	std::vector <sf::Vector2f> tiles;
	std::vector <sf::Vector2f> wall2;
	std::vector <sf::Vector2f> grass;
	std::vector <sf::Vector2f> secondTileType;
	std::vector <Escalator> escalator;
	sf::Vector2f playerInitialPos;
	sf::Vector2f cobbInitialPos;
	std::vector <sf::Vector2f> cobbsAllowablePositions;

	sf::Vector2f furnacePos;


	sf::Sprite wallSprite;
	sf::Sprite tileSprite;
	sf::Sprite wall2Sprite;
	sf::Sprite grassSprite;
};

