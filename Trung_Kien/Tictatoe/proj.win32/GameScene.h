#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
class GameScene : public cocos2d::Scene
{
public:
	int turn=0;
	int digitMap[3][3];
	Sprite* spriteMap[3][3];
	Button* buttonMap[3][3];
	void loadMap(Sprite* sprite, int digitMap[][3], Size sizeBox);
	int tick(Button* buttonMap[][3], Size size, int i, int j, int digitMap[][3]);
	int checkXwin();
	int checkYwin();
	int check(int i,int j);
	int check1();
	int check2();
	void initDigitMap();


	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
};
