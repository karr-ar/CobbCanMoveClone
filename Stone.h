#pragma once
#include "Item.h"
#include "Animation.h"
class Stone :
    public Item
{
    float initialUpwardVelocity;
    float downwardAcceleration;
    float horizontalVelocity;

private:
    float UpwardVelocity=0;
    sf::Vector2f unequipLocation;
    bool _jump = false;
    bool onAir = false;
    bool ReadyForDestructionNoise = false;

    int horizontalDirection = -1;

    Animation stoneDestructionAnimation;
    bool displayDestructionAnimation = false;
    float destructionTimer = 0.5f;

public:
    Stone(float luminosityRadius, sf::Vector2f position, sf::Texture& texture, float equipNoiseRadius, float unequipNoiseRadius , 
        float initialUpwardVelocity, float downwardAcceleration, float horizontalVelocity , float escalator_speed);
    void jump();
    void update(float dt ,sf::Vector2f playerPosition) override;
    void setJump();
    void unequip() override;
    void setHorizontalDirection(int x);
    bool getIsOnAir();
};

