#pragma once


#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "pipe.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);

private:
    void setPhysicsWorld(cocos2d::PhysicsWorld *world)
    {
        sceneWorld = world;
    };
    void SpawnPipe(float dt);

    bool onContactBegin(cocos2d::PhysicsContact &contact);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    void stopFlying(float dt);
    void update(float dt);

    cocos2d::PhysicsWorld *sceneWorld;

    Pipe pipe;
    Bird *bird;

    unsigned int score;

    cocos2d::Label *scoreLable;

};

#endif // __GAME_SCENE_H__
