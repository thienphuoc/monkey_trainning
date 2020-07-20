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


	auto backgroundLeaderBoard = leaderBoardLayer->getChildByName<ui::ImageView*>("listViewBackground");

	ui::ListView* listView = backgroundLeaderBoard->getChildByName<ui::ListView*>("listView1");
	//auto listview = utils::findChild <ui::ListView*>(leaderBoardLayer, "listView1");

	auto item = leaderBoardLayer->getChildByName<ui::ImageView*>("item");
	
	
	//this->addChild(leaderBoardLayer);
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
					auto tempList = ui::ListView::create();
					tempList->setDirection(ui::ScrollView::Direction::VERTICAL);
					tempList->setClippingEnabled(false);
					tempList->setPosition(Vec2(0, 500));
					//tempList->setAnchorPoint(Vec2(0.5,0.5));
					//ui::ListView* tempList = listView->clone();
					
					for (int i = 0; i < document.Size(); i++) {
						auto nameLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
						auto scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
						nameLabel->setPosition(Vec2(origin.x+nameLabel->getContentSize().width+60, visibleSize.height + origin.y - i * nameLabel->getContentSize().height-60));
						scoreLabel->setPosition(Vec2(visibleSize.width-scoreLabel->getContentSize().width-60, visibleSize.height + origin.y - i * scoreLabel->getContentSize().height-60));
						nameLabel->setString(storageData[i].first);
						scoreLabel->setString(std::to_string(storageData[i].second));
						this->addChild(nameLabel);
						this->addChild(scoreLabel);

						//////


						auto temp = item->clone();
						temp->getChildByName<ui::Text*>("name")->setString(storageData[i].first);
						temp->getChildByName<ui::Text*>("score")->setString(std::to_string(storageData[i].second));
						temp->setVisible(true);
						//listView->pushBackCustomItem(temp);
						tempList->pushBackCustomItem(temp);
					}
					//listView->setPositionZ(1111);
					leaderBoardLayer->removeChild(item);
					backgroundLeaderBoard->addChild(tempList);
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


