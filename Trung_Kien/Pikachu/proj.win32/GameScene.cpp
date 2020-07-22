#include "GameScene.h"
#include <HelloWorldScene.h>

Scene* GameScene::createScene()
{
	auto gameScene = GameScene::create();
	return gameScene;
}

bool GameScene::init()
{
	// super init()
	if (!Scene::init()) return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto back = MenuItemImage::create("back1.png", "back2.png",
		CC_CALLBACK_1(GameScene::back, this));
	CCASSERT(back != nullptr, "Fail to load BACK images");

	auto menu = Menu::create(back, nullptr);
	this->addChild(menu);
	menu->setPosition(origin);
	back->setPosition(origin + Vec2(back->getContentSize().width / 2, 
									visibleSize.height - back->getContentSize().height / 2));
	
	//Show Board
	showBoard();

	return true;
}

Layer* GameScene::showBoard()
{
	std::vector<int> count(16, 4);
	Board* board = new Board(8, 8, 16, count);
	auto boardView = BoardView::createBoardView(board);
	this->addChild(boardView, 1);
	float x = (Director::getInstance()->getVisibleSize().width - boardView->getContentSize().width) / 2;
	float y = (Director::getInstance()->getVisibleSize().height - boardView->getContentSize().height) / 2;
	boardView->setPosition({x, y});
	return boardView;
}

void GameScene::back(Ref* pSender) {
	auto homeScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(
		TransitionFade::create(0.5, homeScene, Color3B(0, 255, 255)));
}
