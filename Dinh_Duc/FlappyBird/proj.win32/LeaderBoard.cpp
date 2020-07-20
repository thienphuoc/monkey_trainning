#include <vector>
#include <algorithm>

#include "LeaderBoard.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "network/HttpClient.h"
#include "json/rapidjson.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;




Scene* Leaderboard::createScene()
{
    auto scene = Scene::create();
    auto leaderboard = Leaderboard::create();

    scene->addChild(leaderboard);

    return scene;
};

bool Leaderboard::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto leaderboardLayer = CSLoader::getInstance()->createNode("csb/LeaderBoard.csb");
    this->addChild(leaderboardLayer);

    network::HttpRequest* request = new network::HttpRequest();
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setUrl("https://isschool.firebaseio.com/leaderboard.json");
    request->setResponseCallback([=](network::HttpClient* sender, network::HttpResponse* response) {

        if (200 == response->getResponseCode()) // connect success
        {
            CCLOG("Connection succeeded!");

            std::vector<LeaderBoardInfo> retVec;

            std::vector<char>* buffer = response->getResponseData();

            std::string data = std::string(buffer->begin(), buffer->end());

            if (!data.empty())
            {
                //CCLOG("data:%s", data.c_str());
                rapidjson::Document m_doc;
                m_doc.Parse(data.c_str());

                for (int itr = 0; itr < m_doc.Size(); itr++)
                {
                    std::string l_name = m_doc[itr]["name"].GetString();
                    int l_score = m_doc[itr]["score"].GetInt();
                    retVec.push_back({ l_name,l_score });
                }

            }

            else
            {
            }

            std::sort(retVec.begin(), retVec.end(), leaderboardCompare);

            

            auto listItem = utils::findChild<ui::ImageView*>(leaderboardLayer, "item_bg");

            for (auto info : retVec)
            {
                if (auto listView = utils::findChild<ui::ListView*>(leaderboardLayer, "listview"))
                {
                    auto newItem = listItem->clone();
                    if (auto itemName = utils::findChild<ui::Text*>(newItem, "name"))
                    {
                        itemName->setString(info.m_name);
                    }
                    if (auto itemScore = utils::findChild<ui::Text*>(newItem, "score"))
                    {
                        itemScore->setString(StringUtils::format("Score: %d", info.m_score));
                    }

                    listView->pushBackCustomItem(newItem);
                    newItem->setVisible(true);
                }
                
                listItem->removeFromParent();
            }



        }
        else // connect failed
        {
            CCLOG("Connection failed!");
        }

        });

    network::HttpClient::getInstance()->send(request);
    request->release();
    

    
    auto button_back = leaderboardLayer->getChildByName<ui::Button*>("button_back");
    button_back->setPressedActionEnabled(true);
    button_back->addClickEventListener([=](Ref*)
        {


            goToMainMenu(this);
        });

    return true;
};

//std::vector<Leaderboard::LeaderBoardInfo> Leaderboard::getLeaderBoard()
//{
//    return 
//}


bool Leaderboard::leaderboardCompare(Leaderboard::LeaderBoardInfo a, Leaderboard::LeaderBoardInfo b)
{
    return (a.m_score > b.m_score);
}

void Leaderboard::goToMainMenu(Ref* pSender)
{
    auto scene = MainMenu::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void Leaderboard::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}