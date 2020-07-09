#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe::spawnPipe(Layer* layer)
{
	CCLOG("PIPE SPAWN!\n");

	auto topPipe = Sprite::create("Pipe.png");
	auto bottomPipe = Sprite::create("Pipe.png");
	auto pointNode = Node::create();

	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());
	auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP));

	auto random = CCRANDOM_0_1();

	if (random < LOWER_SCREEN_PIPE_THRESHOLD)
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	else if (random > UPPER_SCREEN_PIPE_THRESHOLD)
		random = UPPER_SCREEN_PIPE_THRESHOLD;

	auto topPipePosition = (random * visibleSize.height) + topPipe->getContentSize().height / 2;
	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);
	pointBody->setDynamic(false);

	topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	topPipeBody->setContactTestBitmask(true);
	bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	bottomPipeBody->setContactTestBitmask(true);
	pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
	pointBody->setContactTestBitmask(true);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);
	pointNode->setPhysicsBody(pointBody);

	topPipe->setPosition(Point(visibleSize.width + topPipe->getContentSize().width + origin.x , topPipePosition));
	bottomPipe->setPosition(Point(topPipe->getPosition().x, topPipePosition - (Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));
	pointNode->setPosition(Point(topPipe->getPosition().x, topPipePosition - (Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP) / 2 - topPipe->getContentSize().height / 2));

	layer->addChild(topPipe);
	layer->addChild(bottomPipe);
	layer->addChild(pointNode);
	
	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));
	auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));
	auto pointNodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0));

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);
	pointNode->runAction(pointNodeAction);
}