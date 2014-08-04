#ifndef __JINGDIAN_SCENE_H__
#define __JINGDIAN_SCENE_H__

#include "cocos2d.h"
#include "Block.h"

USING_NS_CC;

class JingdianScene : public cocos2d::Layer
{
private:

	Size visibleSize;
	int linesCount;
	int lineMax;
	bool showEnd;
	Label *timerLabel;
	Node *gameLayer;
	LayerColor *failLayer;
	LayerColor *winLayer;
	long startTime;
	bool timeRunning;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(JingdianScene);

	//
	void init_failLayer();
	void init_winLayer();
	//添加开始的黄色栏
	void addStartLine();

	//添加结束的绿色栏，占满屏幕
	void addEndLine();

	//添加普通的黑白块栏
	void addNormalLine(int lineIndex);

	//开始游戏
	void startGame();

	//结束游戏
	void endGame(bool bWin);

	//方块下移
	void moveDown();

	//开始计时
	void startTimer();

	//结束计时
	void stopTimer();

	//
	void fanHui();
	void chongLai();

	virtual void update(float dt);

};

#endif // __JINGDIAN_SCENE_H__
