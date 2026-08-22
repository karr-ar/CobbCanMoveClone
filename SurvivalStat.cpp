#include "SurvivalStat.h"

SurvivalStat::SurvivalStat(sf::Texture &texture, sf::Vector2f position, sf::Vector2f firstItemPosition, int no_of_sprites, float maxValue , bool active , bool disappearsAfterIsExhausted) :sprite(texture){

    this->maxValue = maxValue;
    this->no_of_sprites = no_of_sprites;
    this->active = active;

    currentValue = maxValue;
    prevValue = maxValue;

    this->disappearsAfterIsExhausted = disappearsAfterIsExhausted;
    
    frameWidth = texture.getSize().x / no_of_sprites;
    frameHeight = texture.getSize().y;

    sprite.setPosition(firstItemPosition + sf::Vector2f(position.x*frameWidth, position.y*frameHeight));

    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { frameWidth, frameHeight }));
}
void SurvivalStat::update(float dt) {
    if (active) {
        currentValue -= dt;
        if (!increasingValueMode) {
            if (abs(currentValue - prevValue) > (float)maxValue / no_of_sprites) {
                spriteChooser++;
                prevValue -= (float)maxValue / no_of_sprites;
            }
            if (currentValue <= 0) {
                active = false;
                currentValue = 0;
                spriteChooser = disappearsAfterIsExhausted ? no_of_sprites : no_of_sprites - 1;
            }
        }
        else {
            if (abs(currentValue - prevValue) > (float)maxValue / no_of_sprites) {
                spriteChooser--;
                prevValue += (float)maxValue / no_of_sprites;
            }
            if (currentValue >= maxValue) {
                active = false;
                currentValue = maxValue;
                prevValue = maxValue;
            }
        }
        sprite.setTextureRect(sf::IntRect({ spriteChooser*frameWidth, 0 }, { frameWidth, frameHeight }));
    }
}
void SurvivalStat::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
void SurvivalStat::setActive() {
    active = true;
}
bool SurvivalStat::getActive() {
    return active;
}
void SurvivalStat::reset(int currVal) {
    active = false;
    currentValue = currVal;
    prevValue = maxValue;
    spriteChooser = 0;
    sprite.setTextureRect(sf::IntRect({ spriteChooser * frameWidth, 0 }, { frameWidth, frameHeight }));
}
float SurvivalStat::getCurrentVal() {
    return currentValue;
}

void SurvivalStat::setIncreasingValueMode(bool increasingValueMode) {
    this->increasingValueMode = increasingValueMode;
}