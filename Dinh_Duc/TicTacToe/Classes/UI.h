#pragma once

#include "cocos2d.h"

class UI
{
public:
	UI(cocos2d::Layer* layer, int &gameState);

	void showGameOver(cocos2d::Layer* layer);

private:
	void retry(cocos2d::Ref* pSender);
	void goToMainMenu(cocos2d::Ref* pSender);
	void pauseGame(cocos2d::Ref* pSender);

	int* gameState;

	cocos2d::Menu* pauseMenu;
	cocos2d::Sprite* pauseBackground;
};

