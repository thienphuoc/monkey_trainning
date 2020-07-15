#pragma once
#include "cocos2d.h"
#include "Pipe.h"
#include"Bird.h"
class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void spawnPipe(float dt);


    CREATE_FUNC(GameScene);
private:
    Pipe pipe;
    cocos2d::PhysicsWorld* sceneWorld;
    void setPysicsWorld(cocos2d::PhysicsWorld* world) {
        this->sceneWorld = world;
    }
    Bird* bird;
    int score = 0;
};


