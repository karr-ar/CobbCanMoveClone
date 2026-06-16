#pragma once
#include<SFML/Graphics.hpp>
class Entity
{
private:
	sf::Vector2f velocity;
	sf::Vector2f position;
	sf::Vector2f direction;
public:
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();

	void setPosition(sf::Vector2f position);
	void setPosition(float px, float py);
	sf::Vector2f getPosition();

	void setDirection(sf::Vector2f direction);
	void setDirection(float dx, float dy);
	sf::Vector2f getDirection();

	Entity(sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f direction);
};

