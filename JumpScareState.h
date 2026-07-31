#pragma once
#include "GameState.h"
#include "Animation.h"
class JumpScareState :
    public GameState
{
private:
    Animation jumpScareAnimation;
    sf::Sprite sprite;
    float startTime = 0;
public:
    JumpScareState(sf::Texture &texture, const std::unordered_map<std::string, float> & configData, sf::Vector2f windowSize);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void handleInputs() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    std::string isFinished() override;
    std::string nextState = "";
};

