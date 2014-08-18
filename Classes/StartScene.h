#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	
	void initResource(float dt);

	CREATE_FUNC(StartScene);
};

#endif // __STARTSCENE_H__