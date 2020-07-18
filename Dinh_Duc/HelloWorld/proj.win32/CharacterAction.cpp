#include "cocos2d.h"
#include "CharacterAction.h"

USING_NS_CC;

Size visibleSize = Director::getInstance()->getVisibleSize();

class CharacterAction : public ActionInterval
{
public:
	MoveTo* moveToMiddle = MoveTo::create(1.0f, Point(visibleSize.width / 2, visibleSize.height / 2));
	CallFunc* sayHello = CallFunc::create([] {log("Hello!\n"); });
	JumpTo* jumpToScreenEnd = JumpTo::create(1.0f, Vec2(visibleSize.width - 50, visibleSize.height / 2), 100, 1);
	CallFunc* backToOriginalPosition = CallFunc::create([&] {character->setPosition});
	ScaleBy* growTwoTimes;

}