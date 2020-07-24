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

#include "GameScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "Resources/CloseNormal.png",
                                           "Resources/CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto backItem = MenuItemImage::create("Resources/back1.png", "Resources/back2.png");
    auto back = MenuItemImage::create("Resources/back1.png", "Resources/back2.png",
    CC_CALLBACK_1(GameScene::back, this));
    
    auto menuItem = Menu::create(back, nullptr);
    menuItem->setPosition(origin);
    back->setPosition(origin + Vec2(back->getContentSize().width / 2,
                      visibleSize.height - back->getContentSize().height / 2));

    this->addChild(menuItem);
    ShowBoard();
    
    showProgressTimer();
    
    return true;
}

void GameScene::back(Ref *pSender) {
    auto homeScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, homeScene, Color3B(0, 255, 255)));
}

Layer *GameScene::ShowBoard() {
    std::vector<int> count(16, 4);
    Board* board = new Board(X_SIZE, Y_SIZE, 16, count);
    //pokemonCount = X_SIZE * Y_SIZE;
    boardView = BoardView::CreateBoardView(board);
    this->addChild(boardView, 1);
    float x = (Director::getInstance()->getVisibleSize().width - boardView->getContentSize().width) / 2;
    float y = (Director::getInstance()->getVisibleSize().height - boardView->getContentSize().height) / 2;
    boardView->setPosition({x, y});
    return boardView;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameScene::showProgressTimer()
{
    auto screenSize = Director::getInstance()->getVisibleSize();

    auto progressTimer = ProgressTimer::create(Sprite::create("Resources/ProgressBar.png"));
    if(!progressTimer) {
        exit(-1);
    }
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Vec2(0.0f, 0.5f));
    progressTimer->setBarChangeRate(Vec2(1.0f, 0.0f));
    progressTimer->setPercentage(100);
    progressTimer->setScale(screenSize.width / (2*progressTimer->getContentSize().width));
    progressTimer->setPosition(screenSize.width / 2, boardView->getBoundingBox().getMinY() / 2);
    this->addChild(progressTimer);
    progressTimer->runAction(ProgressFromTo::create(GAME_TIME, 100, 0));
    progressTimer->scheduleOnce(schedule_selector(GameScene::EndGame), GAME_TIME);
}

void GameScene::EndGame(float dt) {
    auto mainMenuScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(mainMenuScene);
}
