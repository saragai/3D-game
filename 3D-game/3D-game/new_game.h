/*
new_game.h

(c) 2018 Saragai Takanori
*/
#pragma once

#include "game.h"

class NewGame : public Game
{
private:

public:
	NewGame();
	virtual ~NewGame();

	void Initialize(HWND hWnd);
	void Update();
	void Ai();
	void Collide();
	void Render();

	void ReleaseAll();
	void ResetAll();
};