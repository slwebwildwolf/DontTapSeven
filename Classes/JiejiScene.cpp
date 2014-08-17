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
	moveSpeed = JieJI_Speed;
	moshi = "jieji";
	BaseScene::startGame();	
	timerLabel->setString(StringUtils::format("%d",scoreLine));	
}

void JiejiScene::update(float dt)
{
	timerLabel->setString(StringUtils::format("%d",scoreLine));
}

//开始计时
void JiejiScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		timeRunning = true;
		schedule(schedule_selector(JiejiScene::logic), moveSpeed);
	}
}

//结束计时
void JiejiScene::stopTimer()
{
	if(timeRunning)
	{
		unscheduleUpdate();
		timeRunning = false;
		unschedule(schedule_selector(JiejiScene::logic));
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
	addChild(createEndLayer(Color4B::GREEN,moshi,timerLabel->getString(),StringUtils::format("%d",bestScore)),2);

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
			endGame(false);
			break;
		}
	}
}

void JiejiScene::playRight( Block* b )
{
	BaseScene::playRight(b);
	b->setColor(Color3B::GRAY);
	if (currentLine == 1)
	{
		this->moveDown(moveSpeed);
	}

	this->startTimer();

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


