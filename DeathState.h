#pragma once
#include "GameState.h"
#include "Animation.h"
class DeathState :
    public GameState
{
private:
    Animation deathAnimation;
    bool animationFinished = false;
    sf::Sprite sprite;
    float startTime = 0;
    int noOfSpritesInARow;
    float switchTime;

    sf::Text deathTitle;
    sf::Text deathMessage;
    sf::Text pressAnyButtonMessage;
    bool listenForAnyEvent = false;

    std::string nextState = "";

public:
    DeathState(sf::Texture &texture, sf::Vector2f windowSize , int noOfSpritesInARow , float switchTime, sf::Font& pressStartFont , std::string causeOfDeath);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void handleInputs() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    std::string isFinished() override;
    
};

