#include "Game.h"
#include "PlayingState.h"
#include "DeathState.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Game::createWindow(sf::Vector2f windowSize, std::string windowTitle) {
	sf::VideoMode vm({ (unsigned int)windowSize.x, (unsigned int)windowSize.y });
	window.create(vm, windowTitle);
}

Game::Game() {
	configData = getConfigData("sprites/config/config_file.txt");

	float windowSizeX = configData.count("window_size_x") ? configData["window_size_x"] : 0;
	float windowSizeY = configData.count("window_size_y") ? configData["window_size_y"] : 0;
	windowSize = { windowSizeX, windowSizeY };

	createWindow(windowSize, "CobbCanMoveClone");


	//Resource initialization (textures)
	textureHolder.load(TextureID::Player, "sprites/graphics/Player.PNG");
	textureHolder.load(TextureID::Wall, "sprites/graphics/wall_left.PNG");
	textureHolder.load(TextureID::Tile, "sprites/graphics/floor_light.PNG");
	textureHolder.load(TextureID::Cobb, "sprites/graphics/cobb.png");
	textureHolder.load(TextureID::Candle, "sprites/graphics/candle_spritesheet.png");
	textureHolder.load(TextureID::Stone, "sprites/graphics/stone_break_spritesheet.PNG");
	textureHolder.load(TextureID::Wall2, "sprites/graphics/wall2.PNG");
	textureHolder.load(TextureID::Grass, "sprites/graphics/grass.PNG");
	textureHolder.load(TextureID::Escalator, "sprites/graphics/escalator.PNG");
	textureHolder.load(TextureID::Furnace, "sprites/graphics/furnace.PNG");
	textureHolder.load(TextureID::JumpScare, "sprites/graphics/jumpscare.PNG");
	textureHolder.load(TextureID::Carrot, "sprites/graphics/carrot.PNG");
	textureHolder.load(TextureID::Carrot2, "sprites/graphics/carrott.PNG");
	textureHolder.load(TextureID::Snowflake, "sprites/graphics/snowflake.PNG");
	//Resource initialization (sounds)

	//Resource initialization (Fonts)


	// hand the whole config map + window size down to the first state
	currentState = std::make_unique<PlayingState>(configData, windowSize, textureHolder);
}

void Game::run() {
	sf::Clock clock;
	srand((int)time(0));
	//
	while (window.isOpen()) {
		while (const std::optional<sf::Event> event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			currentState->handleEvent(*event, window); // forward everything else down
		}
		currentState->handleInputs();
		//
		sf::Time dt = clock.restart();
		currentState->update(dt.asSeconds());

		//
		currentState->render(window);

		if (currentState->isFinished() == "jumpscare") {
			currentState = std::make_unique<DeathState>(textureHolder.get(TextureID::JumpScare), configData, windowSize ,21, 0.05);
		}
		else if (currentState->isFinished() == "froze") {

		}
		else if (currentState->isFinished() == "burned") {

		}
		else if (currentState->isFinished() == "starved") {

		}
		else if (currentState->isFinished() == "menu") {

		}
		else if (currentState->isFinished() == "loadingScreen") {

		}
		else { }//do nothing 
	}
}

std::unordered_map<std::string, float> Game::getConfigData(std::string filePath) {
	std::unordered_map<std::string, float> configData;
	std::ifstream configFile(filePath);
	if (!configFile.is_open()) {
		std::cerr << "Error: Could not open config file: " << filePath << "\n";
		return configData;
	}
	std::string line;
	while (std::getline(configFile, line)) {
		std::stringstream ss(line);
		std::string key;
		float value;
		if (ss >> key >> value) {
			configData[key] = value;
		}
	}
	return configData;
}