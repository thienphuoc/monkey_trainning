#pragma once
#include "cocos2d.h"
#include "Board.h"
#include "BoardView.h"

USING_NS_CC;

class GameScene : public Scene
{
	Layer* boardView;

public:

	static Scene* createScene();

	virtual bool init();

	Layer* showBoard();

	void back(Ref* pSender);

	void showProgressTimer();

	CREATE_FUNC(GameScene);
};

