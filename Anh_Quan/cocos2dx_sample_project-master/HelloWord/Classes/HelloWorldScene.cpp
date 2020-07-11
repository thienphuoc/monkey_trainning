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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "Resources/CloseNormal.png",
                                           "Resources/CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

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

    auto label = Label::createWithTTF("Hello World", "Resources/fonts/Marker Felt.ttf", 24);
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
    }
 /*
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
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
    }
 */
    
    // Add background
    auto background = Sprite::create("Resources/background.png");
    if(!background) {
        problemLoading("background.png");
    } else {
        background->setPosition(origin + visibleSize/2);
        //background->setPosition(<#const Vec2 &pos#>);
        this->addChild(background);
    }
    
    auto character = Sprite::create("Resources/character/character_01.png");
    if(!character) {
        problemLoading("character_01.png");
    } else {
        character->setPosition({104.f, 390.0f});
        this->addChild(character);
    }

    // Create character animation
    auto characterAnimation = Animation::create();
    characterAnimation->setDelayPerUnit(0.15f);
    characterAnimation->setLoops(-1);
    std::string dirName = "Resources/character/";
    
    for(int i = 1; i <= 6; i++) {
        std::string pngFile = dirName + "character_0" + std::to_string(i) + ".png";
        characterAnimation->addSpriteFrame(Sprite::create(pngFile)->getSpriteFrame());
    }
    Animate *animated = Animate::create(characterAnimation);
    character->runAction(animated);
  
    // Add character shadow
    auto shadow = Sprite::create(dirName + "shadow.png");
    if(!shadow) {
        problemLoading("shadow.png");
        
        exit(-1);
    } else {
        shadow->setPosition(Vec2(character->getContentSize().width/2, 10.5f));
    }
    character->addChild(shadow, -1);
    
    auto skillAnimation = Animation::create();
    skillAnimation->setDelayPerUnit(0.15f);
    skillAnimation->setLoops(1);
    
    // touch-skill
    dirName = "Resources/skill/";
    for(int i = 1; i <= 9; i++) {
        std::string pngFile = dirName + "attack" + std::to_string(i) + ".png";
        skillAnimation->addSpriteFrame(Sprite::create(pngFile)->getSpriteFrame());
    }
    
    const std::string k_skillAnimationName = "skillAnimation";
    AnimationCache::getInstance()->addAnimation(skillAnimation, k_skillAnimationName);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch *touch, Event *event) {
        return true;
    };
    
    touchListener->onTouchMoved = [](Touch *touch, Event *event) {
        
    };
    
    touchListener->onTouchEnded = [=](Touch *touch, Event *event) {
        auto skill = Sprite::create(dirName + "attack1.png");
        if(!skill){
            exit(-1);
        }
        skill->setPosition(touch->getLocation());
        this->addChild(skill);
        Animate *animate = Animate::create(AnimationCache::getInstance()->getAnimation("skillAnimation"));
        skill->runAction(Sequence::createWithTwoActions(animate,RemoveSelf::create()));
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //character->runAction(MoveTo::create(3.0f, Point(origin, visibleSize/2)));
    
    // create skill-by-character-a and save to cache
    auto keyboardSkill = Animation::create();
    keyboardSkill->setDelayPerUnit(0.15f);
    keyboardSkill->setLoops(1);
    dirName = "Resources/";
    for(int i = 0; i <= 17; i++) {
        std::string pngFile = dirName + "skill_02/skill_02_" + std::to_string(i) + ".png";
        keyboardSkill->addSpriteFrame(Sprite::create(pngFile)->getSpriteFrame());
    }
        
    const std::string k_keyboardSkill = "keyboardSkill";
    AnimationCache::getInstance()->addAnimation(keyboardSkill, k_keyboardSkill);
    
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event *event) {
        //auto moveAction = MoveTo::create(2, Point(100, 100));
        auto moveAction = MoveTo::create(2, Point((origin.x + visibleSize.width/2), origin.y + visibleSize.height/2));
        // auto callBack = CC_CALLBACK_1(<#__selector__#>, <#__target__, ...#>)
        //auto callback = CC_CALLBACK_1(<#__selector__#>, <#__target__, ...#>)
        auto logCallBack = CallFunc::create([=]() -> void{
             //log("Hello");
         });
        auto jumpAction = MoveTo::create(2, Point(origin.x + visibleSize.width, origin.y));
        //auto jumpAction = MoveTo::create(2, Point(200, 200));
         auto setCallBack = CallFunc::create([=](){
             character->setPosition(140, 390);
         });
        auto seq = Sequence::create(moveAction, logCallBack, jumpAction, setCallBack, nullptr);
        
        switch (keycode) {
            case EventKeyboard::KeyCode::KEY_A: {
                // skill by character a
                auto skill_1 = Sprite::create(dirName + "skill_02/skill_02_0.png");
                auto skill_2 = Sprite::create(dirName + "skill_02/skill_02_0.png");
                auto skill_3 = Sprite::create(dirName + "skill_02/skill_02_0.png");
                
                skill_1->setPosition(character->getPosition() + Vec2(+100, 0));
                skill_2->setPosition(character->getPosition() + Vec2(+100, +300));
                skill_3->setPosition(character->getPosition() + Vec2(+100, +100));
                this->addChild(skill_1);
                this->addChild(skill_2);
                this->addChild(skill_3);
                
                Animate *animateSkill_1 = Animate::create(AnimationCache::getInstance()->getAnimation("keyboardSkill"));
                Animate *animateSkill_2 = Animate::create(AnimationCache::getInstance()->getAnimation("keyboardSkill"));
                Animate *animateSkill_3 = Animate::create(AnimationCache::getInstance()->getAnimation("keyboardSkill"));
                skill_1->runAction(Sequence::createWithTwoActions(animateSkill_1,RemoveSelf::create()));
                skill_2->runAction(Sequence::createWithTwoActions(animateSkill_2,RemoveSelf::create()));
                skill_3->runAction(Sequence::createWithTwoActions(animateSkill_3,RemoveSelf::create()));
                break;
            }
            case EventKeyboard::KeyCode::KEY_B:{
                // Scale character size by 2 in 2 seconds
                character->runAction(ScaleBy::create(2.0f, 2));
                shadow->runAction(ScaleBy::create(2.0f, 2));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_R: {
                // Rorate character by an angle of 90
                character->runAction(RotateBy::create(2.0f, 90));
                shadow->runAction(RotateBy::create(2.0f, 90));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_W: {
                // Skew
                ///character->runAction(SkewBy::create(2.0f, 90, 90));
                character->runAction(SkewBy::create(2.0f, 45, 90));
                shadow->runAction(SkewBy::create(2.0f, 45, 90));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_J: {
                character->runAction(JumpBy::create(2, Vec2(300.0f, 300.0f), 30, 5));
                
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_F: {
                // Follow
                //character->runAction(Follow::create(<#Node *followedNode#>));
                //Camera::create()->runAction(Follow::create(character, Rect::ZERO));
                auto followCharacter = Follow::create(character, Rect::ZERO);
                this->runAction(followCharacter);
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_T: {
                // Fate
                character->runAction(FadeTo::create(0.2,0.2));
                shadow->runAction(FadeTo::create(0.2, 0.2));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_N: {
                // tintby
                character->runAction(TintBy::create(2, 3, 4, 0));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_Z: {
                ccBezierConfig biezer;
                biezer.controlPoint_1 = Point(100, 100);
                biezer.controlPoint_2 = Point(100, 100);
                biezer.endPosition = Point(100, 100);
                character->runAction(BezierBy::create(5, biezer));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_D: {
                character->runAction(DelayTime::create(1.05));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_K: {
                character->runAction(Blink::create(2.0, 3));
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_S: {
                // run sequence
                character->runAction(seq);
                break;
            }
            case EventKeyboard::KeyCode::KEY_P: {
                // run a spawn
                auto moveAction = MoveTo::create(2, Vec2(visibleSize.width/2, visibleSize.height/2));
                auto scaleAction = ScaleTo::create(2, 2);
                auto callBackFunc = CallFunc::create([=]() {
                    log("Hello");
                });
                
                auto spawn = Spawn::create(moveAction, scaleAction, callBackFunc, nullptr);
                character->runAction(spawn);
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_Y: {
                // Loop the above sequence forever
               auto repeatForever = RepeatForever::create(seq);                character->runAction(repeatForever);
                
                break;
            }
            case EventKeyboard::KeyCode::KEY_O: {
                // Repeat seq 3 times
                auto repeatthreetimes = Repeat::create(seq, 3);
                character->runAction(repeatthreetimes);
                
                break;
            }
            default:
                break;
        }
    };
    
    //auto move = MoveTo::create(3, Point(visibleSize.width/2, visibleSize.height/2));
    //auto jump = JumpBy::create(float duration, const Vec2 &position, <#float height#>, <#int jumps#>)
    //character->runAction((jump));
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    //character->runAction(MoveTo::create(5.0f, Point(1020.f, 390.0f)));
    
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
