#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "AI.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback


    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    void InitGridRects();
    void InitGridPieces();

    void checkAndPlacePiece(cocos2d::Touch* touch);
    void checkWin(int x, int y);
    void check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int PiecesToCheck);

    void GotoMenuScene(cocos2d::Ref* sender);

    cocos2d::Sprite* gridSprite;
    cocos2d::Rect gridSpaces[3][3];
    cocos2d::Sprite* gridPieces[3][3];

    int gridArray[3][3];
    int turn;
    int gameState;
    AI* ai;
};


#endif // __SPLASH_SCENE_H__