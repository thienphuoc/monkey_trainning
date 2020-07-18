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

#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer *layer) {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    flappyBird = Sprite::create("iphonehd/Ball.png");
    flappyBird->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y) );
    
    auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width/2);
    flappyBird->setPhysicsBody(flappyBody);
    flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappyBody->setContactTestBitmask(true);
    
    layer->addChild(flappyBird, 100);
    
    isFalling = true;
}

void Bird::Fall() {
    if(isFalling == true) {
        flappyBird->setPositionX(visibleSize.width/2 + origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY() - BIRD_FALLING_SPEED * visibleSize.height);
    }
    else {
        flappyBird->setPositionX(visibleSize.width/2 + origin.x);
        flappyBird->setPositionY(flappyBird->getPositionY() + BIRD_FLYING_SPEED * visibleSize.height);
    }
}

