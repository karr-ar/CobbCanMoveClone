#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
class Escalator
{
private:
	sf::Sprite sprite;
	Animation escalatorAnimation;
	sf::Vector2f position;

public :
	Escalator(sf::Texture& texture, sf::Vector2f position);
	void update(float dt);
	void draw(sf::RenderWindow &window);
	sf::Sprite getSprite();
};

