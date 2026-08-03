#include <SFML/Graphics.hpp>
#pragma once
class Smell
{
	sf::Vector2f position;
	float score;
	bool toDelete = false;
public:
	Smell(sf::Vector2f position, float score);
	void update(float dt);
	sf::Vector2f getPosition();
	float getScore();
	bool getToDelete();
};

