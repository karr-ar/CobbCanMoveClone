#include "Game.h"
void Game::run() {
	while (window.isOpen()) {
		inputUpdate();
		update();
		render();
	}
}
void Game::createWindow(sf::Vector2f windowSize,std::string windowTitle) {
	sf::VideoMode vm({ (unsigned int)windowSize.x,(unsigned int)windowSize.y });
	window.create(vm,windowTitle);
}
Game::Game() {
	//window init
	windowSize.x = 1024;
	windowSize.y = 678;
	std::string title = "CobbCanMoveClone";
	createWindow(windowSize, title);

	//
}
void Game::inputUpdate() {
	while (const std::optional<sf::Event> event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
	}
}
void Game::render() {
	window.clear();

	window.display();
}
void Game::update() {

}