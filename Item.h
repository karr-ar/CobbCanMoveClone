#pragma once

#include <SFML//Graphics.hpp>
class Item
{
private:
	sf::Vector2f position;
	bool equipped = false;
	sf::Sprite itemSprite;
public:

	// MUST add a virtual destructor for safe inheritance
	virtual ~Item() = default;
	
	Item(sf::Vector2f position, sf::Texture& texture);
	void setPosition(sf::Vector2f position);
	void setEquipped();
	sf::Vector2f getPosition();
	sf::Sprite& getSprite();
	void unequip();
	void draw(sf::RenderWindow& window);
	bool getEquipped();

	virtual void update(float dt, sf::Vector2f playerPosition);
	
};

