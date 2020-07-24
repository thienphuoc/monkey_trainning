#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include <vector>
#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    

    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

private:
    
    
    void goToGameScene(Ref* pSender);
    void goToLeaderboardScene(Ref* pSender);


};

#endif // __MAIN_MENU_H__
