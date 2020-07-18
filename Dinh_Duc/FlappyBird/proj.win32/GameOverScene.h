#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(unsigned int currentScore);

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

private:
    //static unsigned int m_score;
    void goToGameScene(Ref* pSender);
    void goToMainMenu(Ref* pSender);
};

#endif // __GAME_OVER_SCENE_H__

