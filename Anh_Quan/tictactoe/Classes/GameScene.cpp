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

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include <iostream>

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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto background = Sprite::create(GAME_BACKGROUND_FILEPATH);
    background->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(background);
    
    gridSprite = Sprite::create(GRID_FILEPATH);
    gridSprite->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(gridSprite);
    
    InitGridRects();
    InitGridPieces();
    
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            gridArray[x][y] = EMPTY_PIECE;
        }
    }
    
    turn = X_PIECE;
    ai = new AI(turn);
    gameState = STATE_PLAYING;
    
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

 
void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    
    return true;
}

bool GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    
    return true;
}
bool GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
    if(STATE_PLAYING == gameState) {
        CheckAndPlacePiece(touch);
    }
    
    return true;
}
bool GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event) {
    
    return true;
}

void GameScene::InitGridRects() {
    float size = gridSprite->getBoundingBox().size.width/3;
    float minX = gridSprite->getBoundingBox().getMinX();
    float minY = gridSprite->getBoundingBox().getMinY();
    
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            gridSpaces[x][y] = Rect(minX + x*size, minY + y*size, size, size);
        }
    }
}

void GameScene::InitGridPieces() {
    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
            gridPieces[x][y] = Sprite::create(X_PIECE_FILEPATH);
            gridPieces[x][y]->setPosition(Point(gridSpaces[x][y].getMinX() + gridPieces[x][y]->getContentSize().width/2, gridSpaces[x][y].getMinY() + gridPieces[x][y]->getContentSize().height/2));
            gridPieces[x][y]->setVisible(false);
            gridPieces[x][y]->setOpacity(0);
            
            this->addChild(gridPieces[x][y]);
        }
    }
}

void GameScene::CheckAndPlacePiece(cocos2d::Touch *touch) {
    Rect rect = gridSprite->getBoundingBox();
    Point touchPoint = touch->getLocation();
    
    float touchX = touchPoint.x;
    float touchY = touchPoint.y;
    float size = gridSprite->getBoundingBox().size.width/3;
    int x = (int)(touchX - rect.getMinX())/size;
    int y = (int)(touchY - rect.getMinY())/size;
    //CCLOG("%i %i", x, y);
    
    if(gridArray[x][y] == EMPTY_PIECE) {
        gameState = STATE_PLACING_PIECE;
        gridArray[x][y] = turn;
        
        if(turn == X_PIECE) {
            gridPieces[x][y]->setTexture(X_PIECE_FILEPATH);
        } else {
            gridPieces[x][y]->setTexture(O_PIECE_FILEPATH);
        }
        
        gridPieces[x][y]->setVisible(true);
        gridPieces[x][y]->runAction(Sequence::create(FadeIn::create(PIECE_FADE_IN_TIME), CallFunc::create(std::bind(&GameScene::CheckWin, this, x, y)), NULL));
    }
}

void GameScene::CheckWin(int x, int y) {
    Check3PiecesForMatch();
    
    if(gameState != STATE_WON) {
        gameState = STATE_AI_PLAYING;
        ai->placePiece(&gridArray, gridPieces, &gameState);
        Check3PiecesForMatch();
    }
}

void GameScene::Check3PiecesForMatch() {
    int rowSum[3];
    int columnSum[3];
    int s1 = 0, s2 = 0;
    int x, y;
    for(x = 0; x < 3; x++) {
        rowSum[x] = 0;
        columnSum[x] = 0;
    }
    
    for(x = 0; x < 3; x++) {
        s1 = s1 + gridArray[x][x];
        s2 = s2 + gridArray[x][2 - x];
        for(y = 0; y < 3; y++) {
            rowSum[x] = rowSum[x] + gridArray[x][y];
            columnSum[y] = columnSum[y] + gridArray[x][y];
        }
    }
    
    __String winningPieceStr;
    int winPiece;
    for(x = 0; x < 3; x++) {
        if(rowSum[x] == 3*X_PIECE || columnSum[x] == 3*X_PIECE || s1 == 3*X_PIECE || s2 == 3*X_PIECE) {
            winPiece = X_PIECE;
            winningPieceStr = X_WINNING_PIECE_FILEPATH;
            break;
        } else if(rowSum[x] == 3*O_PIECE || columnSum[x] == 3*O_PIECE || s1 == 3*O_PIECE || s2 == 3*O_PIECE) {
            winningPieceStr = O_WINNING_PIECE_FILEPATH;
            winPiece = O_PIECE;
            break;
        }
    }
    
    if(x < 3) {
        Sprite *winningSprite[3];
        int startX, startY, endX, endY, incX, incY;
        if(s1 == 3*winPiece) {
            startX = 0;
            startY = 0;
            endX = 3;
            endY = 3;
            incX = 1, incY = 1;
        } else if(s2 == 3*winPiece) {
            startX = 0; startY = 2; endX = 3; endY = -1;
            incX = 1; incY = -1;
        } else if(columnSum[x] == 3*winPiece) {
            incX = 1; incY = 1;
            startX = 0; startY = x; endX = 3 ; endY = x + 1;
            incX = 1; incY = 0;
        } else if(rowSum[x] == 3*winPiece) {
            incX = 0; incY = 1;
            startX = x; startY = 0; endX = x + 1; endY = 3;
        }
        
        int indxX[3],  indxY[3];
        for(int i = 0; i < 3; i++) {
            indxX[i] = startX + i*incX;
            indxY[i] = startY + i*incY;
        }
 
        for(int i = 0; i < 3; i++) {
            winningSprite[i] = Sprite::create(winningPieceStr.getCString());
            winningSprite[i]->setPosition(gridPieces[indxX[i]][indxY[i]]->getPosition());
            this->addChild(winningSprite[i]);
            winningSprite[i]->runAction( Sequence::create( DelayTime::create( PIECE_FADE_IN_TIME * 0.5 ), FadeIn::create( PIECE_FADE_IN_TIME ), NULL ) );
        }
    }
}
