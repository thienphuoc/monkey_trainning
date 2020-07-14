/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
    bool onTouchBegan(cocos2d ::Touch *touch, cocos2d ::Event *event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event *event);
   
    void InitGridRects();
    void InitGridPieces();

    void checkAndPlacePiece(cocos2d::Touch* touch);
    void checkWin(int x, int y);
    void check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3);

    cocos2d::Sprite* gridSprite;
    cocos2d::Rect gridSpaces[3][3];
    cocos2d::Sprite* gridPieces[3][3];

    int gridArray[3][3];
    int turn;
    int gameState;
};


#endif // __SPLASH_SCENE_H__
