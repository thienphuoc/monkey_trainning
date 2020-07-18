#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	flappyBird = Sprite::create("Ball.png");
	flappyBird->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto flappyBirdBody = PhysicsBody::createCircle(flappyBird->getContentSize().width/2);
	flappyBirdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBirdBody->setContactTestBitmask(true);

	flappyBird->setPhysicsBody(flappyBirdBody);

	layer->addChild(flappyBird, 100);

}

void Bird::moveBird()
{
	/*auto flap = MoveBy::create(BIRD_FLAP*visibleSize.height, Vec2(0.0f, flappyBird->getContentSize().height * 2.5));
	flappyBird->runAction(flap);*/
	flappyBird->getPhysicsBody()->setVelocity(Vec2(0.0f, 64.0f));
}