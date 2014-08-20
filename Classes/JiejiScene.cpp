#include "JiejiScene.h"
#include "ConstValue.h"
USING_NS_CC;

Scene* JiejiScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = JiejiScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

//开始游戏
void JiejiScene::startGame()
{
	lineMax = JieJi_LineMax;
	moshi = "jieji";
	BaseScene::startGame();	
	setScoreLabel(StringUtils::format("%d",scoreLine));	
}

void JiejiScene::update(float dt)
{
	setScoreLabel(StringUtils::format("%d",scoreLine));
	if ((clock()-moveTime)/1000.0f > 1.0f/moveSpeed)
	{
		logic(1/moveSpeed);
	}		
}

//开始计时
void JiejiScene::startTimer()
{
	if(!timeRunning)
	{		
		timeRunning = true;
		moveSpeed = JieJI_Speed;
		moveTime = clock();
		scheduleUpdate();
	}
}

//结束计时
void JiejiScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
	}
}

void JiejiScene::endGame(bool bWin)
{
	stopTimer();
	int bestScore = LoadIntegerFromXML(moshi.c_str(),0);
	if (scoreLine> bestScore || bestScore == 0)
	{
		bestScore = scoreLine;
		SaveIntegerToXML(moshi.c_str(),bestScore);
	}
	addChild(createEndLayer(Color4B::GREEN,moshi,scoreLabel->getString(),StringUtils::format("%d",bestScore)),2);
}

void JiejiScene::logic( float dt )
{	 
	moveDown(dt);
	auto bs = Block::getBlocks();
	Block *b;

	for(auto it = bs->begin(); it != bs->end(); it++)
	{
		b = *it;
		if(b->getLineIndex()==-1
			&&b->getLineCount()>scoreLine+1)
		{
			//endGame(false);
			break;
		}
	}
}

void JiejiScene::playRight( Block* b )
{
	BaseScene::playRight(b);
	b->setColor(Color3B::GRAY);
	

	this->startTimer();
if (currentLine == 1)
	{
		this->moveDown(1.0f/moveSpeed);
	}
	if (scoreLine == lineMax)
	{
		endGame(true);
	}
}

void JiejiScene::playError( Block* b )
{
	BaseScene::playError(b);
	this->stopTimer();
	auto *blink = Sequence::create(
		Repeat::create( 
		Sequence::create(
		TintTo::create(0.1, 255,255, 255),
		TintTo::create(0.1, 255,0, 0),
		NULL), 				 
		5),
		CallFunc::create(CC_CALLBACK_0(JiejiScene::endGame,this,false)),
		NULL
		);
	b->runAction(blink);
}


