#include <SFML/Graphics.hpp>
#include "Animation.h"
#pragma once
class Furnace
{
private:
	sf::Sprite sprite;
	sf::Vector2f position;
	Animation furnaceAnimation;
	float luminosityRadius;

public:
	Furnace(sf::Vector2f position , sf::Texture &texture , float luminosityRadius);
	void update(float dt);
	void draw(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	sf::Sprite getSprite();
	float getLuminosityRadius();
};

