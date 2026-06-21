#include "Entity.h"
void Entity::setVelocity(float speed) {
	this->speed =  speed;
}
float Entity::getVelocity() {
	return speed;
}
void Entity::setPosition(sf::Vector2f position) {
	this->position.x = position.x;
	this->position.y = position.y;
}
void Entity::setPosition(float px, float py) {
	position.x = px;
	position.y = py;
}
sf::Vector2f Entity::getPosition() {
	return position;
}
void Entity::setDirection(sf::Vector2f direction) {
	this->direction.x = direction.x;
	this->direction.y = direction.y;
}
void Entity::setDirection(float dx, float dy) {
	direction.x = dx;
	direction.y = dy;
}
sf::Vector2f Entity::getDirection() {
	return direction;
}


Entity::Entity(float speed, sf::Vector2f position, sf::Vector2f direction) {
	setVelocity(speed);
	setPosition(position);
	setDirection(direction);
}