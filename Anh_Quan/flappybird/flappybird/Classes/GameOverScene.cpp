/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    
    return GameOverScene::create();
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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Resources/iphonehd/Background.png");
    backgroundSprite->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(backgroundSprite);
    
    auto retryItem = MenuItemImage::create("Resources/iphonehd/Retry Button.png", "Resources/iphonehd/Retry Button Clicked.png", CC_CALLBACK_1(GameOverScene::GotoGameScene, this));
    retryItem->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/4 * 3));
    
    auto mainMemuItem = MenuItemImage::create("Resources/iphonehd/Menu Button.png", "Resources/iphonehd/Menu Button Clicked.png", CC_CALLBACK_1(GameOverScene::GotoMainMenuScene, this));
    mainMemuItem->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/4));
    
    auto menu = Menu::create(retryItem, mainMemuItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    UserDefault *def  = UserDefault::getInstance();
    auto highScore = def->getIntegerForKey("HIGHSCORE FLAPPY", 0);
    if(score > highScore) {
        highScore = score;
        def->getIntegerForKey("HIGHSCORE FLAPPY", highScore);
    }
    def->flush();
    
    __String *tempScore = __String::createWithFormat("%i", score);
    auto currentScore = LabelTTF::create(tempScore->getCString(), "Resources/fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    currentScore->setPosition(Point(origin.x + visibleSize.width*0.25, origin.y + visibleSize.height/2));
    this->addChild(currentScore);
    
    __String *tempHighScore = __String::createWithFormat("%i", highScore);
    auto highScoreLabel = LabelTTF::create(tempHighScore->getCString(), "Resources/fonts/Marker Felt.ttf",  visibleSize.height * SCORE_FONT_SIZE);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(Point(origin.x + visibleSize.width*0.75, origin.y + visibleSize.height/2));
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

void GameOverScene::GotoMainMenuScene(cocos2d::Ref *sender) {
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
    
}

void GameOverScene::GotoGameScene(cocos2d::Ref *sender) {
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
    
}
