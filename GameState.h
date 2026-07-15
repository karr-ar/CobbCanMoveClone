#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
	virtual void handleInputs() = 0;   // continuous/per-frame input, not event-driven
	virtual void update(float dt)=0;
	virtual void render(sf::RenderWindow& window)=0;
	~GameState() = default;
};

