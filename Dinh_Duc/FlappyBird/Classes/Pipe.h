#pragma once

#include "cocos2d.h"

class Pipe
{
public:
	Pipe();

	void spawnPipe(cocos2d::Layer *layer);

private:
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
};
