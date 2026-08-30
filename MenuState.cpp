#include "MenuState.h"
MenuState::MenuState(const std::unordered_map<std::string, float>& configData, sf::Vector2f windowSize,
    ResourceHolder<TextureID, sf::Texture>& textureHolder, sf::Font& pressStartFont) : titleText(pressStartFont), continueText(pressStartFont) , quitText(pressStartFont) ,versionText (pressStartFont) {

    float buttonWidth = 230.f;
    float buttonHeight = 60.f;
    float startX = 40.f;
    float startY = windowSize.y * 0.42f;
    float spacing = 20.f;

    continueButton = sf::FloatRect({ startX, startY }, { buttonWidth, buttonHeight });
    quitButton = sf::FloatRect({ startX, startY + (buttonHeight + spacing) }, { buttonWidth, buttonHeight });

    titleText.setString("COBB\nCAN\nMOVE\nClone");
    titleText.setCharacterSize(40);
    titleText.setPosition({ startX, 60.f });

    titleBasePos = titleText.getPosition();

    versionText.setString("v1.0"); //pull from save file
    versionText.setCharacterSize(12);
    versionText.setPosition({ startX + 40 * 5, 60.f * 4});

    continueText.setString("Continue\nLevel 3"); // pull actual level from save data later
    continueText.setCharacterSize(18);
    sf::FloatRect textRect = continueText.getLocalBounds();
    continueText.setOrigin({
        textRect.position.x + textRect.size.x / 2.f,
        textRect.position.y + textRect.size.y / 2.f
        });
    sf::Vector2f buttonCenter = {
    continueButton.position.x + continueButton.size.x / 2.f,
    continueButton.position.y + continueButton.size.y / 2.f
    };
    continueText.setPosition(buttonCenter);

    quitText.setString("Exit");
    quitText.setCharacterSize(18);
    textRect = quitText.getLocalBounds();
    quitText.setOrigin({
        textRect.position.x + textRect.size.x / 2.f,
        textRect.position.y + textRect.size.y / 2.f
        });
    buttonCenter = {
    quitButton.position.x + quitButton.size.x / 2.f,
    quitButton.position.y + quitButton.size.y / 2.f
    };
    quitText.setPosition(buttonCenter);
}
void MenuState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    mouseOnQuitButton = false;
    mouseOnContinueButton = false;

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    if (quitButton.contains(mousePos)) {
        mouseOnQuitButton = true;
    }
    if (continueButton.contains(mousePos)) {
        mouseOnContinueButton = true;
    }

    if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mp->button == sf::Mouse::Button::Left) {
            if (mouseOnContinueButton) nextState = "continue";
            if (mouseOnQuitButton) nextState = "quit";
        }
    }
}
void MenuState::handleInputs() {
    //nothing here
}
void MenuState::update(float dt) {
    wobbleTime += dt;

    float bobOffset = std::sin(wobbleTime * 2.f) * 5.f; // 2.f = speed, 5.f = pixels of movement
    titleText.setPosition({ titleBasePos.x, titleBasePos.y + bobOffset });
}
void MenuState::render(sf::RenderWindow& window) {
    window.clear();

    sf::RectangleShape continueBox(continueButton.size);
    continueBox.setOrigin({ continueButton.size.x / 2.f, continueButton.size.y / 2.f });
    continueBox.setPosition({
    continueButton.position.x + continueButton.size.x / 2.f,
    continueButton.position.y + continueButton.size.y / 2.f
        });
    if (mouseOnContinueButton) continueBox.setScale({1.1,1});
    else continueBox.setScale({ 1,1 });
    continueBox.setFillColor(sf::Color::Transparent);
    continueBox.setOutlineColor(sf::Color::White);
    continueBox.setOutlineThickness(2.f);
    window.draw(continueBox);

    sf::RectangleShape quitBox(quitButton.size);
    quitBox.setOrigin({ quitButton.size.x / 2.f, quitButton.size.y / 2.f });
    quitBox.setPosition({
    quitButton.position.x + quitButton.size.x / 2.f,
    quitButton.position.y + quitButton.size.y / 2.f
        });
    if (mouseOnQuitButton) quitBox.setScale({ 1.1,1 });
    else quitBox.setScale({ 1,1 });
    quitBox.setFillColor(sf::Color::Transparent);
    quitBox.setOutlineColor(sf::Color::White);
    quitBox.setOutlineThickness(2.f);
    window.draw(quitBox);

    window.draw(titleText);
    window.draw(versionText);
    window.draw(continueText);
    window.draw(quitText);

    window.display();
}
std::string MenuState::isFinished() {
    return nextState;
}