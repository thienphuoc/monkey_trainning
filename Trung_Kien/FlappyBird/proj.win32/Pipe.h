#pragma once
#include "cocos2d.h"
class Pipe
{
public:
	Pipe();
	void spawnPipe(cocos2d::Scene* scene );
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

