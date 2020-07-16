#include "leaderboard.h"
#include<vector>
#include "extendLibrary/rapidjson/document.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGui.h"
//#include "rapidjson/document.h"
using namespace rapidjson;  
Scene* leaderboard::createScene() {
	return leaderboard::create();
}
bool leaderboard::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	CCLOG("aaaaaaaaaaaaa");


	auto leaderBoardLayer = CSLoader::getInstance()->createNode("csb/Leaderboard.csb");
	this->addChild(leaderBoardLayer);

	auto listView = leaderBoardLayer->getChildByName<ui::ListView*>("listView");


	HttpRequest* request = new HttpRequest();
	request->setRequestType(HttpRequest::Type::GET);
	request->setUrl("https://isschool.firebaseio.com/leaderboard.json");
	request->setResponseCallback([=](HttpClient* sender, HttpResponse* response)  {
        if (response->getResponseCode() == 200) {
			std::vector<char>* buffer = response->getResponseData();

			std::string data = std::string(buffer->begin(), buffer->end());

			if (!data.empty())
			{
				//CCLOG("data:%s", data.c_str());
                rapidjson::Document document;
                document.Parse(data.c_str());
                if (document.IsArray()) {
                    //rapidjson::SizeType size = document.Size();
					std::vector<std::pair<std::string, int>> storageData;
					std::pair<std::string, int> temp;
                    for (int i = 0; i < document.Size(); i++) {
                        std::string name = document[i]["name"].GetString();
						int score = document[i]["score"].GetInt();
						temp.first = name.c_str();
						temp.second = score;
						storageData.push_back(temp);
                    }

					for (int i = 0; i < document.Size(); i++) {
						auto nameLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
						auto scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
						nameLabel->setPosition(Vec2(origin.x+nameLabel->getContentSize().width+60, visibleSize.height + origin.y - i * nameLabel->getContentSize().height-60));
						scoreLabel->setPosition(Vec2(visibleSize.width-scoreLabel->getContentSize().width-60, visibleSize.height + origin.y - i * scoreLabel->getContentSize().height-60));
						nameLabel->setString(storageData[i].first);
						scoreLabel->setString(std::to_string(storageData[i].second));
						this->addChild(nameLabel);
						this->addChild(scoreLabel);


						/*auto nameUI = ui::Text::create();
						nameUI->setString(storageData[i].first);
						nameUI->setColor(cocos2d::Color3B::RED);
						

						auto scoreUI = ui::Text::create();
						scoreUI->setString(std::to_string(storageData[i].second));
						nameUI->setColor(cocos2d::Color3B::RED);

						listView->addChild(nameUI);

						auto avatar = ui::ImageView::create("settingsButton.png");*/

					}
					
                }
			}
			else
			{
			}
        }
        else {
            //Error
        }



	});
	request->setTag("Get test");
	HttpClient::getInstance()->send(request);
	request->release();
	return true;
}


