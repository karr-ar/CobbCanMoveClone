#include "Item.h"
#include <iostream>

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
	produceEquipNoise();
}
void Item::unequip() {
	setUnEquipped();

	//produce noise 
	produceUnEquipNoise();
}
Item::Item(float luminosityRadius,sf::Vector2f position, sf::Texture& texture, float equipNoiseRadius, float unequipNoiseRadius, float escalatorSpeed) :itemSprite(texture) {
	this->luminosityRadius = luminosityRadius;
	setPosition(position);

	this->equipNoiseRadius = equipNoiseRadius;
	this->unequipNoiseRadius = unequipNoiseRadius;
	this->escalatorSpeed = escalatorSpeed;
}
sf::Sprite& Item::getSprite() {
	return itemSprite;
}
void Item::update(float dt, sf::Vector2f playerPosition) {
	//delete if its on furnace
	if (isOnFurnace) {
		setDeleteItem();
	}

	if (equipped) {
		itemSprite.setScale(sf::Vector2f(0.5, 0.5));
		setPosition(playerPosition);
	}
	else {
		itemSprite.setScale(sf::Vector2f(1, 1));
		
		if (isOnEscalator ) {
			position.y -= dt * escalatorSpeed;
			isOnEscalator = false;
			setPosition(position);  //this will set sprite position aswell
		}
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
void Item::setUnEquipped() {
	equipped = false;
}
void Item::produceEquipNoise() {
	setNoiseActive();
	currentNoiseRadius = equipNoiseRadius;
}
void Item::produceUnEquipNoise() {
	setNoiseActive();
	currentNoiseRadius = unequipNoiseRadius;
}
void Item::setIsOnEscalatorToTrue() {
	isOnEscalator = true;
}

bool Item::getDeleteItem() {
	return deleteItem;
}
void Item::setDeleteItem() {
	deleteItem = true;
}
void Item::setIsOnFurnace(){
	isOnFurnace = true;
}
void Item::setItemType(std::string type) {
	itemType = type;
}
std::string Item::getItemType() {
	return itemType;
}