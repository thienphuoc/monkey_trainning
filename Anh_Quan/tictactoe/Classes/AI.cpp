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

/*
 * There are something wrong in computeReward
 * Computing in diagonal returns error.
 */
#include "AI.h"
#include "Definitions.h"
#include <iostream>

using namespace std;

USING_NS_CC;

/*
 Reward:
    + Prevent a change to win of enemy: +1
    + Create a change to win with one piece in a line: +1
    + Create a change to win with 2 pieces in a line: +20
    + Lose: -40
    + Win: +40
    + Enemy has a change to win with one piece in a line: -1
    + Enemy has a change to win with 2 pieces in a line: -20
    + Enemy prevent player to win: -1
 */

AI::AI(int playerPiece) {
    maxReward = LOSE_REWARD;
    
    this->playerPiece = playerPiece;
    if(playerPiece == X_PIECE) {
        aiPiece = O_PIECE;
    } else {
        aiPiece = X_PIECE;
    }
    
    for(int i = 0; i < 8; i++) {
        canReward[i] = 1;
    }
}

int getReward(int reward, int piece, int *canReward) {
    if(reward == 3*piece) {
        return WIN_REWARD;
    } else if(reward == 2*piece) {
        return TWO_PIECES_REWARD;
    } else if(reward == 1*piece) {
        return ONE_PIECE_REWARD;
    } else if(reward >= X_PIECE + O_PIECE + EMPTY_PIECE) {
        // A line can be prevented from winning for only one time.
        //*canReward = 0;
        return PREVENT_REWARD;
    } else {
        return 0;
    }
}

int AI::computeReward(int (*gridArray)[3][3], int piece, int (*canReward)[8], int(*rowSum)[3], int (*columnSum)[3], int *s1 ,int *s2) {
    // Compute the reward of a given state
    // Compute sum of rewads in rows and columns and diagonals
    int reward = 0;
        
    for(int i = 0; i < 3; i++) {
        //if((*canReward)[6] == 1) {
            *s1 = *s1 + (*gridArray)[i][i];
        //}
        
       // if((*canReward)[7] == 1) {
            *s2 = *s2 + (*gridArray)[i][2 - i];
       // }
        
        for(int j = 0; j <  3; j++) {
            //if((*canReward)[i] == 1) {
                (*columnSum)[i] = (*columnSum)[i] + (*gridArray)[i][j];
           // }
            //if((*canReward)[3 + i] == 1) {
                (*rowSum)[j] = (*rowSum)[j] + (*gridArray)[i][j];
           // }
        }
    }
    
    //CCLOG("In function computeReward: s1: %i, s2: %i", *s1, *s2);
        
    reward = reward + getReward(*s1, piece, (canReward)[6]);
    //CCLOG("reward: %i", reward);
    reward = reward + getReward(*s2, piece, (canReward)[7]);
    //CCLOG("s1: %i, s2: %i. reward: %i, piece: %i", *s1, *s2, reward, piece);
    for(int i = 0; i < 3; i++) {
        reward = reward + getReward((*rowSum)[i], piece, (canReward)[i]);
        reward = reward + getReward((*columnSum)[i], piece, (canReward)[3 + i]);
        //CCLOG("rowSum[%i]: %i, columnSum[%i]: %i. reward: %i", i, (*rowSum)[i], i, (*columnSum)[i], reward);
    }
        
    return reward;
}

int AI::computePlayerBestReward(int (*gridArray)[3][3], int (*canReward)[8]) {
    int bestReward = LOSE_REWARD;
    
    // After AI has placed a piece, we will compute the best reward that a player can have
    int rowSum[3], columnSum[3], s1, s2;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if((*gridArray)[i][j] == EMPTY_PIECE) {
                (*gridArray)[i][j] = playerPiece;
                s1 = 0; s2 = 0;
                for(int t = 0; t < 3; t++) {
                    rowSum[t] = 0;
                    columnSum[t] = 0;
                }
                
                //CCLOG("Called from computePlayerBestReward: (i = %i, j = %i)", i, j);
                int reward = computeReward(gridArray, playerPiece, canReward, &rowSum, &columnSum, &s1, &s2);
               //CCLOG("Player reward in (%i %i): %i", i, j, reward);
                if(reward > bestReward) {
                    bestReward = reward;
                }
                
                (*gridArray)[i][j] = EMPTY_PIECE;
            }
        }
    }
    
    return bestReward;
}

void AI::placePiece(int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3], int *gameState) {
    int rowSum[3], columnSum[3], s1 = 0, s2 = 0;
    
    int bestReward = -144;
    int playerBestReward = -1;
    int preventAIWinReward;
    //int lostReward;
    int stateReward;
    int bestX = -1, bestY = -1;
    int aiReward;
    for(int i = 0; i < 3; i++) {
        rowSum[i] = 0;
        columnSum[i] = 0;
    }
    
    //CCLOG("s1: %i, s2: %i", s1, s2);
    //lostReward = computeReward(gridArray, playerPiece, &canReward, &rowSum, &columnSum, &s1, &s2);
    //CCLOG("lostReward: %i", lostReward);
    for(int i = 0; i < 3; i++) {
        int j;
        for(j = 0; j < 3; j++) {
            // Create a new node if this place is an empty place
            // If created node has a better bestReward than the current bestReward, then
            // the best reward node is the created node ,else release it.
            // bestReward = currentReward - playerBestReward.
            if((*gridArray)[i][j] == EMPTY_PIECE) {
                //CCLOG("Empty place in (%i, %i)", i, j);
                (*gridArray)[i][j] = aiPiece;
                
                s1 = 0; s2 = 0;
                for(int t = 0; t < 3; t++) {
                    rowSum[t] = 0;
                    columnSum[t] = 0;
                }
                
                //CCLOG("Called from placePiece");
                
                aiReward = computeReward(gridArray, aiPiece, &canReward, &rowSum, &columnSum, &s1, &s2);
                CCLOG("aiReward at (%i, %i): %i", i, j, aiReward);
                //CCLOG("aiReward in (%i, %i): %i, s1: %i, s2: %i", i, j, aiReward, rowSum[1],columnSum[1] );
                if(aiReward >= WIN_REWARD) {
                    bestX = i; bestY = j;
                    CCLOG("Found an place that leads to win at (%i, %i)", i, j);
                    //CCLOG("BESTX: %i, BESTY: %i, %i, rowSum[0]: %i, columnSum[0]: %i", i, j, aiReward, rowSum[0], columnSum[0]);
                    (*gridArray)[i][j] = EMPTY_PIECE;
                    
                    break;
                }  else if(aiReward >= TWO_PIECES_REWARD) {
                   /*
                    * In the case AI places two pieces in a line, then player have to prevent
                    * AI from winning.
                    * In this case, there is a piece locating at (i,j)
                    */
                    int x = -1, y = -1;
                   // CCLOG("predefine: %i %i", x, y);
                    if(s1 == 2*aiPiece) {
                        for(int t = 0; t < 3; t ++) {
                            if((*gridArray)[t][t] == EMPTY_PIECE) {
                                (*gridArray)[t][t] = playerPiece;
                                x = t; y = t;
                                break;
                            }
                        }
                    } else if(s2 == 2*aiPiece) {
                        for(int t = 0; t < 3; t++) {
                            if((*gridArray)[t][2 - t] == EMPTY_PIECE) {
                                (*gridArray)[t][2 -t] = playerPiece;
                                x = t; y = 2 - t;
                                break;
                            }
                        }
                    } else  {
                        for(int t = 0; t < 3; t++) {
                            if(rowSum[t] == 2*aiPiece) {
                                int k;
                                for(k = 0; k < 3; k++) {
                                    if((*gridArray)[k][t] == EMPTY_PIECE) {
                                        (*gridArray)[k][t] = playerPiece;
                                        x = k; y = t;
                                        break;
                                    }
                                }
                                
                                if(k < 3)
                                    break;
                            } else if(columnSum[t] == 2*aiPiece) {
                                int k;
                                for(k = 0; k < 3; k++) {
                                    if((*gridArray)[t][k] == EMPTY_PIECE) {
                                        (*gridArray)[t][k] = playerPiece;
                                        x = t; y = k;
                                        break;
                                    }
                                }
                                if(k < 3)
                                    break;
                            }
                        }
                    }
                    
                     s1 = 0; s2 = 0;
                     for(int t = 0; t < 3; t++) {
                         rowSum[t] = 0;
                         columnSum[t] = 0;
                     }
                    preventAIWinReward = computeReward(gridArray, playerPiece, &canReward, &rowSum, &columnSum, &s1, &s2);
                     if(x >= 0 && y >= 0) {
                        (*gridArray)[x][y] = EMPTY_PIECE;
                     } else {
                         CCLOG("Error occurred when preventing AI from winning.");
                         
                         exit(-1);
                     }
                }
                    // Else, compute the maximum reward that player can earn.
                playerBestReward = computePlayerBestReward(gridArray, &canReward);
                if(playerBestReward < WIN_REWARD)
                    playerBestReward = preventAIWinReward;
                
                CCLOG("aiReward in (%i, %i): %i, playerBestReward: %i", i, j, aiReward, playerBestReward);
                stateReward = aiReward - playerBestReward;
                if(stateReward > bestReward) {
                    bestReward = stateReward;
                    bestX = i; bestY = j;
                }
                
                (*gridArray)[i][j] = EMPTY_PIECE;
            }
        }
        
        if(j < 3) {
            break;
        }
    }
    
    //CCLOG("aiReward for the best case: %i", aiReward);
    if(bestX < 0 || bestY < 0) {
        CCLOG("Error occurred when computing the best place for AI");
        
        exit(-1);
    } else {
        CCLOG("Best position locates at (%i, %i)", bestX, bestY);
    }
    
    *gameState = STATE_PLAYING;
    (*gridArray)[bestX][bestY] = AI_PIECE;
    gridPieces[bestX][bestY]->setTexture(O_PIECE_FILEPATH);
    gridPieces[bestX][bestY]->setVisible(true);
    gridPieces[bestX][bestY]->runAction(cocos2d::FadeIn::create( PIECE_FADE_IN_TIME ));
}

