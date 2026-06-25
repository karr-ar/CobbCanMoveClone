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
}
void Item::unequip() {
	equipped = false;
}
Item::Item(sf::Vector2f position, sf::Texture& texture) :itemSprite(texture) {
	setPosition(position);
	itemSprite.setOrigin(sf::Vector2f(texture.getSize().x/2, texture.getSize().y / 2));
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