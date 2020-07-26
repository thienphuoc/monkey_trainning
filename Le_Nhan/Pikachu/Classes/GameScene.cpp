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


	Node* game_background = CSLoader::getInstance()->createNode("csb/GameScene.csb");
	auto gb_game_pikachu = game_background->getChildByName<ui::ImageView*>("bg_pikachu");

	//this->addChild(game_background);

	//return Menu Game
	auto return_main_menu = gb_game_pikachu->getChildByName<ui::Button*>("return_main_menu");
	return_main_menu->setPressedActionEnabled(true);
	return_main_menu->addClickEventListener([=](Ref*)-> void
		{
			Director::getInstance()->replaceScene(TransitionFade::create(0.75, MainMenuScene::createScene(), Color3B(0, 255, 255)));
		});

	//exit game
	auto exit_game = gb_game_pikachu->getChildByName<ui::Button*>("exit_button");
	exit_game->setPressedActionEnabled(true);
	exit_game->addClickEventListener([=](Ref*)-> void
		{
			Director::getInstance()->end();
		});

	//Pause game
	//auto pauseGame = CSLoader::getInstance()->createNode("csb/PauseGame.csb");
	//auto pauseGame = CSLoader::getInstance()->createNode("csb/PauseGame.csb");


	auto pause_game_button = game_background->getChildByName<ui::Button*>("ResumeGame");
	//auto copy_pause_game_button = game_background->getChildByName<ui::Button*>("ResumeGame");
	pause_game_button->setPressedActionEnabled(true);
	pause_game_button->addClickEventListener([=](Ref*) -> void
		{

			auto pauseGame = CSLoader::getInstance()->createNode("csb/PauseGame.csb");
			//game_background->removeChild(pause_game_button);
			//pause_game_button->removeFromParent();
			
			//gb_game_pikachu->runAction(FadeOut::create(0.5));
			pauseGame->runAction(FadeOut::create(0.5));


			auto bg_paugame = utils::findChild<ui::ImageView*>(pauseGame, "pause_game_bg");


			auto return_menu_button = utils::findChild<ui::Button*>(bg_paugame, "return_main_menu");
			return_menu_button->setPressedActionEnabled(true);
			return_menu_button->addClickEventListener([=](Ref*)->void
				{
					Director::getInstance()->resume();
					Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenuScene::createScene()));
				});

			auto button_resume_game = utils::findChild<ui::Button*>(bg_paugame, "return_game");
			button_resume_game->setPressedActionEnabled(true);
			button_resume_game->addClickEventListener([=](Ref*)->void
				{
					Director::getInstance()->resume();
					pauseGame->runAction(FadeOut::create(0.5));
					//game_background->addChild(copy_pause_game_button);
					pause_game_button->runAction(FadeIn::create(0.5));
					gb_game_pikachu->runAction(FadeIn::create(0.5));
				});
			
			//pause_game_button->runAction(FadeOut::create(0.25));
			
			this->addChild(pauseGame);
			
			Director::getInstance()->pause();
		});

	/*auto resume_game = game_background->getChildByName<ui::Button*>("exit_button");
	resume_game->setPressedActionEnabled(true);
	resume_game->addClickEventListener([=](Ref*) -> void
		{
			auto pauseGame_bg = utils::findChild<ui::ImageView*>(pauseGame, "pause_game_bg");
			pauseGame_bg->runAction(FadeOut::create(0.5));
			//Director::getInstance()->pause();
		});*/
	//this->addChild(pauseGame);
	
	this->addChild(game_background);
	
	showBoard(game_background);

	showProgressTimer();

	CCLOG("%d ta la sieu nhan", dem_pokemon);

	BoardView view;





	return true;
}

Layer* GameScene::showBoard(Node* game_background)
{
	vector<int> count(16, 4);
	Board* board = new Board(8, 8, 16, count);
	auto boardView = BoardView::createBoardView(board);
	game_background->addChild(boardView, 1);
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
	progressTimer->setScaleX(0.9);
	progressTimer->setScaleY(0.5);
	//progressTimer->setPosition(visibleSize.width / 2, boardView->getBoundingBox().getMinY() / 2);
	progressTimer->setPosition(visibleSize.width / 2, visibleSize.height*0.03);
	this->addChild(progressTimer);
	progressTimer->runAction(ProgressFromTo::create(200, 100, 0));
	progressTimer->scheduleOnce(schedule_selector(GameScene::GoToGameOver), 200);
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