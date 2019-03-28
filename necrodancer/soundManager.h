#pragma once
#include "singletonBase.h"
#include <unordered_map>

#include "inc/fmod.hpp"	//fmod.hpp���� ��Ŭ���
#pragma comment(lib, "lib/fmodex64_vc.lib")	//���̺귯�� ���� ���

using namespace FMOD;

struct tagNote
{
	int			beat;					//��Ʈ
	bool		isAlive;				//�����Ҵ�
	D2D1_RECT_F left_RC;				//��Ʈ
	D2D1_RECT_F right_RC;				//��Ʈ
	image*		img;
	float		alpha;

	tagNote()
	{
		beat = 0;
		isAlive = true;
		alpha = 0.0f;
	}
};


#define SOUNDBUFFER 100
#define EXTRACHANNELBUFFER 50

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
	//			�� �� �� �� ��
	// ===================================

	vector<tagNote>									_vBeat;			//��Ʈ ������
	vector<tagNote>::iterator						_viBeat;		//��Ʈ ������

	map<string, vector<tagNote>>					_mBeat;			//�ߺ�������
	map<string, vector<tagNote>>::iterator			_miBeat;		//�ߺ�������

	float										_shopVolume;		//�������κ���
	float*	_specLeft;
	float*	_specRight;
	float*  _spec;

	float _volume = 1.0f;
	float _effectVol = 1.0f;

	tagNote	_note;

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
	// ��� sound volume control
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
	//			�� �� �� �� ��
	// ===================================

	void playZone(string keyName, float volume);				//�뷡Ʈ�°�(�������θ�Ҹ��� ���� ������ �����Ѵ�)
	void pauseZone(string keyName);								//�Ͻ�����(�޴������)
	void resumeZone(string keyName, float volume);				//���(�޴����� �ٽ� ��������)
	void loadBeat(const char * fileName, string keyName);		//��Ʈ���� �ҷ�����
	void setPitch(float pitch);									//�����ɷ����� ��ġ����
	int getPosition(string keyName);							//������� �޾ƿ�
	int getBossPosition(string keyName);
	int getLength(string keyName);								//�뷡 ��ü����
	void getSingShopkeeper(string keyName);						//�������� ����Ʈ��
	void ShopVolume(string keyName, float volume);				//�������ο� ��������

	void playBossZone(string keyName, float volume);

	void playEff(string keyName);



	// ===================================
	//		�� �� �� �� �� (get & set)
	// ===================================

	vector<tagNote>							getVBeat() { return _vBeat; }
	vector<tagNote>::iterator				getVIBeat() { return _viBeat; }

	map<string, vector<tagNote>>			getMBeat() { return _mBeat; }
	map<string, vector<tagNote>>::iterator	getMIBeat() { return _miBeat; }

	float									getShopVolume() { return _shopVolume; }
	void									setShopVolume(float volume) { _shopVolume = volume; }

	float*									getSpec() { return _spec; }

	float getEffectVol() { return _effectVol; }
	void setEffectVol(float effectVol) { _effectVol = effectVol; }
	void EffectVolDown() { _effectVol -= 0.1f; if (_effectVol < 0) _effectVol = 0; }
	void EffectVolUp() { _effectVol += 0.1f; if (_effectVol > 1) _effectVol = 1; }

	float getVolume() { return _volume; }
	void setVolume(float volume) { _volume = volume; }
	void VolDown() { _volume -= 0.1f; if (_volume < 0) _volume = 0; }
	void VolUp() { _volume += 0.1f; if (_volume > 1) _volume = 1; }
};

