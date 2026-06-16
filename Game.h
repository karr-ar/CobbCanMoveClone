#pragma once
#include<SFML//Graphics.hpp>
#include "Player.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
class Game
{ 
public:
	void run();
	Game();
private:
	void inputUpdate();
	void update(float dt);
	void render();
	void createWindow(sf::Vector2f windowSize, std::string windowTitle);
private:
	sf::Vector2f windowSize;
	sf::RenderWindow window;

	std::unique_ptr<Player> player;
	//resourceHolder(texture)
	ResourceHolder<TextureID, sf::Texture> textureHolder;
};

