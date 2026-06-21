#pragma once
#include<SFML/Graphics.hpp>
class Entity
{
private:
	float speed;
	sf::Vector2f position;
	sf::Vector2f direction;
public:
	void setVelocity(float speed);
	float getVelocity();

	void setPosition(sf::Vector2f position);
	void setPosition(float px, float py);
	sf::Vector2f getPosition();

	void setDirection(sf::Vector2f direction);
	void setDirection(float dx, float dy);
	sf::Vector2f getDirection();

	Entity(float speed, sf::Vector2f position, sf::Vector2f direction);
};

