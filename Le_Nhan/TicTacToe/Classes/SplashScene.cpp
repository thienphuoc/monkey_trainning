
#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "SonarCocosHelperCPP/SonarFrameworks.h"
#include "proj.win32/Definition.h"
#include "proj.win32/MainMenuScene.h"


USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SplashScene::create();

    scene->addChild(layer);

    return scene;
}


// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    SonarCocosHelper::GameCenter::signIn();
    SonarCocosHelper::UI::AddCentredBackground(SPLASH_SCENE_BACKGROUND_FILEPATH, this);
    scheduleOnce(schedule_selector(SplashScene::SwithchToMainMenu), SPLASH_SCENE_SHOW_TIME);


       return true;
}

void SplashScene::SwithchToMainMenu(float dt)
{   
    Scene *scene = MainMenuScene::createScene();
    TransitionFade* transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
    Director::getInstance()->replaceScene(transition);
}

