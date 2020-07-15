#include "GameOverScene.h"
#include "GameScene.h"
int score;
Scene* GameOverScene::createScene(int n) {
	score = n;
	return GameOverScene::create();
}
bool GameOverScene::init() {
	


	Sprite* sprite = Sprite::create("background.png");
	this->addChild(sprite);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	};
	keyListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		Director::getInstance()->replaceScene(GameScene::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);


	__String* tempScore = __String::createWithFormat("%d",score);
	auto label = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label);
	return true;
}
