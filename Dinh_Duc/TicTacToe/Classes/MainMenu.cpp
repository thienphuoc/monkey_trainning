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

#include "MainMenu.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"

#include "ui/UIButton.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
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
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto mainMenuBackground = Sprite::create("Main Menu Background.png");
    mainMenuBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(mainMenuBackground);
   
    auto title = Sprite::create("Game Title.png");
    title->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.75);
    this->addChild(title);

    auto playButton = MenuItemImage::create(
        "Play Button.png",
        "Play Button.png",
        CC_CALLBACK_1(MainMenu::goToGameScene, this)
    );
    playButton->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this)
    );
    closeItem->setPosition(origin.x + visibleSize.width - closeItem->getContentSize().width, origin.y + closeItem->getContentSize().height);

    auto achievementsButton = MenuItemImage::create(
        "Achievements.png",
        "Achievements.png",
        CC_CALLBACK_1(MainMenu::goToAchievements, this)
    );
    achievementsButton->setPosition(origin.x + achievementsButton->getContentSize().width/2, origin.y + achievementsButton->getContentSize().height/2);

    //MenuItemToggle()

    auto menu = Menu::create(playButton, closeItem, achievementsButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    auto playButtonOuter = Sprite::create("Play Button Outer.png");
    playButtonOuter->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height /2);
    this->addChild(playButtonOuter);



    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
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
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}

void MainMenu::goToAchievements(Ref* pSender)
{
}