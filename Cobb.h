#pragma once
#include "Entity.h"
#include "Animation.h"
#include "cmath"
class Cobb :
    public Entity
{
    sf::Sprite cobbSprite;
    Animation cobbAnimation;
    sf::Vector2f previousPosition;
    bool updateCobbsPosition = true;
    sf::Vector2f cobbsNewLocation;
public:
    Cobb(sf::Texture &cobbTexture, float velocity, sf::Vector2f position, sf::Vector2f direction);
    void setSprite(sf::Texture cobbTexture);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    void inputUpdate(std::vector <sf::Vector2f> cobbsAllowedPositions, int randomPosIndex);
};

