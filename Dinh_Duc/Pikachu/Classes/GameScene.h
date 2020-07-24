#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    void goToMainMenu(Ref* pSender);
    cocos2d::Layer* showBoard();
    void showProgressTimer(cocos2d::Layer* boardView);
};

#endif // __GAME_SCENE_H__
