#pragma once
#include<SFML//Graphics.hpp>
#include "Player.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
#include "Map.h"
#include "Cobb.h"
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
	bool checkCollision(sf::FloatRect first, sf::FloatRect second);
	void playerWallCollision(bool x_y);
private:
	sf::Vector2f windowSize;
	sf::RenderWindow window;

	sf::View view;

	std::unique_ptr<Player> player;
	std::unique_ptr<Map> map;
	std::unique_ptr<Cobb> cobb;
	//resourceHolder(texture)
	ResourceHolder<TextureID, sf::Texture> textureHolder;
};

