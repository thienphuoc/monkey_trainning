//#include "SplashScene.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto backgroundSprite = Sprite::create("Background.png");
    if (backgroundSprite == nullptr)
    {
        problemLoading("'Background.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(backgroundSprite);

    }

    auto titleLogo = Sprite::create("Title.png");
    titleLogo->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - titleLogo->getContentSize().height / 2));
    this->addChild(titleLogo);


    auto playItem = MenuItemImage::create(
        "Play Button.png", 
        "Play Button Clicked.png",
        CC_CALLBACK_1(MainMenu::goToGameScene, this)
    );

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this)
    );
    
    playItem->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));

    auto menu = Menu::create(playItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

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
