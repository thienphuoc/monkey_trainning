

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "SonarCocosHelperCPP/SonarFrameworks.h"
#include "proj.win32/Definition.h"
#include "proj.win32/GameScene.h"
#include "GameOverScene.h"


#include "SplashScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto mainMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
    this->addChild(mainMenu);

    //Go to Game

    auto menu_background = utils::findChild<ui::ImageView*>(mainMenu, "background");
    menu_background->setVisible(true);

    auto button_retry = utils::findChild<ui::Button*>(menu_background, "go_to_game_button");
    button_retry->setPressedActionEnabled(true);
    button_retry->addClickEventListener([=](Ref*)-> void
        {
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(2, scene));

        });

    auto button_sound = utils::findChild<ui::Button*>(menu_background, "sound_button");
    button_sound->setPressedActionEnabled(true);
    
    button_sound->addClickEventListener([=](Ref*)-> void
        {
            int i = 0;
            auto sprite_sound_on = Sprite::create("res/Sound On.png");
            sprite_sound_on->setPosition(701.95, 63.42);

            auto sprite_sound_off = Sprite::create("res/Sound off.png");
            sprite_sound_off->setPosition(701.95, 63.42);
            if (i % 2 == 0)
            {
                this->addChild(sprite_sound_off);
                this->addChild(sprite_sound_on);
                sprite_sound_off->runAction(FadeIn::create(10000));
                sprite_sound_on->runAction(FadeOut::create(10000));


            }
            else
            {

                this->addChild(sprite_sound_off);
                this->addChild(sprite_sound_on);
                sprite_sound_on->runAction(FadeIn::create(10000));
                sprite_sound_off->runAction(FadeOut::create(10000));
            }
            i++;

        });


    return true;
}



