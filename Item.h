#pragma once

#include <SFML//Graphics.hpp>
class Item
{
private:
	float equipNoiseRadius ;       
	float unequipNoiseRadius ; // will be more and differently strucured for stone throw

	sf::Vector2f position;
	bool equipped = false;
	sf::Sprite itemSprite;
	bool noiseActive = false;
	float currentNoiseRadius=0;
	float luminosityRadius;

	bool isOnEscalator = false;
	float escalatorSpeed;

public:

	// MUST add a virtual destructor for safe inheritance
	virtual ~Item() = default;
	
	Item(float luminosityRadius,sf::Vector2f position, sf::Texture& texture, float equipNoiseRadius, float unequipNoiseRadius , float escalatorSpeed);
	void setPosition(sf::Vector2f position);
	void setEquipped();
	sf::Vector2f getPosition();
	sf::Sprite& getSprite();
	void draw(sf::RenderWindow& window);
	bool getEquipped();
	void setUnEquipped();

	float getLuminosityRadius();

	void setNoiseActive();    
	void setNoiseInactive();
	float getCurrentNoiseRadius();
	bool getNoiseActive();
	void produceEquipNoise();
	void produceUnEquipNoise();

	void setIsOnEscalatorToTrue();

	virtual void update(float dt, sf::Vector2f playerPosition);
	virtual void unequip();                      //overridden in stone class
	
};

