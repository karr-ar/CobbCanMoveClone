#include "Player.h"
Player::Player(sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f direction, sf::Texture& texture, sf::Keyboard::Scancode left, sf::Keyboard::Scancode right,
	sf::Keyboard::Scancode up, sf::Keyboard::Scancode down) : Entity(velocity, position, direction), playerSprite(texture), playerAnimation(texture, { 6,6,6,6,6,6,6,6 }, 0.1, sf::Vector2u(6, 8)) {
	
	playerSprite.setOrigin(sf::Vector2f(playerAnimation.getXyRect().size.x/2, playerAnimation.getXyRect().size.y / 2));
	spriteRowNo = 0;

	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
}
void Player::inputUpdate() {
	sf::Vector2f direction(0, 0);
	if (sf::Keyboard::isKeyPressed(left)) {
		direction.x += -1;
	}
	if (sf::Keyboard::isKeyPressed(right)) {
		direction.x += 1;
	}
	if (sf::Keyboard::isKeyPressed(up)) {
		direction.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(down)) {
		direction.y += 1;
	}
	if (!(direction.x == 0 && direction.y == 0))
		direction = direction.normalized();
	this->setDirection(direction);
	
}
sf::Vector2f Player::update(float dt) {
	spriteRowNo = 0;

	sf::Vector2f position(this->getPosition());
	
	if (this->getDirection().x >0 && this->getDirection().y > 0) {
		position.x += this->getVelocity().x * dt;
		position.y += this->getVelocity().y * dt;
		spriteRowNo = 4;
	}
	else if (this->getDirection().x > 0 && this->getDirection().y <0) {
		position.x += this->getVelocity().x * dt;
		position.y -= this->getVelocity().y * dt;
		spriteRowNo = 6;
	}
	else if (this->getDirection().x < 0 && this->getDirection().y > 0) {
		position.x -= this->getVelocity().x * dt;
		position.y += this->getVelocity().y * dt;
		spriteRowNo = 5;
	}
	else if (this->getDirection().x < 0 && this->getDirection().y < 0) {
		position.x -= this->getVelocity().x * dt;
		position.y -= this->getVelocity().y * dt;
		spriteRowNo = 7;
	}
	else if (this->getDirection().x > 0) {
		position.x += this->getVelocity().x * dt;
		spriteRowNo = 2;
	}
	else if (this->getDirection().y > 0) {
		position.y += this->getVelocity().y * dt;
	}
	else if (this->getDirection().x < 0) {
		position.x -= this->getVelocity().x * dt;
		spriteRowNo = 1;
	}
	else if (this->getDirection().y < 0) {
		position.y -= this->getVelocity().y * dt;
		spriteRowNo = 3;
	}
	
	playerAnimation.update(spriteRowNo,dt);
	playerSprite.setTextureRect(playerAnimation.getXyRect());
	return position;
}
void Player::draw(sf::RenderWindow& window) {
	window.draw(playerSprite);
}
sf::Sprite Player::getPlayerSprite() {
	return playerSprite;
}
void Player::setPosition(sf::Vector2f position) {
	Entity::setPosition(position);
	playerSprite.setPosition(position);
}

void Player::setPosition(float px,float py) {
	Entity::setPosition(px,py);
	playerSprite.setPosition(getPosition());
}

void Player::move(sf::Vector2f offset) {
	this->setPosition(this->getPosition() + offset);
	playerSprite.move(offset);
}