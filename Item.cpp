#include "Item.h"

void Item::setPosition(sf::Vector2f position) {
	this->position = position;
	itemSprite.setPosition(position);
}

sf::Vector2f Item::getPosition() {
	return position;
}

void Item::setEquipped() {
	equipped = true;
	//produce noise 
	setNoiseActive();
	currentNoiseRadius = equipNoiseRadius;
}
void Item::unequip() {
	equipped = false;

	//produce noise 
	setNoiseActive();
	currentNoiseRadius = equipNoiseRadius;
}
Item::Item(float luminosityRadius,sf::Vector2f position, sf::Texture& texture, float equipNoiseRadius, float unequipNoiseRadius) :itemSprite(texture) {
	this->luminosityRadius = luminosityRadius;
	setPosition(position);
	itemSprite.setOrigin(sf::Vector2f(texture.getSize().x/2, texture.getSize().y / 2));

	this->equipNoiseRadius = equipNoiseRadius;
	this->unequipNoiseRadius = unequipNoiseRadius;
}
sf::Sprite& Item::getSprite() {
	return itemSprite;
}
void Item::update(float dt, sf::Vector2f playerPosition) {
	if (equipped) {
		itemSprite.setScale(sf::Vector2f(0.5, 0.5));
		setPosition(playerPosition);
	}
	else {
		itemSprite.setScale(sf::Vector2f(1, 1));
	}
}
void Item::draw(sf::RenderWindow &window) {
	window.draw(itemSprite);
}
bool Item::getEquipped() {
	return equipped;
}
void Item::setNoiseActive() {
	noiseActive = true;
}
void Item::setNoiseInactive() {
	noiseActive = false;
}

float Item::getCurrentNoiseRadius() {
	return currentNoiseRadius;
}
bool Item::getNoiseActive() {
	return noiseActive;
}

float Item::getLuminosityRadius() {
	return luminosityRadius;
}