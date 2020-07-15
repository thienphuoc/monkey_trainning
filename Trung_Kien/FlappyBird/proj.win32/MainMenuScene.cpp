#include "MainMenuScene.h"
#include "GameScene.h"
USING_NS_CC;
Scene* MainMenuScene::createScene() {
	return MainMenuScene::create();
}
bool MainMenuScene::init() {
	Sprite* sprite = Sprite::create("background.png");
	this->addChild(sprite);
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite->setPosition(visibleSize.width / 2+origin.x, visibleSize.height / 2+origin.y);
	auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
    };
	keyListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		Director::getInstance()->replaceScene(GameScene::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	return true;
}
