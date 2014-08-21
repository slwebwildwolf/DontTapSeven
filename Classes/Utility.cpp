#include <Utility.h>

USING_NS_CC;



//¼ì²é7
bool Utility::checkSeven(int num)
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


std::string Utility::GetXMLString( std::string v )
{
	ValueVector p_map = FileUtils::getInstance()->getValueVectorFromFile("Chinese.xml");  
	ValueMap  map=p_map.at(0).asValueMap();
	std::string info=map.at(v).asString();
	return info;
}


std::string Utility::ConverToString( int value )
{
	std::stringstream ss;
	ss<<value;
	return ss.str();
}

long Utility::millisecondNow()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  

	struct timeval tv;      
	gettimeofday(&tv, NULL);    
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;  
#endif  

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )  
	struct timeval tv;      
	gettimeofday(&tv, NULL);    
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;  
#endif 
	
}

std::string Utility::getCurrentTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  

	struct timeval now;  
	struct tm* tm;  

	gettimeofday(&now, NULL);  
	tm = localtime(&now.tv_sec);  

	char date[64] = { 0 };
	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d", (int) tm->tm_year + 1900,
		(int) tm->tm_mon + 1, (int) tm->tm_mday, (int) tm->tm_hour,
		(int) tm->tm_min, (int) tm->tm_sec);

	return StringUtils::format("%s",date);  
#endif  

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )  

	struct tm* tm;  
	time_t timep;  
	time(&timep);  

	tm = localtime(&timep);  
	char date[64] = { 0 };
	sprintf(date, "%d-%02d-%02d %02d:%02d:%02d", (int) tm->tm_year + 1900,
		(int) tm->tm_mon + 1, (int) tm->tm_mday, (int) tm->tm_hour,
		(int) tm->tm_min, (int) tm->tm_sec); 
	return StringUtils::format("%s",date);  
#endif  
}