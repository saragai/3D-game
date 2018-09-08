/*
new_game.cpp

(c) 2018 Saragai Takanori
*/

#include "new_game.h"

NewGame::NewGame()
{

}

NewGame::~NewGame()
{
	ReleaseAll();
}

void NewGame::Initialize(HWND hWnd)
{
	Game::Initialize(hWnd);
	return;
}

void NewGame::Update()
{

}

void NewGame::Ai()
{

}

void NewGame::Collide()
{

}

void NewGame::Render()
{

}

void NewGame::ReleaseAll()
{
	Game::ReleaseAll();
	return;
}

void NewGame::ResetAll()
{
	Game::ResetAll();
	return;
}