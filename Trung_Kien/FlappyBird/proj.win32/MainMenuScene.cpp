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


	/*Button *playButton = Button::create("play button.png");
	playButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(playButton);
	playButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		CCLOG("PLay");
		Director::getInstance()->replaceScene(GameScene::createScene());
	});

	Button* leaderboardButton = Button::create("leaderboard.png");
	leaderboardButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, playButton->getPositionY() - playButton->getContentSize().height));
	this->addChild(leaderboardButton);
	leaderboardButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		CCLOG("leaderboardButton");
		Director::getInstance()->replaceScene(leaderboard::createScene());

	});

	Button* inforButton = Button::create("inforButton.png");
	inforButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, leaderboardButton->getPositionY() - leaderboardButton->getContentSize().height));
	this->addChild(inforButton);
	inforButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		CCLOG("inforButton");
	});

	Button* exitButton = Button::create("exitButton.png");
	exitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, inforButton->getPositionY() - inforButton->getContentSize().height));
	this->addChild(exitButton);
	exitButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		CCLOG("exitButton");
		Director::getInstance()->end();
	});

	Button* settingButton = Button::create("settingButton.png");
	settingButton->setAnchorPoint(Vec2(1, 1));
	settingButton->setPosition(Vec2(visibleSize.width, visibleSize.height));
	this->addChild(settingButton);
	settingButton->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		CCLOG("setting");
	});*/


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
	return true;
}
