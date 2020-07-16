#include "winner.h"
#include"GameScene.h"
 Scene* winner::createScene() {
	return create();
}
 bool winner::init() {
	 auto visibleSize = Director::getInstance()->getVisibleSize();
	 Vec2 origin = Director::getInstance()->getVisibleOrigin();
	 Sprite *endGameScene = Sprite::create("Main Menu Background.png");
	 auto label = Label::createWithTTF("EndGame", "fonts/Marker Felt.ttf", 24);
	 label->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height - label->getContentSize().height));
	 this->addChild(label, 1);
	 this->addChild(endGameScene);
	 Size size = Director::getInstance()->getVisibleSize();
	 endGameScene->setPosition(size.width / 2, size.height / 2 + 30);
	 
	 Button* button = Button::create("Play Button.png");
	 button->setPosition(Vec2(size.width / 2, button->getBoundingBox().size.height * 1.5 + 50));
	 endGameScene->addChild(button);
	 button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		 Scene* gameScene = GameScene::createScene();
		 TransitionFade* tran = TransitionFade::create(2, gameScene);
		 Director::getInstance()->replaceScene(tran);
	});
	 Sprite* outerButton = Sprite::create("Play Button Outer.png");
	outerButton->setPosition(Vec2(size.width / 2, button->getBoundingBox().size.height * 1.5 + 50));
	 endGameScene->addChild(outerButton);
	 
	 Sprite* title = Sprite::create("Game Title.png");
	 this->addChild(title);
	 title->setPosition(size.width / 2, size.height * 0.75);//absolute position
	 return true;
}
