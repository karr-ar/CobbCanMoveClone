#include "Cobb.h"
#include <iostream>
Cobb::Cobb(sf::Texture& cobbTexture, float velocity, sf::Vector2f position, sf::Vector2f direction) :cobbSprite(cobbTexture),
Entity(velocity, position, direction), cobbAnimation(cobbTexture, { 15 }, 0.1, sf::Vector2u(15, 1)) {
	cobbSprite.setTextureRect(cobbAnimation.getXyRect());
	cobbSprite.setOrigin(sf::Vector2f(cobbAnimation.getXyRect().size.x/2, cobbAnimation.getXyRect().size.y / 2));
	cobbSprite.setScale(sf::Vector2f(2.5, 2.5));

}
void Cobb::setPosition(sf::Vector2f position) {
	Entity::setPosition(position);
	cobbSprite.setPosition(position);
}
void Cobb::followTheGivenPosition(sf::Vector2f position) {
	sf::Vector2f direction( position - getPosition());
	if (getDirection().x != 0 && getDirection().y != 0) direction = direction.normalized();

	// Create a 1.5 pixel tolerance zone
	float deadzone = 4;

	if ((position - getPosition()).length() > deadzone) {
		setDirection(direction);
	}
	else {
		setDirection(0, 0);
	}

	this->setDirection(direction);
}
void Cobb::RandomMovement(std::vector <sf::Vector2f> cobbsAllowedPositions, int randomPosIndex) {
	if (updateCobbsPosition) {
		cobbsNewLocation = cobbsAllowedPositions[randomPosIndex];

		//sf::Vector2f direction(cobbsNewLocation - this->getPosition());
		//direction = direction.normalized();
		//this->setDirection(direction);


		updateCobbsPosition = false;
		
	}
	followTheGivenPosition(cobbsNewLocation);
	//ive to also add random stops for cobb and fix its sprite too later to stop moving its legs when its stopped.

	
	if (sqrt(pow(getPosition().x-cobbsNewLocation.x,2)+ pow(getPosition().y - cobbsNewLocation.y, 2)) < 5 ){
		updateCobbsPosition = true;
	}
}
sf::Vector2f Cobb::update(float dt) {
	
	cobbAnimation.update(0, dt);
	cobbSprite.setTextureRect(cobbAnimation.getXyRect());
	if (getDirection().x > 0) {
		cobbSprite.setScale(sf::Vector2f(-2.5, 2.5));
	}
	else {
		cobbSprite.setScale(sf::Vector2f(2.5, 2.5));
	}
	return dt * getDirection() * getVelocity();
}
void Cobb::draw(sf::RenderWindow &window) {
	window.draw(cobbSprite);
}
void Cobb::move(sf::Vector2f offset) {
	setPosition(getPosition()+offset);
}
sf::Sprite Cobb::getCobbSprite() {
	return cobbSprite;
}
void Cobb::UpdateCobbsPosition() {
	updateCobbsPosition = true;
}
void Cobb::cobbCanSee(sf::Vector2f playersPosition, bool active) {
	if (active) {
		followTheGivenPosition(playersPosition);
	}
}