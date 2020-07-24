
#pragma once

#ifndef __GAME_OVER_SCENEN_H__
#define __GAME_OVER_SCENEN_H__
#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
private:
    void GoToMainMenuScene(float dt);
    void GoToGameScene(Ref* sender);
};

#endif // __SPLASH_SCENE_H__