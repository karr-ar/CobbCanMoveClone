#include "Candle.h"

Candle::Candle(float luminosityRadius, sf::Vector2f position, sf::Texture &texture, float equipNoiseRadius, float unequipNoiseRadius) : Item(luminosityRadius,position,texture,equipNoiseRadius,unequipNoiseRadius)
, candleAnimation(texture, {3}, 0.1, sf::Vector2u(3, 1)) {
	
	getSprite().setTextureRect(candleAnimation.getXyRect());
	getSprite().setOrigin(sf::Vector2f(candleAnimation.getXyRect().size.x/2, candleAnimation.getXyRect().size.y / 2));
}
void Candle::update(float dt, sf::Vector2f playerPosition) {
	Item::update(dt,playerPosition);
	candleAnimation.update(0, dt);
	getSprite().setTextureRect(candleAnimation.getXyRect());
}