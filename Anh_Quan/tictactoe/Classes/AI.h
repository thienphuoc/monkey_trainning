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

#ifndef __AI_H__
#define __AI_H__

#include "Definitions.h"
#include "cocos2d.h"

class AI
{
public:
    AI(int playerPiece);
    
    void placePiece(int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3], int *gameState);
    
private:
    int aiPiece;
    int playerPiece;
    int maxReward;
    struct stateNode *bestNode;
    
    int computeReward(int (*gridArray)[3][3], int piece, int (*canReward)[8], int(*rowSum)[3], int (*columnSum)[3], int* s1 ,int* s2);
    int computePlayerBestReward(int (*gridArray)[3][3], int (*canReward)[8]);
    int canReward[8]; 
};

#endif // __AI_H__
