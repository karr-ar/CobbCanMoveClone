#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include "GameState.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"

class Game {
public:
	Game();
	void run();

private:
	void createWindow(sf::Vector2f windowSize, std::string windowTitle);
	std::unordered_map<std::string, float> getConfigData(std::string filePath);

private:
	sf::Vector2f windowSize;
	sf::RenderWindow window;
	std::unordered_map<std::string, float> configData; 
	std::unique_ptr<GameState> currentState;
	ResourceHolder<TextureID, sf::Texture> textureHolder; 
	sf::Font pressStartFont;
};