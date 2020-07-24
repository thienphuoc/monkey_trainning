//#include "SplashScene.h"
#include <vector>
#include <algorithm>

#include "MainMenu.h"
#include "GameScene.h"
#include "LeaderBoard.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"



USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();

    
    
    auto layer = MainMenu::create();

    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
   

    auto mainMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
    this->addChild(mainMenu);

    auto button_play = mainMenu->getChildByName<ui::Button*>("button_play");
    button_play->setPressedActionEnabled(true);
    button_play->addClickEventListener([=](Ref*) {

        goToGameScene(this);

        });

    auto button_leaderboard = mainMenu->getChildByName<ui::Button*>("button_leaderboard");
    CCLOG("button_leaderboard loaded");
    button_leaderboard->setPressedActionEnabled(true);
    button_leaderboard->addClickEventListener([=](Ref*)
        {
       
            auto leaderboard = Leaderboard::createLeaderboard();
            this->addChild(leaderboard);

        });

    auto button_exit = mainMenu->getChildByName<ui::Button*>("button_exit");
    button_exit->setPressedActionEnabled(true);
    button_exit->addClickEventListener([=](Ref*) {

        menuCloseCallback(this);

        });

    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end(); 

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainMenu::goToGameScene(Ref* pSender)
{
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}



