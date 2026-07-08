#pragma once

#include <SFML//Graphics.hpp>
class Item
{
private:
	float equipNoiseRadius = 100;    // hardcoded for now   
	float unequipNoiseRadius = 100; // will be more and differently strucured for stone throw

	sf::Vector2f position;
	bool equipped = false;
	sf::Sprite itemSprite;
	bool noiseActive = false;
	float currentNoiseRadius=0;

public:

	// MUST add a virtual destructor for safe inheritance
	virtual ~Item() = default;
	
	Item(sf::Vector2f position, sf::Texture& texture);
	void setPosition(sf::Vector2f position);
	void setEquipped();
	sf::Vector2f getPosition();
	sf::Sprite& getSprite();
	void unequip();                      //to be overridden in stone class
	void draw(sf::RenderWindow& window);
	bool getEquipped();

	void setNoiseActive();    
	void setNoiseInactive();
	float getCurrentNoiseRadius();
	bool getNoiseActive();

	virtual void update(float dt, sf::Vector2f playerPosition);
	
};

