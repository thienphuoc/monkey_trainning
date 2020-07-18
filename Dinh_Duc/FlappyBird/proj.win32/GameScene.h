#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    unsigned int m_score;
    cocos2d::PhysicsWorld *sceneWorld;
    void setPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; }
    
    void spawnPipe(float dt);

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    Pipe pipe;
    Bird *bird;

    cocos2d::__String* tmpString;
    cocos2d::Label* scoreLabel;
};

#endif // __GAME_SCENE_H__
