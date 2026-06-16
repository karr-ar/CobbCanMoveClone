#include "Animation.h"
Animation::Animation(sf::Texture texture, std::vector<int> spritesPerRow, float switchTime, sf::Vector2u maxImageCount) {
	this->spritesPerRow = spritesPerRow;
	this->switchTime = switchTime;
	this->maxImageCount = maxImageCount;
	totalTime = 0;
	currentImage.x = 0;

	xyRect.size.x = texture.getSize().x / float(maxImageCount.x);
	xyRect.size.y = texture.getSize().y / float(maxImageCount.y);
}
void Animation::update(int row, float dt) {
	currentImage.y = row;
	totalTime += dt;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= spritesPerRow[row]) {
			currentImage.x = 0;
		}
	}
	xyRect.position.x = xyRect.size.x * currentImage.x;
	xyRect.position.y = xyRect.size.y * currentImage.y;
}
sf::IntRect Animation::getXyRect() {
	return xyRect;
}