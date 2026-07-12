#include "Cobb.h"
#include <iostream>
Cobb::Cobb(sf::Texture& cobbTexture, float velocity, float cobbInvestigationSpeed, float cobbChasingSpeed, sf::Vector2f position, sf::Vector2f direction,float cobbScaledBy, float cobbsVisualRadius) :cobbSprite(cobbTexture),
Entity(velocity, position, direction), cobbAnimation(cobbTexture, { 15 }, 0.1, sf::Vector2u(15, 1)) {
	cobbSprite.setTextureRect(cobbAnimation.getXyRect());
	cobbSprite.setOrigin(sf::Vector2f(cobbAnimation.getXyRect().size.x/2, cobbAnimation.getXyRect().size.y / 2));
	cobbSprite.setScale(sf::Vector2f(2.5, 2.5));


	this->cobbChasingSpeed = cobbChasingSpeed;
	this->cobbInvestigationSpeed= cobbInvestigationSpeed;
	this->cobbScaledBy= cobbScaledBy;   //when cobb is chasing is enabled it gets bigger 
	this->cobbsVisualRadius = cobbsVisualRadius;

}
void Cobb::setPosition(sf::Vector2f position) {
	Entity::setPosition(position);
	cobbSprite.setPosition(position);
}
void Cobb::followTheGivenPosition(sf::Vector2f position) {
	sf::Vector2f direction( position - getPosition());
	if (direction.x != 0 && direction.y != 0) direction = direction.normalized();

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
void Cobb::RandomMovement(sf::Vector2f nextRandomPos) {
	if (updateCobbsPosition) {
		cobbsNewLocation = nextRandomPos;

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
void Cobb::cobbCanSee() {
		followTheGivenPosition(lastSeenPosition);
		if ((this->getPosition() - lastSeenPosition).length() < 5) {
			cobbsVisualRetention = false;
	}
}
void Cobb::canCobbSeeThePlayer(sf::Vector2f playerPos, bool isPlayerVisible) {
	if (((this)->getPosition() - (playerPos)).length() <= cobbsVisualRadius && isPlayerVisible) {
		canCobbSee = true;
		lastSeenPosition = playerPos;
		cobbsVisualRetention = true;
	}
	else {
		canCobbSee = false;
	}
}
void Cobb::chooseMovement(sf::Vector2f nextRandomPos) {

	if (canCobbSee || cobbsVisualRetention) {
		this->setVelocity(cobbChasingSpeed);
		cobbCanSee();
	}
	else if (cobbsHearingRetention) {
		this->setVelocity(cobbChasingSpeed);
		cobbFollowsLastHeardPosition();
	}
	else {
		this->setVelocity(getVelocity());
		RandomMovement(nextRandomPos);
	}
}
void Cobb::setCobbsHearingRetention() {
	cobbsHearingRetention = true;
}
void Cobb::setCobbsLastHeardPosition(sf::Vector2f lastHeardPosition) {
	this->lastHeardPosition = lastHeardPosition;
}
void Cobb::cobbFollowsLastHeardPosition(){
	followTheGivenPosition(lastHeardPosition);
	if ((this->getPosition() - lastHeardPosition).length() < 5) {
		cobbsHearingRetention = false;
	}
}