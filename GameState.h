#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
	//both the functions below are for inputs
	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
	virtual void handleInputs() = 0;   // continuous/per-frame input, not event-driven
	//for update
	virtual void update(float dt)=0;
	//for drawing 
	virtual void render(sf::RenderWindow& window)=0;
	// virtual destructor is a must — without it, deleting through a GameState*
	// only runs ~GameState(), skipping derived class cleanup (leaks/UB)
	virtual ~GameState() = default;
};

