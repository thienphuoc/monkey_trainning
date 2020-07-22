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

#include "AI.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gameBackground = Sprite::create("Main Menu Background.png");
    gameBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(gameBackground);

    gridSprite = Sprite::create("Grid.png");
    gridSprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(gridSprite);

    InitGridRects();
    
    InitGridPieces();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gridArray[i][j] = EMPTY_PIECE;
        }
    }
    
    //////////////////////////////////////////////////////////////////
    /*for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            CCLOG("AFTER INIT: Grid (%d, %d): %d", i, j, gridArray[i][j]);
            
        }
    }*/
    
    gameState = STATE_PLAYERS_TURN;

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);

    touchListener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };

    touchListener->onTouchMoved = [](Touch* touch, Event* event)
    {

    };

    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);

    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}

void GameScene::InitGridRects()
{
    float rowOrigin, colOrigin;
    for (int i = 0; i < 3; i++)
    {
        rowOrigin = gridSprite->getBoundingBox().getMinY() + gridSprite->getBoundingBox().size.height / 3 * (2 - i);
        for (int j = 0; j < 3; j++)
        {
            colOrigin = gridSprite->getBoundingBox().getMinX() + gridSprite->getBoundingBox().size.width/ 3 * j;
            gridSpaces[i][j] = Rect(colOrigin, rowOrigin, gridSprite->getBoundingBox().size.width / 3, gridSprite->getBoundingBox().size.height / 3);
            
            
            /*CCLOG("Init rect %.3f + %.3f, %.3f + %.3f",
                colOrigin,
                gridSprite->getBoundingBox().size.width / 3,
                rowOrigin,
                gridSprite->getBoundingBox().size.height / 3
            );*/
        }
    }
    CCLOG("InitGridRects!");
}

void GameScene::InitGridPieces()
{
    for (int i=0; i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            gridPieces[i][j] = Sprite::create("X.png");
            gridPieces[i][j]->setPosition(Vec2(gridSprite->getPosition().x + gridPieces[i][j]->getContentSize().width * (j - 1),
                                               gridSprite->getPosition().y + gridPieces[i][j]->getContentSize().height * (1 - i)));
            gridPieces[i][j]->setVisible(false);
            //gridPieces[i][j]->setOpacity(0);
            this->addChild(gridPieces[i][j]);
        } 
    }
    CCLOG("InitGridPieces!");
}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Rect playBoard = gridSprite->getBoundingBox();
    auto touchPoint = touch->getLocation();

    if (gameState = STATE_PLAYERS_TURN)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                //CCLOG("Grid (%d, %d): %d", i, j, gridArray[i][j]);
                if (gridSpaces[i][j].containsPoint(touchPoint))
                {
                    if (EMPTY_PIECE == gridArray[i][j])
                    {
                        gridArray[i][j] = PLAYER_PIECE;
                        if (PLAYER_PIECE == O_PIECE)
                            gridPieces[i][j]->setTexture("O.png");
                        gridPieces[i][j]->setVisible(true);
                        //gridPieces[i][j]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));

                        if (lastMoveWon(i, j, PLAYER_PIECE))
                        {
                            //Game Over
                            GameScene::menuCloseCallback(this);
                        }
                        else if (!isMoveLeft(gridArray))
                        {
                            //Game draw
                            GameScene::menuCloseCallback(this);
                        }
                        gameState = STATE_AI_PLAYING;
                        Move aiMove = findBestMove(gridArray);
                        gridArray[aiMove.x][aiMove.y] = AI_PIECE;
                        if (AI_PIECE == O_PIECE)
                            gridPieces[aiMove.x][aiMove.y]->setTexture("O.png");
                        gridPieces[aiMove.x][aiMove.y]->setVisible(true);
                        //gridPieces[aiMove.x][aiMove.y]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));

                        if (lastMoveWon(i, j, AI_PIECE))
                        {
                            //Game Over
                            GameScene::menuCloseCallback(this);
                        }
                        else if (!isMoveLeft(gridArray))
                        {
                            //Game draw
                            GameScene::menuCloseCallback(this);
                        }

                        gameState = STATE_PLAYERS_TURN;
                    }
                    /*CCLOG("Touched grid (%d,%d)", i, j);
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            CCLOG("AFTER TOUCH: Grid (%d, %d): %d", i, j, gridArray[i][j]);

                        }
                    }*/
                }
            }
        }
    }
    //CCLOG("Touched at %.5f, %.5f",touchPoint.x,touchPoint.y);
}

bool GameScene::lastMoveWon(int row, int column, int piece)
{
    //Game won diagonally: case 1
    if (row == column)
    {
        if (gridArray[(row + 1) % 3][(column + 1) % 3] == piece && gridArray[(row + 2) % 3][(column + 2) % 3] == piece)
        {
            if (piece == X_PIECE)
            {
                for (int i = 0; i < 3; i++)
                {
                    gridPieces[i][i]->setTexture("X Win.png");
                }
            }
            else if (piece == O_PIECE)
            {
                for (int i = 0; i < 3; i++)
                {
                    gridPieces[i][i]->setTexture("O Win.png");
                }
            }
            return true;
        }
    }
    
    //Game won diagonally: case 2
    if ((row + column)== 2)
    {
        if (gridArray[(row + 1) % 3][(column - 1) % 3] == piece && gridArray[(row + 2) % 3][(column - 2) % 3] == piece)
        {
            if (piece == X_PIECE)
            {
                for (int i = 0; i < 3; i++)
                {
                    gridPieces[i][2-i]->setTexture("X Win.png");
                }
            }
            else if (piece == O_PIECE)
            {
                for (int i = 0; i < 3; i++)
                {
                    gridPieces[i][2-i]->setTexture("O Win.png");
                }
            }
            return true;
        }
    }

    //Game won horizontally
    if (gridArray[row][(column + 1) % 3] == piece && gridArray[row][(column + 2) % 3] == piece)
    {
        if (piece == X_PIECE) 
        {
            for (int col = 0; col < 3; col++)
            {
                gridPieces[row][col]->setTexture("X Win.png");
            }
        }
        else if (piece == O_PIECE)
        {
            for (int col = 0; col < 3; col++)
            {
                gridPieces[row][col]->setTexture("O Win.png");
            }
        }
        return true;
    }

    //Game won vertically
    if (gridArray[(row + 1) % 3][column] == piece && gridArray[(row + 2) % 3][column] == piece)
    {
        if (piece == X_PIECE)
        {
            for (int ro = 0; ro < 3; ro++)
            {
                gridPieces[ro][column]->setTexture("X Win.png");
            }
        }
        else if (piece == O_PIECE)
        {
            for (int ro = 0; ro < 3; ro++)
            {
                gridPieces[ro][column]->setTexture("O Win.png");
            }
        }
        return true;
    }

    return false;
    
}