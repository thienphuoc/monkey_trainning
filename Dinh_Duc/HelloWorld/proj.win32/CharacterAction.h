#pragma once

#include <cocos2d.h>

USING_NS_CC;

Size visibleSize;

class CharacterAction : public ActionInterval
{
public:	
	
	MoveTo* moveToMiddle;
	CallFunc* sayHello;
	JumpTo* jumpToScreenEnd;
	CallFunc* backToOriginalPosition;
	ScaleBy* growTwoTimes;

	
};