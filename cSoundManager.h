#pragma once
#define g_pSoundManager cSoundManager::GetInstance()

#include "Sound/inc/fmod.hpp"
#pragma comment(lib, "Sound/lib/fmodex_vc.lib")

#define SOUND_BUFFER 10
#define EXTRA_SOUND_CHANNEL 5

#define TOTAL_SOUND_CHANNEL (SOUND_BUFFER + EXTRA_SOUND_CHANNEL)

using namespace FMOD;

class cSoundManager
{
public:
	/*cSoundManager();
	~cSoundManager();*/

	SINGLETONE(cSoundManager)
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

	arrSounds _mTotalSounds;

	System* _system;
	Sound** _sound;
	Channel** _channel;

	unsigned int _soundLength;
	unsigned int _curruntTime;
	bool		 _isPlaying;

public:
	void Update();

	void AddSound(string keyName, string soundName, bool background, bool loop);
	void Play(string keyName, float volume);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);
	void Mute(string keyName);



	int GetSize() { return _mTotalSounds.size(); }

	void SetVolume(string keyName, float volume);

	unsigned int GetSoundLength() { return _soundLength; }
	unsigned int GetCurruntTime() { return _curruntTime; }
	bool IsPlaying() { return _isPlaying; }
	Channel* GetPlayingChannel(string keyName);

	
};

