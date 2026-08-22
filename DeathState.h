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
public:
    DeathState(sf::Texture &texture, const std::unordered_map<std::string, float> & configData, sf::Vector2f windowSize , int noOfSpritesInARow , float switchTime );
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void handleInputs() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    std::string isFinished() override;
    std::string nextState = "";
};

