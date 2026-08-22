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

class PlayingState : public GameState {
public:
    PlayingState(const std::unordered_map<std::string, float>& configData, sf::Vector2f windowSize,
                                                ResourceHolder<TextureID, sf::Texture>& textureHolder);
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


private:
    std::unordered_map<std::string, float> configData; // this state's own copy/reference
    sf::Vector2f windowSize;
    sf::View view;

    std::unique_ptr<Player> player;
    std::unique_ptr<Map> map;
    std::unique_ptr<Cobb> cobb;
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
};