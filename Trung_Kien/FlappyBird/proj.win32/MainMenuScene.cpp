#include "MainMenuScene.h"
#include "GameScene.h"
#include "leaderboard.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace ui;
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





	auto mainMenuButton = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
	this->addChild(mainMenuButton);

	auto playButton = mainMenuButton->getChildByName<Button*>("playButton");
	playButton->addClickEventListener([](Ref*) {
		CCLOG("play");
		Director::getInstance()->replaceScene(GameScene::createScene());
	});

	auto leaderBoardButton = mainMenuButton->getChildByName<Button*>("leaderBoardButton");
	leaderBoardButton->addClickEventListener([](Ref*) {
		CCLOG("leaderBoardButton");
		Director::getInstance()->replaceScene(leaderboard::createScene());
	});
	auto aboutButton = mainMenuButton->getChildByName<Button*>("aboutButton");
	aboutButton->addClickEventListener([](Ref*) {
		CCLOG("aboutButton");
	});
	auto exitButton = mainMenuButton->getChildByName<Button*>("exitButton");
	exitButton->addClickEventListener([](Ref*) {
		CCLOG("exitButton");
		Director::getInstance()->end();
	});
	auto settingField = mainMenuButton->getChildByName<ImageView*>("settingField");
	auto settingsButton = mainMenuButton->getChildByName<Button*>("settingsButton");
	settingsButton->addClickEventListener([=](Ref*) {
		CCLOG("settingsButton");
		settingField->setVisible(true);
	});
	return true;
}
