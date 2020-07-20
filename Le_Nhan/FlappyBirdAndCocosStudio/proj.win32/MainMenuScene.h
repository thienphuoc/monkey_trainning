#pragma once

#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);
private:
    void GoToGameScene(Ref* sender);
};

#endif // __SPLASH_SCENE_H__
