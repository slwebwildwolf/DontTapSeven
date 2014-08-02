#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "Block.h"
//#include "2d\CCSprite.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
{
private:

	Size visibleSize;

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);

	static Sprite* createMenu(Color3B color, Size size,std::string label, float fontSize, Color3B textColor);

	bool  onTouchBegan(Touch* t, Event*  e);
};

#endif // __MAINMENU_SCENE_H__