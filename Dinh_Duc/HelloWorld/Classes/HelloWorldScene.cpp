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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = HelloWorld::create();
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
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
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    /*auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }*/

    // add "HelloWorld" splash screen"
    /*auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }*/

    //                  BACKGROUND
    auto background = Sprite::create("background.png");
    if (background == nullptr)
    {
        problemLoading("background.png");
    }
    else
    {
        background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

        this->addChild(background, 0);
    }

    //                  CHARACTER
    auto character = Sprite::create("character/character_01.png");
    character->setPosition(Vec2(origin.x+visibleSize.width/3, origin.y+visibleSize.height/2));
    this->addChild(character);


    //                  CHARACTER ANIMATION
    auto characterAnimation = Animation::create();
    characterAnimation->setDelayPerUnit(0.15f);

    characterAnimation->setLoops(-1);
    for (int i = 1; i < 7; i++) 
    {
        std::string framePath = "character/character_0" + std::to_string(i) + ".png";
        characterAnimation->addSpriteFrame(Sprite::create(framePath)->getSpriteFrame());
    }
    

    Animate* animate = Animate::create(characterAnimation);
    character->runAction(animate);


    //                  SHADOW
    auto shadow = Sprite::create("character/shadow.png");
    shadow->setPosition(Vec2(character->getContentSize().width/2, 5.0f));
    character->addChild(shadow, -1);

    //                  CHARACTER MOVEMENT
    MoveTo* move = MoveTo::create(1.0f, Point(visibleSize.width / 2, visibleSize.height / 2));
    CallFunc* sayHello = CallFunc::create([] {log("Hello!\n"); });
    JumpTo* jum = JumpTo::create(1.0f, Vec2(character->getPosition().x + background->getContentSize().width / 2, character->getPosition().y), 100, 1);
    CallFunc* returnToOrgPos = CallFunc::create([&] {character->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 2)); });
    ScaleBy* scale = ScaleBy::create(1.0f, 2.0f);

    Sequence* seqAction = Sequence::create(move, sayHello, jum, returnToOrgPos, NULL);
    Spawn* spnAction = Spawn::create(move, scale, sayHello, NULL);




    //                  SKILL
    ////            Animation
    auto skillAnimation1 = Animation::create();
    auto skillAnimation2 = Animation::create();
    skillAnimation1->setDelayPerUnit(1.0f/15);
    skillAnimation2->setDelayPerUnit(1.0f/15);
    skillAnimation1->setLoops(1);
    skillAnimation2->setLoops(1);

    for (int i = 1; i < 10; i++)
    {
        std::string framePath = "skill/attack" + std::to_string(i) + ".png";
        skillAnimation1->addSpriteFrame(Sprite::create(framePath)->getSpriteFrame());
    }
    const std::string k_skillAnimationName1 = "skillAnimation1";
    AnimationCache::getInstance()->addAnimation(skillAnimation1, k_skillAnimationName1);

    for (int i = 0; i < 18; i++)
    {
        std::string framePath = "skill_02/skill_02_" + std::to_string(i) + ".png";
        skillAnimation2->addSpriteFrame(Sprite::create(framePath)->getSpriteFrame());
    }
    const std::string k_skillAnimationName2 = "skillAnimation2";
    AnimationCache::getInstance()->addAnimation(skillAnimation2, k_skillAnimationName2);


    ////            TOUCH EVENT
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };
    touchListener->onTouchMoved = [](Touch* touch, Event* event)
    {

    };
    touchListener->onTouchEnded = [=](Touch* touch, Event* event)
    {
        auto skill = Sprite::create("skill/attack1.png");
        skill->setPosition(touch->getLocation());
        this->addChild(skill);

        Animate* animate = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation1"));

        skill->runAction(Sequence::createWithTwoActions(animate, RemoveSelf::create()));
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    ////                  KEYBOARD EVENT
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
    {
        return true;
    };
    keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_A)
        {
            auto skill1 = Sprite::create("skill_02/skill_02_0.png"),
                skill2 = Sprite::create("skill_02/skill_02_0.png"),
                skill3 = Sprite::create("skill_02/skill_02_0.png");
            skill1->setPosition(character->getPosition() + Vec2(100, 0));
            skill2->setPosition(character->getPosition() + Vec2(100, 300));
            skill3->setPosition(character->getPosition() + Vec2(200, 100));
            this->addChild(skill1);
            this->addChild(skill2);
            this->addChild(skill3);
            Animate* animate1 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation2"));
            Animate* animate2 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation2"));
            Animate* animate3 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation2"));
            skill1->runAction(Sequence::createWithTwoActions(animate1, RemoveSelf::create()));
            skill2->runAction(Sequence::createWithTwoActions(animate2, RemoveSelf::create()));
            skill3->runAction(Sequence::createWithTwoActions(animate3, RemoveSelf::create()));
            
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_Q)
        {
            character->runAction(seqAction);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_W)
        {
            character->runAction(spnAction);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_E)
        {
            RepeatForever* repeatForever = RepeatForever::create(seqAction);
            character->runAction(repeatForever);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_R)
        {
            Repeat* repeat = Repeat::create(seqAction, 3);
            character->runAction(repeat);
        }
    
        else if (keyCode == EventKeyboard::KeyCode::KEY_T)
        {
            auto *rect = new Rect(0,0,visibleSize.width,visibleSize.height);
            Follow* follow = Follow::create(character);
            
            this->runAction(follow);
        }

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

