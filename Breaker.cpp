#include "Breaker.h"
Breaker::Breaker(sf::Texture& texture, sf::Vector2f position) : sprite(texture), breakerAnimation(texture,{2,1}, 0.5, sf::Vector2u(2,2)) {
	sprite.setTextureRect(breakerAnimation.getXyRect());
	sprite.setOrigin(sf::Vector2f(breakerAnimation.getXyRect().size.x / 2, breakerAnimation.getXyRect().size.y / 2));
	sprite.setPosition(position);
}
void Breaker::flipBreaker() {
	flipped = true;
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