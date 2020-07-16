#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void playClicked(); 
    CREATE_FUNC(MainMenuScene);
};

