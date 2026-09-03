#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include "GameState.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
#include "MenuState.h"
#include "Challenges.h"
#include "LoadingState.h"
#include <algorithm>

class Game {
public:
	Game();
	void run();

private:
	void createWindow(sf::Vector2f windowSize, std::string windowTitle);
	std::unordered_map<std::string, float> getConfigData(std::string filePath);
	void loadFromSaveFile();
	void saveGame();
	void levelGenerator();
	void rollChallenges();
	void selectMap();
	void findTasks();

private:
	sf::Vector2f windowSize;
	sf::RenderWindow window;
	std::unordered_map<std::string, float> configData; 
	std::unordered_map<std::string, float> saveData;
	int level;
	std::unique_ptr<GameState> currentState;
	ResourceHolder<TextureID, sf::Texture> textureHolder; 
	sf::Font pressStartFont;

	std::unordered_map<Challenges, bool> challenges;
	Maps map;
	int noOfCoal;
	int noOfBreakers;
};