#include "MainMenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

#include "GameOverScene.h"

Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();

    auto layer = GameOverScene::create();

    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto mainMenu = CSLoader::getInstance()->createNode("csb/GameOver_bg.csb");
    this->addChild(mainMenu);

    //Go to Game

    auto item_window = utils::findChild<ui::ImageView*>(mainMenu, "Background_window");
    item_window->setVisible(true);

    auto button_retry = utils::findChild<ui::Button*>(item_window, "return_game");
    button_retry->setPressedActionEnabled(true);
    button_retry->addClickEventListener([=](Ref*)-> void
        {
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(2, scene));

        });

    auto button_main_menu = utils::findChild<ui::Button*>(item_window, "return_main_menu");
    button_main_menu->setPressedActionEnabled(true);
    button_main_menu->addClickEventListener([=](Ref*)-> void
        {
            auto scene = MainMenuScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(2, scene));



        });


    return true;
}