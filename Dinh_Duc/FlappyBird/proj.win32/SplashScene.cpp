#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SplashScene::create();
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
bool SplashScene::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto backgroundSprite = Sprite::create("Splash Screen.png");
    if (backgroundSprite == nullptr)
    {
        problemLoading("'Splash Screen.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(backgroundSprite, 0);

        //this->scheduleOnce(schedule_selector(SplashScene::goToMainMenu), SPLASH_SCENE_DISPLAY_TIME);
        this->scheduleOnce(schedule_selector(SplashScene::goToMainMenu), SPLASH_SCENE_DISPLAY_TIME);
    }
    return true;
}


void SplashScene::goToMainMenu(float dt)
{
    auto scene = MainMenu::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
