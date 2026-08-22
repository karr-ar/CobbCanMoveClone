#include <SFML//Graphics.hpp>
#pragma once
class SurvivalStat
{
	float maxValue;
	float currentValue;
	float prevValue;
	sf::Sprite sprite;
	int no_of_sprites;
	bool active = false;
	int spriteChooser=0;
	int frameWidth;
	int frameHeight;
	bool disappearsAfterIsExhausted = false;// made for freezing mechanics
	bool increasingValueMode = false;  //   made for freezing mechanics

public:
	SurvivalStat(sf::Texture& texture, sf::Vector2f position, sf::Vector2f firstItemPosition, int no_of_sprites, float maxValue , bool active , bool disappearsAfterIsExhausted);
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void setActive();
	void reset(int currVal);
	bool getActive();
	float getCurrentVal();
	void setIncreasingValueMode(bool increasingValueMode);
};

