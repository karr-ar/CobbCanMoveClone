#include "DeathState.h"
DeathState::DeathState(sf::Texture& texture, const std::unordered_map<std::string, float > & configData, sf::Vector2f windowSize
												,int noOfSpritesInARow, float switchTime) : sprite(texture) ,deathAnimation(texture,{noOfSpritesInARow,1}, switchTime, sf::Vector2u(noOfSpritesInARow,1)) {
	sprite.setTextureRect(deathAnimation.getXyRect());
	sprite.setOrigin(sf::Vector2f(deathAnimation.getXyRect().size/2));
	sprite.setPosition(sf::Vector2f(windowSize.x/2, windowSize.y / 2));
	sprite.setScale(sf::Vector2f(5, 5));

	this->noOfSpritesInARow = noOfSpritesInARow;
	this->switchTime = switchTime;
}
void DeathState::update(float dt) {
	if (!animationFinished) {
		deathAnimation.update(0, dt);
		sprite.setTextureRect(deathAnimation.getXyRect());
		startTime += dt;
	}
	if (startTime > noOfSpritesInARow* switchTime - switchTime) {
		animationFinished = true;
		//display text and wait for user input to move back to main menu
	}
}
void DeathState::render(sf::RenderWindow& window) {
	window.clear();
	window.draw(sprite);
	window.display();
}
void DeathState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	return;
}
void DeathState::handleInputs() {
	return;
}
std::string DeathState::isFinished() {
	return nextState;
}