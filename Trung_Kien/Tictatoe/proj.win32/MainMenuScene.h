#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
class MainMenuScene :public cocos2d::Scene
{
	bool isSoundOn = true;
public:
	int countSound = 1;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void touchEvent(Ref* sender, Widget::TouchEventType type);
	void volumTouch(Ref* sender, Widget::TouchEventType type,Sprite* sprite,Button* soundButton);
	void volumTouch1(Ref* sender, Widget::TouchEventType type, Sprite* sprite, Button* soundButton1);
	void achiveTouch(Ref* sender, Widget::TouchEventType type);
	CREATE_FUNC(MainMenuScene);
};

