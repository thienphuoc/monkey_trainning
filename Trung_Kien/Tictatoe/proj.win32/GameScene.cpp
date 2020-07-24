#include "GameScene.h"
#include<iostream>
#include"winner.h"
#include"MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "AI.h"

bool isSoundOn;
bool isPlayWithBot;
Scene* GameScene::createScene(bool b,bool bot) {
	isSoundOn = b;
	isPlayWithBot = bot;
	return GameScene::create();
}
bool GameScene::init() {
	Sprite* gameScene = Sprite::create("Main Menu Background.png");
	this->addChild(gameScene);
	Size size = Director::getInstance()->getVisibleSize();
	gameScene->setPosition(size.width / 2, size.height / 2);
	initDigitMap();
	loadMap(gameScene, digitMap, gameScene->getBoundingBox().size);
	return true;
}
void GameScene::loadMap(Sprite* sprite, int digitMap[][3], Size sizeBox) {
	//initDigitMap();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			buttonMap[i][j] = Button::create("rec.png");
			sprite->addChild(buttonMap[i][j]);
			buttonMap[i][j]->setAnchorPoint(Vec2(0, 0));
			Size size = buttonMap[i][j]->getBoundingBox().size;
			buttonMap[i][j]->setPosition(Vec2(i * (size.width+5) + sizeBox.width / 2 - 1.5 * size.width, j * (size.height+5) + 90));
			buttonMap[i][j]->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
				tick(buttonMap, size, i, j, digitMap);
				if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("punch.mp3");
				});
		}
	}
}
int GameScene::tick(Button* buttonMap[][3], Size size, int i, int j, int digitMap[][3]) {
	bool b = buttonMap[i][j]->getChildren().size() == 0;
	if (!isPlayWithBot) {
		if (b) {
			if (GameScene::turn % 2 == 0) {
				Sprite* xTick = Sprite::create("X.png");
				xTick->setAnchorPoint(Vec2(0.5, 0.5));
				xTick->setPosition(size.width / 2, size.height / 2);
				std::string tag = std::to_string(i) + std::to_string(j);
				buttonMap[i][j]->addChild(xTick);
				digitMap[i][j] = 1;

				if (check(i, j) != 0)return check(i, j);
				if (check1() != 0)return check1();
				if (check2() != 0)return check2();


			}
			else if (GameScene::turn % 2 == 1) {
				if (!isPlayWithBot) {
					Sprite* yTick = Sprite::create("O.png");
					yTick->setAnchorPoint(Vec2(0.5, 0.5));
					yTick->setPosition(size.width / 2, size.height / 2);
					buttonMap[i][j]->addChild(yTick);
					digitMap[i][j] = 2;
					if (check(i, j) != 0)return check(i, j);
					if (check1() != 0)return check1();
					if (check2() != 0)return check2();
				}

			}
			GameScene::turn++;
		}
	}else {//play with bot
		AI* ai = new AI();
		if (b) {
			//player tick
			Sprite* xTick = Sprite::create("X.png");
			xTick->setAnchorPoint(Vec2(0.5, 0.5));
			xTick->setPosition(size.width / 2, size.height / 2);
			std::string tag = std::to_string(i) + std::to_string(j);
			buttonMap[i][j]->addChild(xTick);
			digitMap[i][j] = 1;
			if (check(i, j) != 0)return check(i, j);
			if (check1() != 0)return check1();
			if (check2() != 0)return check2();

			// bot tick
			Sprite* yTick = Sprite::create("O.png");
			yTick->setAnchorPoint(Vec2(0.5, 0.5));
			yTick->setPosition(size.width / 2, size.height / 2);
			std::pair<int, int> t = GameScene::aiGreedy(ai);
			int ii = t.first, jj = t.second;
			buttonMap[ii][jj]->addChild(yTick);
			digitMap[ii][jj] = 2;
			if (check(ii, jj) != 0)return check(ii, jj);
			if (check1() != 0)return check1();
			if (check2() != 0)return check2();
		}
	}

	return 0;
}
void GameScene::print() {
	CCLOG("pass function thanh cong");
}
int GameScene::check(int i, int j) {
	int hangNgangX = 0, hangDocX = 0, hangDocY = 0, hangNgangY = 0;
	for (int c = 0; c < 3; c++) {
		if (digitMap[i][c] == 1) {
			hangDocX++;
			if (hangDocX == 3) {
				//endgame
				for (int m = 0; m < 3; m++) {
					Size size = buttonMap[i][m]->getBoundingBox().size;
					//spriteMap[i][m]->removeAllChildren();
					Sprite* xTick = Sprite::create("X Win.png");
					xTick->setAnchorPoint(Vec2(0.5, 0.5));
					xTick->setPosition(size.width / 2, size.height / 2);
					buttonMap[i][m]->addChild(xTick);
					//spriteMap[i][m]->addChild(Sprite::create("X Win.png"), 2);
				}

				Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
				if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
				return 1;
			}
		}
		if (digitMap[c][j] == 1) {
			hangNgangX++;
			if (hangNgangX == 3) {
				//endgame
				for (int m = 0; m < 3; m++) {
					Size size = buttonMap[m][j]->getBoundingBox().size;
					Sprite* xTick = Sprite::create("X Win.png");
					xTick->setAnchorPoint(Vec2(0.5, 0.5));
					xTick->setPosition(size.width / 2, size.height / 2);
					buttonMap[m][j]->addChild(xTick);
				}
				Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
				if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
				return 1;
			}
		}
		if (digitMap[i][c] == 2) {
			hangDocY++;
			if (hangDocY == 3) {
				//endgame
				for (int m = 0; m < 3; m++) {
					Size size = buttonMap[i][m]->getBoundingBox().size;
					Sprite* yTick = Sprite::create("O Win.png");
					yTick->setAnchorPoint(Vec2(0.5, 0.5));
					yTick->setPosition(size.width / 2, size.height / 2);
					buttonMap[i][m]->addChild(yTick);
				}
				Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
				if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
				return 2;
			}
		}
		if (digitMap[c][j] == 2) {
			hangNgangY++;
			if (hangNgangY == 3) {
				//endgame
				for (int m = 0; m < 3; m++) {
					Size size = buttonMap[m][j]->getBoundingBox().size;
					Sprite* yTick = Sprite::create("O Win.png");
					yTick->setAnchorPoint(Vec2(0.5, 0.5));
					yTick->setPosition(size.width / 2, size.height / 2);
					buttonMap[m][j]->addChild(yTick);
				}
				Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
				if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
				return 2;
			}
		}

	}
	return 0;
}
int GameScene::check1() {
	int xwin = 0, ywin = 0, xwin1 = 0, ywin1 = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				if (digitMap[i][j] == 1) {
					xwin++;
					if (xwin == 3) {
						for (int m = 0; m < 3; m++) {
							Size size = buttonMap[m][m]->getBoundingBox().size;
							Sprite* xTick = Sprite::create("X Win.png");
							xTick->setAnchorPoint(Vec2(0.5, 0.5));
							xTick->setPosition(size.width / 2, size.height / 2);
							buttonMap[m][m]->addChild(xTick);
						}
						Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
						if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
						return 1;
					}

				}
				if (digitMap[i][j] == 2) {
					ywin++;
					if (ywin == 3) {
						for (int m = 0; m < 3; m++) {
							Size size = buttonMap[m][m]->getBoundingBox().size;
							Sprite* yTick = Sprite::create("O Win.png");
							yTick->setAnchorPoint(Vec2(0.5, 0.5));
							yTick->setPosition(size.width / 2, size.height / 2);
							buttonMap[m][m]->addChild(yTick);
						}
						Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
						if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
						return 2;
					}
				}
			}
			if (i == 2 - j) {
				if (digitMap[i][j] == 1) {
					xwin1++;
					if (xwin1 == 3) {
						for (int m = 0; m < 3; m++) {
							Size size = buttonMap[m][2 - m]->getBoundingBox().size;
							Sprite* xTick = Sprite::create("X Win.png");
							xTick->setAnchorPoint(Vec2(0.5, 0.5));
							xTick->setPosition(size.width / 2, size.height / 2);
							buttonMap[m][2 - m]->addChild(xTick);
						}
						Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
						if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
						return 1;
					}

				}
				if (digitMap[i][j] == 2) {
					ywin1++;
					if (ywin1 == 3) {
						for (int m = 0; m < 3; m++) {
							Size size = buttonMap[m][2 - m]->getBoundingBox().size;
							Sprite* yTick = Sprite::create("O Win.png");
							yTick->setAnchorPoint(Vec2(0.5, 0.5));
							yTick->setPosition(size.width / 2, size.height / 2);
							buttonMap[m][2 - m]->addChild(yTick);
						}
						Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
						if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
						return 2;
					}
				}
			}
		}
	}
	return 0;
}
int GameScene::check2() {
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (digitMap[i][j] != -1) count++;
		}
	}
	if (count == 9) {
		Director::getInstance()->replaceScene(MainMenuScene::createScene());
		if (isSoundOn) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("victory.mp3");
		return 3;
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
std::pair<int, int> GameScene::aiGreedy(AI *ai){
	std::pair<int, int> Pair;
	bool temp1 = false;
	int tempMap[3][3];
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			tempMap[x][y] = digitMap[x][y];
		}
	}
	for (int ii = 0; ii < 3; ii++) {
		for (int jj = 0; jj < 3; jj++) {
			if (digitMap[ii][jj] == -1) {
				digitMap[ii][jj] = 2;
				if (check(ii, jj) == 2 ||check1() == 2) {//o win
					Pair.first = ii;
					Pair.second = jj;
					return Pair;
				}
				digitMap[ii][jj] = tempMap[ii][jj];

			}
		}
	}
	return ai->basic(digitMap);
}