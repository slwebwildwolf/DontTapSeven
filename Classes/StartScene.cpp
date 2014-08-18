#include "StartScene.h"
#include "MainMenuScene.h"
#include "Piano.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StartScene::init()
{
	if ( !LayerColor::initWithColor(Color4B::BLUE) )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
 
	auto label = LabelTTF::create("Hello World", "Arial", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
 
	scheduleOnce(SEL_SCHEDULE(&StartScene::initResource), 0.01f);

	return true;
}

void StartScene::initResource( float dt )
{
	Piano::getInstance()->init();
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}



