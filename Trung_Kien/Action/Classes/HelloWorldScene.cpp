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

#include "proj.win32/KeyboardScene.h"
#include<iostream>
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
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // add "HelloWorld" splash screen"
    Sprite* back1 = Sprite::create("background.png");
    Sprite* c1 = Sprite::create("character_01.png");
    back1->addChild(c1);
    back1->setPosition(origin + visibleSize / 2);
    c1->setPosition(0, back1->getBoundingBox().size.height/2);
    this->addChild(back1);

    Sprite* monster = Sprite::create("character_01.png");
    back1->addChild(monster);
    monster->setTag(9);
    monster->setPosition(Vec2(back1->getBoundingBox().size.width / 2, back1->getBoundingBox().size.height / 2));
    
    Animation* animation = Animation::create();
    animation->setDelayPerUnit(0.15f);
    animation->setLoops(-1);
    animation->addSpriteFrame(Sprite::create("character/character_01.png")->getSpriteFrame());
    animation->addSpriteFrame(Sprite::create("character/character_02.png")->getSpriteFrame());
    animation->addSpriteFrame(Sprite::create("character/character_03.png")->getSpriteFrame());
    animation->addSpriteFrame(Sprite::create("character/character_04.png")->getSpriteFrame());
    animation->addSpriteFrame(Sprite::create("character/character_05.png")->getSpriteFrame());
    animation->addSpriteFrame(Sprite::create("character/character_06.png")->getSpriteFrame());

    Animate* animate = Animate::create(animation);
    c1->runAction(animate);

    /*auto shadow = Sprite::create("character/shadow.png");
    shadow->setPosition(origin + visibleSize / 2);
    c1->addChild(shadow,-1);*/
    Animation* skillAnimation = Animation::create();
    skillAnimation->setDelayPerUnit(0.15f);
    skillAnimation->setLoops(1);
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack1.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack2.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack3.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack4.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack5.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack6.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack7.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack8.png")->getSpriteFrame());
    skillAnimation->addSpriteFrame(Sprite::create("skill/attack9.png")->getSpriteFrame());

    AnimationCache::getInstance()->addAnimation(skillAnimation, "skillAnimation");


    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };

    touchListener->onTouchMoved= [](Touch* touch, Event* event) {
        
    };
    touchListener->onTouchEnded = [=](Touch* touch, Event* event) {
        Sprite* skill = Sprite::create("skill/attack1.png");
        skill->setPosition(Vec2(touch->getLocation()));
        this->addChild(skill);
        Animate* animate = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation"));
        skill->runAction(Sequence::createWithTwoActions(animate, RemoveSelf::create()));
        //CCLOG("move: %d --- %d", touch->getLocation().x, touch->getLocation().y);
        if (back1->getChildByTag(9) != NULL) {
            //monster->setPosition(touch->getLocation());
            Rect rec1 /*= monster->getBoundingBox();*/;
                Rect rec2 /*= skill->getBoundingBox();*/;
            rec1.setRect(monster->getPositionX(), monster->getPositionY(), 900,900);
            rec2.setRect(skill->getPositionX(), skill->getPositionY(), 900,900);
            if (rec2.intersectsRect(rec1)) {

                back1->removeChild(monster, NULL);
                CCLOG("danh trung roi");
            }
            else {
                CCLOG("ga`");
            }
        }
       
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, back1);


    Animation* skillA = Animation::create();
    skillA->setDelayPerUnit(0.1);
    skillA->setLoops(1);
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_0.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_1.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_2.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_3.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_4.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_5.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_6.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_7.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_8.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_9.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_10.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_11.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_12.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_13.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_14.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_15.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_16.png")->getSpriteFrame());
    skillA->addSpriteFrame(Sprite::create("skill_02/skill_02_17.png")->getSpriteFrame());
    AnimationCache::getInstance()->addAnimation(skillA, "skillA");

    bool static releaseRight = 0;
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        /*switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            {
                c1->setPosition(c1->getPositionX()+10, c1->getPositionY());

            }
            break;
        }*/
        
    };
    
    
    keyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        switch(keyCode){
            case EventKeyboard::KeyCode::KEY_A:
            {
                auto skill1 = Sprite::create("skill_02/skill_02_0.png");
                auto skill2 = Sprite::create("skill_02/skill_02_0.png");
                auto skill3 = Sprite::create("skill_02/skill_02_0.png");

                Animate* animate1 = Animate::create(AnimationCache::getInstance()->getAnimation("skillA"));
                Animate* animate2 = Animate::create(AnimationCache::getInstance()->getAnimation("skillA"));
                Animate* animate3 = Animate::create(AnimationCache::getInstance()->getAnimation("skillA"));
                skill1->setPosition(c1->getPosition() + Vec2(+40, 0));
                skill2->setPosition(c1->getPosition() + Vec2(+40, +120));
                skill3->setPosition(c1->getPosition() + Vec2(+80, +40));
                this->addChild(skill1);
                this->addChild(skill2);
                this->addChild(skill3);
                skill1->runAction(Sequence::createWithTwoActions(animate1, RemoveSelf::create()));
                skill2->runAction(Sequence::createWithTwoActions(animate2, RemoveSelf::create()));
                skill3->runAction(Sequence::createWithTwoActions(animate3, RemoveSelf::create()));
            }
                break;
            case EventKeyboard::KeyCode::KEY_BACK :
            {
                c1->setPosition(0, back1->getBoundingBox().size.height / 2);
            }
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            {
                auto m = MoveTo::create(5.0f, Vec2(back1->getBoundingBox().size.width / 2, back1->getBoundingBox().size.height / 2));
                c1->runAction(m);
                c1->runAction(ScaleTo::create(5, 2));
            }
                break;
            case EventKeyboard::KeyCode::KEY_0:
            {
                auto m = MoveTo::create(5.0f, Vec2(back1->getBoundingBox().size.width / 2, back1->getBoundingBox().size.height / 2));
                auto m1= MoveTo::create(5.0f, Vec2(0, back1->getBoundingBox().size.height / 2));
                auto se = Sequence::create(m, m1,NULL);
                c1->runAction(RepeatForever::create(se));
            }
                break;
            case EventKeyboard::KeyCode::KEY_3:
            {
                auto m = MoveTo::create(2.0f, Vec2(back1->getBoundingBox().size.width / 2, back1->getBoundingBox().size.height / 2));
                auto m1 = MoveTo::create(2.0f, Vec2(0, back1->getBoundingBox().size.height / 2));
                auto se = Sequence::create(m, m1, NULL);
                c1->runAction(Repeat::create(se,3));
            }
            break;
            case EventKeyboard::KeyCode::KEY_5:
            {
                c1->runAction(MoveBy::create(5.0f, Vec2(1020.f, 390.0f)));
            }
                break;
            case EventKeyboard::KeyCode::KEY_R:
            {
                c1->runAction(RotateTo::create(3, 180));
            }
            break;
            case EventKeyboard::KeyCode::KEY_E:
            {
                c1->runAction(RotateBy::create(3, 180));
            }
            break;
            case EventKeyboard::KeyCode::KEY_S:
            {
                c1->runAction(ScaleTo::create(3, 3));
            }
            break;
            case EventKeyboard::KeyCode::KEY_Z:
            {
                c1->runAction(ScaleBy::create(3, 2));
            }
            break;
            case EventKeyboard::KeyCode::KEY_F:
            {
                c1->runAction(FadeTo::create(3, 100));

            }
            break;
            case EventKeyboard::KeyCode::KEY_I:
            {
                c1->setOpacity(0);
                c1->runAction(FadeIn::create(3));
            }
            break;
            case EventKeyboard::KeyCode::KEY_O:
            {
                c1->runAction(FadeOut::create(3));
            }
            break;
            case EventKeyboard::KeyCode::KEY_T:
            {
                c1->runAction(TintTo::create(3, 255, 0, 0));
            }
            break;
            case EventKeyboard::KeyCode::KEY_B:
            {
                ccBezierConfig b;
                b.controlPoint_1=Point(0, 0);
                b.controlPoint_2=Point(0, 100);
                b.endPosition=Point(100, 100);
                c1->runAction(BezierTo::create(5, b));
            }
            break;
            case EventKeyboard::KeyCode::KEY_L:
            {
                log("testing");
                CCLOG("testing");
            }
            break;
            case EventKeyboard::KeyCode::KEY_J:
            {
                c1->runAction(JumpTo::create(2,Vec2(back1->getBoundingBox().size.width, back1->getBoundingBox().size.height/2),100,1));
            }
            break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            {
                c1->runAction(MoveBy::create(0.01,Vec2(0,5)));

            }
            break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            {
                c1->runAction(MoveBy::create(0.01, Vec2(0, -5)));

            }
            break;
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            {
                c1->runAction(MoveBy::create(0.01, Vec2(-5, 0)));

            }
            break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            {
                c1->runAction(MoveBy::create(0.2, Vec2(5, 0)));
            }   
            break;
            case EventKeyboard::KeyCode::KEY_ENTER:
            {
                Director::getInstance()->replaceScene(KeyboardScene::createScene());
            }
            break;

        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    
    

    return true;
    //tao character
    
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
