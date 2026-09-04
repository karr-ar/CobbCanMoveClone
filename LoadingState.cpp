#include "LoadingState.h"

LoadingState::LoadingState(sf::Vector2f windowSize, sf::Font& pressStartFont, int level, std::unordered_map<Challenges, bool>& challenges) :pressToContinue(pressStartFont) {

	float startX = 40.f;
	float startY = windowSize.y * 0.2f;
	float spacing = 20.f;

	std::string text = "level " + std::to_string(level) + "/7";
	int i = 0;
	for (char c : text) {
		levelText.push_back(sf::Text(pressStartFont));
		levelText[i].setString(c);
		levelText[i].setCharacterSize(30);
		levelText[i].setPosition({ startX + i * 30, startY });
		i++;
	}
	levelTextBaseLocation = {startX,startY};

	int charSize = 30;
	for (const auto& pair : challenges) {
			challengeText.push_back(sf::Text(pressStartFont));
			int i = challengeText.size() - 1;
			challengeText[i].setCharacterSize(charSize);
			challengeText[i].setFillColor(sf::Color::Transparent);
			challengeText[i].setPosition({startX, startY + levelText[0].getCharacterSize() + 3*spacing + i*(spacing + charSize)});
			if (pair.first == Challenges::YouCanFreeze || pair.first == Challenges::YouCanStarve) {
				challengeText[i].setString("You Can ");
			}
			else {
				challengeText[i].setString("Cobb Can ");
			}
			sf::FloatRect bounds = challengeText[i].getGlobalBounds();
			float text2X = bounds.position.x + bounds.size.x;
			float text2Y = challengeText[i].getPosition().y;

			challengeText2.push_back(ChallengeAnimation(pair.first, pressStartFont, 0.2f, { text2X, text2Y }, 25, sf::Color::Red));
	}

	pressToContinue.setCharacterSize(17);
	pressToContinue.setFillColor(sf::Color::Transparent);
	pressToContinue.setString("Press Any Button To Continue");
	pressToContinue.setPosition({startX,  startY + levelText[0].getCharacterSize() + 5 * spacing + challengeText.size() * (spacing + charSize) });

}
void LoadingState::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	if (!listenForAnyEvent) return; // ignore input until the reveal is done

	if (event.is<sf::Event::KeyPressed>() || event.is<sf::Event::MouseButtonPressed>()) {
		nextState = "playing"; 
	}
}
void LoadingState::handleInputs() {

}
void LoadingState::update(float dt) {
	time += dt;

	for (int i = 0;i < levelText.size();i++) {
		if (i % 2 == 0) {
			float bobOffset = std::sin(time * 4.f ) * 5.f;
			levelText[i].setPosition({ levelTextBaseLocation.x +i*30, levelTextBaseLocation.y + bobOffset});
		}
		else {
			float bobOffset = std::sin(time * 2.5f) * 5.f;
			levelText[i].setPosition({ levelTextBaseLocation.x + i * 30, levelTextBaseLocation.y + bobOffset });
		}
	}

	for (int i = 0;i < challengeText2.size();i++) {
		challengeText2[i].update(dt);
	}

	if (abs(time - prevTime) >= timeGapBetweenEachChallengeText) {
		prevTime += timeGapBetweenEachChallengeText;
		challengeTransparencyRemover++;
		if (challengeTransparencyRemover < challengeText.size()) {
			challengeText[challengeTransparencyRemover].setFillColor(sf::Color::White);
			challengeText2[challengeTransparencyRemover].setStart();
		}
		else {
			listenForAnyEvent = true;
			pressToContinue.setFillColor(sf::Color::Yellow);
		}
	}
}
void LoadingState::render(sf::RenderWindow& window) {
	window.clear();
	for (int i = 0;i < levelText.size();i++) {
		window.draw(levelText[i]);
	}
	for (int i = 0;i < challengeText.size();i++) {
		window.draw(challengeText[i]);
	}
	for (int i = 0;i < challengeText2.size();i++) {
		challengeText2[i].draw(window);
	}
	window.draw(pressToContinue);
	window.display();
}
std::string LoadingState::isFinished() {
	return nextState;
}