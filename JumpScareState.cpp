#include "JumpScareState.h"
JumpScareState::JumpScareState(sf::Texture& texture, const std::unordered_map<std::string, float > & configData, sf::Vector2f windowSize) : sprite(texture) ,jumpScareAnimation(texture,{21,1}, 0.05, sf::Vector2u(21,1)) {
	sprite.setTextureRect(jumpScareAnimation.getXyRect());
	sprite.setOrigin(sf::Vector2f(jumpScareAnimation.getXyRect().size/2));
	sprite.setPosition(sf::Vector2f(windowSize.x/2, windowSize.y / 2));
	sprite.setScale(sf::Vector2f(5, 5));
}
void JumpScareState::update(float dt) {
	jumpScareAnimation.update(0, dt);
	sprite.setTextureRect(jumpScareAnimation.getXyRect());
	startTime += dt;
	if (startTime > 1.05) {
		//nextState = "loadingScreen";
		jumpScareAnimation.update(1, dt);
		sprite.setTextureRect(jumpScareAnimation.getXyRect());  //this is temporary fix
	}
}
void JumpScareState::render(sf::RenderWindow& window) {
	window.clear();
	window.draw(sprite);
	window.display();
}
void JumpScareState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	return;
}
void JumpScareState::handleInputs() {
	return;
}
std::string JumpScareState::isFinished() {
	return nextState;
}