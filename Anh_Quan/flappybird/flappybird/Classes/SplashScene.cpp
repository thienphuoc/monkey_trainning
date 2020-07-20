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

#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"

USING_NS_CC;

using namespace rapidjson;
using namespace network;

struct LeaderBoardInfo {
    std::string m_name;
    int m_score;
    LeaderBoardInfo() {};
    LeaderBoardInfo(std::string i_name, int i_score) :
        m_name(i_name),
        m_score(i_score)
    {
    }
};

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    //CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackGroundMusic("Resources/Sounds/Hit.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Hit.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Point.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Wing.mp3");

    auto mainMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
    this->addChild(mainMenu);

    auto playButton = mainMenu->getChildByName<ui::Button*>("button_play");
    playButton->setPressedActionEnabled(true);
    playButton->addClickEventListener([=](Ref*) {
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
        });

    /*
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(schedule_selector(SplashScene::GotoMainScene), DISPLAY_TIME_SPLASH_SCENE)
    ;

    auto backgrounSprite = Sprite::create("iphonehd/Splash Screen.png");
    backgrounSprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgrounSprite);
    */

    auto loaderButton = mainMenu->getChildByName<ui::Button*>("button_leaderboard");
    loaderButton->setPressedActionEnabled(true);
    loaderButton->addClickEventListener([=](Ref*) {
        HttpRequest* request = new HttpRequest();
        request->setRequestType(HttpRequest::Type::GET);
        request->setUrl("https://isschool.firebaseio.com/leaderboard.json");
        request->setResponseCallback([=](HttpClient* sender, HttpResponse* response) {
            if (200 == response->getResponseCode()) // connect success
            {
                CCLOG("Connect success");
                auto leaderBoard = CSLoader::getInstance()->createNode("csb/leader.csb");
                if (!leaderBoard) {
                    CCLOG("Cannot found leader.csb");
                }
                else {
                    CCLOG("leader.csb found");
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
                //CCLOG("%s", data.c_str());  

                if (!data.empty())
                {
                    Document m_document;
                    m_document.Parse(data.c_str());
                    std::vector<LeaderBoardInfo> leaderBoardList;

                    for (int i = 0; i < m_document.Size(); i++)
                    {
                        //leaderBoardList.push_back({"thien_phuoc", 2000});
                        leaderBoardList.push_back({ m_document[i]["name"].GetString(), m_document[i]["score"].GetInt() });
                        //CCLOG("%s %d",  m_document[i]["name"].GetString(), m_document[i]["score"].GetInt());
                    }

                    for (int i = 0; i < leaderBoardList.size(); i++) {
                        for (int j = i + 1; j < leaderBoardList.size(); j++) {
                            if (leaderBoardList[j].m_score > leaderBoardList[i].m_score) {
                                LeaderBoardInfo tmp;
                                tmp.m_name = leaderBoardList[j].m_name;
                                tmp.m_score = leaderBoardList[j].m_score;
                                leaderBoardList[j].m_name = leaderBoardList[i].m_name;
                                leaderBoardList[j].m_score = leaderBoardList[i].m_score;
                                leaderBoardList[i].m_score = tmp.m_score;
                                leaderBoardList[i].m_name = tmp.m_name;
                            }
                        }
                    }

                    if (auto listview = utils::findChild <ui::ListView*>(leaderBoard, "list_view")) {
                        for (auto info : leaderBoardList) {
                            //if (auto listview = utils::findChild <ui::ListView*>(leaderBoard, "list_view")) {
                                //listview->setScrollBarEnabled(true);
                               // listview->setBounceEnabled(true);
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

                            listview->addChild(newItem);

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
        HttpClient::getInstance()->send(request);
        request->release();
        //        auto loaderBoard = CSLoader::getInstance()->createNode("csb/leader.csb");
                 // this->addChild(leaderBoard, 1000);

        });


    return true;
}


void SplashScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void SplashScene::GotoMainScene(float dt) {
    auto scene = MainMenuScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));


}
