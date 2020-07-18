
#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;
unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    auto scene = Scene::create();

    auto layer = GameOverScene::create();

    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("iphone/Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    auto retryItem = MenuItemImage::create("iphone/RetryButton.png", "RetryButtonClicked.png", 
        CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3));
    auto mainMenuItem = MenuItemImage::create("iphone/MenuButton.png", "MenuButtonClicked.png",
        CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
    mainMenuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4));

    auto menu = Menu::create(retryItem, mainMenuItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

    UserDefault *def = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
    if (score > highScore)
    {
        highScore = score;
        def->setIntegerForKey("HIGHSCORE", highScore);
    }
    def->flush();


    __String *tempScore = __String::createWithFormat("%i", score);
    auto currentScore = LabelTTF::create(tempScore->getCString(), "fonts/Market Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    currentScore->setPosition(Point(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(currentScore);   

    __String *tempHighScore = __String::createWithFormat("%i", highScore);

    auto highScoreLabel = LabelTTF::create(tempHighScore->getCString(), "fonts/Market Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);

    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(highScoreLabel);


    return true;
}

void GameOverScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

