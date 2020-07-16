#pragma once
#include "cocos2d.h"
#include "network/HttpClient.h"
USING_NS_CC;
using namespace network;


class leaderboard : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();



    CREATE_FUNC(leaderboard);
};


