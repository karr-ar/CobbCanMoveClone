#pragma once
class GameState
{
	virtual void handleInputs() =0;
	void update(float dt);
	void render();
};

