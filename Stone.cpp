#include "Stone.h"
Stone::Stone(float luminosityRadius, sf::Vector2f position, sf::Texture& texture, float equipNoiseRadius,
	float unequipNoiseRadius,  float initialUpwardVelocity, float downwardAcceleration, float horizontalVelocity, float escalator_speed) :Item(luminosityRadius,position,texture,equipNoiseRadius,unequipNoiseRadius, escalator_speed),
																												stoneDestructionAnimation(texture,{5},0.1,sf::Vector2u(5,1)) {
	getSprite().setOrigin(sf::Vector2f(stoneDestructionAnimation.getXyRect().size.x / 2, stoneDestructionAnimation.getXyRect().size.x / 2));
	getSprite().setTextureRect(stoneDestructionAnimation.getXyRect());

	this->initialUpwardVelocity = initialUpwardVelocity;
	this->downwardAcceleration = downwardAcceleration;
	this->horizontalVelocity = horizontalVelocity;
}
void Stone::jump() {
	if (onAir && UpwardVelocity <= 0.0f && getPosition().y >= unequipLocation.y) {
		UpwardVelocity = 0;
		onAir = false;
		displayDestructionAnimation = true;
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
	if (displayDestructionAnimation) {
		stoneDestructionAnimation.update(0, dt);
		getSprite().setTextureRect(stoneDestructionAnimation.getXyRect());
		destructionTimer -= dt;
		if (destructionTimer <= 0) {
			deleteStone = true;
			displayDestructionAnimation = false;
		}
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
bool Stone::getDeleteStone() {
	return deleteStone;
}