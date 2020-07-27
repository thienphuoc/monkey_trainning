
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "proj.win32/Definition.h"
#include "SonarCocosHelperCPP/SonarFrameworks.h"
#include "GameOverScene.h"
#include "cocostudio/CocoStudio.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();

    auto layer = GameScene::create();

    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }



     auto mainMenu = CSLoader::getInstance()->createNode("csb/Pause_game_bg.csb");
     this->addChild(mainMenu);

     auto background_game = mainMenu->getChildByName<ui::ImageView*>("Game_Background");
     //background_game->setVisible(true);

     auto button_pause_game = background_game->getChildByName<ui::Button*>("Button_pause");
     button_pause_game->setPressedActionEnabled(true);
     button_pause_game->addClickEventListener([=](Ref*)->void
         {
             //Director::getInstance()->pause();
             auto pause_game_bg = CSLoader::getInstance()->createNode("csb/PauseGame.csb");
             pause_game_bg->runAction(FadeIn::create(0.5));
             
             auto bg_pause = pause_game_bg->getChildByName<ui::ImageView*>("bg_Pause");

             auto button_return_game_scene = utils::findChild<ui::Button*>(bg_pause, "return_game_Scene");
             button_return_game_scene->setPressedActionEnabled(true);
             button_return_game_scene->addClickEventListener([=](Ref*) -> void
                 {
                     Director::getInstance()->resume();
                     pause_game_bg->removeFromParent();
                     //pause_game_bg->runAction(FadeOut::create(0.5));
                 });


             auto button_return_menu_game = utils::findChild<ui::Button*>(bg_pause, "return_menu_game");
             button_return_menu_game->setPressedActionEnabled(true);
             button_return_menu_game->addClickEventListener([=](Ref*) -> void
                 { 
                     Director::getInstance()->resume();
                     Director::getInstance()->replaceScene(TransitionFade::create(0.25, MainMenuScene::createScene()));
                     pause_game_bg->removeFromParent();
                 });
             this->addChild(pause_game_bg);
             Director::getInstance()->pause();


            

         });



   // SonarCocosHelper::UI::AddCentredBackground(GAME_MENU_BACKGROUND_FILEPATH, this);
  //  auto mainMenu = CSLoader::getInstance()->createNode("csb/Pause_game_b.csb");
    //this->addChild(mainMenu);
   gridSprite = Sprite::create(GRID_FILEPATH);
    gridSprite->setPosition(SonarCocosHelper::UI::GetScreenCenter());
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

    turn = PLAYER_PIECE;

    ai = new AI(turn);

   

    gameState = STATE_PLAYING;

    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMove, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void GameScene::onTouchMove(Touch* touch, Event* event)
{

}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    if (STATE_PLAYING == gameState)
    {
        checkAndPlacePiece(touch);
    }

}

void GameScene::onTouchCancelled(Touch* touch, Event* envent)
{

}

void GameScene::InitGridRects()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            gridSpaces[x][y] = Rect(gridSprite->getBoundingBox().getMinX() + ((gridSprite->getBoundingBox().size.width / 3) * x),
                gridSprite->getBoundingBox().getMinY() + ((gridSprite->getBoundingBox().size.height / 3) * y),
                gridSprite->getBoundingBox().size.width / 3, gridSprite->getBoundingBox().size.height / 3);
        }
    }
}

void GameScene::InitGridPieces()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            gridPieces[x][y] = Sprite::create(X_FILEPATH);
            gridPieces[x][y]->setPosition(Vec2(gridSprite->getPositionX() + (gridPieces[x][y]->getContentSize().width * (x - 1)),
                gridSprite->getPositionY() + (gridPieces[x][y]->getContentSize().height * (y - 1))));
            gridPieces[x][y]->setVisible(false);
            gridPieces[x][y]->setOpacity(0);
            this->addChild(gridPieces[x][y]);
        }
    }
}

void GameScene::checkAndPlacePiece(Touch* touch)
{
    Rect rect1 = gridSprite->getBoundingBox();
    Point touchPoint = touch->getLocation();

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (gridSpaces[x][y].containsPoint(touchPoint))
            {
                if (EMPTY_PIECE == gridArray[x][y])
                {
                    gameState = STATE_PLACING_PIECE;
                    gridArray[x][y] = turn;

                    if (X_PIECE == turn)
                    {
                        gridPieces[x][y]->setTexture(X_FILEPATH);
                    }
                    else
                    {
                        gridPieces [x][y]->setTexture(O_FILEPATH);
                    }
                    gridPieces [x][y]->setVisible(true);
                    gridPieces [x][y]->runAction(Sequence::create(FadeIn::create(PIECE_FADE_IN_TIME), CallFunc::create(std::bind(&GameScene::checkWin, this, x, y)), NULL));
                }
            }
        }
    }
}

void GameScene::checkWin(int x, int y)
{
    check3PiecesForMatch(0, 0, 0, 1, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 0, 2, 0, 1, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 1, 0, 2, 0, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 2, 0, 1, 0, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 1, 1, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 2, 2, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 1, 0, 0, 0, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 0, 0, 1, 0, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 2, 1, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 2, 2, 2, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 1, 1, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 0, 2, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(1, 2, 0, 2, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(1, 2, 1, 1, 1, 0, PLAYER_PIECE);
    check3PiecesForMatch(1, 2, 1, 0, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(0, 1, 0, 0, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(0, 1, 1, 1, 2, 1, PLAYER_PIECE);
    check3PiecesForMatch(0, 1, 2, 1, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(1, 0, 0, 0, 2, 0, PLAYER_PIECE);
    check3PiecesForMatch(1, 0, 1, 1, 1, 2, PLAYER_PIECE);
    check3PiecesForMatch(1, 0, 1, 2, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 1, 2, 0, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 1, 1, 1, 0, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 1, 0, 1, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 1, 2, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 0, 2, 1, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 2, 1, 2, 0, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 2, 0, 2, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 1, 1, 0, 0, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 0, 0, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(0, 2, 0, 1, 0, 0, PLAYER_PIECE);
    check3PiecesForMatch(0, 2, 0, 0, 0, 1, PLAYER_PIECE);
    check3PiecesForMatch(0, 2, 1, 2, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(0, 2, 2, 2, 1, 2, PLAYER_PIECE);
    check3PiecesForMatch(0, 2, 1, 1, 2, 0, PLAYER_PIECE);
    check3PiecesForMatch(0, 2, 2, 0, 1, 1, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 1, 0, 1, 2, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 1, 2, 1, 0, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 0, 0, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 2, 2, 0, 0, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 0, 1, 2, 1, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 2, 1, 0, 1, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 2, 0, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(1, 1, 0, 2, 2, 0, PLAYER_PIECE);



    /*check3PiecesForMatch(0, 0, 1, 0, 2, 0, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 1, 1, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(0, 0, 0, 1, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(1, 0, 1, 1, 1, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 2, 1, 2, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 0, 1, 1, 0, 2, PLAYER_PIECE);
    check3PiecesForMatch(2, 1, 1, 1, 0, 1, PLAYER_PIECE);
    check3PiecesForMatch(2, 2, 1, 2, 0, 2, PLAYER_PIECE);*/

    if (STATE_WON != gameState)
    {
        gameState = STATE_AI_PLAYING;
        ai->PlacePiece(&gridArray, gridPieces, &gameState);
        check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
        check3PiecesForMatch(0, 0, 0, 2, 0, 1, AI_PIECE);
        check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
        check3PiecesForMatch(0, 0, 2, 0, 1, 0, AI_PIECE);
        check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
        check3PiecesForMatch(0, 0, 2, 2, 1, 1, AI_PIECE);
        check3PiecesForMatch(2, 0, 1, 0, 0, 0, AI_PIECE);
        check3PiecesForMatch(2, 0, 0, 0, 1, 0, AI_PIECE);
        check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
        check3PiecesForMatch(2, 0, 2, 2, 2, 1, AI_PIECE);
        check3PiecesForMatch(2, 0, 1, 1, 0, 2, AI_PIECE);
        check3PiecesForMatch(2, 0, 0, 2, 1, 1, AI_PIECE);
        check3PiecesForMatch(1, 2, 0, 2, 2, 2, AI_PIECE);
        check3PiecesForMatch(1, 2, 1, 1, 1, 0, AI_PIECE);
        check3PiecesForMatch(1, 2, 1, 0, 1, 1, AI_PIECE);
        check3PiecesForMatch(0, 1, 0, 0, 0, 2, AI_PIECE);
        check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
        check3PiecesForMatch(0, 1, 2, 1, 1, 1, AI_PIECE);
        check3PiecesForMatch(1, 0, 0, 0, 2, 0, AI_PIECE);
        check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
        check3PiecesForMatch(1, 0, 1, 2, 1, 1, AI_PIECE);
        check3PiecesForMatch(2, 1, 2, 0, 2, 2, AI_PIECE);
        check3PiecesForMatch(2, 1, 1, 1, 0, 1, AI_PIECE);
        check3PiecesForMatch(2, 1, 0, 1, 1, 1, AI_PIECE);
        check3PiecesForMatch(2, 2, 1, 2, 0, 2, AI_PIECE);
        check3PiecesForMatch(2, 2, 0, 2, 1, 2, AI_PIECE);
        check3PiecesForMatch(2, 2, 2, 1, 2, 0, AI_PIECE);
        check3PiecesForMatch(2, 2, 2, 0, 2, 1, AI_PIECE);
        check3PiecesForMatch(2, 2, 1, 1, 0, 0, AI_PIECE);
        check3PiecesForMatch(2, 2, 0, 0, 1, 1, AI_PIECE);
        check3PiecesForMatch(0, 2, 0, 1, 0, 0, AI_PIECE);
        check3PiecesForMatch(0, 2, 0, 0, 0, 1, AI_PIECE);
        check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
        check3PiecesForMatch(0, 2, 2, 2, 1, 2, AI_PIECE);
        check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);
        check3PiecesForMatch(0, 2, 2, 0, 1, 1, AI_PIECE);
        check3PiecesForMatch(1, 1, 1, 0, 1, 2, AI_PIECE);
        check3PiecesForMatch(1, 1, 1, 2, 1, 0, AI_PIECE);
        check3PiecesForMatch(1, 1, 0, 0, 2, 2, AI_PIECE);
        check3PiecesForMatch(1, 1, 2, 2, 0, 0, AI_PIECE);
        check3PiecesForMatch(1, 1, 0, 1, 2, 1, AI_PIECE);
        check3PiecesForMatch(1, 1, 2, 1, 0, 1, AI_PIECE);
        check3PiecesForMatch(1, 1, 2, 0, 0, 2, AI_PIECE);
        check3PiecesForMatch(1, 1, 0, 2, 2, 0, AI_PIECE);

        /*check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
        check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
        check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
        check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
        check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
        check3PiecesForMatch(2, 0, 1, 1, 0, 2, AI_PIECE);
        check3PiecesForMatch(2, 1, 1, 1, 0, 1, AI_PIECE);
        check3PiecesForMatch(2, 2, 1, 2, 0, 2, AI_PIECE);*/
    }


    int emptyNum = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if ( EMPTY_PIECE != gridArray[i][j])
            {
                emptyNum--;
            }
        }
    }

    if (emptyNum == 0)
    {
        gameState = STATE_DRAW;
    }

    if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState)
    {
        Director::getInstance()->replaceScene(TransitionFade::create(2, GameOverScene::createScene()));
    }

}

void GameScene::check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int PiecesToCheck)
{
    if (PiecesToCheck == gridArray [x1][y1] && PiecesToCheck == gridArray [x2][y2] && PiecesToCheck == gridArray [x3][y3])
    {
        __String winStr;
        if (O_PIECE == PiecesToCheck)
        {
            winStr = O_WIN_FILEPATH;
        }
        else
        {
            winStr = X_WIN_FILEPATH;
        }

        Sprite* winningPipes[3];

        winningPipes[0] = Sprite::create(winStr.getCString());
        winningPipes[0]->setPosition(gridPieces [x1][y1]->getPosition());
        winningPipes[0]->setOpacity(0);
        this->addChild(winningPipes[0]);

        winningPipes[1] = Sprite::create(winStr.getCString());
        winningPipes[1]->setPosition( gridPieces [x2][y2] ->getPosition());
        winningPipes[1]->setOpacity(0);
        this->addChild(winningPipes[1]);

        winningPipes[2] = Sprite::create(winStr.getCString());
        winningPipes[2]->setPosition(gridPieces [x3][y3] -> getPosition());
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



/*void GameScene::checkWin(int x, int y)
{

    check3PiecesForMatch(0, 0, 1, 0, 2, 0);
    check3PiecesForMatch(0, 0, 1, 1, 2, 2);
    check3PiecesForMatch(0, 0, 0, 1, 0, 2);
    check3PiecesForMatch(1, 0, 1, 1, 1, 2);
    check3PiecesForMatch(2, 0, 2, 1, 2, 2);
    check3PiecesForMatch(2, 0, 1, 1, 0, 2);
    check3PiecesForMatch(2, 1, 1, 1, 0, 1);
    check3PiecesForMatch(2, 2, 1, 2, 0, 2);


    if (X_PIECE == turn)
    {
        turn = O_PIECE;
    }
    else
    {
        turn = X_PIECE;
    }
    if (STATE_PLACING_PIECE == gameState)
    {
        gameState = STATE_PLAYING;
    }
}

void GameScene::check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3)
{
    if (turn == gridArray[x1][y1] && turn == gridArray[x2][y2] && turn == gridArray[x3][y3])
    {
        __String winStr;
        if (O_PIECE == turn)
        {
            winStr = O_WIN_FILEPATH;
        }
        else
        {
            winStr = X_WIN_FILEPATH;
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
        gameState = STATE_WON;
    }
}*/