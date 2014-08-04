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
	//��ӿ�ʼ�Ļ�ɫ��
	void addStartLine();

	//��ӽ�������ɫ����ռ����Ļ
	void addEndLine();

	//�����ͨ�ĺڰ׿���
	void addNormalLine(int lineIndex);

	//��ʼ��Ϸ
	void startGame();

	//������Ϸ
	void endGame(bool bWin);

	//��������
	void moveDown();

	//��ʼ��ʱ
	void startTimer();

	//������ʱ
	void stopTimer();

	//
	void fanHui();
	void chongLai();

	virtual void update(float dt);

};

#endif // __JINGDIAN_SCENE_H__
