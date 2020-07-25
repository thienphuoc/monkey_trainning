#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"


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

    /*auto gameBackground = Sprite::create(GAME_BACKGROUND_FILEPATH);
    gameBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(gameBackground);*/

    auto gameMenu = CSLoader::getInstance()->createNode("GameScene.csb");
    this->addChild(gameMenu);

    auto BackButton = gameMenu->getChildByName<ui::Button*>("Button_Back");
    BackButton->setPressedActionEnabled(true);
    BackButton->addClickEventListener([=](Ref*) {

        GameScene::GotoMenuScene(this);

        });

    auto RetryButton = gameMenu->getChildByName<ui::Button*>("Button_Retry");
    RetryButton->setPressedActionEnabled(true);
    RetryButton->addClickEventListener([=](Ref*) {

        Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_TIME, GameScene::createScene()));

        });

    gridSprite = Sprite::create(GRID_FILEPATH);
    gridSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 0.4 + origin.y));
    this->addChild(gridSprite);
    InitGridRects();
    InitGridPieces();

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            gridArray[x][y] = EMPTY_PIECE;
        }
    }

    turn = X_PIECE;
    ai = new AI(turn);
    gameState = STATE_PLAYING;

    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    return true; // true if the function wants to swallow the touch
}

// called when the user moves their finger
void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

// called when the user lifts their finger
void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (STATE_PLAYING == gameState)
    {
        checkAndPlacePiece(touch);
    }
}

void GameScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{
}

void GameScene::InitGridRects()
{
    float size = gridSprite->getBoundingBox().size.width / 3;
    float minX = gridSprite->getBoundingBox().getMinX();
    float minY = gridSprite->getBoundingBox().getMinY();

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            gridSpaces[x][y] = Rect(minX + x * size, minY + y * size, size, size);
        }
    }
}

void GameScene::InitGridPieces()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            gridPieces[x][y] = Sprite::create(X_PIECE_FILEPATH);
            gridPieces[x][y]->setPosition(Vec2(gridSprite->getPositionX() + (gridPieces[x][y]->getContentSize().width * (x - 1)), gridSprite->getPositionY() + (gridPieces[x][y]->getContentSize().height * (y - 1))));
            gridPieces[x][y]->setVisible(false);
            gridPieces[x][y]->setOpacity(0);
            this->addChild(gridPieces[x][y]);
        }
    }
}

void GameScene::checkAndPlacePiece(cocos2d::Touch* touch)
{
    Rect rect = gridSprite->getBoundingBox();
    Point touchPoint = touch->getLocation();

    float touchX = touchPoint.x;
    float touchY = touchPoint.y;
    float size = gridSprite->getBoundingBox().size.width / 3;
    int x = (int)(touchX - rect.getMinX()) / size;
    int y = (int)(touchY - rect.getMinY()) / size;
    //CCLOG("%i %i", x, y);

    if (gridArray[x][y] == EMPTY_PIECE) {
        gameState = STATE_PLACING_PIECE;
        gridArray[x][y] = turn;

        if (turn == X_PIECE) {
            gridPieces[x][y]->setTexture(X_PIECE_FILEPATH);
        }
        else {
            gridPieces[x][y]->setTexture(O_PIECE_FILEPATH);
        }

        gridPieces[x][y]->setVisible(true);
        gridPieces[x][y]->runAction(Sequence::create(FadeIn::create(PIECE_FADE_IN_TIME), CallFunc::create(std::bind(&GameScene::checkWin, this, x, y)), NULL));
    }
}

void GameScene::checkWin(int x, int y)
{
    check3PiecesForMatch(0, 0, 1, 0, 2, 0, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 1, 1, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 0, 1, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(1, 0, 1, 1, 1, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 2, 1, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 1, 1, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 1, 1, 1, 0, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 1, 2, 0, 2, PLAYER_PIECE);

    if (STATE_WON != gameState)
    {
        gameState = STATE_AI_PLAYING;
        ai->PlacePiece(&gridArray, gridPieces, &gameState);

        check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
        check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
        check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
        check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
        check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
        check3PiecesForMatch(2, 0, 1, 1, 0, 2, AI_PIECE);
        check3PiecesForMatch(2, 1, 1, 1, 0, 1, AI_PIECE);
        check3PiecesForMatch(2, 2, 1, 2, 0, 2, AI_PIECE);
    }


    int emptyNum = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (EMPTY_PIECE != gridArray[i][j])
            {
                emptyNum--;
            }
        }
    }

    if (emptyNum == 0)
    {
        gameState = STATE_DRAW;
    }

}

void GameScene::check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int PiecesToCheck)
{
    if (PiecesToCheck == gridArray[x1][y1] && PiecesToCheck == gridArray[x2][y2] && PiecesToCheck == gridArray[x3][y3])
    {
        __String winStr;
        if (O_PIECE == PiecesToCheck)
        {
            winStr = O_WINNING_PIECE_FILEPATH;
        }
        else
        {
            winStr = X_WINNING_PIECE_FILEPATH;
        }

        Sprite* winningPipes[3];

        winningPipes[0] = Sprite::create(winStr.getCString());
        winningPipes[0]->setPosition(gridPieces[x1][y1]->getPosition());
        winningPipes[0]->setOpacity(0);
        this->addChild(winningPipes[0]);

        winningPipes[1] = Sprite::create(winStr.getCString());
        winningPipes[1]->setPosition(gridPieces[x2][y2]->getPosition());
        winningPipes[1]->setOpacity(0);
        this->addChild(winningPipes[1]);

        winningPipes[2] = Sprite::create(winStr.getCString());
        winningPipes[2]->setPosition(gridPieces[x3][y3]->getPosition());
        winningPipes[2]->setOpacity(0);
        this->addChild(winningPipes[2]);

        winningPipes[0]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));
        winningPipes[1]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 0.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));
        winningPipes[2]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 1.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));
        if (PLAYER_PIECE == PiecesToCheck)
        {
            gameState = STATE_WON;
        }
        else
        {
            gameState = STATE_LOSE;
        }
    }
}
void GameScene::GotoMenuScene(cocos2d::Ref* sender) 
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(SCENE_TRANSITION_TIME, scene));

}