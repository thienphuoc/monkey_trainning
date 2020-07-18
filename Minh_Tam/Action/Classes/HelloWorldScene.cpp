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

#include <iostream>
#include <string>
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
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
    auto m_visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 m_origin = Director::getInstance()->getVisibleOrigin();

    //background
    auto background = Sprite::create("background.png");
    background->setPosition(m_origin + m_visibleSize / 2);
    this->addChild(background);

    //charactor
    auto character = Sprite::create("character/character_01.png");
    character->setPosition({ 104.f, 390.0f });
    this->addChild(character);

    //animation
    auto characterAnimation = Animation::create();
    characterAnimation->setDelayPerUnit(0.15f);

    characterAnimation->setLoops(-1);
    for (int i = 1; i < 6; i++) {
        std::string imgPath = "character/character_0" + std::to_string(i) + ".png";
        characterAnimation->addSpriteFrame(Sprite::create(imgPath)->getSpriteFrame());
    }

    Animate* animate = Animate::create(characterAnimation);
    character->runAction(animate);

    //shadow
    auto shadow = Sprite::create("character/shadow.png");
    shadow->setPosition(Vec2(character->getContentSize().width / 2, 10.5f));
    character->addChild(shadow, -1);

    //attack
    auto skillAnimation = Animation::create();
    skillAnimation->setDelayPerUnit(0.15f);
    skillAnimation->setLoops(1);
    for (int k = 1; k < 9; k++) {
        std::string imgPath1 = "skill/attack" + std::to_string(k) + ".png";
        skillAnimation->addSpriteFrame(Sprite::create(imgPath1)->getSpriteFrame());
    }
    const std::string k_skillAnimationName = "skillAnimation";
    AnimationCache::getInstance()->addAnimation(skillAnimation, k_skillAnimationName);

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
        Animate* animate = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation"));
        skill->runAction(Sequence::createWithTwoActions(animate, RemoveSelf::create()));
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    //skill02 Press A
    auto skillAnimation02 = Animation::create();
    skillAnimation02->setDelayPerUnit(0.15f);
    skillAnimation02->setLoops(1);
    for (int j = 0; j < 17; j++) {
        std::string imgPath2 = "skill_02/skill_02_" + std::to_string(j) + ".png";
        skillAnimation02->addSpriteFrame(Sprite::create(imgPath2)->getSpriteFrame());
    }
    const std::string k_skillAnimationName02 = "skillAnimation02";
    AnimationCache::getInstance()->addAnimation(skillAnimation02, k_skillAnimationName02);
    auto pressListener = EventListenerKeyboard::create();
    pressListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) 
    {

    };
    pressListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_A)
        {
            auto skill02 = Sprite::create("skill_02/skill_02_0.png"),
                skill01 = Sprite::create("skill_02/skill_02_0.png"),
                skill03 = Sprite::create("skill_02/skill_02_0.png");
            skill01->setPosition(character->getPosition() + Vec2(+100, 0));
            skill02->setPosition(character->getPosition() + Vec2(+100, +300));
            skill03->setPosition(character->getPosition() + Vec2(+200, +100));
            this->addChild(skill01);
            this->addChild(skill02);
            this->addChild(skill03);
            Animate* animate01 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation02"));
            Animate* animate02 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation02"));
            Animate* animate03 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation02"));
            skill01->runAction(Sequence::createWithTwoActions(animate01, RemoveSelf::create()));
            skill02->runAction(Sequence::createWithTwoActions(animate02, RemoveSelf::create()));
            skill03->runAction(Sequence::createWithTwoActions(animate03, RemoveSelf::create()));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_G)
        {
            character->runAction(MoveTo::create(2.0f, character->getPosition() + Point(100.0f, 0)));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_F)
        {
            character->runAction(RotateTo::create(0, character->getRotation()+ 90));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
        {
            character->runAction(RotateBy::create(0, 90));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_E)
        {
            character->runAction(ScaleTo::create(2,character->getScale() + 2));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
        {
            character->runAction(ScaleBy::create(2, 2));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
        {
            character->runAction(ScaleBy::create(2, 0.5));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_X)
        {
            character->runAction(SkewBy::create(2, 37, -37));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_Y)
        {
            character->runAction(JumpBy::create(2, Vec2(200,0), 50 , 4 ));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_Z)
        {
            character->runAction(FadeOut::create(2.0f));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_K)
        {
            character->runAction(TintBy::create(2, 30, 100, -100));
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_I)
        {
            MoveTo* move = MoveTo::create(1.0f, Point(visibleSize.width / 2, visibleSize.height / 2));
            CallFunc* sayHello = CallFunc::create([] {log("Hello!\n"); });
            JumpTo* jum = JumpTo::create(1.0f, Vec2(character->getPosition().x + background->getContentSize().width / 2, character->getPosition().y), 100, 1);
            CallFunc* returnO = CallFunc::create([&] {character->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 2)); });
            ScaleBy* scale = ScaleBy::create(1.0f, 2.0f);

            Sequence* seqAction = Sequence::create(move, sayHello, jum, returnO, NULL);
            Spawn* spnAction = Spawn::create(move, scale, sayHello, NULL);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(pressListener, this);

    


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
