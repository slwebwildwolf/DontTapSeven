#ifndef Utility_H
#define Utility_H

#include "cocos2d.h"

USING_NS_CC;

#define SaveBooleanToXML CCUserDefault::getInstance()->setBoolForKey
#define SaveStringToXML CCUserDefault::getInstance()->setStringForKey
#define SaveIntegerToXML CCUserDefault::getInstance()->setIntegerForKey
#define SaveDoubleToXML CCUserDefault::getInstance()->setDoubleForKey

#define LoadBooleanFromXML CCUserDefault::getInstance()->getBoolForKey
#define LoadStringFromXML CCUserDefault::getInstance()->getStringForKey
#define LoadIntegerFromXML CCUserDefault::getInstance()->getIntegerForKey
#define LoadDoubleToXML CCUserDefault::getInstance()->getDoubleForKey

class Utility
{

public:
	//检查7
	static std::string ConverToString(int value);
	static bool checkSeven(int num);
	static std::string GetXMLString(std::string v);
	static long millisecondNow();
	static std::string getCurrentTime(); 
};

#endif


