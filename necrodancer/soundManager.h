#pragma once
#include "singletonBase.h"
#include <unordered_map>

#include "inc/fmod.hpp"	//fmod.hpp파일 인클루드
#pragma comment(lib, "lib/fmodex64_vc.lib")	//라이브러리 파일 등록

using namespace FMOD;

struct tagNote
{
	int			beat;					//비트
	bool		isAlive;				//빗흐살았니
	D2D1_RECT_F left_RC;				//렉트
	D2D1_RECT_F right_RC;				//렉트
	image*		img;
	float		alpha;

	tagNote()
	{
		beat = 0;
		isAlive = true;
		alpha = 0.0f;
	}
};


#define SOUNDBUFFER 200
#define EXTRACHANNELBUFFER 100

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager: public singletonBase<soundManager>
{
private:
	typedef unordered_map<string, Sound**> arrSounds;
	typedef unordered_map<string, Sound**>::iterator arrSoundsIter;
	typedef unordered_map<string, Channel**> arrChannels;
	typedef unordered_map<string, Channel**>::iterator arrChannelsIter;

private:
	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;

	ChannelGroup* _bgmGroup;
	ChannelGroup* _effectGroup;

	SoundGroup* _bgmSoundGroup;
	SoundGroup* _effectSoundGroup;

private:
	// ===================================
	//			네 흣 로 댄 수
	// ===================================

	vector<tagNote>									_vBeat;			//비트 담을곳
	vector<tagNote>::iterator						_viBeat;		//비트 담을곳

	map<string, vector<tagNote>>					_mBeat;			//중복방지용
	map<string, vector<tagNote>>::iterator			_miBeat;		//중복방지용

	float										_shopVolume;		//상점주인볼륨
	float*	_specLeft;
	float*	_specRight;
	float*  _spec;

	float _volume = 1.0f;
	float _effectVol = 1.0f;

	float _bossVolume = 1.0f;
	float _drumVolume = 1.0f;
	float _hornVolume = 1.0f;
	float _keytarVolume = 1.0f;
	float _stringsVolume = 1.0f;



	tagNote	_note;

	string _shopBgmKey;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void play(string keyName, float volume = 1.0f); // 0.0 ~ 1.0f -> 0 ~ 255
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	// effect voluem control
	void setEffectVolume(float volume);
	// bgm volume control
	void setBgmVolume(float volume);
	// 모든 sound volume control
	void setAllSoundVolume(float volume);

	// pause
	void setEffectPause();
	void setBgmPause();
	void setAllSoundPause();

	// resume
	void setEffectResume();
	void setBgmResume();
	void setAllSoundResume();

	void allSoundStop();


	soundManager();
	~soundManager();


public:

	// ===================================
	//			네 흣 로 댄 수
	// ===================================

	void playZone(string keyName, float volume);				//노래트는곳(상점주인목소리랑 같이 나오게 설정한다)
	void pauseZone(string keyName);								//일시정지(메뉴띄울경우)
	void resumeZone(string keyName, float volume);				//계속(메뉴에서 다시 던전으로)
	void loadBeat(const char * fileName, string keyName);		//비트정보 불러오기
	void setPitch(float pitch);									//함정걸렸을때 피치조절
	int getPosition(string keyName);							//현재길이 받아옴
	int getBossPosition(string keyName);
	int getLength(string keyName);								//노래 전체길이
	void getSingShopkeeper(string keyName);						//상점주인 스펙트럼
	void ShopVolume(string keyName, float volume);	//상점주인용 볼륨조절
	
	void setBossVolume(string keyName, float volume);	//보스용
	void setDrumVolume(string keyName, float volume);	//보스용
	void setHornVolume(string keyName, float volume);	//보스용
	void setKeytarVolume(string keyName, float volume);	//보스용
	void setStringsVolume(string keyName, float volume);	//보스용


	void playBossZone(string keyName, float volume);

	void playEff(string keyName);



	// ===================================
	//		네 흣 로 댄 수 (get & set)
	// ===================================

	vector<tagNote>							getVBeat() { return _vBeat; }
	vector<tagNote>::iterator				getVIBeat() { return _viBeat; }

	map<string, vector<tagNote>>			getMBeat() { return _mBeat; }
	map<string, vector<tagNote>>::iterator	getMIBeat() { return _miBeat; }

	float									getShopVolume() { return _shopVolume; }
	void									setShopVolume(float volume) { _shopVolume = volume; }

	float*									getSpec() 
	{ 
		return _spec; 
	}

	float getEffectVol() { return _effectVol; }
	void setEffectVol(float effectVol) { _effectVol = effectVol; }
	void EffectVolDown() { _effectVol -= 0.1f; if (_effectVol < 0) _effectVol = 0; }
	void EffectVolUp() { _effectVol += 0.1f; if (_effectVol > 1) _effectVol = 1; }

	float getVolume() { return _volume; }
	void setVolume(float volume) { _volume = volume; }
	void VolDown() { _volume -= 0.1f; if (_volume < 0) _volume = 0; }
	void VolUp() { _volume += 0.1f; if (_volume > 1) _volume = 1; }

	string getShopBgmKey() { return _shopBgmKey;}
	void setShopBgmKey(string name) { _shopBgmKey = name; }
};

