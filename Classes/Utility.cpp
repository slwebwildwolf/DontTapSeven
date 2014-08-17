#include <Utility.h>

USING_NS_CC;


template<class T> std::string ConverToString(T value)
{
	std::stringstream ss;
	ss<<value;
	return ss.str();
}
//¼ì²é7
bool checkSeven(int num)
{
	if (num%7==0)
	{
		return true;
	}

	int i = ConverToString(num).find('7');
	if (i>=0)
	{
		return true;
	}

	return false;
}


std::string GetXMLString( std::string v )
{
	ValueVector p_map = FileUtils::getInstance()->getValueVectorFromFile("Chinese.xml");  
	ValueMap  map=p_map.at(0).asValueMap();
	std::string info=map.at(v).asString();
	return info;
}

 


