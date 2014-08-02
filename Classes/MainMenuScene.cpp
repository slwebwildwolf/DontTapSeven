#include "MainMenuScene.h"
#include "ObjectTag.h"
#include "HelloWorldScene.h"
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
	Size menuSize = Size(visibleSize.width/2,visibleSize.height/2);
	auto menu1 = createMenu(Color3B::WHITE,menuSize,"chan", 50, Color3B::BLACK);
	menu1->setPosition(0,0);
	menu1->setTag(ObjectTag_MainMenu_Chan);
	addChild(menu1);

	auto menu2 = createMenu(Color3B::BLACK,menuSize,"gengduo", 50, Color3B::WHITE);
	menu2->setPosition(visibleSize.width/2,0);
	menu2->setTag(ObjectTag_MainMenu_Gengduo);
	addChild(menu2);

	auto menu3 = createMenu(Color3B::BLACK,menuSize,"jingdian", 50, Color3B::WHITE);
	menu3->setPosition(0,visibleSize.height/2);
	menu3->setTag(ObjectTag_MainMenu_Jingdian);
	addChild(menu3);

	auto menu4 = createMenu(Color3B::WHITE,menuSize,"jieji", 50, Color3B::BLACK);
	menu4->setPosition(visibleSize.width/2,visibleSize.height/2);
	menu4->setTag(ObjectTag_MainMenu_Jieji);
	addChild(menu4);

	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1 ,menu1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone() ,menu2);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone() ,menu3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(),menu4);

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
	ValueVector p_map = FileUtils::getInstance()->getValueVectorFromFile("Chinese.xml");  
	ValueMap  map=p_map.at(0).asValueMap();
	std::string info=map.at(label).asString();
	auto myLabel = LabelBMFont::create(info, "fonts/Chinese.fnt");
	myLabel->setColor(textColor);
	 
	m->addChild(myLabel);
	myLabel->setPosition(size.width/2, size.height/2);
	return m;
}

bool MainMenu::onTouchBegan( Touch* t, Event* e )
{
	auto target = static_cast<Sprite*>(e->getCurrentTarget());//获取的当前触摸的目标  

	switch (target->getTag())
	{
	case ObjectTag_MainMenu_Chan:
		{
			auto scene =HelloWorld::createScene();  
			Director::getInstance()->pushScene(scene); 
			break;
		}
	case ObjectTag_MainMenu_Gengduo:
		break;
	case ObjectTag_MainMenu_Jingdian:
		break;
	case ObjectTag_MainMenu_Jieji:
		break;
	default:
		break;
	}

	return false;  
}

 
	/*ValueVector p_map = FileUtils::getInstance()->getValueVectorFromFile("Chinese.xml");  

	ValueMap  map=p_map.at(0).asValueMap();

	std::string info=map.at(label).asString();
	auto myLabel = Label::createWithTTF(info,"fonts/yahei_mono.ttf",fontSize);
	myLabel->setString(info);
	myLabel->setColor(Color3B::RED); */

/*
	auto myLabel = Label::create();
	myLabel->setString(label);
	myLabel->setSystemFontSize(fontSize);
	//myLabel->setTextColor(textColor);
	myLabel->setColor(Color3B::BLUE);*/

// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// 	auto myLabel = Label::createWithSystemFont(info, "DroidSansFallback", fontSize);
// #endif

// #if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
// 	auto myLabel = Label::createWithTTF(info,"fonts/yahei_mono.ttf",fontSize);
// #endif


/*
CCDictionary *strings =CCDictionary::createWithContentsOfFile("one.xml"); 
const char *charwomen= ((CCString*)strings->objectForKey("women"))->m_sString.c_str();    
CCLabelBMFont* labelFont =CCLabelBMFont::create(charchinese, "one.fnt");
labelFont->setPosition(ccp(100,100));
addChild(labelFont);

*/
/*ValueMap value_map = FileUtils::getInstance()->getValueMapFromFile("Chinese.plist");
	std::string info = value_map.at(label).asString();*/