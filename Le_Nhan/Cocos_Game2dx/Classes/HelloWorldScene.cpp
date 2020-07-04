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

#include<iostream>
using namespace std;
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

    auto label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("background.png");
    if (sprite == nullptr)
    {
        problemLoading("'background.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(origin + visibleSize / 2);

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    //add Character
    auto character = Sprite::create("character/character_01.png");
    character->setPosition({ 100.f, 200.0f });
    this->addChild(character);

    /* auto character1 = Sprite::create("character/character_01.png");
     character1->setPosition({ 100.f, 300.0f });
     this->addChild(character1);*/
     //Create Animation cho nhan vat
    auto characterAnimation = Animation::create();
    //characterAnimation->addSpriteFrameWithTexture(String::create("nhan")->getCString());


    characterAnimation->setDelayPerUnit(0.15f);
    characterAnimation->setLoops(-1);
    characterAnimation->addSpriteFrame(Sprite::create("character/character_01.png")->getSpriteFrame());
    characterAnimation->addSpriteFrame(Sprite::create("character/character_02.png")->getSpriteFrame());
    characterAnimation->addSpriteFrame(Sprite::create("character/character_03.png")->getSpriteFrame());
    characterAnimation->addSpriteFrame(Sprite::create("character/character_04.png")->getSpriteFrame());
    characterAnimation->addSpriteFrame(Sprite::create("character/character_05.png")->getSpriteFrame());

    Animate* animate = Animate::create(characterAnimation);
    Animate* animate5 = Animate::create(characterAnimation);
    character->runAction(animate);
    //character->runAction(MoveTo::create(10.0f, Point(400.f, 200.0f)));
    //character->runAction(MoveBy::create(3.0f, Point(200.f, 0)));
    //character->runAction(MoveTo::create(5.0f, Point(character->getPosition() + Point(100.0f, 0))));
    //character->runAction(RotateTo::create(5.0f, 600.f));//Nhân vật xoay quanh tại chỗ
    //character->runAction(ScaleTo::create(10.0f, 2.0f, 2.0f ));//phóng to nhân vật
    //character->runAction(ScaleBy::create(10.0f, 2.0f, 2.0f));
    //character->runAction(SkewTo::create(10.f, 10.0f, 200.0f));//Quay một vòng về phía tay phải phóng to nhân vật, sau đó thu nhỏ nhân vật
    //character->runAction(SkewBy::create(10.0f, 10.0f, 200.0f));//Quay một vòng về phía tay trái phóng to nhân vật, sau đó thu nhỏ nhân vật
    //character->runAction(JumpTo::create(10.0f, Point(300.f, 200.0f), 30.0f, 20.0f));//Thiết lập cho nhân vật nhảy lên cao một khoảng
    //character->runAction(JumpBy::create(10.0f, Point(300.f, 200.0f), 30.0f, 20.0f));
    //character->runAction(FadeTo::create(5.0f, 0));//Làm mờ nhân vật.(Chú ý khi làm mờ nhân vật phải làm mờ luôn cả bóng của nhân vật)
    //character->runAction(FadeIn::create(1.0f));
    //character->runAction(FadeOut::create(1.0f));Làm mờ nhân vật
    //character->runAction(TintTo::create(5.f, 225, 0, 225));//Đổi màu cho nhân vật(thời gian, đỏ, xanh lá cây, xanh dương)
    //character->runAction(TintBy::create(2.0f, 127, 255, 127));//(duration, deltaRed, deltaGreen, deltaBlue)
    //character->runAction(Follow::create(sprite, Rect(0, 0, 100.0f, 300.0f)));
    /*ccBezierConfig config;
    config.controlPoint_1 = Vec2(60, 100);
    config.controlPoint_2 = Vec2(-60, 100);
    config.endPosition = Vec2(60, 150);
    character->runAction(BezierBy::create(2.0f, config));
    character->runAction(BezierTo::create(5.0f, config));*/
    //character->runAction(DelayTime::create(20.0f));
    //character->runAction(Blink::create(30, 30));Làm cho nhân vật nhấp nháy (thời gian, độ nhấp nháy)


    //character->runAction(Hide::create()); //Nhân vật ẩn đi
    //character->runAction(Show::create());//Nhân vật hiện ra
    //character->runAction(RemoveSelf::create(true));//Xoa nhan vat
    //character->runAction(FlipX::create(true));//Nhân vật quay về đằng sau
    //character->runAction(FlipY::create(true));//Nhân vật lộn ngược lên
    //character->runAction(Place::create(Point(200.f, 0)));x    

    //callFunc
   /* auto jump = JumpBy::create(5.0f, Vec2(10.0f, 10.0f), 100.0f, 1.0f);
    //auto rotate = RotateTo::create(10.0f, 10);
    auto tintTo = TintTo::create(5.f, 225, 0, 225);
    auto callblackJump = CallFunc::create(CC_CALLBACK_0(HelloWorld::finishedAction, this));
    auto callblackRotate = CallFunc::create([&]()
        {
            auto labe2 = Label::createWithTTF("nhian", "fonts/Marker Felt.ttf", 24);
            labe2->setPosition(130.0f, 150.0f);
            this->addChild(labe2, 1);
            log("Rotate");
        });
    //auto callblackRotate = CallFunc::create([&]() {log("Rotate"); });
    auto Seq = Sequence::create(tintTo, callblackJump, jump, callblackRotate, nullptr);
    character->runAction(Seq);*/


    /* //Bài tập 1, 4, 3: use sequence,
     Vector<FiniteTimeAction*> actions;
     actions.pushBack(MoveTo::create(5.0f, Point(visibleSize.width/2, visibleSize.height/2)));
     actions.pushBack(DelayTime::create(2));
     actions.pushBack(CallFunc::create([&]()
         {
             auto lable3 = Label::createWithTTF("hello", "fonts/Marker Felt.ttf", 24);
             lable3->setPosition(visibleSize.width / 2, visibleSize.height / 2);
             this->addChild(lable3, 1);
         }));
     actions.pushBack(DelayTime::create(2));
     actions.pushBack(JumpTo::create(3.0f, Point(origin.x + visibleSize.width - character->getContentSize().width, origin.y), 30.0f, 3.0f));
     actions.pushBack(DelayTime::create(2));
     //actions.pushBack(RemoveSelf::create(true));
     //actions.pushBack(CallFunc::create(HelloWorld::finishedAction, this));
     actions.pushBack(CallFunc::create([=]()->
         void
         {
             character->setPosition(100.0f, 200.0f);
         }
        ));

     //auto moveTo = MoveTo::create(5.0f, Point(400.0f, 200.0f));
     //auto jumpBy = JumpBy::create(3.0f, Point(300.0f, 200.0f), 30.0f, 20.0f);

     //auto mySpawn = Spawn::createWithTwoActions(moveTo, jumpBy);
     //actions.pushBack(mySpawn);
     // Bài tập 1
     auto sequence = Sequence::create(actions);

     //Bài tập 3: use RepeatForever
     auto repeatSequence = RepeatForever::create(sequence);
     //Bài tập 4: use Rrpeat
    // auto repeatSequence = Repeat::create(sequence, 3);
     character->runAction(repeatSequence);
     //character->runAction(sequence);*/




     /*//Bài tập 2: use Spawn
     Vector<FiniteTimeAction*> actions;
     auto moveTo = MoveTo::create(5.0f, Point(400.0f, 200.0f));
     auto scale = ScaleTo::create(5.0f, 2.0f, 2.0f);
     auto logHello = CallFunc::create([&]() {
         auto lable3 = Label::createWithTTF("hello", "fonts/Marker Felt.ttf", 24);
         lable3->setPosition(130.0f, 150.0f);
         this->addChild(lable3, 1);
         });
     //actions.pushBack(moveTo);
     auto mySpawn1 = Spawn::createWithTwoActions(moveTo, logHello);
     auto mySpawn2 = Spawn::createWithTwoActions(scale, moveTo);
     actions.pushBack(mySpawn1);
     actions.pushBack(mySpawn2);
     auto sequence = Sequence::create(actions);
     character->runAction(sequence);*/







     //character->runAction(CallFunc::create(CC_CALLBACK_0(HelloWorld::setPosition(100.0f, 200.0f), this)));





     //create shadow cho nhan vat
    auto shadow = Sprite::create("character/shadow.png");
    shadow->setPosition(Vec2(character->getContentSize().width / 2, 10.5f));
    character->addChild(shadow, -1);
    //shadow->runAction(FadeTo::create(5.0f, 0));
    //character1->addChild(shadow, -1);
    //shadow->runAction(Place::create(Point(200.f, 0)));

    //create skill cho nhan vat
    auto skillAnimation = Animation::create();
    skillAnimation->setDelayPerUnit(0.15f);//Hình ảnh trước cách hình ảnh sau 0.15giay
    skillAnimation->setLoops(1); //skill loop 1 la
    char spriteNameImage[50] = { 0 };
    for (int i = 1; i < 10; i++)
    {
        sprintf(spriteNameImage, "skill/attack%d.png", i);
        skillAnimation->addSpriteFrame(Sprite::create(spriteNameImage)->getSpriteFrame());
    }
    const std::string k_skillAninmationName = "skillAnimation";
    AnimationCache::getInstance()->addAnimation(skillAnimation, k_skillAninmationName);

    //lambda funtion
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



    //create skill 2
    auto skillAnimation1 = Animation::create();
    skillAnimation1->setDelayPerUnit(0.15f);//Hình ảnh trước cách hình ảnh sau 0.15giay
    skillAnimation1->setLoops(1); //skill loop 1 la
    char spriteNameImage1[50] = { 0 };
    for (int i = 0; i < 18; i++)
    {
        sprintf(spriteNameImage1, "skill_02/skill_02_%d.png", i);
        skillAnimation1->addSpriteFrame(Sprite::create(spriteNameImage1)->getSpriteFrame());
    }
    const std::string k1_skillAninmationName = "skillAnimation1";
    AnimationCache::getInstance()->addAnimation(skillAnimation1, k1_skillAninmationName);
    //Keyboard event
    auto listenrkeyboard = EventListenerKeyboard::create();

    listenrkeyboard->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        //return true;
    };
    //
    listenrkeyboard->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_A:
        {
            auto skill_set = Sprite::create("skill_02/skill_02_0.png");
            skill_set->setPosition({ 150.f, 160.f });
            this->addChild(skill_set);
            auto skill_set1 = Sprite::create("skill_02/skill_02_0.png");
            skill_set1->setPosition({ 200.f, 260.f });
            this->addChild(skill_set1);
            auto skill_set2 = Sprite::create("skill_02/skill_02_0.png");
            skill_set2->setPosition({ 150.f, 360.f });
            this->addChild(skill_set2);

            Animate* animate1 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation1"));
            Animate* animate2 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation1"));
            Animate* animate3 = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation1"));

            skill_set->runAction(Sequence::createWithTwoActions(animate1, RemoveSelf::create()));
            skill_set1->runAction(Sequence::createWithTwoActions(animate2, RemoveSelf::create()));
            skill_set2->runAction(Sequence::createWithTwoActions(animate3, RemoveSelf::create()));
            break;
        }
        case EventKeyboard::KeyCode::KEY_B:
        {
            character->runAction(RotateBy::create(1.0f, 90.0f));
            shadow->runAction(RotateBy::create(1.0f, 90.0f));
            break;
        }
        case EventKeyboard::KeyCode::KEY_C:
        {
            character->runAction(ScaleBy::create(1.0f, 2, 2));
            shadow->runAction(ScaleBy::create(1.0f, 2, 2));
            break;
        }
        case EventKeyboard::KeyCode::KEY_D:
        {
            character->runAction(SkewBy::create(2.0f, 20.0f, 30.0f));
            shadow->runAction(SkewBy::create(2.0f, 20.0f, 30.0f));
            break;
        }
        case EventKeyboard::KeyCode::KEY_E:
        {
            character->runAction(JumpBy::create(2.0f, Point(350.0f, 200.0f), 20.0f, 30.0f));
            shadow->runAction(JumpBy::create(2.0f, Point(350.0f, 200.0f), 20.0f, 30.0f));
            break;
        }
        case EventKeyboard::KeyCode::KEY_F:
        {
            character->runAction(FadeOut::create(1.0f));
            shadow->runAction(FadeOut::create(1.0f));
            break;
        }
        case EventKeyboard::KeyCode::KEY_G:
        {
            character->runAction(FadeIn::create(1.0f));
            shadow->runAction(FadeIn::create(1.0f));
            break;
        }
        case EventKeyboard::KeyCode::KEY_H:
        {
            character->runAction(TintBy::create(1.0f, 255, 0, 255));
            shadow->runAction(TintBy::create(1.0f, 255, 0, 255));
            break;
        }
        case EventKeyboard::KeyCode::KEY_K:
        {
            character->runAction(Follow::create(character));
            shadow->runAction(Follow::create(character));
            break;
        }
        case EventKeyboard::KeyCode::KEY_L:
        {
            ccBezierConfig config;
            config.controlPoint_1 = Vec2(60.0f, 100.0f);
            config.controlPoint_2 = Vec2(-100.0f, 200.0f);
            config.endPosition = Vec2(50.0f, 150.0f);
            character->runAction(BezierBy::create(2.0f, config));
            shadow->runAction(BezierBy::create(2.0f, config));
            break;
        }
        case EventKeyboard::KeyCode::KEY_M:
        {
            ccBezierConfig config;
            config.controlPoint_1 = Vec2(60.0f, 100.0f);
            config.controlPoint_2 = Vec2(100.0f, 200.0f);
            config.endPosition = Vec2(50.0f, 150.0f);
            character->runAction(BezierTo::create(2.0f, config));
            shadow->runAction(BezierTo::create(2.0f, config));
            break;
        }
        case EventKeyboard::KeyCode::KEY_N:
        {
            character->runAction(Blink::create(2.0f, 30));
            shadow->runAction(Blink::create(2.0f, 30));
            break;
        }
        case EventKeyboard::KeyCode::KEY_O:
        {
            character->runAction(Hide::create());
            shadow->runAction(Hide::create());
            break;
        }
        case EventKeyboard::KeyCode::KEY_I:
        {
            character->runAction(Show::create());
            shadow->runAction(Show::create());
            break;
        }
        case EventKeyboard::KeyCode::KEY_J:
        {
            character->runAction(FlipX::create(true));
            shadow->runAction(FlipX::create(true));
            break;
        }
        case EventKeyboard::KeyCode::KEY_P:
        {
            character->runAction(FlipY::create(true));
            shadow->runAction(FlipY::create(true));
            break;
        }
        case EventKeyboard::KeyCode::KEY_S:
        {
            character->runAction(Place::create(character->getPosition() + Vec2(100.0f, 200.0f)));
            shadow->runAction(Place::create(character->getPosition() + Vec2(100.0f, 200.0f)));
            break;
        }
        case EventKeyboard::KeyCode::KEY_0:
        {
            Vector<FiniteTimeAction*> actions;
            actions.pushBack(MoveTo::create(5.0f, Point(visibleSize.width / 2, visibleSize.height / 2)));
            actions.pushBack(DelayTime::create(2));
            actions.pushBack(CallFunc::create([&]()
                {
                    auto lable3 = Label::createWithTTF("hello", "fonts/Marker Felt.ttf", 24);
                    lable3->setPosition(visibleSize.width / 2, visibleSize.height / 2);
                    this->addChild(lable3, 1);
                }));
            actions.pushBack(DelayTime::create(2));
            actions.pushBack(JumpTo::create(3.0f, Point(origin.x + visibleSize.width - character->getContentSize().width, origin.y), 30.0f, 3.0f));
            actions.pushBack(DelayTime::create(2));
            //actions.pushBack(RemoveSelf::create(true));
            //actions.pushBack(CallFunc::create(HelloWorld::finishedAction, this));
            actions.pushBack(CallFunc::create([=]()->
                void
                {
                    character->setPosition(100.0f, 200.0f);
                }
            ));

            // Bài tập 1
            auto sequence = Sequence::create(actions);
            character->runAction(sequence);
            //character->runAction(sequence);
        }
        case EventKeyboard::KeyCode::KEY_1:
        {
            Vector<FiniteTimeAction*> actions;
            actions.pushBack(MoveTo::create(5.0f, Point(visibleSize.width / 2, visibleSize.height / 2)));
            actions.pushBack(DelayTime::create(2));
            actions.pushBack(CallFunc::create([&]()
                {
                    auto lable3 = Label::createWithTTF("hello", "fonts/Marker Felt.ttf", 24);
                    lable3->setPosition(visibleSize.width / 2, visibleSize.height / 2);
                    this->addChild(lable3, 1);
                }));
            actions.pushBack(DelayTime::create(2));
            actions.pushBack(JumpTo::create(3.0f, Point(origin.x + visibleSize.width - character->getContentSize().width, origin.y), 30.0f, 3.0f));
            actions.pushBack(DelayTime::create(2));
            //actions.pushBack(RemoveSelf::create(true));
            //actions.pushBack(CallFunc::create(HelloWorld::finishedAction, this));
            actions.pushBack(CallFunc::create([=]()->
                void
                {
                    character->setPosition(100.0f, 200.0f);
                }
            ));
            auto sequence = Sequence::create(actions);

            //Bài tập 3: use RepeatForever
            auto repeatSequence = RepeatForever::create(sequence);
            character->runAction(repeatSequence);
            //character->runAction(sequence);*/
        }
        case EventKeyboard::KeyCode::KEY_2:
        {
            Vector<FiniteTimeAction*> actions;
            actions.pushBack(MoveTo::create(5.0f, Point(visibleSize.width / 2, visibleSize.height / 2)));
            actions.pushBack(DelayTime::create(2));
            actions.pushBack(CallFunc::create([&]()
                {
                    auto lable3 = Label::createWithTTF("hello", "fonts/Marker Felt.ttf", 24);
                    lable3->setPosition(visibleSize.width / 2, visibleSize.height / 2);
                    this->addChild(lable3, 1);
                }));
            actions.pushBack(DelayTime::create(2));
            actions.pushBack(JumpTo::create(3.0f, Point(origin.x + visibleSize.width - character->getContentSize().width, origin.y), 30.0f, 3.0f));
            actions.pushBack(DelayTime::create(2));
            //actions.pushBack(RemoveSelf::create(true));
            //actions.pushBack(CallFunc::create(HelloWorld::finishedAction, this));
            actions.pushBack(CallFunc::create([=]()->
                void
                {
                    character->setPosition(100.0f, 200.0f);
                }
            ));

            auto sequence = Sequence::create(actions);
            //Bài tập 4: use Rrpeat
           auto repeatSequence = Repeat::create(sequence, 3);
            character->runAction(repeatSequence);
            //character->runAction(sequence);
        }
        default:
            break;
        }
    };
    // auto move = MoveTo::create(2, Point(200.0f, 300.0f));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenrkeyboard, this);
    return true;
}

/*void HelloWorld::onkeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    auto sprite = Sprite::create("character/character_01.png");
    sprite->setPosition({ 120.f, 220.0f });
    this->addChild(sprite);
    auto listenrkeyboard = EventListenerKeyboard::create();
    listenrkeyboard->onKeyPressed
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}*/


void HelloWorld::finishedAction()
{
    CCLOG("Hello");
}

void HelloWorld::setLocation()
{
    this->setPosition(100.0f, 200.0f);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
