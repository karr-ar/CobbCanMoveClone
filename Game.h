#pragma once
#include<SFML//Graphics.hpp>
class Game
{ 
public:
	void run();
	Game();
private:
	void inputUpdate();
	void update();
	void render();
	void createWindow(sf::Vector2f windowSize, std::string windowTitle);
private:
	sf::Vector2f windowSize;
	sf::RenderWindow window;
};

