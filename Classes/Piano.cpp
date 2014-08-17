#include "Piano.h"
#include "cocos2d.h"
#include "ConstValue.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


static Piano* s_SharedPiano;

void Piano::playPiano(char sound )
{
	switch (sound)
	{
	case 'A':
		SimpleAudioEngine::getInstance()->playEffect(Sound_A);
		break;
	case 'B':
		SimpleAudioEngine::getInstance()->playEffect(Sound_B);
		break;
	case 'C':
		SimpleAudioEngine::getInstance()->playEffect(Sound_C);
		break;
	case 'D':
		SimpleAudioEngine::getInstance()->playEffect(Sound_D);
		break;
	case 'E':
		SimpleAudioEngine::getInstance()->playEffect(Sound_E);
		break;
	case 'F':
		SimpleAudioEngine::getInstance()->playEffect(Sound_F);
		break;
	case 'G':
		SimpleAudioEngine::getInstance()->playEffect(Sound_G);
		break;
	case 'H':
		SimpleAudioEngine::getInstance()->playEffect(Sound_H);
		break;
	case 'I':
		SimpleAudioEngine::getInstance()->playEffect(Sound_I);
		break;
	case 'J':
		SimpleAudioEngine::getInstance()->playEffect(Sound_J);
		break;
	case 'K':
		SimpleAudioEngine::getInstance()->playEffect(Sound_K);
		break;
	case 'L':
		SimpleAudioEngine::getInstance()->playEffect(Sound_L);
		break;
	case 'M':
		SimpleAudioEngine::getInstance()->playEffect(Sound_M);
		break;
	case 'N':
		SimpleAudioEngine::getInstance()->playEffect(Sound_N);
		break;
	case 'O':
		SimpleAudioEngine::getInstance()->playEffect(Sound_O);
		break;
	case 'P':
		SimpleAudioEngine::getInstance()->playEffect(Sound_P);
		break;
	case 'Q':
		SimpleAudioEngine::getInstance()->playEffect(Sound_Q);
		break;
	case 'R':
		SimpleAudioEngine::getInstance()->playEffect(Sound_R);
		break;
	case 'S':
		SimpleAudioEngine::getInstance()->playEffect(Sound_S);
		break;
	case 'T':
		SimpleAudioEngine::getInstance()->playEffect(Sound_T);
		break;
	case 'U':
		SimpleAudioEngine::getInstance()->playEffect(Sound_U);
		break;
	case 'V':
		SimpleAudioEngine::getInstance()->playEffect(Sound_V);
		break;
	case 'W':
		SimpleAudioEngine::getInstance()->playEffect(Sound_W);
		break;
	case 'X':
		SimpleAudioEngine::getInstance()->playEffect(Sound_X);
		break;
	case 'Y':
		SimpleAudioEngine::getInstance()->playEffect(Sound_Y);
		break;
	case 'Z':
		SimpleAudioEngine::getInstance()->playEffect(Sound_Z);
		break;
	default:
		break;
	}
}

Piano::Piano()
{
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_A );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_B );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_C );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_D );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_E );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_F );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_G );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_H );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_I );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_J );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_K );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_L );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_M );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_N );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_O );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_P );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_Q );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_R );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_S );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_T );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_U );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_V );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_W );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_X );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_Y );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_Z );

	SimpleAudioEngine::getInstance()->preloadEffect(Sound_beep );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_camera );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_cheer );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_error );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_error_piano );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_mistake );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_tick );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_touch );
	SimpleAudioEngine::getInstance()->preloadEffect(Sound_win );
	 
	//Í¯»°
	musics.push_back("LONOLLONOLLONOOOMMLLONOLLQPPOLONOMMMOTSPPRRQQQQNPOONOONORLSRQPPPRRQQQQVUTUVVPOTTTSSSLSRQQRQQRQRQPOOQSTTTSPPRQOQSTTTSPPRQRQPOPQMMOONO");
	//ÐÇÓïÐÄÔ¸
	musics.push_back("TVUTSTQTSTVUVUTUVVWXXXXWVUTUSTVUTSTQSTXWVUVVUTTTTSSTQ");
	//»áºôÎüµÄÍ´
	musics.push_back("STVTXXTWWWVUVWXWSVVUTUVRRRVVWVSSSSYXWXXSTVTXXTWWWVUVWXWSVVVUTUVRRRVVWVSSSSTUVVUVV");
	//Ð¡ÐÇÐÇ
	musics.push_back("OOSSTTSRRQQPPOSSRRQQPSSRRQQPOOSSTTSRRQQPPO");

}

Piano::~Piano()
{
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_A );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_B );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_C );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_D );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_E );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_F );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_G );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_H );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_I );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_J );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_K );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_L );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_M );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_N );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_O );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_P );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_Q );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_R );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_S );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_T );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_U );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_V );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_W );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_X );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_Y );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_Z );

	SimpleAudioEngine::getInstance()->unloadEffect(Sound_beep );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_camera );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_cheer );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_error );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_error_piano );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_mistake );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_tick );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_touch );
	SimpleAudioEngine::getInstance()->unloadEffect(Sound_win );
}

void Piano::playBeep()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_beep);
}

void Piano::playCamera()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_camera);
}

void Piano::playCheer()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_cheer);
}

void Piano::playError()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_error);
}

void Piano::playError_piano()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_error_piano);
}

void Piano::playMistake()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_mistake);
}

void Piano::playTick()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_tick);
}

void Piano::playTouch()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_touch);
}

void Piano::playWin()
{
	SimpleAudioEngine::getInstance()->playEffect(Sound_win);
}

Piano* Piano::getInstance()
{
	if (!s_SharedPiano)
	{
		s_SharedPiano = new Piano();
	}

	return s_SharedPiano;
}

void Piano::init()
{
	srand(time(NULL));
	musicNow = rand()%musics.size();
	musicNowCount = 0;
}

void Piano::playMusic()
{
	if (musicNowCount >=musics.at(musicNow).size() )
	{
		init();
	}
	
	char sound = musics.at(musicNow)[musicNowCount++];
	playPiano(sound);
	log("play music %d %d %c",musicNow,musicNowCount,sound);
}
