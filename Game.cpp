#include "Game.h"
void Game::run() {
	sf::Clock clock;
	while (window.isOpen()) {
		inputUpdate();
		sf::Time dt = clock.restart();
		update(dt.asSeconds());
		render();
	}
}
void Game::createWindow(sf::Vector2f windowSize,std::string windowTitle) {
	sf::VideoMode vm({ (unsigned int)windowSize.x,(unsigned int)windowSize.y });
	window.create(vm,windowTitle);
}
Game::Game() {
	
	//window init
	windowSize.x = 1920;
	windowSize.y = 1080;
	std::string title = "CobbCanMoveClone";
	createWindow(windowSize, title);

	//Resource initialization (textures)
	textureHolder.load(TextureID::Player, "sprites/graphics/Player.PNG");
	//Resource initialization (sounds)

	//Resource initialization (Fonts)
	
	//Player Initialization
	player = std::make_unique<Player>(sf::Vector2f(100,100),sf::Vector2f(windowSize.x/2,windowSize.y/2), sf::Vector2f(0,0),textureHolder.get(TextureID::Player),
		sf::Keyboard::Scancode::A, sf::Keyboard::Scancode::D, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S);
}
void Game::inputUpdate() {
	while (const std::optional<sf::Event> event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		player->inputUpdate();
	}
}
void Game::render() {
	window.clear();
	player->draw(window);
	window.display();
}
void Game::update(float dt) {
	player->update(dt);
}