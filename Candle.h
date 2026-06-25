#pragma once
#include "Animation.h"
#include "Item.h"
class Candle :
	public Item
{
private:
	float luminosityRadius;
	float warmthRadius;
	Animation candleAnimation;
public:

	Candle(float luminosityRadius, float warmthRadius,sf::Vector2f position, sf::Texture &texture);
	float getLuminosityRadius();
	float getWarmthRadius();

	void update(float dt, sf::Vector2f playerPosition) override;
};

