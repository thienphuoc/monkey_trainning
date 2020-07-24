#pragma once
#include "cocos2d.h"

class Bird
{
public:
	Bird(cocos2d::Layer* layer);

	void moveBird();
private:
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize; 
	cocos2d::Sprite *flappyBird;
};