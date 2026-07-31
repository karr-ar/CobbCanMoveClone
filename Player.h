#pragma once
#include "Animation.h"
#include "Entity.h"
#include "Item.h"
#include "Candle.h"
#include <memory>
#include "Stone.h"
#include "Furnace.h"

class Player :
    public Entity
{
public:
    Player(float velocity, sf::Vector2f position, sf::Vector2f direction,sf::Texture &texture, float playersWalkingNoiseRadius, sf::Keyboard::Scancode left, sf::Keyboard::Scancode right,
                                                                                                        sf::Keyboard::Scancode up, sf::Keyboard::Scancode down, sf::Keyboard::Scancode equip , float escalatorSpeed);
    void setSprite(sf::Texture);
    void draw(sf::RenderWindow &window);
    sf::Vector2f update(float dt);
    void inputUpdate();
    sf::Sprite getPlayerSprite();
    void setPosition(sf::Vector2f);
    void setPosition(float px, float py);
    void move(sf::Vector2f offset);
    sf::Keyboard::Scancode getEquipButton();
    
    void equipItem(std::vector<std::unique_ptr<Item>>& items);
    bool itemPlayerCollision(sf::Sprite itemSprite, sf::Sprite playerSprite);
    void drawPlayersEquippedItem(sf::RenderWindow& window); // bcz this needs to be drawn after the player unlike other items

    void setVisibility(const std::vector<std::unique_ptr<Item>>& items ,const  std::unique_ptr <Furnace> &furnace);
    bool getVisibility();

    bool getIsWalking();
    float getPlayersWalkingNoiseRadius();

    void setDirectionOfStoneHeldByPlayer();

    void setIsOnEscalatorToTrue();

    Item* getItemEquipped();
    void itemEquippedByPlayerJustGotDeletedSoSettingItNull();

private:
    float playerInitialSpeed; // this will come from config file  this will remain constant unlike players actual speed that can change if player is on escalator that speed is handled in entity class

    sf::Sprite playerSprite;
    sf::Keyboard::Scancode left;
    sf::Keyboard::Scancode right;
    sf::Keyboard::Scancode up;
    sf::Keyboard::Scancode down;
    sf::Keyboard::Scancode equip;

    Animation playerAnimation;
    int spriteRowNo;

    Item* itemEquipped =nullptr;
    bool visible = false;

    float playersWalkingNoiseRadius;
    bool isWalking = false;

    bool isOnEscalator = false;

    float escalatorSpeed;
};