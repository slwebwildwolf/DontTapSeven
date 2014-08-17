#include "MainMenuScene.h"
#include "ConstValue.h"
#include "ChanScene.h"
#include "JiejiScene.h"
#include "JingdianScene.h"
#include "JiSuScene.h"
#include "SleepScene.h"
USING_NS_CC;

cocos2d::Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	Size menuSize = Size(visibleSize.width/2,visibleSize.height/3);
	auto menu1 = createMenu(Color3B::WHITE,menuSize,"sleep", 50, Color3B::BLACK);
	menu1->setPosition(0,0);
	menu1->setTag(ObjectTag_MainMenu_Sleep);
	addChild(menu1);

	auto menu2 = createMenu(Color3B::BLACK,menuSize,"gengduo", 50, Color3B::WHITE);
	menu2->setPosition(visibleSize.width/2,0);
	menu2->setTag(ObjectTag_MainMenu_Gengduo);
	addChild(menu2);

	auto menu3 = createMenu(Color3B::BLACK,menuSize,"chan", 50, Color3B::WHITE);
	menu3->setPosition(0,visibleSize.height/3);
	menu3->setTag(ObjectTag_MainMenu_Chan);
	addChild(menu3);

	auto menu4 = createMenu(Color3B::WHITE,menuSize,"jisu", 50, Color3B::BLACK);
	menu4->setPosition(visibleSize.width/2,visibleSize.height/3);
	menu4->setTag(ObjectTag_MainMenu_JiSu);
	addChild(menu4);

	auto menu5 = createMenu(Color3B::WHITE,menuSize,"jingdian", 50, Color3B::BLACK);
	menu5->setPosition(0,visibleSize.height/3*2);
	menu5->setTag(ObjectTag_MainMenu_Jingdian);
	addChild(menu5);

	auto menu6 = createMenu(Color3B::BLACK,menuSize,"jieji", 50, Color3B::WHITE);
	menu6->setPosition(visibleSize.width/2,visibleSize.height/3*2);
	menu6->setTag(ObjectTag_MainMenu_Jieji);
	addChild(menu6);

	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,menu1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),menu2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),menu3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),menu4);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),menu5);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),menu6);

	return true;
}

Sprite* MainMenu::createMenu(Color3B color, Size size,std::string label, float fontSize, Color3B textColor)
{
	auto m = Sprite::create();

	//设置大小
	m->setContentSize(size);
	//设置锚点为左下角
	m->setAnchorPoint(Point::ZERO);
	//设置区域
	m->setTextureRect(Rect(0, 0, size.width, size.height));
	//设置颜色
	m->setColor(color);

	//设置文字
	auto myLabel = Label::create();
	myLabel->setString(GetXMLString(label));
	myLabel->setSystemFontSize(fontSize);
	myLabel->setColor(textColor);
	
	m->addChild(myLabel);
	myLabel->setPosition(size.width/2, size.height/2);
	return m;
}

bool MainMenu::onTouchBegan( Touch* t, Event* e )
{
	Piano::getInstance()->playTouch();
	auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标  
	Point locationInNode = target->convertToNodeSpace(t->getLocation());  
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode))//判断触摸点是否在目标的范围内
		switch (target->getTag())
		{
		case ObjectTag_MainMenu_Jingdian:
			{
				auto scene =JingdianScene::createScene();  
				Director::getInstance()->pushScene(scene); 
				CCLog("Jing Dian Scene");		
			}
			break;
		case ObjectTag_MainMenu_Jieji:
			{
				auto scene =JiejiScene::createScene();  
				Director::getInstance()->pushScene(scene); 
				CCLog("Jie Ji Scene");	
			}
			break;

		case ObjectTag_MainMenu_Chan:
			{
				auto scene =ChanScene::createScene();  
				Director::getInstance()->pushScene(scene); 	
			}
			break;
		case ObjectTag_MainMenu_JiSu:
			{
				auto scene =JiSuScene::createScene();  
				Director::getInstance()->pushScene(scene); 
				CCLog("Ji Su Scene");		
			}
			break;
		case ObjectTag_MainMenu_Sleep:
			{
				auto scene =JiejiScene::createScene();  
				Director::getInstance()->pushScene(scene); 
				CCLog("Sleep Scene");	
			}
			break;
		case ObjectTag_MainMenu_Gengduo:
			{
				auto scene =ChanScene::createScene();  
				Director::getInstance()->pushScene(scene); 
				CCLog("Chan Scene");		
			}
			break;
		
		default:
			break;
		}

	return false;  
}

 ////////////////////////////////////////////////////////////////////////////////////
/*ValueVector p_map = FileUtils::getInstance()->getValueVectorFromFile("Chinese.xml");  
ValueMap  map=p_map.at(0).asValueMap();
std::string info=map.at(label).asString();
//auto myLabel = LabelBMFont::create(info, "fonts/Chinese.fnt");
auto myLabel = Label::createWithTTF(label,"fonts/yahei_mono.ttf",fontSize);
myLabel->setColor(textColor);*/
////////////////////////////////////////////////////////////////////////////////////////
	/*ValueVector p_map = FileUtils::getInstance()->getValueVectorFromFile("Chinese.xml");  

	ValueMap  map=p_map.at(0).asValueMap();

	std::string info=map.at(label).asString();
	auto myLabel = Label::createWithTTF(info,"fonts/yahei_mono.ttf",fontSize);
	myLabel->setString(info);
	myLabel->setColor(Color3B::RED); */
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	auto myLabel = Label::create();
	myLabel->setString(label);
	myLabel->setSystemFontSize(fontSize);
	//myLabel->setTextColor(textColor);
	myLabel->setColor(Color3B::BLUE);*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// 	auto myLabel = Label::createWithSystemFont(info, "DroidSansFallback", fontSize);
// #endif

// #if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
// 	auto myLabel = Label::createWithTTF(info,"fonts/yahei_mono.ttf",fontSize);
// #endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*ValueMap value_map = FileUtils::getInstance()->getValueMapFromFile("Chinese.plist");
	std::string info = value_map.at(label).asString();*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////