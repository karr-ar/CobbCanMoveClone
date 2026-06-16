#include "Entity.h"
void Entity::setVelocity(sf::Vector2f velocity) {
	this->velocity.x = velocity.x;
	this->velocity.y = velocity.y;
}
void Entity::setVelocity(float vx, float vy) {
	velocity.x = vx;
	velocity.y = vy;
}
sf::Vector2f Entity::getVelocity() {
	return velocity;
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


Entity::Entity(sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f direction) {
	setVelocity(velocity);
	setPosition(position);
	setDirection(direction);
}