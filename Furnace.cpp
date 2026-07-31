#include "Furnace.h"

Furnace::Furnace(sf::Vector2f position, sf::Texture& texture, float luminosityRadius) : sprite(texture) , furnaceAnimation(texture , {4},0.2, sf::Vector2u(4,1)) {
	this->position = position;
	//i wont set its origin to center cuz the image is bigger than its environment and finding its middle point will require unnecessary work
	// also as rest of the sprites are centered position given for this one must be its actual position + size of surrounding sprites/2 
	sprite.setTextureRect(furnaceAnimation.getXyRect());
	sprite.setPosition(position);
	this->luminosityRadius = luminosityRadius;
}
void Furnace::update(float dt) {
	furnaceAnimation.update(0, dt);
	sprite.setTextureRect(furnaceAnimation.getXyRect());
}
void Furnace::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
sf::Vector2f Furnace::getPosition() {
	return position;
}
sf::Sprite Furnace::getSprite() {
	return sprite;
}
float Furnace::getLuminosityRadius() {
	return luminosityRadius;
}