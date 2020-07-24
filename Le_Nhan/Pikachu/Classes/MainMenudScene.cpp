

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "proj.win32/GameScene.h"
#include "proj.win32/Audio.h"
using namespace std;

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto start_game = MainMenuScene::create();
    Audio::playBackgroundMusic();
    return start_game;
}


// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto mainMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
    this->addChild(mainMenu);

    auto go_to_game_button = utils::findChild<ui::Button*>(mainMenu, "play_game");
    go_to_game_button->setPressedActionEnabled(true);
    go_to_game_button->addClickEventListener([=](Ref*)-> void
        {
            Director::getInstance()->replaceScene(TransitionFade::create(0.75, GameScene::createScene(), Color3B(30, 255, 20)));
        });

    //auto exit_game = utils::findChild<ui::Button*>(mainMenu, "exit_button"); 
    auto exit_game = mainMenu->getChildByName<ui::Button*>("exit_button");
    exit_game->setPressedActionEnabled(true);
    exit_game->addClickEventListener([=](Ref*)-> void
        {
            Director::getInstance()->end();
        });






    return true;
}

