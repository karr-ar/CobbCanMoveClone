#include "Stone.h"
Stone::Stone(float luminosityRadius, sf::Vector2f position, sf::Texture& texture, float equipNoiseRadius,
	float unequipNoiseRadius,  float initialUpwardVelocity, float downwardAcceleration, float horizontalVelocity) :Item(luminosityRadius,position,texture,equipNoiseRadius,unequipNoiseRadius){

	this->initialUpwardVelocity = initialUpwardVelocity;
	this->downwardAcceleration = downwardAcceleration;
	this->horizontalVelocity = horizontalVelocity;
}
void Stone::jump() {
	if (onAir && UpwardVelocity <= 0.0f && getPosition().y >= unequipLocation.y) {
		UpwardVelocity = 0;
		onAir = false;
		if (ReadyForDestructionNoise) {
			produceUnEquipNoise();
			ReadyForDestructionNoise = false;
		}
	}
	if (_jump == true) {
		UpwardVelocity = initialUpwardVelocity;
		onAir = true;
		_jump = false;
	}
}
void Stone::update(float dt, sf::Vector2f playerPosition) {

	Item::update(dt, playerPosition);

	jump();

	if (onAir) {
		sf::Vector2f currPosition = getPosition();

		UpwardVelocity = UpwardVelocity + downwardAcceleration * dt;
		currPosition.y -= UpwardVelocity * dt;
		currPosition.x += horizontalDirection * dt * horizontalVelocity;

		setPosition(currPosition);
	}
}
void Stone::unequip() {
	//dont call item class's unequip!
	//cuz it sets noise to true the moment it unequips 

	setUnEquipped();
	_jump = true;
	ReadyForDestructionNoise = true;
	unequipLocation = getPosition();

}
void Stone::setHorizontalDirection(int x) {
	horizontalDirection = x;
}