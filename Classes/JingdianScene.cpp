#include "JingdianScene.h"
#include "Utility.h"

USING_NS_CC;

Scene* JingdianScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = JingdianScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool JingdianScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init())
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();

	srand(time(NULL));
    lineMax = 5;
// 	init_failLayer();
// 	init_winLayer();

	gameLayer = Node::create();
	addChild(gameLayer);	

	timerLabel = Label::create();
	timerLabel->setColor(Color3B::BLUE);
	timerLabel->setSystemFontSize(50);
	timerLabel->setString("0.000\"");
	timerLabel->setPosition(visibleSize.width/2, visibleSize.height-30);
	addChild(timerLabel);

	//addStartLine();
	
	//addEndLine();

	startGame();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch* t, Event* e)
	{
		log("onTouch");
		auto bs = Block::getBlocks();
		Block *b;

		for(auto it = bs->begin(); it != bs->end(); it++)
		{
			b = *it;

			if(b->getLineIndex()==1&&b->getBoundingBox().containsPoint(t->getLocation()))
			{
				if(b->getColor()==Color3B::BLACK)
				{
					b->setColor(Color3B::GRAY);
					this->moveDown();
					this->startTimer();
					CCLog("%d",Block::getBlocks()->size());
					if (Block::getBlocks()->size() == 9)
					{
						endGame(true);
					}
				}
				else if(b->getColor()==Color3B::GREEN)
				{
					this->moveDown();
					this->stopTimer();
				}
				else
				{
					auto *blink = Sequence::create(
						 Repeat::create( 
							 Sequence::create(
								 TintTo::create(0.1, 255,255, 255),
								 TintTo::create(0.1, 255,0, 0),
								 NULL), 				 
							5),
						CallFunc::create(CC_CALLBACK_0(JingdianScene::endGame,this,false)),
						NULL
						);
					b->runAction(blink);
				}
				break;
			}
		}

		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

//开始游戏
void JingdianScene::startGame()
{
	linesCount = 0;
	showEnd = false;
	timeRunning = false;
	removeChildByName("endLayer");
	Block::clearBlocks();

	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
}

//添加开始的黄色栏
void JingdianScene::addStartLine()
{
	//auto b = new Block();
	//b->createWithArgs(Color3B::YELLOW, Size(visibleSize.width,visibleSize.height/4), "", 10, Color4B::BLACK);
	auto b = Block::createWithArgs(Color3B::GREEN, Size(visibleSize.width,visibleSize.height/4), "", 10, Color4B::BLACK);
	gameLayer->addChild(b);
	b->setLineIndex(0);
}

//添加结束的绿色栏，占满屏幕
void JingdianScene::addEndLine()
{
	auto b = Block::createWithArgs(Color3B::GREEN, visibleSize, "", 30, Color4B::BLACK);
	gameLayer->addChild(b);
	b->setLineIndex(4);
}

//添加普通的黑白块栏
void JingdianScene::addNormalLine(int lineIndex)
{
	linesCount++;

	Block *b;
	int blackIndex = rand()%4;
	for(int i=0; i<4; i++)
	{
		b = Block::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibleSize.width/4-1,visibleSize.height/4-1), "", 20, Color4B::BLACK);
		b->setPosition(i*visibleSize.width/4, lineIndex*visibleSize.height/4);
		b->setLineIndex(lineIndex);
		gameLayer->addChild(b);
	}
}

//方块下移
void JingdianScene::moveDown()
{
	if(linesCount<lineMax)
	{
		addNormalLine(4);
	}
	else if(!showEnd)
	{
		addEndLine();
		showEnd = true;
	}

	auto bs = Block::getBlocks();
	for(auto it=bs->begin(); it!=bs->end(); it++)
	{
		(*it)->moveDowm();
	}
}

void JingdianScene::update(float dt)
{
	gameTime = clock()-startTime;

	timerLabel->setString(StringUtils::format("%g",((double)gameTime)/1000));
	
}

//开始计时
void JingdianScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		startTime = clock();
		timeRunning = true;
	}
}

//结束计时
void JingdianScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
	}
}

void JingdianScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void JingdianScene::fanHui()
{
	Director::getInstance()->popScene();
}

void JingdianScene::chongLai()
{
	startGame();
}


void JingdianScene::endGame(bool bWin)
{
	stopTimer();
	long bestTime = LoadIntegerFromXML("Jingdian",0);
	if (bWin)
	{		
		if (gameTime< bestTime || bestTime == 0)
		{
			bestTime = gameTime;
			SaveIntegerToXML("Jingdian",bestTime);
		}
		addChild(createEndLayer(Color4B::GREEN,"jingdianmoshi",timerLabel->getString(),StringUtils::format("%g",((double)bestTime)/1000)),2);
	} 
	else
	{
		addChild(createEndLayer(Color4B::RED,"jingdianmoshi","",StringUtils::format("%g",((double)bestTime)/1000)),2);
	}
}

LayerColor* JingdianScene::createEndLayer(Color4B bgColor,std::string moshi,std::string score,std::string best)
{
	auto endLayer = LayerColor::create(bgColor);
	//endLayer->retain();
	endLayer->setName("endLayer");

	ValueVector p_map = FileUtils::getInstance()->getValueVectorFromFile("Chinese.xml");  
	ValueMap  map=p_map.at(0).asValueMap();
	//模式
	moshi=map.at(moshi).asString();
	auto moshilb = LabelBMFont::create(moshi, "fonts/Chinese.fnt");
	moshilb->setPosition(visibleSize.width / 2,visibleSize.height-100);
	endLayer->addChild(moshilb);
	//失败 or 成绩
	if (score == "")
	{
		score=map.at("shibai").asString();
	}	 
	auto scorelb = LabelBMFont::create(score, "fonts/Chinese.fnt");
	scorelb->setPosition(visibleSize.width / 2,visibleSize.height /2+30);
	endLayer->addChild(scorelb);
	//最佳

	auto bestlb = LabelBMFont::create(map.at("zuijia").asString()+best, "fonts/Chinese.fnt");
	bestlb->setPosition(visibleSize.width / 2,visibleSize.height /2-30);
	endLayer->addChild(bestlb);
	//
	std::string info1=map.at("chonglai").asString();
	auto myLabel = LabelBMFont::create(info1, "fonts/Chinese.fnt");
	auto item1 = MenuItemLabel::create(myLabel, CC_CALLBACK_0(JingdianScene::chongLai, this) );

	std::string info2=map.at("fanhui").asString();
	auto myLabe2 = LabelBMFont::create(info2, "fonts/Chinese.fnt");
	auto item2 = MenuItemLabel::create(myLabe2, CC_CALLBACK_0(JingdianScene::fanHui, this) );

	auto menu = Menu::create( item1, item2, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPositionY(100);
	endLayer->addChild(menu);
	
	return endLayer;
}
