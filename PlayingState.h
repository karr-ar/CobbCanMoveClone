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

class PlayingState : public GameState {
public:
    PlayingState(const std::unordered_map<std::string, float>& configData, sf::Vector2f windowSize,
                                                ResourceHolder<TextureID, sf::Texture>& textureHolder);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void handleInputs() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    bool checkCollision(sf::FloatRect first, sf::FloatRect second);
    void playerWallCollision(bool x_y);
    void spawnItems();
    void drawItems(sf::RenderWindow& window);
    void updateItems(float dt);
    bool calculateCobbCanSee();
    void workOnCobbCanHear();
    sf::Texture generateLightMask(int radius);
    void deleteStones();

    void updateEscalator(float dt);
    void drawEscalator(sf::RenderWindow &window);
    void escalatorMovesAnythingOnIt();

private:
    std::unordered_map<std::string, float> configData; // this state's own copy/reference
    sf::Vector2f windowSize;
    sf::View view;

    std::unique_ptr<Player> player;
    std::unique_ptr<Map> map;
    std::unique_ptr<Cobb> cobb;
    std::vector<std::unique_ptr<Item>> items;
    std::unique_ptr < std::vector <Escalator>> escalator =nullptr;

    sf::RenderTexture lightMapTexture;
    //std::vector<sf::Vector2f> darknessPockets;
    sf::Texture lightMaskTexture;

    ResourceHolder<TextureID, sf::Texture>& textureHolder;
};