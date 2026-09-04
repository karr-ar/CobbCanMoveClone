#include "DeathState.h"
DeathState::DeathState(sf::Texture& texture, sf::Vector2f windowSize,int noOfSpritesInARow,
	float switchTime, sf::Font& pressStartFont, std::string causeOfDeath):sprite(texture),deathAnimation(texture,{noOfSpritesInARow,1}, switchTime,
		sf::Vector2u(noOfSpritesInARow,1)), deathMessage(pressStartFont) , deathTitle(pressStartFont), pressAnyButtonMessage(pressStartFont) {
	sprite.setTextureRect(deathAnimation.getXyRect());
	sprite.setOrigin(sf::Vector2f(deathAnimation.getXyRect().size/2));
	sprite.setPosition(sf::Vector2f(windowSize.x/2, windowSize.y / 2));
	sprite.setScale(sf::Vector2f(5, 5));

	this->noOfSpritesInARow = noOfSpritesInARow;
	this->switchTime = switchTime;

	float startX = windowSize.x * 0.3;
	float startY = windowSize.y * 0.5;
	float spacing = 10;

	deathTitle.setPosition({startX*1.2f, startY});
	deathTitle.setCharacterSize(20);
	deathMessage.setPosition({startX, startY +20 + spacing});
	deathMessage.setCharacterSize(12);
	pressAnyButtonMessage.setPosition({ startX, startY + 20 + 12 + spacing * 2 });
	pressAnyButtonMessage.setCharacterSize(10);

	pressAnyButtonMessage.setString("Press Any Button To Continue");
	if (causeOfDeath == "starved") {
		deathTitle.setString("YOU STARVED");
		deathMessage.setString("Cobb wasn't the one who got you.");
	}
	else if (causeOfDeath == "froze") {
		deathTitle.setString("YOU FROZE");
		deathMessage.setString("The cold got there first.");
	}
	else if (causeOfDeath == "jumpscared") {
		deathTitle.setString("COBB FOUND YOU");
		deathMessage.setString("He was faster than you thought.");
	}
	else {
		deathTitle.setString("YOU BURNED");
		deathMessage.setString("The furnace doesn't care who feeds it.");
	}

	deathTitle.setFillColor(sf::Color::Transparent);
	deathMessage.setFillColor(sf::Color::Transparent);
	pressAnyButtonMessage.setFillColor(sf::Color::Transparent);
}
void DeathState::update(float dt) {
	if (!animationFinished) {
		deathAnimation.update(0, dt);
		sprite.setTextureRect(deathAnimation.getXyRect());
		startTime += dt;
	}
	if (startTime > noOfSpritesInARow* switchTime - switchTime) {
		animationFinished = true;

		deathTitle.setFillColor(sf::Color::Red);
		deathMessage.setFillColor(sf::Color::White);
		pressAnyButtonMessage.setFillColor(sf::Color::Yellow);
		listenForAnyEvent = true;
	}
}
void DeathState::render(sf::RenderWindow& window) {
	window.clear();
	window.draw(sprite);

	window.draw(deathTitle);
	window.draw(deathMessage);
	window.draw(pressAnyButtonMessage);

	window.display();
}
void DeathState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	if (!listenForAnyEvent) return;

	if (event.is<sf::Event::KeyPressed>() || event.is<sf::Event::MouseButtonPressed>()) {
		nextState = "menu";
	}
}
void DeathState::handleInputs() {
	return;
}
std::string DeathState::isFinished() {
	return nextState;
}