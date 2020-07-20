#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "AI.h"
#include "GameOverScene.h"
using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    bool onTouchBegan(Touch *touch, Event* event);
    void onTouchMove(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);

    void InitGridRects();
    void InitGridPieces();

    void checkAndPlacePiece(Touch* touch);
    void checkWin(int x, int y);
    //nguoi voi nguoi
   // void check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3);

    //nguoi voi may
    void check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int PieceToCheck);

    Sprite *gridSprite;
    Rect gridSpaces[3][3];
    Sprite *gridPieces[3][3];

    int gridArray[3][3];

    int turn; 
    int gameState;

    AI *ai;
};

#endif // __HELLOWORLD_SCENE_H__
