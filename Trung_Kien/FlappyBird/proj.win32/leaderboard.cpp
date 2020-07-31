#include "leaderboard.h"
#include<vector>
#include "extendLibrary/rapidjson/document.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGui.h"
#include <algorithm>
#include "GameScene.h"
//#include "rapidjson/document.h"
Scene* leaderboard::createScene() {
	return leaderboard::create();
}
bool leaderboard::init() {
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	CCLOG("aaaaaaaaaaaaa");


	auto leaderBoardLayer = CSLoader::getInstance()->createNode("csb/Leaderboard.csb");
	this->addChild(leaderBoardLayer);



	ui::ListView* listView = utils::findChild <ui::ListView*>(leaderBoardLayer, "ListView_2");
	//auto listview = utils::findChild <ui::ListView*>(leaderBoardLayer, "listView1");

	auto item = utils::findChild <ui::ImageView*>(leaderBoardLayer, "temp");
	
	
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
					std::vector<std::pair<std::string, int>> storageData;
					std::pair<std::string, int> temp;
                    for (int i = 0; i < document.Size(); i++) {
                        std::string name = document[i]["name"].GetString();
						int score = document[i]["score"].GetInt();
						temp.first = name.c_str();
						temp.second = score;
						storageData.push_back(temp);
                    }
					/*std::sort(storageData.begin(), storageData.end(), [](const std::pair<std::string, int>& a,
						const std::pair<std::string, int>& b) {
							return a.second > b.second;	
					});*/
					std::sort(storageData.begin(), storageData.end(), [](auto &a,auto &b) {
							return a.second > b.second;
					});
					for (int i = 0; i < document.Size(); i++) {

						auto temp = item->clone();
						temp->setOpacity(255);//0-255
						temp->getChildByName<ui::Text*>("name")->setString(storageData[i].first);
						temp->getChildByName<ui::Text*>("score")->setString(std::to_string(storageData[i].second));
						listView->pushBackCustomItem(temp);
					}
					item->removeFromParent();
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
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
	};
	keyListener->onKeyReleased = [](EventKeyboard::KeyCode keyCode, Event* event) {
		//Director::getInstance()->replaceScene(GameScene::createScene()); // lỗi nếu replace scene trước khi http loaded??
		Director::getInstance()->pushScene(GameScene::createScene());//push scene thì leaderscene vẫn còn nên http dù chưa chạy xong vẫn đc chạy tiếp??? do đó ko có lỗi
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	
	return true;
}
