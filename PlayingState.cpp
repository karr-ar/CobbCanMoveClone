#include "PlayingState.h"
#include <iostream>

PlayingState::PlayingState(const std::unordered_map<std::string, float>& config, sf::Vector2f winSize,ResourceHolder<TextureID, sf::Texture>& textureHolder ,
    int noOfCoals, int noOfBreakers, sf::Font& pressStartFont, Maps mapp, std::unordered_map<Challenges, bool> &challenges)
    : configData(config), windowSize(winSize) ,  textureHolder(textureHolder) ,pressStartFont(pressStartFont), coalText(pressStartFont), breakerText(pressStartFont)
{
    this->noOfCoals = noOfCoals;
    this->noOfBreakers = noOfBreakers;
    this->challenges = challenges;
    
    //load Config Data
    float cobbsNormalSpeed = configData.count("cobbs_normal_speed") ? configData["cobbs_normal_speed"] : 0;
    float cobbsInvestigationSpeed = configData.count("cobbs_investigation_speed") ? configData["cobbs_investigation_speed"] : 0;
    float cobbsChasingSpeed = configData.count("cobbs_chasing_speed") ? configData["cobbs_chasing_speed"] : 0;
    float cobbScaledBy = configData.count("cobbs_scaled_by") ? configData["cobbs_scaled_by"] : 0;
    float cobbsVisualRadius = configData.count("cobbs_visual_radius") ? configData["cobbs_visual_radius"] : 0;

    float least_score_that_will_enrage_cobb = configData.count("least_score_that_will_enrage_cobb") ? configData["least_score_that_will_enrage_cobb"] : 0;
    float cobb_smell_radius = configData.count("cobb_smell_radius") ? configData["cobb_smell_radius"] : 0;
    float searching_time = configData.count("searching_time") ? configData["searching_time"] : 0;

    float playerSpeed = configData.count("players_speed") ? configData["players_speed"] : 0;
    float playerWalkingNoiseRadius = configData.count("players_walking_noise_radius") ? configData["players_walking_noise_radius"] : 0;

    float radiusOfLightMaskTexture = configData.count("radius_of_lightMaskTexture") ? configData["radius_of_lightMaskTexture"] : 0;

    float escalator_speed = configData.count("escalator_speed") ? configData["escalator_speed"] : 0;

    float furnace_glow_radius = configData.count("furnace_glow_radius") ? configData["furnace_glow_radius"] : 0;

    hunger_decreased_by_carrot = configData.count("hunger_decreased_by_carrot") ? configData["hunger_decreased_by_carrot"] : 0;

    // Map initialization
    map = std::make_unique<Map>("sprites/graphics/map.txt", textureHolder.get(TextureID::Wall), textureHolder.get(TextureID::Tile),   //hardcoded map path for now
                               textureHolder.get(TextureID::Wall2), textureHolder.get(TextureID::Grass), textureHolder.get(TextureID::Escalator));  


    //map just helped us create escalator at specified position it wont handle update logic and all for it
    escalator = std::make_unique<std::vector <Escalator>>(map->getEscalator());

    //initializing furnace
    furnace = std::make_unique<Furnace>(Furnace(map->getFurnacePos(), textureHolder.get(TextureID::Furnace), furnace_glow_radius));

    sf::Vector2f playerInitialLoc = map->getPlayerInitialPosition();

    sf::Vector2f cobbInitialLoc = map->getCobbInitialPosition();

    //Player Initialization
    player = std::make_unique<Player>(playerSpeed, playerInitialLoc, sf::Vector2f(0, 0), textureHolder.get(TextureID::Player), playerWalkingNoiseRadius,
        sf::Keyboard::Scancode::A, sf::Keyboard::Scancode::D, sf::Keyboard::Scancode::W, sf::Keyboard::Scancode::S, sf::Keyboard::Scancode::E
                                                                                                                   , escalator_speed);


    //cobb Initialize
    cobbs.push_back( std::make_unique<Cobb>(textureHolder.get(TextureID::Cobb), cobbsNormalSpeed, cobbsInvestigationSpeed, cobbsChasingSpeed, cobbInitialLoc, sf::Vector2f(0, 0), cobbScaledBy, cobbsVisualRadius
                                                                                                        ,cobb_smell_radius,least_score_that_will_enrage_cobb , searching_time, challenges));
    if (challenges.count(Challenges::CobbCanDuplicate) && challenges[Challenges::CobbCanDuplicate]) {
        cobbs.push_back(std::make_unique<Cobb>(textureHolder.get(TextureID::Cobb), cobbsNormalSpeed, cobbsInvestigationSpeed, cobbsChasingSpeed, cobbInitialLoc, sf::Vector2f(0, 0), cobbScaledBy, cobbsVisualRadius
            , cobb_smell_radius, least_score_that_will_enrage_cobb, searching_time, challenges));
    }
    else if (challenges.count(Challenges::CobbDuplicateX2) && challenges[Challenges::CobbDuplicateX2]) {
        cobbs.push_back(std::make_unique<Cobb>(textureHolder.get(TextureID::Cobb), cobbsNormalSpeed, cobbsInvestigationSpeed, cobbsChasingSpeed, cobbInitialLoc, sf::Vector2f(0, 0), cobbScaledBy, cobbsVisualRadius
            , cobb_smell_radius, least_score_that_will_enrage_cobb, searching_time, challenges));
        cobbs.push_back(std::make_unique<Cobb>(textureHolder.get(TextureID::Cobb), cobbsNormalSpeed, cobbsInvestigationSpeed, cobbsChasingSpeed, cobbInitialLoc, sf::Vector2f(0, 0), cobbScaledBy, cobbsVisualRadius
            , cobb_smell_radius, least_score_that_will_enrage_cobb, searching_time, challenges));
    }

    spawnItems();
    spawnBreakers();

    view.setCenter(player->getPosition());
    view.setSize(windowSize);

    if (!lightMapTexture.resize(sf::Vector2u(windowSize.x, windowSize.y))) {
        std::cout << "Critical Error: Failed to create lightmap texture!" << std::endl;
    }
    lightMaskTexture = generateLightMask(radiusOfLightMaskTexture);

    if(challenges.count(Challenges::YouCanStarve)  && challenges[Challenges::YouCanStarve]) spawnHungerSystem();
    if (challenges.count(Challenges::YouCanFreeze) && challenges[Challenges::YouCanFreeze]) spawnTemperatureSystem();

    //setting texts
    if (noOfCoals > 0) {
        coalText.setString("Coals Delivered : " + std::to_string(noOfCoalsBurned) +"/"+ std::to_string(noOfCoals));
        coalText.setCharacterSize(16);
        coalText.setPosition(sf::Vector2f(30,30));
        coalText.setFillColor(sf::Color::White);
    }
    if (noOfBreakers > 0) {
        breakerText.setString("Breakers Flipped : " + std::to_string(noOfBreakersFlipped) + "/" + std::to_string(noOfBreakers));
        breakerText.setCharacterSize(16);
        breakerText.setPosition(sf::Vector2f(30, 60));
        breakerText.setFillColor(sf::Color::White);
    }
    
}
void PlayingState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (const auto* resized = event.getIf<sf::Event::Resized>()) {
        sf::Vector2f newSize((float)resized->size.x, (float)resized->size.y);
        view.setSize(newSize);
        windowSize = newSize;
    }
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == player->getEquipButton()) {
            bool pressedInteractButton = false;
            for (int i = 0; i < breakers.size(); i++) {
                if (breakers[i].getPlayerNearBreaker() && !breakers[i].getFlipped()) {
                    breakers[i].flipBreaker();
                    noOfBreakersFlipped++;
                    pressedInteractButton = true;
                    //cobb must follow this position whenever breaker is flipped without any (radius) condition
                    for (auto & cobb : cobbs) {
                        cobb->setCobbsHearingRetention();
                        cobb->setCobbsLastHeardPosition(breakers[i].getBreakerSprite().getPosition());
                    }
                    break;
                }
            }
            if (!pressedInteractButton) {
                player->equipItem(items);
            }
        }
    }
}
void PlayingState::handleInputs() {
    player->inputUpdate();
    std::vector<sf::Vector2f> cobbsAllowedPositions = map->getCobbsAllowablePositions();
    for (auto& cobb : cobbs) {
       cobb->chooseMovement(cobbsAllowedPositions[rand() % cobbsAllowedPositions.size()]);
    }
}
void PlayingState::update(float dt) {
    sf::Vector2f offsetPlayer = player->update(dt);
    player->move(sf::Vector2f(offsetPlayer.x, 0));
    playerWallCollision(true);
    player->move(sf::Vector2f(0, offsetPlayer.y));
    playerWallCollision(false);

    if (challenges[Challenges::YouCanStarve])  updateHungerSystem(dt);
    if (challenges[Challenges::YouCanFreeze])  updateTemperatureSystem(dt);

    addScent();
    updateScent(dt);
    deleteScent();

    player->setVisibility(items,furnace); // constantlly checks for player being under the light source
    for (auto& cobb : cobbs) {
        cobb->canCobbSeeThePlayer(player->getPosition(), player->getVisibility());
    }
    

    workOnCobbCanHear();
    for (auto& cobb : cobbs) {
        cobb->setScentRetentionAndLastPositionSmelled(scent);

        cobb->move(sf::Vector2f(cobb->update(dt)));
    }
    

    //update escalators sprite
    updateEscalator(dt);

    //update furnace
    furnace->update(dt);

    //check if anythings on furnace
    furnaceBurns();
    //jumpscare
    playerCobbCollision();
    //freeze or starve
    playerFreezesOrDiesOfHunger();

    escalatorMovesAnythingOnIt();

    updateItems(dt);
    deleteItems();

    playerBreakerCollision();
    updateBreakers(dt);

    view.setCenter(player->getPosition()); //for now the camera is rigid but ill fix it  later

    tasksCompleted();

    if (noOfCoals > 0) {
        coalText.setString("Coals Delivered : " + std::to_string(noOfCoalsBurned) + "/" + std::to_string(noOfCoals));
    }
    if (noOfBreakers > 0) {
        breakerText.setString("Breakers Flipped : " + std::to_string(noOfBreakersFlipped) + "/" + std::to_string(noOfBreakers));
    }
}

void PlayingState::render(sf::RenderWindow& window) {
    window.clear();
    window.setView(view);
    map->draw(window);
    drawEscalator(window);
    
    drawItems(window);
    drawBreakers(window);

    player->draw(window);
    player->drawPlayersEquippedItem(window);
    //drawing furnace after everything else cuz even if it takes time to delete it should atleast hide for a while
    furnace->draw(window);
    
    for (auto& cobb : cobbs) {
        cobb->draw(window);
    }
   

    float darknessLevel = configData.count("amount_of_darkness(range[0-255])") ? configData["amount_of_darkness(range[0-255])"] : 0;
    lightMapTexture.clear(sf::Color(0, 0, 0, darknessLevel));
    lightMapTexture.setView(view);


    //sf::CircleShape darknessCloud(100);
    //darknessCloud.setOrigin(sf::Vector2f(350, 350));
    //darknessCloud.setFillColor(sf::Color(0, 0, 0, 245));

    //for (const auto& darkPos : darknessPockets) {
    //	darknessCloud.setPosition(darkPos);
    //	lightMapTexture.draw(darknessCloud);
    //}


    sf::BlendMode eraserblend(sf::BlendMode::Factor::Zero, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add,
        sf::BlendMode::Factor::Zero, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add);
    sf::RenderStates eraser;
    eraser.blendMode = eraserblend;

    sf::Sprite lightGlow(lightMaskTexture);
    lightGlow.setOrigin(sf::Vector2f(lightMaskTexture.getSize().x / 2, lightMaskTexture.getSize().y / 2));

    float radiusOfLightMaskTexture = configData.count("radius_of_lightMaskTexture") ? configData["radius_of_lightMaskTexture"] : 0;

    for (int i = 0; i < items.size(); i++) {
        Candle* candle = dynamic_cast<Candle*>(items[i].get());
        if (candle != nullptr) {
            float scaleFactor = candle->getLuminosityRadius() / radiusOfLightMaskTexture;
            lightGlow.setScale(sf::Vector2f(scaleFactor, scaleFactor));
            lightGlow.setPosition(candle->getPosition());
            lightMapTexture.draw(lightGlow, eraser);
        }
    }

    for (int i = 0; i < items.size(); i++) {
        Stone* stone = dynamic_cast<Stone*>(items[i].get());
        if (stone != nullptr) {
            float scaleFactor = stone->getLuminosityRadius() / radiusOfLightMaskTexture;
            lightGlow.setScale(sf::Vector2f(scaleFactor, scaleFactor));
            lightGlow.setPosition(stone->getPosition());
            lightMapTexture.draw(lightGlow, eraser);
        }
    }

    for (int i = 0; i < items.size(); i++) {
        float scaleFactor = items[i]->getLuminosityRadius() / radiusOfLightMaskTexture;
        lightGlow.setScale(sf::Vector2f(scaleFactor, scaleFactor));
        lightGlow.setPosition(items[i]->getPosition());
        lightMapTexture.draw(lightGlow, eraser);
    }

    for (int i = 0;i < breakers.size();i++) {
        lightGlow.setPosition(breakers[i].getBreakerSprite().getPosition());
        lightMapTexture.draw(lightGlow, eraser);
    }

    float playerGlowRadius = configData.count("players_glow_radius") ? configData["players_glow_radius"] : 0;
    float scaleFactor = playerGlowRadius / radiusOfLightMaskTexture;
    lightGlow.setScale(sf::Vector2f(scaleFactor, scaleFactor));
    lightGlow.setPosition(player->getPosition());
    lightMapTexture.draw(lightGlow, eraser);

    float cobbGlowRadius = configData.count("cobbs_glow_radius") ? configData["cobbs_glow_radius"] : 0;
    scaleFactor = cobbGlowRadius / radiusOfLightMaskTexture;
    lightGlow.setScale(sf::Vector2f(scaleFactor, scaleFactor));
    for (auto& cobb : cobbs) {
        lightGlow.setPosition(cobb->getPosition());
        lightMapTexture.draw(lightGlow, eraser);   
    }

    
    scaleFactor = furnace->getLuminosityRadius() / radiusOfLightMaskTexture;
    lightGlow.setScale(sf::Vector2f(scaleFactor, scaleFactor));
    lightGlow.setPosition(furnace->getPosition() + sf::Vector2f(furnace->getSprite().getTextureRect().size/2));
    lightMapTexture.draw(lightGlow, eraser);

    lightMapTexture.display();
    sf::Sprite lightMapSprite(lightMapTexture.getTexture());
    window.setView(window.getDefaultView());
    window.draw(lightMapSprite);

    drawHungerSystem(window);
    drawTemperatureSystem(window);

    //displaying texts
    window.draw(coalText);
    window.draw(breakerText);

    window.display();
}

std::string PlayingState::isFinished() {
    return gameOver;
}

bool PlayingState::checkCollision(sf::FloatRect first, sf::FloatRect second) {
    return first.findIntersection(second).has_value();
}

void PlayingState::playerWallCollision(bool x_y) { // true for x and false for y
    std::vector<sf::Vector2f> walls = map->getWalls();
    sf::FloatRect playerRect = player->getPlayerSprite().getGlobalBounds();
    for (int i = 0; i < walls.size(); i++) {
        sf::FloatRect wallRect = map->getWallSprite().getGlobalBounds();
        wallRect.position = walls[i] - sf::Vector2f(map->getWallSprite().getTexture().getSize().x / 2, map->getWallSprite().getTexture().getSize().y / 2);
        if (checkCollision(playerRect, wallRect) && x_y) {
            if (player->getDirection().x > 0) {
                player->setPosition(player->getPosition().x - playerRect.findIntersection(wallRect)->size.x, player->getPosition().y);
            }
            else if (player->getDirection().x < 0) {
                player->setPosition(player->getPosition().x + playerRect.findIntersection(wallRect)->size.x, player->getPosition().y);
            }
        }
        if (checkCollision(playerRect, wallRect) && !x_y) {
            if (player->getDirection().y > 0) {
                player->setPosition(player->getPosition().x, player->getPosition().y - playerRect.findIntersection(wallRect)->size.y);
            }
            else if (player->getDirection().y < 0) {
                player->setPosition(player->getPosition().x, player->getPosition().y + playerRect.findIntersection(wallRect)->size.y);
            }
        }
    }
    walls = map->getWalls2();
    player->getPlayerSprite().getGlobalBounds();
    for (int i = 0; i < walls.size(); i++) {
        sf::FloatRect wallRect = map->getWallSprite().getGlobalBounds();
        wallRect.position = walls[i] - sf::Vector2f(map->getWallSprite().getTexture().getSize().x / 2, map->getWallSprite().getTexture().getSize().y / 2);
        if (checkCollision(playerRect, wallRect) && x_y) {
            if (player->getDirection().x > 0) {
                player->setPosition(player->getPosition().x - playerRect.findIntersection(wallRect)->size.x, player->getPosition().y);
            }
            else if (player->getDirection().x < 0) {
                player->setPosition(player->getPosition().x + playerRect.findIntersection(wallRect)->size.x, player->getPosition().y);
            }
        }
        if (checkCollision(playerRect, wallRect) && !x_y) {
            if (player->getDirection().y > 0) {
                player->setPosition(player->getPosition().x, player->getPosition().y - playerRect.findIntersection(wallRect)->size.y);
            }
            else if (player->getDirection().y < 0) {
                player->setPosition(player->getPosition().x, player->getPosition().y + playerRect.findIntersection(wallRect)->size.y);
            }
        }
    }
}

//void Game::spawnDarkness() {
//	std::vector<sf::Vector2f> cobbsAllowedPositions = map->getCobbsAllowablePositions();
//
//	int number_of_dark_zones = 24; // Adjust to make the game harder/easier
//	for (int i = 0; i < number_of_dark_zones; i++) {
//		sf::Vector2f randomPos = cobbsAllowedPositions[rand() % cobbsAllowedPositions.size()];
//		darknessPockets.push_back(randomPos);
//	}

void PlayingState::spawnItems() {
    float escalator_speed = configData.count("escalator_speed") ? configData["escalator_speed"] : 0;


    std::vector<sf::Vector2f>  itemSpawnPositions = map->getItemSpawnPositions();
    float generalItemsEquipNoiseRadius = configData.count("items_equip_noise_radius") ? configData["items_equip_noise_radius"] : 0;
    float generalItemsUnEquipNoiseRadius = configData.count("items_unequip_noise_radius") ? configData["items_unequip_noise_radius"] : 0;
    float general_item_luminosity_radius = configData.count("luminosity_radius") ? configData["luminosity_radius"] : 0;

    //spawning candles 
    int no_of_candles = configData.count("number_of_candles") ? static_cast<int>(configData["number_of_candles"]) : 0;
    float candles_luminosity_radius = configData.count("candles_luminosity_radius") ? configData["candles_luminosity_radius"] : 0;

    for (int i = 0; i < no_of_candles; i++) {
        items.push_back(std::make_unique<Candle>(candles_luminosity_radius, itemSpawnPositions[rand() % itemSpawnPositions.size()], textureHolder.get(TextureID::Candle), generalItemsEquipNoiseRadius, generalItemsUnEquipNoiseRadius,escalator_speed));
    }

    //spawning rocks
    int no_of_rocks = configData.count("number_of_rocks") ? static_cast<int>(configData["number_of_rocks"]) : 0;
    float stones_unequip_noise_radius = 0;         //0 because it can be heard in the entire map and i wont even check the radius when player throws stone as cobb will always follow that position without any radius check
    float stones_initial_upward_velocity = configData.count("stones_initial_upward_velocity") ? configData["stones_initial_upward_velocity"] : 0;
    float stones_downward_acceleration = configData.count("stones_downward_acceleration") ? configData["stones_downward_acceleration"] : 0;
    float stones_horizontal_velocity = configData.count("stones_horizontal_velocity") ? configData["stones_horizontal_velocity"] : 0;

    for (int i = 0; i < no_of_rocks; i++) {
        items.push_back(std::make_unique<Stone>(general_item_luminosity_radius, itemSpawnPositions[rand() % itemSpawnPositions.size()], textureHolder.get(TextureID::Stone), generalItemsEquipNoiseRadius, stones_unequip_noise_radius, stones_initial_upward_velocity, stones_downward_acceleration, stones_horizontal_velocity, escalator_speed));
    }

    //spawning carrots
    int number_of_carrots = configData.count("number_of_carrots") ? static_cast<int>(configData["number_of_carrots"]) : 0;
    for (int i = 0;i < number_of_carrots;i++) {
        items.push_back(std::make_unique<Item>(general_item_luminosity_radius, itemSpawnPositions[rand() % itemSpawnPositions.size()], textureHolder.get(TextureID::Carrot2), generalItemsEquipNoiseRadius, 0, escalator_speed));
        items[items.size() - 1]->setItemType("Carrot");
    }

    //spawning coals
    for (int i = 0;i < noOfCoals;i++) {
        items.push_back(std::make_unique<Item>(general_item_luminosity_radius, itemSpawnPositions[rand() % itemSpawnPositions.size()], textureHolder.get(TextureID::Coal), generalItemsEquipNoiseRadius, generalItemsUnEquipNoiseRadius, escalator_speed));
        items[items.size() - 1]->setItemType("Coal");
    }

    
}
void PlayingState::spawnBreakers() {
    for (int i = 0;i < noOfBreakers;i++) {
        int idx = rand() % map->getBreakerPositions().size();
        breakers.push_back(Breaker(textureHolder.get(TextureID::Breaker), map->getBreakerPositions()[idx]));
        map->deleteBreaker(idx);
    }
}

void PlayingState::drawBreakers(sf::RenderWindow& window) {
    for (int i = 0;i < breakers.size();i++) {
        breakers[i].draw(window);
    }
}

void PlayingState::updateBreakers(float dt) {
    for (int i = 0;i < breakers.size();i++) {
        breakers[i].update(dt);
    }
}

void PlayingState::drawItems(sf::RenderWindow& window) {
    for (int i = 0; i < items.size(); i++) {
        if (!items[i]->getEquipped()) {
            items[i]->draw(window);
        }
    }
}

void PlayingState::updateItems(float dt) {

    //if carrots are equipped delete them
    for (int i = 0; i < items.size(); i++) {
        if (items[i]->getItemType() == "Carrot") {
            if (items[i]->getEquipped()) {
                items[i]->setDeleteItem();
                foodEatenValue += hunger_decreased_by_carrot;
            }
        }
        items[i]->update(dt, player->getPosition());
    }
}

sf::Texture PlayingState::generateLightMask(int radius) {
    int size = 2 * radius;
    sf::Image image;
    image.resize(sf::Vector2u(size, size), sf::Color(255, 255, 255, 0));
    sf::Vector2f center(sf::Vector2f(radius, radius));

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            sf::Vector2f pixelPos(x, y);
            float distance = sqrt((pixelPos.x - center.x) * (pixelPos.x - center.x) + (pixelPos.y - center.y) * (pixelPos.y - center.y));
            if (distance <= radius) {
                float ratio = 1.0f - distance / radius;
                int alpha = 255 * ratio * ratio;
                image.setPixel(sf::Vector2u(x, y), sf::Color(255, 255, 255, alpha));
            }
        }
    }
    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cout << "failed to convert image to texture";
    }
    return texture;
}
void PlayingState::workOnCobbCanHear() {
    for (auto& cobb : cobbs) {
        float closestDist = std::numeric_limits<float>::max();
        sf::Vector2f closestPos;
        bool heard = false;

        for (int i = 0; i < items.size(); i++) {
            if (items[i]->getNoiseActive()) {
                items[i]->setNoiseInactive();

                float dist = (cobb->getPosition() - items[i]->getPosition()).length();

                Stone* stone = dynamic_cast<Stone*>(items[i].get());
                if (stone != nullptr) {
                    // stones heard everywhere — no radius check, always wins
                    closestDist = 0;
                    closestPos = items[i]->getPosition();
                    heard = true;
                    break;
                }

                if (dist <= items[i]->getCurrentNoiseRadius() && dist < closestDist) {
                    closestDist = dist;
                    closestPos = items[i]->getPosition();
                    heard = true;
                }
            }
        }

        if (heard) {
            cobb->setCobbsHearingRetention();
            cobb->setCobbsLastHeardPosition(closestPos);
        }

        if (player->getIsWalking()) {
            float playerDist = (cobb->getPosition() - player->getPosition()).length();
            if (playerDist <= player->getPlayersWalkingNoiseRadius()) {
                if (!heard || playerDist < closestDist) {
                    cobb->setCobbsHearingRetention();
                    cobb->setCobbsLastHeardPosition(player->getPosition());
                }
            }
        }
    }
    
}
void PlayingState::deleteItems() {
    for (int i = 0;i < items.size();i++) {
            if (items[i]->getDeleteItem()) {
                if (player->getItemEquipped()) {
                    player->itemEquippedByPlayerJustGotDeletedSoSettingItNull();
                }
                items.erase(items.begin()+i);
                i--;
            
        }
    }
}
void PlayingState::updateEscalator(float dt) {
    for (int i = 0;i < escalator->size();i++) {
        escalator->at(i).update(dt);
    }
}
void PlayingState::drawEscalator(sf::RenderWindow& window) {
    for (int i = 0;i < escalator->size();i++) {
        escalator->at(i).draw(window);
    }
}
void PlayingState::escalatorMovesAnythingOnIt() {
    for (int i = 0;i < items.size();i++) {
        sf::FloatRect itemRect = items[i]->getSprite().getGlobalBounds();
        for (int j = 0;j < escalator->size(); j++) {
            sf::FloatRect escalatorRect = escalator->at(j).getSprite().getGlobalBounds();
            auto intersection = itemRect.findIntersection(escalatorRect);
            if (intersection.has_value() && intersection->size.x >= itemRect.size.x /1.85f) {
                items[i]->setIsOnEscalatorToTrue();
                break;
            }
        }
    }
    //collision for player
        sf::FloatRect playerRect = player->getPlayerSprite().getGlobalBounds();
        for (int j = 0;j < escalator->size(); j++) {
            sf::FloatRect escalatorRect = escalator->at(j).getSprite().getGlobalBounds();
            auto intersection = playerRect.findIntersection(escalatorRect);
            if (intersection.has_value() && intersection->size.x >= playerRect.size.x / 2.0f ) {
                player->setIsOnEscalatorToTrue();
                break;
            }
        }
}

void PlayingState::addScent() {
    float initial_scent_score = configData.count("initial_scent_score") ? configData["initial_scent_score"] : 0;
    float distance_difference_required_for_new_scent = configData.count("distance_difference_required_for_new_scent") ? configData["distance_difference_required_for_new_scent"] : 0;
    if (player->getIsWalking()) {
        if (scent.empty()) {
            scent.push_back(std::make_unique<Smell>(player->getPosition(), initial_scent_score));
        }
        else if ((player->getPosition() - scent[scent.size() - 1]->getPosition()).length() >= distance_difference_required_for_new_scent) {
            scent.push_back(std::make_unique<Smell>(player->getPosition(), initial_scent_score));
        }
        else {
            //do nothing
        }
    }
}
void PlayingState::updateScent(float dt) {
    for (int i = 0;i < scent.size();i++) {
        scent[i]->update(dt);
    }
}
void PlayingState::deleteScent() {
    float cobb_consuming_scent_radius = configData.count("cobb_consuming_scent_radius") ? configData["cobb_consuming_scent_radius"] : 0;
    for (int i = 0;i < scent.size();i++) {
        for (auto& cobb : cobbs) {
            if (scent[i]->getToDelete() || (scent[i]->getPosition() - cobb->getPosition()).length() <= cobb_consuming_scent_radius) {
                scent[i] = nullptr;
                scent.erase(scent.begin() + i);
                i--;
                break;
            }
        }
    }
}

void PlayingState::spawnHungerSystem() {
    hunger_max_value = configData.count("hunger_max_value") ? configData["hunger_max_value"] : 0;
    noOfImagesOfFood = configData.count("no_of_sprites_in_food_spritesheet") ? static_cast<int>(configData["no_of_sprites_in_food_spritesheet"]) : 0;
    sf::Vector2f firstCarrotPos = sf::Vector2f(windowSize.x/2, windowSize.y/2) - sf::Vector2f(25,50);

    for (int i = 0;i < 3;i++){
        bool active = i == (3 - 1);
        hunger.push_back(std::make_unique<SurvivalStat>(textureHolder.get(TextureID::Carrot), sf::Vector2f(i, 0),firstCarrotPos, noOfImagesOfFood, hunger_max_value / noOfImagesOfFood, active , true));
    }
}
void PlayingState::drawHungerSystem(sf::RenderWindow &window) {
    for (int i = 0;i < hunger.size();i++) {
        hunger[i]->draw(window);
    }
}
void PlayingState::updateHungerSystem(float dt) {
    for (int i = 0;i < hunger.size() ;i++) {
        hunger[i]->update(dt);
        if ( i != hunger.size() - 1 &&  hunger[i + 1]->getCurrentVal() <=0 ) {
            hunger[i]->setActive();
        }
    }
    if (foodEatenValue > 0) {
        int i = 0;
        float segmentMax = hunger_max_value / noOfImagesOfFood;

        while (foodEatenValue > 0 && i < hunger.size()) {
            float remaining = segmentMax - hunger[i]->getCurrentVal(); // capture BEFORE reset

            if (remaining <= 0) {
                // segment already full, nothing to do here
                i++;
                continue;
            }

            if (foodEatenValue >= remaining) {
                hunger[i]->reset(segmentMax);
                foodEatenValue -= remaining;
            }
            else {
                hunger[i]->reset(hunger[i]->getCurrentVal() + foodEatenValue);
                foodEatenValue = 0;
                hunger[i]->setActive();
            }
            i++;
        }
        foodEatenValue = 0; // discard any leftover if hunger is already full
    }
    hunger[hunger.size() - 1]->setActive();
}


void PlayingState::spawnTemperatureSystem() {
    temperature_max_value = configData.count("temperature_max_value") ? configData["temperature_max_value"] : 0;
    noOfImagesOfSnowFlake = configData.count("no_of_sprites_in_temperature_spritesheet") ? static_cast<int>(configData["no_of_sprites_in_temperature_spritesheet"]) : 0;
    sf::Vector2f firstSnowflakePos = sf::Vector2f(windowSize.x / 2, windowSize.y / 2) - sf::Vector2f(20, 70);

    for (int i = 0;i < 3;i++) {
        bool active = i == (0);
        temperature.push_back(std::make_unique<SurvivalStat>(textureHolder.get(TextureID::Snowflake), sf::Vector2f(i, 0), firstSnowflakePos, noOfImagesOfSnowFlake, temperature_max_value / noOfImagesOfSnowFlake,active , false));
    }
}
void PlayingState::drawTemperatureSystem(sf::RenderWindow& window) {
    for (int i = 0;i < temperature.size();i++) {
        temperature[i]->draw(window);
    }
}
void PlayingState::updateTemperatureSystem(float dt) {
    freezingMode = true;
    float segmentMax = temperature_max_value / noOfImagesOfSnowFlake;
    if (player->getVisibility()) {
        freezingMode = false;
    }
    for (int i = temperature.size()-1;i >=0;i--) {
        if (freezingMode) {
            temperature[i]->update(dt);
            if (i != 0 && temperature[i - 1]->getCurrentVal() <= 0) {
                temperature[i]->setActive();
            }
        }
        else {
            temperature[i]->setIncreasingValueMode(true);
            temperature[i]->update(-dt);
            temperature[i]->setIncreasingValueMode(false);
            if ( temperature[i]->getCurrentVal() >= segmentMax) {
                continue;
            }
            else {
                temperature[i]->setActive();
                break;
            }
        }
    }
    if(freezingMode) temperature[0]->setActive();
}

void PlayingState::playerBreakerCollision() {
    sf::Vector2f playerPos = player->getPosition();
    for (int i = 0; i < breakers.size(); i++) {
        float dist = (playerPos - breakers[i].getBreakerSprite().getPosition()).length();
        bool near = dist < 70.f && !breakers[i].getFlipped();
        breakers[i].setHighlight(near);
        breakers[i].setPlayerNearBreaker(near);
    }
}

//covering all possible deaths
// Wherever you compute the hitbox — update the debug shape too
void PlayingState::playerCobbCollision() {
    for (auto& cobb : cobbs) {
        sf::FloatRect playerRect = player->getPlayerSprite().getGlobalBounds();
        sf::FloatRect cobbRect = cobb->getCobbSprite().getGlobalBounds();

        sf::Vector2f center = cobb->getCobbSprite().getPosition();
        sf::Vector2f hitboxSize(cobbRect.size.x * 0.6f, cobbRect.size.y * 0.44f);

        sf::FloatRect cobbHitbox(
            { center.x - hitboxSize.x / 2.f, center.y - hitboxSize.y / 1.65f },
            hitboxSize
        );

        if (playerRect.findIntersection(cobbHitbox)) {
            gameOver = "jumpscare";
        }
    }
}
void PlayingState::playerFreezesOrDiesOfHunger() {
    if (challenges[Challenges::YouCanFreeze] && temperature[temperature.size() - 1]->getCurrentVal() <= 0) {
        gameOver = "froze";
    }
    if (challenges[Challenges::YouCanStarve] && hunger[0]->getCurrentVal() <= 0) {
        gameOver = "starved";
    }
}
void PlayingState::furnaceBurns() {
    sf::FloatRect furnaceRect = furnace->getSprite().getGlobalBounds();
    for (int i = 0;i < items.size();i++) {
        Stone* stone = dynamic_cast<Stone*>(items[i].get());
        if (stone != nullptr && stone->getIsOnAir()) continue;
        sf::FloatRect itemRect = items[i]->getSprite().getGlobalBounds();
        if (itemRect.findIntersection(furnaceRect)) {
            items[i]->setIsOnFurnace();
            if (items[i]->getItemType() == "Coal")noOfCoalsBurned++;
        }
    }
    sf::FloatRect playerRect = player->getPlayerSprite().getGlobalBounds();
    if (playerRect.findIntersection(furnaceRect)) {
        gameOver = "burned";
    }
}

void PlayingState::tasksCompleted() {
    if (noOfCoals == noOfCoalsBurned && noOfBreakers == noOfBreakersFlipped) gameOver = "win";
}