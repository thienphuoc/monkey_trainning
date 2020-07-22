#include "MainMenu.h"
#include "GameScene.h"
#include "Board.h"
#include "BoardView.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
   
    auto backButton = MenuItemImage::create("back1.png", "back2.png", CC_CALLBACK_1(GameScene::goToMainMenu, this));
    backButton->setPosition(origin.x + backButton->getContentSize().width / 2, origin.y + visibleSize.height - backButton->getContentSize().height / 2);

    auto menu = Menu::create(backButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    showBoard();

    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameScene::goToMainMenu(Ref* pSender)
{
    auto scene = MainMenu::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
}

Layer* GameScene::showBoard()
{
    std::vector<int> count(16, 4);
    Board* board = new Board(8, 8, 16, count);
    auto boardView = BoardView::createBoardView(board);
    this->addChild(boardView, 1);
    float x = (Director::getInstance()->getVisibleSize().width - boardView->getContentSize().width) / 2;
    float y = (Director::getInstance()->getVisibleSize().height - boardView->getContentSize().height) / 2;
    boardView->setPosition({ x,y });
    return boardView;
}