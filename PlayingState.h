#pragma once
#include "GameState.h"
#include "Player.h"
#include "Map.h"
#include "Cobb.h"
#include "Item.h"
#include "Candle.h"
#include <unordered_map>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.h"
#include "Furnace.h"
#include "Smell.h"
#include "SurvivalStat.h"
#include "Breaker.h"
#include "Challenges.h"

class PauseState {
    sf::FloatRect pauseMenu;
    sf::FloatRect continueButton;
    sf::FloatRect exitButton;

    sf::Text continueText;
    sf::Text exitText;

    bool mouseOnContinueButton = false;
    bool mouseOnExitButton = false;

public:
    PauseState(sf::Vector2f windowSize, sf::Font& pressStartFont):continueText(pressStartFont), exitText(pressStartFont) {

        float menuWidth = 300;
        float menuHeight = 350;

        float startX = windowSize.x / 2 - menuWidth/2;
        float startY = windowSize.y / 2 - menuHeight/2;

        pauseMenu = sf::FloatRect({startX,startY}, {menuWidth,menuHeight});
        
        float buttonWidth = 200;
        float buttonHeight = 50;

        startX = windowSize.x / 2 - buttonWidth/2;
        startY = windowSize.y / 2 - buttonHeight/2 - 50 ;
        float spacing = 50;

        continueButton = sf::FloatRect({ startX,startY }, { buttonWidth, buttonHeight });
        exitButton = sf::FloatRect({ startX,startY + continueButton.size.y + spacing }, { buttonWidth, buttonHeight });

        continueText.setString("Resume");
        continueText.setCharacterSize(10);
        continueText.setOrigin(continueText.getLocalBounds().getCenter());
        continueText.setPosition(continueButton.getCenter());

        exitText.setString("Exit");
        exitText.setCharacterSize(10);
        exitText.setOrigin(exitText.getLocalBounds().getCenter());
        exitText.setPosition(exitButton.getCenter());
    }
    
    std::string handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        mouseOnExitButton = false;
        mouseOnContinueButton = false;

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

        if (exitButton.contains(mousePos)) {
            mouseOnExitButton = true;
        }
        if (continueButton.contains(mousePos)) {
            mouseOnContinueButton = true;
        }

        if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mp->button == sf::Mouse::Button::Left) {
                if (mouseOnContinueButton) return "continue";
                if (mouseOnExitButton) return "quit";
            }
        }
        return "";
    }

    void draw(sf::RenderWindow& window) {
        sf::RectangleShape pausemenu(pauseMenu.size);
        pausemenu.setFillColor(sf::Color::Black);
        pausemenu.setOutlineColor(sf::Color::Blue);
        pausemenu.setPosition(pauseMenu.position);
        pausemenu.setOutlineThickness(4.f);
        window.draw(pausemenu);

        sf::RectangleShape continueBox(continueButton.size);
        continueBox.setOrigin({ continueButton.size.x / 2.f, continueButton.size.y / 2.f });
        continueBox.setPosition({
        continueButton.position.x + continueButton.size.x / 2.f,
        continueButton.position.y + continueButton.size.y / 2.f
            });
        if (mouseOnContinueButton) continueBox.setScale({ 1.1,1 });
        else continueBox.setScale({ 1,1 });
        continueBox.setFillColor(sf::Color::Transparent);
        continueBox.setOutlineColor(sf::Color::White);
        continueBox.setOutlineThickness(2.f);
        window.draw(continueBox);

        sf::RectangleShape quitBox(exitButton.size);
        quitBox.setOrigin({ exitButton.size.x / 2.f, exitButton.size.y / 2.f });
        quitBox.setPosition({
        exitButton.position.x + exitButton.size.x / 2.f,
        exitButton.position.y + exitButton.size.y / 2.f
            });
        if (mouseOnExitButton) quitBox.setScale({ 1.1,1 });
        else quitBox.setScale({ 1,1 });
        quitBox.setFillColor(sf::Color::Transparent);
        quitBox.setOutlineColor(sf::Color::White);
        quitBox.setOutlineThickness(2.f);
        window.draw(quitBox);

        window.draw(continueText);
        window.draw(exitText);
    }
};

class PlayingState : public GameState {
public:
    PlayingState(const std::unordered_map<std::string, float>& configData, sf::Vector2f windowSize,  ResourceHolder<TextureID,
        sf::Texture>& textureHolder, int noOfCoals, int noOfBreakers , sf::Font& pressStartFont , Maps mapp , std::unordered_map<Challenges, bool> &challenges);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void handleInputs() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    std::string isFinished() override;

private:
    bool checkCollision(sf::FloatRect first, sf::FloatRect second);
    void playerWallCollision(bool x_y);
    void spawnItems();
    void drawItems(sf::RenderWindow& window);
    void updateItems(float dt);
    bool calculateCobbCanSee();
    void workOnCobbCanHear();
    sf::Texture generateLightMask(int radius);
    void deleteItems();

    void updateEscalator(float dt);
    void drawEscalator(sf::RenderWindow &window);
    void escalatorMovesAnythingOnIt();

    void addScent();
    void updateScent(float dt);
    void deleteScent();

    void spawnHungerSystem();
    void drawHungerSystem(sf::RenderWindow &window);
    void updateHungerSystem(float dt);

    void spawnTemperatureSystem();
    void drawTemperatureSystem(sf::RenderWindow& window);
    void updateTemperatureSystem(float dt);

    //possible deaths
    void playerFreezesOrDiesOfHunger();
    void playerCobbCollision();
    void furnaceBurns();         // this one is not only for player but also for items

    void spawnBreakers();
    void drawBreakers(sf::RenderWindow& window);
    void updateBreakers(float dt);
    void playerBreakerCollision();

    void tasksCompleted();

private:
    std::unordered_map<std::string, float> configData; // this state's own copy/reference
    sf::Vector2f windowSize;
    sf::View view;

    std::unique_ptr<Player> player;
    std::unique_ptr<Map> map;
    // only incase of duplicate  size will be > 1
    std::vector<std::unique_ptr<Cobb>> cobbs;

    std::vector<std::unique_ptr<Item>> items;
    std::unique_ptr < std::vector <Escalator>> escalator =nullptr;
    std::unique_ptr <Furnace> furnace = nullptr;

    std::vector<std::unique_ptr <SurvivalStat>> hunger;
    float foodEatenValue = 0;
    float hunger_decreased_by_carrot;
    float hunger_max_value;
    int noOfImagesOfFood;


    std::vector<std::unique_ptr <SurvivalStat>> temperature;
    bool freezingMode = false;
    float temperature_max_value;
    int noOfImagesOfSnowFlake;

    sf::RenderTexture lightMapTexture;
    //std::vector<sf::Vector2f> darknessPockets;
    sf::Texture lightMaskTexture;

    ResourceHolder<TextureID, sf::Texture>& textureHolder;

    std::string gameOver = ""; //shouldnt be simple and plain like this i gotta work for different animations on different deaths

    std::vector<std::unique_ptr<Smell>> scent;


    //everything related to coals and breakers 
    sf::Font& pressStartFont;
    int noOfCoals;
    int noOfBreakers;
    int noOfCoalsBurned = 0;
    int noOfBreakersFlipped =0;
    sf::Text coalText;
    sf::Text breakerText;
    std::vector <Breaker> breakers;

    std::unordered_map<Challenges, bool> challenges;

    bool gamePause = false;
    PauseState pauseState;

};