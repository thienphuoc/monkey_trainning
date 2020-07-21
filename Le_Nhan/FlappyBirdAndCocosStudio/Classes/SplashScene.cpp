
#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "vector"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include <iostream>
#include <algorithm>
USING_NS_CC;
using namespace std;
using namespace rapidjson;
using namespace network;
using namespace std;

struct LeaderBoardInfo
{
    std::string m_name;
    int m_score;

    LeaderBoardInfo() {}

    LeaderBoardInfo(std::string i_name, int i_score) :
        m_name(i_name),
        m_score(i_score)
    {

    }
};

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();

    auto layer = SplashScene::create();

    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Hit.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Point.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Wing.mp3");

    auto mainMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
    this->addChild(mainMenu);

    //Go to Game
    auto button = mainMenu->getChildByName<ui::Button*>("button_play");
    button->setPressedActionEnabled(true);
    button->addClickEventListener([=](Ref*)-> void
        {
            auto scene = MainMenuScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

            //auto scene = GameScene::createScene();
            //Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

        });

    //Go to score
    auto button_leder_broad = mainMenu->getChildByName<ui::Button*>("button_leader_board");
    button_leder_broad->setPressedActionEnabled(true);
    button_leder_broad->addClickEventListener([=](Ref*)-> void
        {
            
            // Request List Score
            HttpRequest* request = new HttpRequest();
            request->setRequestType(HttpRequest::Type::GET);
            request->setUrl("https://isschool.firebaseio.com/leaderboard.json");
            request->setResponseCallback([=](HttpClient* sender, HttpResponse* response) {

                if (200 == response->getResponseCode()) // connect success
                {
                    std::vector<char>* buffer = response->getResponseData();

                    std::string data = std::string(buffer->begin(), buffer->end());

                    if (!data.empty())
                    {
                        Document m_document;
                        vector<LeaderBoardInfo> LeaderBroadList;
                        //CCLOG("data:%s", data.c_str());
                        m_document.Parse(data.c_str());

                        CCLOG("%d\n", m_document.Size());

                        for (int i = 0; i < m_document.Size(); i++)
                        {
                           
                            string l_name = m_document[i]["name"].GetString();
                            int l_score = m_document[i]["score"].GetInt();

                            // CCLOG("%s   ,   %s\n", l_name, l_score);
                            LeaderBroadList.push_back({ l_name, l_score });
                        }

                        //sort Score
                        for (int i = 0; i < LeaderBroadList.size(); i++)
                        {
                            for (int j = 1; j < LeaderBroadList.size(); j++)
                            {
                                if (LeaderBroadList[j].m_score > LeaderBroadList[j - 1].m_score)
                                {
                                    swap(LeaderBroadList[j].m_score, LeaderBroadList[j - 1].m_score);
                                    swap(LeaderBroadList[j].m_name, LeaderBroadList[j - 1].m_name);
                                }
                            }
                        }

                        //Go to table socre
                        auto leaderbroad = CSLoader::getInstance()->createNode("csb/Leadbroad.csb");
                        this->addChild(leaderbroad, 1000);


                        //return Mainmenu
                        auto button_exit = leaderbroad->getChildByName<ui::Button*>("exit_button");
                        button_exit->setPressedActionEnabled(true);
                        button_exit->addClickEventListener([=](Ref*)-> void
                            {
                                log("nhaannn");
                                 auto scene = SplashScene::createScene();
                                 Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

                                 //auto scene = GameScene::createScene();
                                 //Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

                            });



                        //Show list socre
                        auto item = utils::findChild<ui::ImageView*>(leaderbroad, "item_bg");
                        item->setVisible(true);

                        for (auto info : LeaderBroadList)
                        {
                            if (auto listView = utils::findChild<ui::ListView*>(leaderbroad, "listview"))
                            {
                                auto newItem = item->clone();

                                if (auto nameLabel = newItem->getChildByName<ui::Text*>("name"))
                                {
                                    nameLabel->setString(info.m_name);
                                }

                                if (auto scoreLabel = newItem->getChildByName<ui::Text*>("score"))
                                {
                                    scoreLabel->setString(StringUtils::format("Score %i", info.m_score));
                                }
                                listView->addChild(newItem);
                            }

                        }

                        item->removeFromParent();
                    }
                    else
                    {
                    }

                }
                else // connect failed
                {
                }


                });

            request->setTag("Get test");
            HttpClient::getInstance()->send(request);
            request->release();


            //auto scene = MainMenuScene::createScene();
            //Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

            //auto scene = GameScene::createScene();
            //Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

        });



    /* auto visibleSize = Director::getInstance()->getVisibleSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();

     this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
     auto backgroundSprite = Sprite::create("iphone/SplashScreen.png");
     backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
     this->addChild(backgroundSprite);*/



     //ssize_t size;

    return true;
}


void SplashScene::GoToGameScene(Ref* sender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void SplashScene::GoToMainMenuScene(float dt)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}




