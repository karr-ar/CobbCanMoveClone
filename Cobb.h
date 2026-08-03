#pragma once
#include "Entity.h"
#include "Animation.h"
#include "cmath"
#include "Player.h"
#include "Smell.h"
class Cobb :
    public Entity
{
    sf::Sprite cobbSprite;
    Animation cobbAnimation;
    sf::Vector2f previousPosition;
    bool updateCobbsPosition = true;
    sf::Vector2f cobbsNewLocation;
    bool canCobbSee = false;                    // this is to help with make him follow , it doesnt help if level has turned this ability off , gotta work for that seperately
    sf::Vector2f lastSeenPosition;
    bool cobbsVisualRetention = false;

    sf::Vector2f lastHeardPosition;
    bool cobbsHearingRetention = false;

    float cobbInvestigationSpeed;
    float cobbChasingSpeed;
    float cobbScaledBy;
    float cobbsVisualRadius;

    float cobb_smell_radius;
    bool scentRetention = false;
    sf::Vector2f lastPositionSmelled;
    float least_score_that_will_enrage_cobb;
    bool isCobbEnragedDueToSmell = false;

public:
    Cobb(sf::Texture &cobbTexture, float velocity, float cobbInvestigationSpeed, float cobbChasingSpeed, sf::Vector2f position, sf::Vector2f direction, float cobbScaledBy, float cobbsVisualRadius
                                                                        , float cobb_smell_radius , float least_score_that_will_enrage_cobb);
    void setSprite(sf::Texture cobbTexture);
    sf::Vector2f update(float dt);
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);
    void move(sf::Vector2f offset);
    sf::Sprite getCobbSprite();
    void UpdateCobbsPosition();
    void RandomMovement(sf::Vector2f nextRandomPos);
    void cobbCanSee();
    void followTheGivenPosition( sf::Vector2f position);   
    void canCobbSeeThePlayer(sf::Vector2f playerPos,bool isPlayerVisible);
    void chooseMovement(sf::Vector2f nextRandomPos);

    void setCobbsHearingRetention();
    void setCobbsLastHeardPosition(sf::Vector2f lastHeardPosition);
    void cobbFollowsLastHeardPosition();

    void setScentRetentionAndLastPositionSmelled(const std::vector<std::unique_ptr<Smell>> &scent);
    void cobbFollowsLastSmelledPosition();
};

