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

#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create(MAIN_MENU_SCENE_BACKGROUND_FILEPATH);
    background->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(background);
    
    Sprite *title = Sprite::create(MAIN_MENU_TITLE_FILEPATH);
    title->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.75));
    this->addChild(title);
    
    Button *playButton = Button::create(MAIN_MENU_PLAY_BUTTON, MAIN_MENU_PLAY_BUTTON_PRESSED);
    playButton->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.35));
    this->addChild(playButton);
    playButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
    playButton->setTag(TAG_MAIN_MENU_PLAY_BUTTON);
        
    Sprite *playButtonOuter = Sprite::create(MAIN_MENU_PLAY_BUTTON_OUTER);
    playButtonOuter->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height*0.35));
    this->addChild(playButtonOuter);
    
    Button *soundButton = Button::create(SOUND_ON_BUTTON, SOUND_OFF_BUTTON);
   // MenuItemToggle *soundButton = MenuItemToggle::create();
    soundButton->setPosition(Point(origin.x + visibleSize.width - soundButton->getContentSize().width/2, origin.y + soundButton->getContentSize().height/2));
    this->addChild(soundButton);
    
     
    
    return true;
}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainMenuScene::touchEvent(Ref *sender, Widget::TouchEventType type) {
    Node *node = (Node *) sender;
    switch(type) {
        case Widget::TouchEventType::BEGAN: {
            
            break;
        }
            
        case Widget::TouchEventType::ENDED: {
            if(TAG_MAIN_MENU_PLAY_BUTTON == node->getTag()) {
                Scene *scene = GameScene::createScene();
                TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
                
                Director::getInstance()->replaceScene(scene);
            }
            break;
        }

        case Widget::TouchEventType::MOVED: {
            
            break;
        }

        case Widget::TouchEventType::CANCELED: {
            
            break;
        }

        default:
            break;
    }
}
