#include "MainMenuScene.h"
#include "GameScene.h"
Scene* MainMenuScene::createScene() {
	return create();
}
bool MainMenuScene::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* sprite = Sprite::create("Main Menu Background.png");
	this->addChild(sprite);
	Size size=Director::getInstance()->getVisibleSize();
	float temp = size.height - sprite->getContentSize().width;
	sprite->setPosition(size.width/2,size.height/2+30);
	Sprite* title = Sprite::create("Game Title.png");
	this->addChild(title);
	title->setPosition(size.width / 2, size.height  *0.75);//absolute position


	Button* button = Button::create("Play Button.png");
	button->setPosition(Vec2(size.width / 2, button->getBoundingBox().size.height*1.5+50));
	this->addChild(button);
	button->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
	Sprite* outerButton = Sprite::create("Play Button Outer.png");
	outerButton->setPosition(Vec2(size.width / 2, button->getBoundingBox().size.height * 1.5 + 50));
	this->addChild(outerButton);



	Button *soundButton = Button::create("Sound On.png");
	soundButton->setPosition(Vec2(0,0));
	soundButton->setAnchorPoint(Vec2(0, 0));
	sprite->addChild(soundButton);
	soundButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::volumTouch, this,sprite,soundButton));


	Button* achiveButton = Button::create("Achievements.png");
	sprite->addChild(achiveButton);
	achiveButton->setAnchorPoint(Vec2(1,0));
	achiveButton->setPosition(Vec2(sprite->getBoundingBox().size.width, 0));
	achiveButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::achiveTouch, this));

	return true;
}
void MainMenuScene::touchEvent(Ref* sender, Widget::TouchEventType type) {
	Scene* gameScene = GameScene::createScene();
	TransitionFade* tran = TransitionFade::create(2, gameScene);
	Director::getInstance()->replaceScene(tran);
	CCLOG("Clicked");
}



// on off button
void MainMenuScene::volumTouch(Ref* sender, Widget::TouchEventType type,Sprite* sprite,Button* soundButton) {
	
	sprite->removeChild(soundButton,NULL);
	Button* soundButton1 = Button::create("Sound Off.png");

	soundButton1->setPosition(Vec2(0, 0));
	soundButton1->setAnchorPoint(Vec2(0, 0));
	sprite->addChild(soundButton1);
	soundButton1->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::volumTouch1, this, sprite, soundButton1));
	CCLOG("on button");
}
void MainMenuScene::volumTouch1(Ref* sender, Widget::TouchEventType type, Sprite* sprite, Button* soundButton1) {
	sprite->removeChild(soundButton1,NULL);
	Button* soundButton = Button::create("Sound On.png");
	soundButton->setPosition(Vec2(0, 0));
	soundButton->setAnchorPoint(Vec2(0, 0));
	sprite->addChild(soundButton);
	soundButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::volumTouch, this, sprite, soundButton));
	CCLOG("off button");
}
//

void MainMenuScene::achiveTouch(Ref* sender, Widget::TouchEventType type) {
	CCLOG("archive clicked");
}