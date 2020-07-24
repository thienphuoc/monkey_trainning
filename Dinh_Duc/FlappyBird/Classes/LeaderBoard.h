#ifndef __LEADERBOARD_H__
#define __LEADERBOARD_H__

#include "cocos2d.h"


class Leaderboard : public cocos2d::Layer
{
public:    
    static cocos2d::Layer* createLeaderboard();

    //virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Leaderboard);

    

private:
    typedef struct LeaderBoardInfo
    {
        std::string m_name;
        int m_score;

        LeaderBoardInfo();
        LeaderBoardInfo(std::string i_name, int i_score) :
            m_name(i_name),
            m_score(i_score)
        {
        }
    } LeaderBoardInfo;

    static bool leaderboardCompare(Leaderboard::LeaderBoardInfo a, Leaderboard::LeaderBoardInfo b);

    
};

#endif // __LEADERBOARD_H__