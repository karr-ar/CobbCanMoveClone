#include "Game.h"
#include "PlayingState.h"
#include "DeathState.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem> 

void Game::createWindow(sf::Vector2f windowSize, std::string windowTitle) {
	sf::VideoMode vm({ (unsigned int)windowSize.x, (unsigned int)windowSize.y });
	window.create(vm, windowTitle);
}

Game::Game() {
	configData = getConfigData("config/config_file.txt");

	loadFromSaveFile();

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
	textureHolder.load(TextureID::Coal, "sprites/graphics/coal2.PNG");
	textureHolder.load(TextureID::Breaker, "sprites/graphics/breaker.PNG");
	textureHolder.load(TextureID::FrozeToDeath, "sprites/graphics/froze.PNG");
	textureHolder.load(TextureID::StarvedToDeath, "sprites/graphics/starved.PNG");
	textureHolder.load(TextureID::BurntToDeath, "sprites/graphics/burned.PNG");
	//Resource initialization (sounds)

	//Resource initialization (Fonts)
	pressStartFont.openFromFile("fonts/PressStart2P-Regular.ttf");

	// hand the whole config map + window size down to the first state
	currentState = std::make_unique<MenuState>( windowSize , pressStartFont, level);
}

void Game::run() {
	sf::Clock clock;
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
		if (currentState->isFinished() == "quit") {
			window.close();
		}
		else if (currentState->isFinished() == "continue") {
			levelGenerator();
			currentState = std::make_unique<LoadingState>(windowSize, pressStartFont, level , challenges);
		}
		else if (currentState->isFinished() == "playing") {
			currentState = std::make_unique<PlayingState>(configData, windowSize,textureHolder, noOfCoal,noOfBreakers , pressStartFont , map, challenges);
		}
		else if (currentState->isFinished() == "jumpscare") {
			currentState = std::make_unique<DeathState>(textureHolder.get(TextureID::JumpScare), windowSize ,21, 0.05 , pressStartFont , "jumpscared");
		}
		else if (currentState->isFinished() == "froze") {
			currentState = std::make_unique<DeathState>(textureHolder.get(TextureID::FrozeToDeath), windowSize, 20, 0.02, pressStartFont , "froze");
		}
		else if (currentState->isFinished() == "burned") {
			currentState = std::make_unique<DeathState>(textureHolder.get(TextureID::BurntToDeath), windowSize, 20, 0.03, pressStartFont , "burned");
		}
		else if (currentState->isFinished() == "starved") {
			currentState = std::make_unique<DeathState>(textureHolder.get(TextureID::StarvedToDeath), windowSize, 20, 0.1, pressStartFont , "starved");
		}
		else if (currentState->isFinished() == "menu") {
			currentState = std::make_unique<MenuState>(windowSize, pressStartFont, level);
		}
		else if (currentState->isFinished() == "win") {
			if (level < 7) {
				level++;
				saveGame();
				levelGenerator();
				currentState = std::make_unique<LoadingState>(windowSize, pressStartFont, level, challenges);
			}
			else {
				saveGame();
				currentState = std::make_unique<MenuState>(windowSize, pressStartFont, level);
			}
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

void Game::loadFromSaveFile() {
	std::string dirName = "save";
	std::string saveFileName = dirName + "/save.txt";

	// Ensure the directory exists first
	if (!std::filesystem::exists(dirName)) {
		std::filesystem::create_directory(dirName);
	}

	std::ifstream saveFile(saveFileName); 
	if (saveFile.is_open() && saveFile.good()) {
		saveFile.close(); // Close before reading via getConfigData if it opens it again
		saveData = getConfigData(saveFileName);
		level = saveData.count("level") ? saveData["level"] : 1;
	}
	else {
		level = 1;
		std::ofstream outFile(saveFileName);
		if (outFile.is_open()) {
			outFile << "level 1\n"; 
		}
	}
}
void Game::saveGame() {
	std::ofstream file("save/save.txt");
	if (file.is_open()) {
		file << "level " << level << "\n";
		file.close();
	}
}
void Game::levelGenerator() {
	rollChallenges();   
	selectMap();       
	findTasks();
}
void Game::rollChallenges() {
	challenges.clear();
	challenges[Challenges::CobbCanMove] = true;
	std::vector<Challenges> pool;
	if (level == 1) return;
	if (level >1) {
		pool.push_back(Challenges::CobbCanSmell);
		pool.push_back(Challenges::CobbCanHear);
		pool.push_back(Challenges::CobbCanSee);
	}
	if (level >2) {
		pool.push_back(Challenges::YouCanStarve);
		pool.push_back(Challenges::YouCanFreeze);
	}
	if (level >3) {
		pool.push_back(Challenges::CobbCanDuplicate);
		pool.push_back(Challenges::CobbCanChase);
	}
	if(level>4) {
		pool.push_back(Challenges::CobbDuplicateX2);
	}
	for (int i = 0;i < level - 1;i++) {
		int idx = rand() % pool.size();
		if (i == level - 2 && pool[idx] == Challenges::CobbDuplicateX2) {
			challenges[Challenges::CobbCanDuplicate] = true;
			break;
		}
		else if (i < level - 2 && pool[idx] == Challenges::CobbDuplicateX2) {
			i++;
		}
		Challenges picked = pool[idx];
		challenges[picked] = true;
		pool.erase(pool.begin() + idx);

		if (picked == Challenges::CobbCanDuplicate) {
			pool.erase(std::remove(pool.begin(), pool.end(), Challenges::CobbDuplicateX2), pool.end());
		}
		else if (picked == Challenges::CobbDuplicateX2) {
			pool.erase(std::remove(pool.begin(), pool.end(), Challenges::CobbCanDuplicate), pool.end());
		}
	}
}
void Game::selectMap() {
	//gonna fix this later cuz for now i dont have maps
	map = Maps::Map1;

}
void Game::findTasks() {
	switch (level) {
	case 1:
		noOfCoal = 3;
		noOfBreakers = 0;
		break;
	case 2:
		noOfCoal = 5;
		noOfBreakers = 0;
		break;
	case 3:
		noOfCoal = 6;
		noOfBreakers = 1;
		break;
	case 4:
		noOfCoal = 7;
		noOfBreakers = 2;
		break;
	case 5:
		noOfCoal = 8;
		noOfBreakers = 4;
		break;
	case 6:
		noOfCoal = 10;
		noOfBreakers = 5;
		break;
	case 7:
		noOfCoal = 0;
		noOfBreakers = 0;
		break;
	default:
		noOfCoal = 1;
		noOfBreakers = 0;
		break;
	}
}