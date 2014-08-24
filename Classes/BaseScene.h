#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
#include "Utility.h"
#include "Piano.h"

USING_NS_CC;

class BaseScene : public cocos2d::Layer
{
protected:
	Size visibleSize;
	int linesCount;
	int lineMax;
	int scoreLine;
	int currentLine;
	bool showEnd;
	bool timeRunning;
	float gameTime;
	float moveSpeed;
	LabelAtlas* scoreLabel;
	Node *gameLayer;
	LayerColor *endLayer;
	std::string moshi;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	void setScoreLabel(std::string text,float sizeScale = 0.5f ,Color3B color = Color3B::GREEN);
	//添加开始的栏
	void addStartLine();
	//添加结束的绿色栏，占满屏幕
	void addEndLine();
	//添加普通的黑白块栏
	void addNormalLine(int lineIndex);
	//方块下移
	void moveDown(float dt = 0.1f);
	//
	void autoDown(float speed);
	//
	void menuCloseCallback(cocos2d::Ref* pSender);
	LayerColor* createEndLayer(Color4B bgColor,std::string moshi,std::string score,std::string best);

	//开始计时
	virtual void startTimer()=0;
	//结束计时
	virtual void stopTimer()=0;
	//
	void fanHui();
	void chongLai();

	virtual void startGame();
	virtual void endGame(bool bWin)=0;
	virtual void playRight(Block* b);
	virtual void playError(Block* b);
	void test(float dt);
};

#endif // __BASE_SCENE_H__
