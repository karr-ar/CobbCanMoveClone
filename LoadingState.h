#pragma once
#include "GameState.h"
#include "Challenges.h"

class ChallengeAnimation {
	bool start = false;
	float timeDiffBetweenEachChar;
	std::vector <sf::Text> characters;
	sf::Color color;
	float time = 0;
	float prevTime = 0;
	int characterTransparencyRemover = -1;

public:
	ChallengeAnimation(Challenges challenge, sf::Font& pressStartFont, float timeDiffBetweenEachChar, sf::Vector2f position, int size, sf::Color color) {
		this->timeDiffBetweenEachChar = timeDiffBetweenEachChar;
		this->color = color;

		std::string text;
		if (challenge == Challenges::CobbCanMove) text = "Move";
		else if (challenge == Challenges::CobbCanChase) text = "Chase";
		else if (challenge == Challenges::CobbCanDuplicate) text = "Duplicate";
		else if (challenge == Challenges::CobbCanHear) text = "Hear";
		else if (challenge == Challenges::CobbCanSee) text = "See";
		else if (challenge == Challenges::CobbCanSmell) text = "Smell";
		else if (challenge == Challenges::CobbDuplicateX2) text = "Duplicate x 2";
		else if (challenge == Challenges::YouCanFreeze) text = "Freeze";
		else if (challenge == Challenges::YouCanStarve) text = "Starve";

		for (int i = 0;i < text.size();i++) {
			characters.push_back(sf::Text(pressStartFont));
			characters[i].setString(text[i]);
			characters[i].setCharacterSize(size);
			characters[i].setFillColor(sf::Color::Transparent);
			characters[i].setPosition({ position.x + i * size,position.y });
		}
	}
	void update(float dt) {
		if (start) {
			time += dt;
			if (abs(time - prevTime) >= timeDiffBetweenEachChar) {
				prevTime += timeDiffBetweenEachChar;
				characterTransparencyRemover++;
				if (characterTransparencyRemover < characters.size()) characters[characterTransparencyRemover].setFillColor(color);
				else start = false;
			}
		}
	}
	void draw(sf::RenderWindow& window) {
		for (int i = 0;i < characters.size();i++) {
			window.draw(characters[i]);
		}
	}
	void setStart() {
		start = true;
	}
};


class LoadingState :
    public GameState
{
public:
    LoadingState(sf::Vector2f windowSize, sf::Font& pressStartFont , int level , std::unordered_map<Challenges, bool> &challenges);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    void handleInputs() override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    std::string isFinished() override;

private:
    std::vector<sf::Text> levelText;
    sf::Vector2f levelTextBaseLocation;
    float time = 0;

    std::vector<sf::Text> challengeText;
    float timeGapBetweenEachChallengeText = 1;
    float prevTime = 0;
    int challengeTransparencyRemover = -1;

	std::vector<ChallengeAnimation> challengeText2;

    sf::Text pressToContinue;
    bool listenForAnyEvent = false;

    std::string nextState = "";
};

