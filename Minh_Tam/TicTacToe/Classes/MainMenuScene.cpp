#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto mainMenu = CSLoader::getInstance()->createNode("MainMenu.csb");
    this->addChild(mainMenu);

    auto PlayButton = mainMenu->getChildByName<ui::Button*>("Button_Play");
    PlayButton->setPressedActionEnabled(true);
    PlayButton->addClickEventListener([=](Ref*) {

        MainMenuScene::GotoGameScene(this);

        });

    return true;
}
void MainMenuScene::GotoGameScene(cocos2d::Ref* sender) {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_TIME, scene));

}