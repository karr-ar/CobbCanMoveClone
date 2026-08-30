#include "Breaker.h"
Breaker::Breaker(sf::Texture& texture, sf::Vector2f position) : sprite(texture), breakerAnimation(texture,{2,1}, 0.5, sf::Vector2u(2,2)) {
	sprite.setTextureRect(breakerAnimation.getXyRect());
	sprite.setOrigin(sf::Vector2f(breakerAnimation.getXyRect().size.x / 2, breakerAnimation.getXyRect().size.y / 2));
	sprite.setPosition(position);
}void Breaker::flipBreaker() {
	flipped = true;
	breakerAnimation.update(1, 0);  // switch to row 1, zero dt so no frame advance
	sprite.setTextureRect(breakerAnimation.getXyRect());
}
void Breaker::update(float dt) {
	if (!flipped) {
		breakerAnimation.update(0, dt);
	}
	else {
		breakerAnimation.update(1, dt);
	}
	sprite.setTextureRect(breakerAnimation.getXyRect());
}
void Breaker::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
sf::Sprite Breaker::getBreakerSprite() {
	return sprite;
}
bool Breaker::getFlipped() {
	return flipped;
}
void Breaker::setPlayerNearBreaker(bool val) {
	playerNearBreaker = val;
}
void Breaker::setHighlight(bool on) {
	sprite.setColor(on ? sf::Color(100, 255, 220, 255) : sf::Color::White);
}
bool Breaker::getPlayerNearBreaker() {
	return playerNearBreaker;
}