#ifndef Utility_H
#define Utility_H

#define SaveStringToXML CCUserDefault::getInstance()->setStringForKey

#define SaveIntegerToXML CCUserDefault::getInstance()->setIntegerForKey

#define SaveBooleanToXML CCUserDefault::getInstance()->setBoolForKey

#define LoadStringFromXML CCUserDefault::getInstance()->getStringForKey

#define LoadIntegerFromXML CCUserDefault::getInstance()->getIntegerForKey

#define LoadBooleanFromXML CCUserDefault::getInstance()->getBoolForKey

#endif