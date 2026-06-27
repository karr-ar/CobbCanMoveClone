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
	textureHolder.load(TextureID::Candle, "sprites/graphics/candle_spritesheet.png");
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
		sf::Keyboard::Scancode::A, sf::Keyboard::Scancode::D, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S, sf::Keyboard::Scancode::E);

	//cobb Initialize
	cobb = std::make_unique<Cobb>(textureHolder.get(TextureID::Cobb), 250, cobbInitialLoc ,sf::Vector2f(0,0));  
	
	//spawn the items
	spawnItems();

	//view init
	view.setCenter(sf::Vector2f(player->getPosition()));
	view.setSize(sf::Vector2f(windowSize.x,windowSize.y));

	if (!lightMapTexture.resize(sf::Vector2u(windowSize.x, windowSize.y))) {
		std::cout << "Critical Error: Failed to create lightmap texture!" << std::endl;
	}
	lightMaskTexture = generateLightMask(70);
//	spawnDarkness();
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
		if (const auto& keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->scancode == player->getEquipButton()) {
				player->equipItem(items);
			}
		}
	}
	player->inputUpdate();
	std::vector <sf::Vector2f> cobbsAllowedPositions = map->getCobbsAllowablePositions();
	//cobb->RandomMovement(cobbsAllowedPositions, rand() % cobbsAllowedPositions.size());
	cobb->cobbCanSee(player->getPosition(),true);
}
void Game::render() {
	window.clear();
	window.setView(view);
	map->draw(window);
	drawItems();
	player->draw(window);
	player->drawPlayersEquippedItem(window);
	cobb->draw(window);

	//lightMapTexture.clear(sf::Color(0, 0, 0, 0));
	lightMapTexture.clear(sf::Color(0, 0, 0, 245));
	lightMapTexture.setView(view);

	//sf::CircleShape darknessCloud(100);
	//darknessCloud.setOrigin(sf::Vector2f(350, 350));
	//darknessCloud.setFillColor(sf::Color(0, 0, 0, 245));

	//for (const auto& darkPos : darknessPockets) {
	//	darknessCloud.setPosition(darkPos);
	//	lightMapTexture.draw(darknessCloud);
	//}

	sf::BlendMode eraserblend(sf::BlendMode::Factor::Zero, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add,
		sf::BlendMode::Factor::Zero, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add);
	sf::RenderStates eraser;
	eraser.blendMode = eraserblend;

	sf::Sprite lightGlow(lightMaskTexture);
	lightGlow.setOrigin(sf::Vector2f(lightMaskTexture.getSize().x / 2, lightMaskTexture.getSize().y / 2));

	for (int i = 0;i < items.size();i++) {
		Candle* candle = dynamic_cast<Candle*>(items[i].get());
		if (candle != nullptr) {
			float scaleFactor = candle->getLuminosityRadius() / 70; //here 70 is the radius passed to sf::Texture generateLightMask(int radius); 
			lightGlow.setScale(sf::Vector2f(scaleFactor, scaleFactor));
			lightGlow.setPosition(candle->getPosition());
			lightMapTexture.draw(lightGlow,eraser);
		}
	}

	lightMapTexture.display();
	sf::Sprite lightMapSprite(lightMapTexture.getTexture());
	window.setView(window.getDefaultView());
	window.draw(lightMapSprite);

	window.display();
}
void Game::update(float dt) {
	sf::Vector2f offsetPlayer= player->update(dt) ;
	player->move(sf::Vector2f(offsetPlayer.x, 0));
	playerWallCollision(true);
	player->move(sf::Vector2f(0, offsetPlayer.y));
	playerWallCollision(false);
	cobb->move(sf::Vector2f(cobb->update(dt)));
	updateItems(dt);
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
void Game::spawnItems() {
	std::vector <sf::Vector2f> cobbsAllowedPositions = map->getCobbsAllowablePositions();
	//spawning candles 
	int no_of_candles = 16;
	for (int i = 0;i < 16;i++) {
		items.push_back(std::make_unique<Candle>(550,25, cobbsAllowedPositions[rand() % cobbsAllowedPositions.size()],textureHolder.get(TextureID::Candle)));   //hard coding for now
	}
	//spawning rocks
}
void Game::drawItems() {  //draws everything except equipped item
	for (int i = 0;i < items.size();i++) {
		if (!items[i]->getEquipped()) {
			items[i]->draw(window);
		}
	}
}
void Game::updateItems(float dt) {
	for (int i = 0;i < items.size();i++) {
		items[i]->update(dt, player->getPosition());
	}
}

//void Game::spawnDarkness() {
//	std::vector<sf::Vector2f> cobbsAllowedPositions = map->getCobbsAllowablePositions();
//
//	int number_of_dark_zones = 24; // Adjust to make the game harder/easier
//	for (int i = 0; i < number_of_dark_zones; i++) {
//		sf::Vector2f randomPos = cobbsAllowedPositions[rand() % cobbsAllowedPositions.size()];
//		darknessPockets.push_back(randomPos);
//	}
//}

sf::Texture Game::generateLightMask(int radius) {
	int size = 2 * radius;
	sf::Image image;
	image.resize(sf::Vector2u(size, size), sf::Color(255, 255, 255, 0));
	sf::Vector2f center(sf::Vector2f(radius, radius));

	for (int y = 0;y < size;y++) {
		for (int x = 0;x < size;x++) {
			sf::Vector2f pixelPos(x, y);
			float distance = sqrt((pixelPos.x-center.x)*(pixelPos.x - center.x) + (pixelPos.y - center.y)*(pixelPos.y - center.y));

			if (distance <= radius) {
				float ratio = 1.0f - distance / radius;
				int alpha = 255 * ratio * ratio;
				image.setPixel(sf::Vector2u(x, y), sf::Color(255, 255, 255, alpha));
			}
		}
	}
	sf::Texture texture;
	if (!texture.loadFromImage(image)) {
		std::cout << "failed to convert image to texture";
	}
	return texture;
}