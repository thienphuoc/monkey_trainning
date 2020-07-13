#include "GameScene.h"
#include<iostream>
#include"winner.h"
#include"MainMenuScene.h"
Scene* GameScene::createScene() {
	return create();
}
bool GameScene::init() {
	Sprite* gameScene = Sprite::create("Main Menu Background.png");
	this->addChild(gameScene);
	Size size = Director::getInstance()->getVisibleSize();
	gameScene->setPosition(size.width / 2, size.height / 2);
	initDigitMap();
	std::cout << "asd";
	loadMap(gameScene,digitMap,gameScene->getBoundingBox().size);
	return true;
}
void GameScene::loadMap(Sprite* sprite, int digitMap[][3],Size sizeBox) {
	//initDigitMap();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			buttonMap[i][j] = Button::create("rec.png");
			sprite->addChild(buttonMap[i][j]);
			buttonMap[i][j]->setAnchorPoint(Vec2(0, 0));
			Size size = buttonMap[i][j]->getBoundingBox().size;
			buttonMap[i][j]->setPosition(Vec2(i*size.width+sizeBox.width/2-1.5*size.width,j*size.height+90));
			buttonMap[i][j]->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
				tick(buttonMap, size, i, j,digitMap);
			});
		}
	}
}
int GameScene::tick(Button* buttonMap[][3],Size size,int i, int j,int digitMap[][3]) {
	bool b = buttonMap[i][j]->getChildren().size() == 0;
	if (b) {
		if (GameScene::turn % 2==0) {
			Sprite* xTick = Sprite::create("X.png");
			xTick->setAnchorPoint(Vec2(0.5, 0.5));
			xTick->setPosition(size.width / 2, size.height / 2);
			std::string tag = std::to_string(i) + std::to_string(j);
			buttonMap[i][j]->addChild(xTick);
			digitMap[i][j] = 1;
			
			check(i,j);
			check1();
			
		}
		else if (GameScene::turn % 2 == 1) {
			Sprite* yTick = Sprite::create("O.png");
			yTick->setAnchorPoint(Vec2(0.5, 0.5));
			yTick->setPosition(size.width / 2, size.height / 2);
			buttonMap[i][j]->addChild(yTick);
			digitMap[i][j] = 2;
			check(i,j);
			check1();
		}
		GameScene::turn++;
	}
	return 0;
}

int GameScene::check(int i,int j) {
	int hangNgangX = 0, hangDocX = 0, hangDocY = 0, hangNgangY = 0;
	for (int c = 0; c < 3; c++) {
		if (digitMap[i][c] == 1) {
			hangDocX++;
			if (hangDocX == 3) {
				//endgame
				Director::getInstance()->replaceScene(MainMenuScene::createScene());
				return 1;
			}
		}
		if (digitMap[c][j] == 1) {
			hangNgangX++;
			if (hangNgangX == 3) {
				//endgame
				Director::getInstance()->replaceScene(MainMenuScene::createScene());
				return 1;
			}
		}
		if (digitMap[i][c] == 2) {
			hangDocY++;
			if (hangDocY == 3) {
				//endgame
				Director::getInstance()->replaceScene(MainMenuScene::createScene());
				return 1;
			}
		}
		if (digitMap[c][j] == 2) {
			hangNgangY++;
			if (hangNgangY == 3) {
				//endgame
				Director::getInstance()->replaceScene(MainMenuScene::createScene());
				return 1;
			}
		}
		
	}
	return 0;
}
int GameScene::check1() {
	int xwin = 0,ywin=0, xwin1 = 0, ywin1 = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				if (digitMap[i][j] == 1) {
					xwin++;
					if (xwin == 3) {
						Director::getInstance()->replaceScene(MainMenuScene::createScene());
						return 1;
					}

				}
				if (digitMap[i][j] == 2) {
					ywin++;
					if (ywin == 3) {
						Director::getInstance()->replaceScene(MainMenuScene::createScene());
						return 2;
					}
				}
			}
			if (i == 2 - j) {
				if (digitMap[i][j] == 1) {
					xwin1++;
					if (xwin1 == 3) {
						Director::getInstance()->replaceScene(MainMenuScene::createScene());
						return 1;
					}

				}
				if (digitMap[i][j] == 2) {
					ywin1++;
					if (ywin1 == 3) {
						Director::getInstance()->replaceScene(MainMenuScene::createScene());
						return 2;
					}
				}
			}
		}
	}
	return 0;
}
void GameScene::initDigitMap() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			digitMap[i][j] = -1;
		}
	}
}