#include "Smell.h"
Smell::Smell(sf::Vector2f position, float score) {
	this->position = position;
	this->score = score;
}
void Smell::update(float dt) {
	score -= dt;
	if (score <= 0) toDelete = true;
}
sf::Vector2f Smell::getPosition() {
	return position;
}
float Smell::getScore() {
	return score;
}
bool Smell::getToDelete() {
	return toDelete;
}