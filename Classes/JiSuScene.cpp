#include "JiSuScene.h"
#include "ConstValue.h"

USING_NS_CC;

Scene* JiSuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = JiSuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void JiSuScene::startGame()
{
	scoreSpeed = 0;
	lineMax = JiSu_LineMax;
	moveSpeed = JiSu_Speed;
	moshi = "jisu";
	BaseScene::startGame();	
	setScoreLabel(StringUtils::format("%g",scoreSpeed));	
}

void JiSuScene::update(float dt)
{
	if(timeRunning)
	{
		gameTime = clock()-startTime;
		scoreSpeed = scoreLine*1000/((double)gameTime);
		setScoreLabel(StringUtils::format("%g",scoreSpeed));
	}
}

//开始计时
void JiSuScene::startTimer()
{
	if(!timeRunning)
	{
		scheduleUpdate();
		startTime = clock();
		timeRunning = true;
		schedule(schedule_selector(JiSuScene::logic), moveSpeed);
	}
}

//结束计时
void JiSuScene::stopTimer()
{
	if(timeRunning)
	{
		timeRunning = false;
		unscheduleUpdate();		
		unschedule(schedule_selector(JiSuScene::logic));
	}
}


void JiSuScene::endGame(bool bWin)
{
	stopTimer();
	double bestScore = LoadDoubleToXML(moshi.c_str(),0);
	if (scoreSpeed> bestScore || bestScore == 0)
	{
		bestScore = scoreSpeed;
		SaveIntegerToXML(moshi.c_str(),bestScore);
	}
	addChild(createEndLayer(Color4B::GREEN,moshi,scoreLabel->getString(),StringUtils::format("%g",bestScore)),2);

}

void JiSuScene::logic( float dt )
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

void JiSuScene::playRight( Block* b )
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

void JiSuScene::playError( Block* b )
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
		CallFunc::create(CC_CALLBACK_0(JiSuScene::endGame,this,false)),
		NULL
		);
	b->runAction(blink);
}
