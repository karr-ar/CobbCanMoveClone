#include "Game.h"
void Game::run() {
	sf::Clock clock;
	srand((int)time(0));
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
	textureHolder.load(TextureID::Wall, "sprites/graphics/wall_left.PNG");
	textureHolder.load(TextureID::Tile, "sprites/graphics/floor_light.PNG");
	textureHolder.load(TextureID::Cobb, "sprites/graphics/cobb.png");
	//Resource initialization (sounds)

	//Resource initialization (Fonts)
	
	//Map initialization
	map = std::make_unique<Map>("sprites/graphics/map.txt", textureHolder.get(TextureID::Wall), textureHolder.get(TextureID::Tile));

	//finding players initial location
	sf::Vector2f playerInitialLoc = map->getPlayerInitialPosition();
	
	//finding cobbs initial position
	sf::Vector2f cobbInitialLoc = map->getCobbInitialPosition();
	
	//Player Initialization
	player = std::make_unique<Player>(300,playerInitialLoc, sf::Vector2f(0,0),textureHolder.get(TextureID::Player),
		sf::Keyboard::Scancode::A, sf::Keyboard::Scancode::D, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S);

	//cobb Initialize
	cobb = std::make_unique<Cobb>(textureHolder.get(TextureID::Cobb), 170, cobbInitialLoc ,sf::Vector2f(0,0));  
	

	//view init
	view.setCenter(sf::Vector2f(player->getPosition()));
	view.setSize(sf::Vector2f(windowSize.x,windowSize.y));
}
void Game::inputUpdate() {
	while (const std::optional<sf::Event> event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (const auto* resized = event->getIf<sf::Event::Resized>()) {
			sf::Vector2f newSize((float)resized->size.x, (float)resized->size.y);
			view.setSize(newSize);
			windowSize = newSize;
		}
	}
	player->inputUpdate();
	std::vector <sf::Vector2f> cobbsAllowedPositions = map->getCobbsAllowablePositions();
	cobb->inputUpdate(cobbsAllowedPositions, rand() % cobbsAllowedPositions.size());
}
void Game::render() {
	window.clear();
	window.setView(view);
	map->draw(window);
	player->draw(window);
	cobb->draw(window);
	window.display();
}
void Game::update(float dt) {
	sf::Vector2f offsetPlayer= player->update(dt) ;
	player->move(sf::Vector2f(offsetPlayer.x, 0));
	playerWallCollision(true);
	player->move(sf::Vector2f(0, offsetPlayer.y));
	playerWallCollision(false);
	cobb->move(sf::Vector2f(cobb->update(dt)));
	view.setCenter(player->getPosition());//for now the camera is rigid but ill fix it  later
}
//collision for player and walls
bool Game::checkCollision(sf::FloatRect first, sf::FloatRect second) {
	if (first.findIntersection(second)) {
		return true;
	}
	else {
		return false;
	}
}

void Game::playerWallCollision(bool x_y) {    // true for x and false for y
	std::vector<sf::Vector2f > walls = map->getWalls();
	sf::FloatRect playerRect = player->getPlayerSprite().getGlobalBounds();
	for (int i = 0;i < walls.size();i++) {
		sf::FloatRect wallRect = map->getWallSprite().getGlobalBounds();
		wallRect.position = walls[i]- sf::Vector2f(map->getWallSprite().getTexture().getSize().x/2, map->getWallSprite().getTexture().getSize().y/2);
		if (checkCollision(playerRect, wallRect) && x_y) {
			if (player->getDirection().x > 0) {
				player->setPosition(player->getPosition().x - playerRect.findIntersection(wallRect)->size.x, player->getPosition().y);
			}
			else if (player->getDirection().x < 0) {
				player->setPosition(player->getPosition().x + playerRect.findIntersection(wallRect)->size.x, player->getPosition().y);
			}
			
		}
		if (checkCollision(playerRect, wallRect) && !x_y) {
			if (player->getDirection().y > 0) {
				player->setPosition(player->getPosition().x , player->getPosition().y - playerRect.findIntersection(wallRect)->size.y);
			}
			else if (player->getDirection().y < 0) {
				player->setPosition(player->getPosition().x , player->getPosition().y + playerRect.findIntersection(wallRect)->size.y);
			}

		}
	}
}
