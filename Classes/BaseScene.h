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
	long startTime;
	long gameTime;
	float moveSpeed;
	Label *timerLabel;
	Node *gameLayer;
	LayerColor *endLayer;
	std::string moshi;
public:
	virtual bool init();  

	//��ӿ�ʼ����
	void addStartLine();
	//��ӽ�������ɫ����ռ����Ļ
	void addEndLine();
	//�����ͨ�ĺڰ׿���
	void addNormalLine(int lineIndex);
	//��������
	void moveDown(float dt = 0.1f);

	//
	void menuCloseCallback(cocos2d::Ref* pSender);
	LayerColor* createEndLayer(Color4B bgColor,std::string moshi,std::string score,std::string best);

	//
	void fanHui();
	void chongLai();

	virtual void startGame();
	virtual void playRight(Block* b);
	virtual void playError(Block* b);
	void test(float dt);
};

#endif // __BASE_SCENE_H__
