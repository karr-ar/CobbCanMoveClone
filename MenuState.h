#pragma once
#include "GameState.h"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
class MenuState :
    public GameState
{
public:
    MenuState( sf::Vector2f windowSize, sf::Font& pressStartFont , int level);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void handleInputs() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    std::string isFinished() override;

private:
    sf::FloatRect continueButton;
    sf::FloatRect quitButton;

    bool mouseOnContinueButton= false;
    bool mouseOnQuitButton = false;

    sf::Text titleText;
    sf::Text continueText;
    sf::Text quitText;
    sf::Text versionText;

    float wobbleTime = 0.f;
    sf::Vector2f titleBasePos;

    std::string nextState = "";

};

