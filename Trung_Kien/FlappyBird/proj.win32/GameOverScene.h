#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameOverScene : public cocos2d::Scene 
{
public:
	static Scene* createScene(int score);
	virtual bool init();
	CREATE_FUNC(GameOverScene);
};

