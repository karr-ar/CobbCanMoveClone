#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
class Breaker
{
private:
	sf::Sprite sprite;
	Animation breakerAnimation;
	bool flipped = false;
public:
	Breaker(sf::Texture &texture , sf::Vector2f position);
	void flipBreaker();
	void update(float dt);
	void draw(sf::RenderWindow &window);
};

