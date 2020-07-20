

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "SonarCocosHelperCPP/SonarFrameworks.h"
#include "proj.win32/Definition.h"
#include "proj.win32/GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();

    auto layer = MainMenuScene::create();

    scene->addChild(layer);

    return scene;
}



// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //SonarCocosHelper::UI::AddCentredBackground(MAIN_MENU_BACKGROUND_FILEPATH, this);
    Sprite* bacground = Sprite::create(MAIN_MENU_BACKGROUND_FILEPATH);
    bacground->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(bacground);

    Sprite *title = Sprite::create(MAIN_MENU_TITLE_FILEPATH);
    title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height *0.75 + origin.y));
    this->addChild(title);

    Button *playButton = Button::create(MAIN_MENU_PLAY_BUTTON, MAIN_MENU_PLAY_BUTTON_OUTER);
    playButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2.5 + origin.y));
    this -> addChild(playButton);

    playButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
    playButton->setTag(TAG_MAIN_MENU_PLAY_BUTTON);

    Sprite* playButtonOuter = Sprite::create(MAIN_MENU_PLAY_BUTTON_OUTER);
    playButtonOuter->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2.5 + origin.y));
    this->addChild(playButtonOuter);

    SonarCocosHelper::UI ui;

    //123
    ui.AddAudioToggle(SOUND_ON_BUTTON, SOUND_ON_BUTTON_PRESSED, SOUND_OFF_BUTTON, SOUND_OFF_BUTTON_PRESSED, this,
        SonarCocosHelper::UIButtonPosition::eBottomRight);

    Button* achievementsButton = Button::create(ACHIEVEMENTS_BUTTONS, ACHIEVEMENTS_BUTTONS_PRESSED);
    achievementsButton->setPosition(Vec2(achievementsButton->getContentSize().width/2 + origin.x, achievementsButton->getContentSize().height/2 + origin.y));
    this->addChild(achievementsButton);
    achievementsButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));

    achievementsButton->setTag(TAG_ACHIEVEMENTS_BUTTON);

    return true;
}

void MainMenuScene::touchEvent(Ref* sender, Widget::TouchEventType type)
{
    Node* node = (Node*)sender;
    switch (type) 
    {
    case Widget::TouchEventType::BEGAN:
        break;

    case Widget::TouchEventType::MOVED:
        break;

    case Widget::TouchEventType::ENDED:
        if (TAG_MAIN_MENU_PLAY_BUTTON == node->getTag())
        {
            Scene* scene = GameScene::createScene();
            TransitionFade* transitionFade = TransitionFade::create(SCENE_TRANSITION_TIME, scene);
            Director::getInstance()->replaceScene(scene);
        }
        else if (TAG_ACHIEVEMENTS_BUTTON == node->getTag())
        {
            //SonarCocosHelper::GameCenter::showAchievements();
            //SonarCocosHelper::GooglePlayServices::showAchievements();
        }
        break;

    case Widget::TouchEventType::CANCELED:
        break;

    default:
        break;
    }
}

