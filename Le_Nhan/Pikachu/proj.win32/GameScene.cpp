#include "GameScene.h"
#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Board.h"
#include <vector>
#include "GameOverScene.h"
#include "BoardView.h"
using namespace std;


Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init()) return false;


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto game_background = CSLoader::getInstance()->createNode("csb/GameScene.csb");

	this->addChild(game_background);

	//return Menu Game
	auto return_main_menu = game_background->getChildByName<ui::Button*>("return_main_menu");
	return_main_menu->setPressedActionEnabled(true);
	return_main_menu->addClickEventListener([=](Ref*)-> void
		{
			Director::getInstance()->replaceScene(TransitionFade::create(0.75, MainMenuScene::createScene(), Color3B(0, 255, 255)));
		});

	//exit game
	auto exit_game = game_background->getChildByName<ui::Button*>("exit_button");
	exit_game->setPressedActionEnabled(true);
	exit_game->addClickEventListener([=](Ref*)-> void
		{
			Director::getInstance()->end();
		});

	showBoard();


	showProgressTimer();

	CCLOG("%d ta la sieu nhan", dem_pokemon);

	BoardView view;



	return true;
}

Layer* GameScene::showBoard()
{
	vector<int> count(16, 4);
	Board* board = new Board(8, 8, 16, count);
	auto boardView = BoardView::createBoardView(board);
	this->addChild(boardView, 1);
	float x = (Director::getInstance()->getVisibleSize().width - boardView->getContentSize().width) / 2;
	float y = (Director::getInstance()->getVisibleSize().height - boardView->getContentSize().height) / 2;

	boardView->setPosition(x, y);
	return boardView;
}

void GameScene::showProgressTimer()
{



	auto visibleSize = Director::getInstance()->getVisibleSize();
	//auto board = boardView->getBoundingBox();
	auto progressTimer = ProgressTimer::create(Sprite::create("ProgressBar.png"));
	progressTimer->setType(ProgressTimer::Type::BAR);
	progressTimer->setMidpoint(Vec2(0.0f, 0.5f));
	progressTimer->setBarChangeRate(Vec2(1.0f, 0.0f));
	progressTimer->setPercentage(100);
	progressTimer->setScaleX(1);
	progressTimer->setScaleY(1);
	//progressTimer->setPosition(visibleSize.width / 2, boardView->getBoundingBox().getMinY() / 2);
	progressTimer->setPosition(visibleSize.width / 2, visibleSize.height*0.03);
	this->addChild(progressTimer);
	progressTimer->runAction(ProgressFromTo::create(100, 100, 0));
	progressTimer->scheduleOnce(schedule_selector(GameScene::GoToGameOver), 100);
}

void GameScene::GoToGameOver(float dt)
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.25, scene));
}


void GameScene::GetDemCountRemovePokemon()
{
	//dem_pokemon = view_board.dem;
}