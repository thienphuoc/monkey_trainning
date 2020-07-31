#include "GameScene.h"
#include "HelloWorldScene.h"

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


	auto back = MenuItemImage::create("back1.png", "back1.png",
		CC_CALLBACK_1(GameScene::back, this));
	CCASSERT(back != nullptr, "Fail to load BACK images");

	auto menu = Menu::create(back, nullptr);
	this->addChild(menu);
	menu->setPosition(origin);
	back->setPosition(origin + Vec2(back->getContentSize().width / 2, 
									visibleSize.height - back->getContentSize().height / 2));
	
	//Show Board
	showBoard();
	showProgressTimer();
	return true;
}

Layer* GameScene::showBoard()
{
	/*std::vector<int> count(16, 4);
	Board* board = new Board(8, 8, 16, count);
	Ở đây  tạo một bảng 8x8, tổng cộng là 64 ô pokemon, có 16 loại pokemon khác nhau, mỗi loại xuất hiện 4 lần trong bảng*/
	std::vector<int> count(24, 6);
	Board* board = new Board(12,12 , 24, count);
	auto boardView = BoardView::createBoardView(board);
	this->addChild(boardView, 1);
	float x = (Director::getInstance()->getVisibleSize().width - boardView->getContentSize().width) / 2;
	float y = (Director::getInstance()->getVisibleSize().height - boardView->getContentSize().height) / 2;
	boardView->setPosition({x, y+50});
	return boardView;
}

void GameScene::back(Ref* pSender) {
	auto homeScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(
		TransitionFade::create(0.5, homeScene, Color3B(0, 255, 255)));
}

void GameScene::showProgressTimer()
{
	auto screenSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//auto board = boardView->getBoundingBox();

	auto progressTimer = ProgressTimer::create(Sprite::create("ProgressBar.png"));
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Vec2(0.0f, 0.5f));
	progressTimer->setBarChangeRate(Vec2(1.0f, 0.0f));
	progressTimer->setPercentage(100);
	progressTimer->setScale(0.4);
	progressTimer->setPosition(screenSize.width/2,screenSize.height+origin.y);
	this->addChild(progressTimer,2);
	progressTimer->runAction(ProgressFromTo::create(600, 100, 0));

	this->scheduleOnce([=](float dt) {
		CCLOG("gaaaaaaaaa");
		Director::getInstance()->replaceScene(HelloWorld::createScene());
		//progressTimer->pause();
	}, 600, "progressTimerOnFinished");

	//this->unschedule("progressTimerOnFinished");
	
}
