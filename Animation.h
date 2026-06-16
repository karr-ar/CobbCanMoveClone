#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
	Animation(sf::Texture, std::vector<int> spritesPerRow,float switchTime, sf::Vector2u maxImageCount);
	void update(int row,float dt);
	sf::IntRect getXyRect();
private:
	sf::IntRect xyRect;
	sf::Vector2u currentImage;
	std::vector<int> spritesPerRow;
	sf::Vector2u maxImageCount;

	float totalTime;
	float switchTime;
};

