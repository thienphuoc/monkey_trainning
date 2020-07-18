#include "GameScene.h"
#include "GameOverScene.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

unsigned int m_score;

Scene* GameOverScene::createScene(unsigned int currentScore)
{
    m_score = currentScore;

    auto scene = Scene::create();

    auto layer = GameOverScene::create();

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
bool GameOverScene::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("Background.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto retryItem = MenuItemImage::create(
        "Retry Button.png",
        "Retry Button Clicked.png",
        CC_CALLBACK_1(GameOverScene::goToGameScene, this)
    );

    auto mainMenuItem = MenuItemImage::create(
        "Menu Button.png",
        "Menu Button Clicked.png",
        CC_CALLBACK_1(GameOverScene::goToMainMenu, this)
    );

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(GameOverScene::menuCloseCallback, this)
    );

    auto scoreLabel = Label::create(__String::createWithFormat("%d",m_score)->getCString(), 
        "fonts/Marker Felt.ttf", 
        SCORE_FONT_SIZE * visibleSize.height);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(origin.x + visibleSize.width *0.4, origin.y + visibleSize.height /2);
    this->addChild(scoreLabel);

    retryItem->setPosition(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.75); //2 + retryItem->getContentSize().height);
    mainMenuItem->setPosition(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height * 0.25);/// 2 - mainMenuItem->getContentSize().height);
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, 
        origin.y + closeItem->getContentSize().height / 2));

    auto menu = Menu::create(retryItem, mainMenuItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    UserDefault* def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
    if (m_score > highScore)
    {
        highScore = m_score;
        def->setIntegerForKey("HIGHSCORE", highScore);
    }
    def->flush();
    auto highScoreLabel = Label::create(__String::createWithFormat("%d", highScore)->getCString(),
        "fonts/Marker Felt.ttf",
        SCORE_FONT_SIZE * visibleSize.height);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(origin.x + visibleSize.width *0.6, origin.y + visibleSize.height / 2);
    this->addChild(highScoreLabel);


    return true;
}


void GameOverScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameOverScene::goToGameScene (Ref* pSender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,scene));
}

void GameOverScene::goToMainMenu(Ref* pSender)
{
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
