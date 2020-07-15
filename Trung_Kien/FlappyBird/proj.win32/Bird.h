#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Bird
{
	Size visibleSize;
	Vec2 origin;
	Sprite* bird;
public:
	Bird(Scene *scene);
	void fly();
};

