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

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "json/rapidjson.h"
#include "json/document.h"


#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"


using namespace rapidjson;

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    /*auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("iphonehd/Background.png");
    backgroundSprite->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(backgroundSprite);

    auto titleSprite = Sprite::create("iphonehd/Title.png");
    titleSprite->setPosition(Point(origin.x + visibleSize.width / 2, visibleSize.height - titleSprite->getContentSize().height));
    this->addChild(titleSprite);

    auto playItem = MenuItemImage::create("iphonehd/Play Button.png", "iphonehd/Play Button Clicked.png", CC_CALLBACK_1(MainMenuScene::GotoGameScene, this));
    playItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);*/



    auto mainMenu = CSLoader::getInstance()->createNode("MainMenu.csb");
    this->addChild(mainMenu);

    auto PlayButton = mainMenu->getChildByName<ui::Button*>("Button_Play");
    PlayButton->setPressedActionEnabled(true);
    PlayButton->addClickEventListener([=](Ref*) {

        MainMenuScene::GotoGameScene(this);

        });

    auto ExitButton = mainMenu->getChildByName<ui::Button*>("Button_exit");
    ExitButton->setPressedActionEnabled(true);
    ExitButton->addClickEventListener([=](Ref*) {

        MainMenuScene::menuCloseCallback(this);

        });

    auto loaderButton = mainMenu->getChildByName<ui::Button*>("Button_leader_board");
    loaderButton->setPressedActionEnabled(true);
    loaderButton->addClickEventListener([=](Ref*) {
        network::HttpRequest* request = new network::HttpRequest();
        request->setRequestType(network::HttpRequest::Type::GET);
        request->setUrl("https://isschool.firebaseio.com/leaderboard.json");
        request->setResponseCallback([=](network::HttpClient* sender, network::HttpResponse* response) {
            if (200 == response->getResponseCode()) // connect success
            {
                CCLOG("Connect success");
                auto leaderBoard = CSLoader::getInstance()->createNode("LeaderBoard.csb");
                if (!leaderBoard) {
                    CCLOG("Cannot found LeaderBoard.csb");
                }
                else {
                    CCLOG("LeaderBoard.csb found");
                }
                auto leader_bg = utils::findChild<ui::ImageView*>(leaderBoard, "leader_board_bg");
                auto item = utils::findChild <ui::ImageView*>(leaderBoard, "item_bg");
                if (!item) {
                    CCLOG("Cannot found item");
                }
                else {
                    CCLOG("item found");
                }
                std::vector<char>* buffer = response->getResponseData();
                if (!buffer) {
                    CCLOG("Buffer for response returns NULL");
                }
                else {
                    CCLOG("Buffer created");
                }

                std::string data = std::string(buffer->begin(), buffer->end());
                CCLOG("%s", data.c_str());  

                if (!data.empty())
                {
                    Document m_document;
                    m_document.Parse(data.c_str());
                    std::vector<LeaderBoardInfo> leaderBoardList;

                    for (int i = 0; i < m_document.Size(); i++)
                    {

                        std::string l_name = m_document[i]["name"].GetString();
                        int l_score = m_document[i]["score"].GetInt();

                        // CCLOG("%s   ,   %s\n", l_name, l_score);
                        leaderBoardList.push_back({ l_name, l_score });
                    }

                    //sort Score
                    for (int i = 0; i < leaderBoardList.size(); i++)
                    {
                        for (int j = 1; j < leaderBoardList.size(); j++)
                        {
                            if (leaderBoardList[j].m_score > leaderBoardList[j - 1].m_score)
                            {
                                //swap(leaderBoardList[j].m_score, leaderBoardList[j - 1].m_score);

                                std::swap(leaderBoardList[j].m_score, leaderBoardList[j-1].m_score);

                                std::swap(leaderBoardList[j].m_name, leaderBoardList[j - 1].m_name);
                            }
                        }
                    }
                    for (int i = 0; i < leaderBoardList.size(); i++) {
                        CCLOG("%s %d 1", m_document[i]["name"].GetString(), m_document[i]["score"].GetInt());
                    }

                    if (auto listview = utils::findChild <ui::ListView*>(leaderBoard, "listview")) {
                        for (auto info : leaderBoardList) {
                            
                            auto newItem = item->clone();
                            newItem->setVisible(true);

                            if (auto nameLabel = newItem->getChildByName <ui::Text*>("name")) {
                                nameLabel->setString(info.m_name);
                                //listview->addChild(nameLabel);
                            }
                            else {
                                CCLOG("Cannot create nameLabel");
                            }

                            if (auto scoreLabel = newItem->getChildByName <ui::Text*>("score")) {
                                scoreLabel->setString(StringUtils::format("Score: %i", info.m_score));
                                //listview->addChild(scoreLabel);
                            }
                            else {
                                CCLOG("Cannot create scoreLable");
                            }

                            listview->pushBackCustomItem(newItem);

                            item->removeFromParent();
                            //}
                        }
                    }
                }

                this->addChild(leaderBoard);

            }
            else // connect failed
            {
                CCLOG("Connect failed");
            }

            });


        request->setTag("Get test");
        network::HttpClient::getInstance()->send(request);
        request->release();
        //        auto loaderBoard = CSLoader::getInstance()->createNode("csb/leader.csb");
                 // this->addChild(leaderBoard, 1000);

        });

    return true;



}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainMenuScene::GotoGameScene(cocos2d::Ref* sender) {
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
