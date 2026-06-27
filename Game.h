#pragma once
#include <iostream>

#include<SFML//Graphics.hpp>
#include "Player.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
#include "Map.h"
#include "Cobb.h"
#include "Item.h"
#include "Candle.h"
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
	void cobbWallCollision(bool x_y);
	void spawnItems();
	void drawItems();
	void updateItems(float dt);

	//for darkness
	void spawnDarkness();

	sf::Texture generateLightMask(int radius); 

private:
	sf::Vector2f windowSize;
	sf::RenderWindow window;

	sf::View view;

	std::unique_ptr<Player> player;
	std::unique_ptr<Map> map;
	std::unique_ptr<Cobb> cobb;

	std::vector<std::unique_ptr<Item>> items;


	//for darkness
	sf::RenderTexture lightMapTexture;
	//std::vector<sf::Vector2f> darknessPockets;
	sf::Texture lightMaskTexture;

	//resourceHolder(texture)
	ResourceHolder<TextureID, sf::Texture> textureHolder;
};

