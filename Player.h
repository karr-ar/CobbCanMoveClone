#pragma once
#include "Animation.h"
#include "Entity.h"
class Player :
    public Entity
{
public:
    Player(sf::Vector2f velocity, sf::Vector2f position, sf::Vector2f direction,sf::Texture &texture, sf::Keyboard::Scancode left, sf::Keyboard::Scancode right, 
                                                                                                        sf::Keyboard::Scancode up, sf::Keyboard::Scancode down);
    void setSprite(sf::Texture);
    void draw(sf::RenderWindow &window);
    void update(float dt);
    void inputUpdate();
private:
    sf::Sprite playerSprite;
    sf::Keyboard::Scancode left;
    sf::Keyboard::Scancode right;
    sf::Keyboard::Scancode up;
    sf::Keyboard::Scancode down;

    Animation playerAnimation;
    int spriteRowNo;
};

