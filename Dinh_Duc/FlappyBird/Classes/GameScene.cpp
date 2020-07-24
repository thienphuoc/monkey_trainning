#include "GameScene.h"
#include "GameOverScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"
#include "Pipe.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    //return GameScene::create();
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{

    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    m_score = 0;
    tmpString = __String::createWithFormat("%d", m_score);

    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(backgroundSprite);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true); 

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    this->schedule(schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width);

    bird = new Bird(this);

    scoreLabel = Label::create(tmpString->getCString(), "fonts/Marker Felt.ttf", SCORE_FONT_SIZE*visibleSize.height);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.75);
    this->addChild(scoreLabel, 1000);

    


    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [](Touch* touch, Event* event)
    {
        return true;
    };

    touchListener->onTouchMoved = [](Touch* touch, Event* event)
    {
        
    };

    touchListener->onTouchEnded = [=](Touch* touch, Event* event)
    {
        bird->moveBird();
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


    return true;
}


void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void GameScene::spawnPipe(float dt)
{
    pipe.spawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact) 
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask())
        || ((BIRD_COLLISION_BITMASK == b->getCollisionBitmask()) && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        //CCLOG("Score: %d",m_score);
        auto scene = GameOverScene::createScene(m_score);

        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }

    else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask())
        || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        //CCLOG("Score + 1");
        m_score++;
        tmpString = __String::createWithFormat("%d", m_score);
        scoreLabel->setString(tmpString->getCString());
    }

    return true;
}