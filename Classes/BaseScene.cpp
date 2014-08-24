#include "BaseScene.h"
#include "ConstValue.h"

USING_NS_CC;

bool BaseScene::init()
{
	if ( !Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	srand(time(NULL));

	scoreLine = 0;
	gameLayer = Node::create();
	addChild(gameLayer);	

	//scoreLabel = Label::createWithBMFont("fonts/score_font.fnt", "");
	scoreLabel = LabelAtlas::create("123 Test", "fonts/tuffy_bold_italic-charmap.png", 48, 64, ' ');
	scoreLabel->setPosition(visibleSize.width/2, visibleSize.height-30);

	this->addChild(scoreLabel);;

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
			currentLine = b->getLineCount();
			if(currentLine - scoreLine ==1&&
				b->getBoundingBox().containsPoint(t->getLocation()-gameLayer->getPosition()))
			{
				++scoreLine;
				if((b->getColor()==Color3B::BLACK && !Utility::checkSeven(currentLine)) ||
					(b->getColor()==Color3B::WHITE && Utility::checkSeven(currentLine)))
				{
					playRight(b);					
				}
				else
				{
					playError(b);
				}
				break;
			}
		}
		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//schedule(schedule_selector(BaseScene::test), 0.5f);

	return true;
}


LayerColor* BaseScene::createEndLayer(Color4B bgColor,std::string moshi,std::string score,std::string best )
{
	auto endLayer = LayerColor::create(bgColor);
	endLayer->setName("endLayer");
	//模式
	auto moshilb = Label::create();
	moshilb->setString(Utility::GetXMLString(moshi)+Utility::GetXMLString("moshi"));
	moshilb->setPosition(visibleSize.width / 2,visibleSize.height-100);
	moshilb->setSystemFontSize(36);
	endLayer->addChild(moshilb);
	//失败 or 成绩
	if (score == "")
	{
		score=Utility::GetXMLString("shibai");
	}	 
	auto scorelb = Label::create();
	scorelb->setString(score);
	scorelb->setPosition(visibleSize.width / 2,visibleSize.height /2+30);
	scorelb->setSystemFontSize(36);
	endLayer->addChild(scorelb);
	//最佳
	auto bestlb =Label::create();
	bestlb->setString(Utility::GetXMLString("zuijia")+best);
	bestlb->setPosition(visibleSize.width / 2,visibleSize.height /2-30);
	bestlb->setSystemFontSize(36);
	endLayer->addChild(bestlb);
	//
	auto chonglailb = Label::create();
	chonglailb->setString(Utility::GetXMLString("chonglai"));
	chonglailb->setSystemFontSize(36);
	auto item1 = MenuItemLabel::create(chonglailb, CC_CALLBACK_0(BaseScene::chongLai, this) );

	auto fanhuilb = Label::create();
	fanhuilb->setString(Utility::GetXMLString("fanhui"));
	fanhuilb->setSystemFontSize(36);
	auto item2 = MenuItemLabel::create(fanhuilb, CC_CALLBACK_0(BaseScene::fanHui, this) );

	auto menu = Menu::create( item1, item2, NULL);
	menu->alignItemsHorizontallyWithPadding(50);
	menu->setPositionY(100);
	endLayer->addChild(menu);

	return endLayer;
}

void BaseScene::chongLai()
{
	startGame();
}
void BaseScene::fanHui()
{
	Director::getInstance()->popScene();
}

//添加开始的栏
void BaseScene::addStartLine()
{
	auto b = Block::createWithArgs(Color3B::GREEN, Size(visibleSize.width,visibleSize.height/4), "", 10, Color4B::BLACK);
	gameLayer->addChild(b);
	b->setLineIndex(0);
	b->setLineCount(linesCount);
}

//添加结束的绿色栏，占满屏幕
void BaseScene::addEndLine()
{
	auto b = Block::createWithArgs(Color3B::GREEN, visibleSize, "", 30, Color4B::BLACK);
	gameLayer->addChild(b);
	b->setLineIndex(4);
}

//添加普通的黑白块栏
void BaseScene::addNormalLine(int lineIndex)
{
	linesCount++;

	Block *b;
	int blackIndex = rand()%4;
	for(int i=0; i<4; i++)
	{
		b = Block::createWithArgs(blackIndex == i ? Color3B::BLACK : Color3B::WHITE, Size(visibleSize.width/4-1,visibleSize.height/4-1), "", 20, Color4B::BLACK);
		b->setPosition(i*visibleSize.width/4, lineIndex*visibleSize.height/4);
		b->setLineIndex(lineIndex);
		b->setLineCount(linesCount);
		gameLayer->addChild(b);
	}
}

//方块下移
void BaseScene::moveDown(float dt)
{
	if(linesCount<lineMax)
	{
		addNormalLine(linesCount+1);
		//addNormalLine(4);
	}
	else if(!showEnd)
	{
		addEndLine();
		showEnd = true;
	}

	/*auto bs = Block::getBlocks();
	for(auto it=bs->begin(); it!=bs->end(); it++)
	{
		(*it)->moveDowm(dt);
	}*/

	gameLayer->runAction(Sequence::create(MoveTo::create(dt, Point(gameLayer->getPositionX(),gameLayer->getPositionY()- visibleSize.height/4)), 
		CallFunc::create([this]()
	{
		log("==========================================");
		auto bs = Block::getBlocks();
		for(auto it=bs->begin(); it!=bs->end(); it++)
		{
			(*it)->moveDowm(0);
		}
		if(timeRunning)
			autoDown(moveSpeed);
	}), NULL));
}

void BaseScene::menuCloseCallback( cocos2d::Ref* pSender )
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

void BaseScene::startGame()
{
	linesCount = 0;
	scoreLine = 0;
	showEnd = false;
	timeRunning = false;
	moveSpeed=0;
	removeChildByName("endLayer");
	Block::clearBlocks();
	gameLayer->setPosition(0,0);
	addStartLine();
	addNormalLine(1);
	addNormalLine(2);
	addNormalLine(3);
	
	log("Base startgame");	
}

void BaseScene::playRight( Block* b )
{
	Piano::getInstance()->playMusic();
	b->setColor(Color3B::GRAY);

	this->startTimer();
	
	if (moveSpeed==0)
	{
		this->moveDown(Chan_Speed);
	} 

	if (scoreLine == lineMax)
	{
		endGame(true);
	}
}

void BaseScene::playError( Block* b )
{
	Piano::getInstance()->playMistake();
	this->stopTimer();
	auto *blink = Sequence::create(
		Repeat::create( 
		Sequence::create(
		TintTo::create(0.1, 255,255, 255),
		TintTo::create(0.1, 255,0, 0),
		NULL), 				 
		5),
		CallFunc::create(CC_CALLBACK_0(BaseScene::endGame,this,false)),
		NULL
		);
	b->runAction(blink);
}

void BaseScene::test( float dt )
{
	Piano::getInstance()->playMusic();
}

void  BaseScene::setScoreLabel(std::string text,float sizeScale,Color3B color)
{	 
	scoreLabel->setString(text);
	scoreLabel->setColor(color);
	scoreLabel->setScale(sizeScale);	
	scoreLabel->setPositionX(visibleSize.width/2 - scoreLabel->getContentSize().width*sizeScale/2.0f);
 
}

void BaseScene::autoDown( float speed )
{
	if (speed>0 && timeRunning)
	{
		moveDown(1.0f/speed);
		auto bs = Block::getBlocks();
		Block *b;

		for(auto it = bs->begin(); it != bs->end(); it++)
		{
			b = *it;
			if(b->getLineIndex()==-1
				&&b->getLineCount()>scoreLine+1)
			{
				endGame(false);
				break;
			}
		}
	}
}
