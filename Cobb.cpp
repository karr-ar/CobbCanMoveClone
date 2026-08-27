#include "Cobb.h"
#include <iostream>
Cobb::Cobb(sf::Texture& cobbTexture, float velocity, float cobbInvestigationSpeed, float cobbChasingSpeed, sf::Vector2f position, sf::Vector2f direction,float cobbScaledBy, float cobbsVisualRadius
																					, float cobb_smell_radius, float least_score_that_will_enrage_cobb, float searchingTime) :cobbSprite(cobbTexture),
Entity(velocity, position, direction), cobbAnimation(cobbTexture, { 14 }, 0.1, sf::Vector2u(14, 1)) {
	cobbSprite.setTextureRect(cobbAnimation.getXyRect());
	cobbSprite.setOrigin(sf::Vector2f(cobbAnimation.getXyRect().size.x/2, cobbAnimation.getXyRect().size.y / 2));
	cobbSprite.setScale(sf::Vector2f(1.5, 1.5));

	this->cobbNormalSpeed = velocity;
	this->cobbChasingSpeed = cobbChasingSpeed;
	this->cobbInvestigationSpeed= cobbInvestigationSpeed;
	this->cobbScaledBy= cobbScaledBy;   //when cobb is chasing is enabled it gets bigger 
	this->cobbsVisualRadius = cobbsVisualRadius;

	this->cobb_smell_radius = cobb_smell_radius;
	this->least_score_that_will_enrage_cobb = least_score_that_will_enrage_cobb;

	this->searchingTime = searchingTime;

}
void Cobb::setPosition(sf::Vector2f position) {
	Entity::setPosition(position);
	cobbSprite.setPosition(position);
}
void Cobb::followTheGivenPosition(sf::Vector2f position) {
	sf::Vector2f direction( position - getPosition());
	if (direction.x != 0 || direction.y != 0) direction = direction.normalized();

	// Create a 1.5 pixel tolerance zone
	float deadzone = 4;

	if ((position - getPosition()).length() > deadzone) {
		setDirection(direction);
	}
	else {
		setDirection(0, 0);
	}

}
void Cobb::RandomMovement(sf::Vector2f nextRandomPos) {
	if (updateCobbsPosition) {
		cobbsNewLocation = nextRandomPos;

		//sf::Vector2f direction(cobbsNewLocation - this->getPosition());
		//direction = direction.normalized();
		//this->setDirection(direction);


		updateCobbsPosition = false;
		
	}
	followTheGivenPosition(cobbsNewLocation);
	//ive to also add random stops for cobb and fix its sprite too later to stop moving its legs when its stopped.

	
	if (sqrt(pow(getPosition().x-cobbsNewLocation.x,2)+ pow(getPosition().y - cobbsNewLocation.y, 2)) < 5 ){
		updateCobbsPosition = true;
		if ((rand() % 100) < 40) {
			startInvestigation(cobbsNewLocation);
		}
	}
}
sf::Vector2f Cobb::update(float dt) {
	
	cobbAnimation.update(0, dt);
	cobbSprite.setTextureRect(cobbAnimation.getXyRect());
	if (getDirection().x > 0) {
		cobbSprite.setScale(sf::Vector2f(1.5, 1.5));
	}
	else {
		cobbSprite.setScale(sf::Vector2f(-1.5, 1.5));
	}

	if (cobbInvestigates && investState == InvestigationState::Searching) {
		searchTimeCounter -= dt;
	}

	return dt * getDirection() * getVelocity();
}
void Cobb::draw(sf::RenderWindow &window) {
	window.draw(cobbSprite);
}
void Cobb::move(sf::Vector2f offset) {
	setPosition(getPosition()+offset);
}
sf::Sprite Cobb::getCobbSprite() {
	return cobbSprite;
}
void Cobb::UpdateCobbsPosition() {
	updateCobbsPosition = true;
}
void Cobb::cobbCanSee() {
		followTheGivenPosition(lastSeenPosition);
		if ((this->getPosition() - lastSeenPosition).length() < 5) {
			cobbsVisualRetention = false;
			startInvestigation(lastSeenPosition);
	}
}
void Cobb::canCobbSeeThePlayer(sf::Vector2f playerPos, bool isPlayerVisible) {
	if (((this)->getPosition() - (playerPos)).length() <= cobbsVisualRadius && isPlayerVisible) {
		canCobbSee = true;
		lastSeenPosition = playerPos;
		cobbsVisualRetention = true;
	}
	else {
		canCobbSee = false;
	}
}
void Cobb::chooseMovement(sf::Vector2f nextRandomPos) {

	if (canCobbSee || cobbsVisualRetention) {
		this->setVelocity(cobbChasingSpeed);
		cobbCanSee();
	}
	else if (cobbsHearingRetention) {
		this->setVelocity(cobbChasingSpeed);
		cobbFollowsLastHeardPosition();
	}
	else if (scentRetention) {
		if (isCobbEnragedDueToSmell) {
			this->setVelocity(cobbChasingSpeed);
		}
		else {
			this->setVelocity(cobbNormalSpeed);
		}
		cobbFollowsLastSmelledPosition();
	}
	else if (cobbInvestigates) {
		this->setVelocity(cobbInvestigationSpeed);
		cobbsInvestigationMechanics();
	}
	else {
		this->setVelocity(cobbNormalSpeed);
		RandomMovement(nextRandomPos);
	}
}
void Cobb::setCobbsHearingRetention() {
	cobbsHearingRetention = true;
}
void Cobb::setCobbsLastHeardPosition(sf::Vector2f lastHeardPosition) {
	this->lastHeardPosition = lastHeardPosition;
}
void Cobb::cobbFollowsLastHeardPosition(){
	followTheGivenPosition(lastHeardPosition);
	if ((this->getPosition() - lastHeardPosition).length() < 5) {
		cobbsHearingRetention = false;
		startInvestigation(lastHeardPosition);
	}
}
void Cobb::setScentRetentionAndLastPositionSmelled(const std::vector<std::unique_ptr<Smell>>& scent) {
	scentRetention = false;
	isCobbEnragedDueToSmell = false;
	
	if (!scent.empty()) {
		float minDistanceDiffBetweenScentAndCobb= (getPosition()-scent[0]->getPosition()).length();
		int idx = 0;
		for (int i = 1;i < scent.size();i++) {
			if ((getPosition() - scent[i]->getPosition()).length() < minDistanceDiffBetweenScentAndCobb) {
				minDistanceDiffBetweenScentAndCobb = (getPosition() - scent[i]->getPosition()).length();
				idx = i;
			}
		}
		if (minDistanceDiffBetweenScentAndCobb <= cobb_smell_radius) {
			scentRetention = true;
			lastPositionSmelled = scent[idx]->getPosition();
			if (scent[idx]->getScore() >= least_score_that_will_enrage_cobb) {
				isCobbEnragedDueToSmell = true;
			}
		}
	}
	// Design note: Cobb could instead be made to continuously chase the freshest scent
	// by deleting nearby scent points the moment he reaches them (removing the pause
	// entirely). I chose not to do this on purpose -- letting him briefly stand still
	// at the last smelled position, even with a few older scent points still lingering
	// nearby, makes him pause for a beat like he's actually sniffing the air before
	// picking up the next trail, instead of just tracking a point mechanically.
	// This reads as far more unsettling/alive than a smooth, uninterrupted follow.
}
void Cobb::cobbFollowsLastSmelledPosition() {
	followTheGivenPosition(lastPositionSmelled);
	if ((this->getPosition() - lastPositionSmelled).length() < 10) {
		scentRetention = false;
		isCobbEnragedDueToSmell = false;
		startInvestigation(lastPositionSmelled);
	}
}
void Cobb::cobbsInvestigationMechanics() {
	switch (investState) {
	case InvestigationState::Moving:
		followTheGivenPosition(positionToFollow);
		if ((this->getPosition() - positionToFollow).length() < 5) {
			investState = InvestigationState::Searching;
			searchTimeCounter = searchingTime;
		}
		break;
	case InvestigationState::Searching:
		this->setDirection(0.0f, 0.0f);
		if (searchTimeCounter <= 0) {
			investState = InvestigationState::Finished;
		}
		break;
	case InvestigationState::Finished:
		cobbInvestigates = false;
		break;
	}
}
void Cobb::startInvestigation(sf::Vector2f targetPos) {
	positionToFollow = targetPos;
	investState = InvestigationState::Moving;
	searchTimeCounter = searchingTime;
	cobbInvestigates = true;
}