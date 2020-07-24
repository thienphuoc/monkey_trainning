#include "UI.h"
#include "Definitions.h"
#include "GameScene.h"
#include "MainMenu.h"

USING_NS_CC;

UI::UI(Layer* layer, int& gameState)
{
	this->gameState = &gameState;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	MenuItemSprite* pauseItem = MenuItemSprite::create(Sprite::create("Pause Button.png"), 
														Sprite::create("Pause Button.png"), 
														Sprite::create("Pause Button.png"),
														CC_CALLBACK_1(UI::pauseGame,this));
	pauseItem->setPosition(origin.x + visibleSize.width - pauseItem->getContentSize().width / 2,
		origin.y + visibleSize.height - pauseItem->getContentSize().height / 2
	);

	Menu* menuButtons = Menu::create(pauseItem, NULL);
	menuButtons->setPosition(Vec2::ZERO);
	layer->addChild(menuButtons);

	pauseBackground = Sprite::create("Pause Background.png");
	pauseBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	pauseBackground->setOpacity(0);
	layer->addChild(pauseBackground);

	MenuItemImage* overlayPauseWindowItem = MenuItemImage::create("Pause Window.png",
																"Pause Window.png",
																"Pause Window.png",
																NULL);
	MenuItemSprite* resumeItem = MenuItemSprite::create(Sprite::create("Resume Button.png"),
															Sprite::create("Resume Button.png"),
															Sprite::create("Resume Button.png"),
															CC_CALLBACK_1(UI::pauseGame,this));
	resumeItem->setPosition(-overlayPauseWindowItem->getContentSize().width / 4,
		resumeItem->getPosition().y);
	
	MenuItemSprite* mainMenuItem = MenuItemSprite::create(Sprite::create("Home Button.png"),
															Sprite::create("Home Button.png"),
															Sprite::create("Home Button.png"),
															CC_CALLBACK_1(UI::goToMainMenu, this));
	mainMenuItem->setPosition(overlayPauseWindowItem->getContentSize().width / 4,
		mainMenuItem->getPosition().y);

	pauseMenu = Menu::create(overlayPauseWindowItem, resumeItem, mainMenuItem, NULL);
	////////////
	pauseMenu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height *1.5);
	layer->addChild(pauseMenu);
}

void UI::showGameOver(Layer* layer)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	Sprite* background = Sprite::create("Pause Background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	background->setOpacity(0);
	layer->addChild(background);
	background->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 2.5), FadeIn::create(GAME_OVER_BACKGROUND_FADE_IN_TIME), NULL));
	
	MenuItemImage* overlayWindowItem = MenuItemImage::create("Pause Window.png",
		"Pause Window.png",
		"Pause Window.png",
		NULL);
	MenuItemSprite* retryItem = MenuItemSprite::create(Sprite::create("Retry Button.png"),
		Sprite::create("Retry Button.png"),
		Sprite::create("Retry Button.png"),
		CC_CALLBACK_1(UI::retry, this));
	retryItem->setPosition(overlayWindowItem->getContentSize().width / 4, retryItem->getPosition().y);

	MenuItemSprite* mainMenuItem = MenuItemSprite::create(Sprite::create("Home Button.png"),
		Sprite::create("Home Button.png"),
		Sprite::create("Home Button.png"),
		CC_CALLBACK_1(UI::goToMainMenu, this));
	mainMenuItem->setPosition(-overlayWindowItem->getContentSize().width / 4, mainMenuItem->getPosition().y);

	Menu* menu = Menu::create(overlayWindowItem,mainMenuItem,retryItem,NULL);
	/////////
	menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height *1.5);

	EaseBounceOut* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)));
	Sequence* menuShowSeq = Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME * 2.5), menuActionEasing, NULL);
	menu->runAction(menuShowSeq);
}

void UI::retry(cocos2d::Ref* pSender)
{
	Scene* scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(SPLASH_SCENE_TRANSITION_TIME, scene));

}

void UI::goToMainMenu(cocos2d::Ref* pSender)
{
	Scene* scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(SPLASH_SCENE_TRANSITION_TIME, scene));

}

void UI::pauseGame(cocos2d::Ref* pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	if (STATE_PLAYERS_TURN == *gameState)
	{
		*gameState = STATE_PAUSED;
		pauseBackground->runAction(FadeIn::create(PAUSE_BACKGROUND_FADE_TIME));

		EaseBounceOut* menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)));
		pauseMenu->runAction(menuActionEasing);
	}
	else if (STATE_PAUSED == *gameState)
	{
		*gameState = STATE_PLAYERS_TURN;
		pauseBackground->runAction(FadeOut::create(PAUSE_BACKGROUND_FADE_TIME));

		EaseBounceOut * menuActionEasing = EaseBounceOut::create(MoveTo::create(MENU_MOVE_BOUNCE_DURATION, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 1.5)));		pauseMenu->runAction(menuActionEasing);
	
	
	}
}