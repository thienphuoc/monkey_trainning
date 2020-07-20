
#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics( );
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    return scene;
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

    auto backgroundSprite = Sprite::create("iphone/Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(backgroundSprite);

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    this->schedule(schedule_selector(GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCE * visibleSize.width);

    bird = new Bird(this);

    auto ContactListen = EventListenerPhysicsContact::create();
    ContactListen->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ContactListen, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    score = 0;
    __String *tempScore = __String::createWithFormat("%i", score);
    scoreLable = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", visibleSize.height * SCORE_FONT_SIZE);
    scoreLable->setColor(Color3B::WHITE);
    scoreLable->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
    this->addChild(scoreLable, 10000);

    this->scheduleUpdate();
    return true;
}

void GameScene::SpawnPipe(float dt)
{
    pipe.SpawnPipe(this);
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();

    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask())
         || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
       // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Hit.mp3");
       // CCLOG("SCORE: %i", score);
        auto scene = GameOverScene::createScene(score);

        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    else if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask())
        || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        //CCLOG("Point Scored");
       // CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Point.mp3");    
        score++;
        __String* tempScore = __String::createWithFormat("%i", score);
        scoreLable->setString(tempScore->getCString());
    }
    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    bird->fly();
    this->scheduleOnce(schedule_selector(GameScene::stopFlying), BIRD_FLY_DURATION);
    return true;
}
void GameScene::stopFlying(float dt)
{
    bird->stopFlying();
}
void GameScene::update(float dt)
{
    bird->Fall();
}
