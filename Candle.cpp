#include "Candle.h"

Candle::Candle(float luminosityRadius, float warmthRadius, sf::Vector2f position, sf::Texture &texture) : Item(position,texture), candleAnimation(texture, {3}, 0.1, sf::Vector2u(3, 1)) {
	this->luminosityRadius = luminosityRadius;
	this->warmthRadius = warmthRadius;
	
	getSprite().setTextureRect(candleAnimation.getXyRect());
	getSprite().setOrigin(sf::Vector2f(candleAnimation.getXyRect().size.x/2, candleAnimation.getXyRect().size.y / 2));
}
float Candle::getLuminosityRadius() {
	return luminosityRadius;
}
float Candle::getWarmthRadius() {
	return warmthRadius;
}
void Candle::update(float dt, sf::Vector2f playerPosition) {
	Item::update(dt,playerPosition);
	candleAnimation.update(0, dt);
	getSprite().setTextureRect(candleAnimation.getXyRect());
}