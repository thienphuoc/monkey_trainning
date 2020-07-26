#pragma once

#include "cocos2d.h"
#include "Board.h"
#include "BoardView.h"
#include "MainMenuScene.h"
using namespace std;

USING_NS_CC;

class GameScene : public Scene
{
	
	Layer* boardView;
	ProgressTimer* progressTimer;

public:
	unsigned int dem_pokemon = 0;
	unsigned int count_click_pause_game = 0;
	//BoardView* view_board;
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	Layer* showBoard(Node* game_background);
	void showProgressTimer();

	void GetDemCountRemovePokemon();

	void GoToGameOver(float dt);
	Layer* FadeOutBoard();

	CREATE_FUNC(GameScene);




};
