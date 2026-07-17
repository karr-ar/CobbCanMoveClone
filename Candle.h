#pragma once
#include "Animation.h"
#include "Item.h"
class Candle :
	public Item
{
private:
	Animation candleAnimation;
public:

	Candle(float luminosityRadius,sf::Vector2f position, sf::Texture &texture, float equipNoiseRadius, float unequipNoiseRadius , float escalatorSpeed);

	void update(float dt, sf::Vector2f playerPosition) override;
};

