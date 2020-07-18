#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
class winner:public cocos2d::Scene
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(winner);
};

