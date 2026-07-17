#include "Escalator.h"
Escalator::Escalator(sf::Texture &texture, sf::Vector2f position) :sprite(texture) , escalatorAnimation (texture,{3} , 0.3 , sf::Vector2u(3,1)) {
	this->position = position;
	sprite.setOrigin(sf::Vector2f(escalatorAnimation.getXyRect().size.x/2, escalatorAnimation.getXyRect().size.y / 2));
	sprite.setTextureRect(escalatorAnimation.getXyRect());
	sprite.setPosition(position);
}
void Escalator::update(float dt) {
	escalatorAnimation.update(0, dt);
	sprite.setTextureRect(escalatorAnimation.getXyRect());
}
void Escalator::draw(sf::RenderWindow& window) {
	sf::RectangleShape rect(sf::Vector2f(sprite.getTextureRect().size));
	rect.setOrigin(sf::Vector2f(escalatorAnimation.getXyRect().size.x / 2, escalatorAnimation.getXyRect().size.y / 2));
	rect.setPosition(sprite.getPosition());
	rect.setFillColor(sf::Color(15, 12, 10));
	window.draw(rect);
	window.draw(sprite);
}
sf::Sprite Escalator::getSprite() {
	return sprite;
}