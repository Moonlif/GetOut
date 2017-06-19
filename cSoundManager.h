#pragma once
#define g_pSoundManager cSoundManager::GetInstance()

#include "Sound/inc/fmod.hpp"
#pragma comment(lib, "Sound/lib/fmodex_vc.lib")

#define SOUND_BUFFER 30
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

	arrSounds m_mTotalSounds;

	System* m_system;
	Sound** m_sound;
	Channel** m_channel;

	unsigned int m_nSoundLength;
	unsigned int m_curruntTime;
	bool		 m_isPlaying;

public:
	void Update();

	void AddSound(string keyName, string soundName, bool background, bool loop);
	void Play(string keyName, float volume);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);
	void Mute(string keyName);

	int GetSize() { return m_mTotalSounds.size(); }

	void SetVolume(string keyName, float volume);

	unsigned int GetSoundLength(string key);
	unsigned int GetCurruntTime(string key);
	bool GetIsPlaying(string key);
	Channel* GetPlayingChannel(string keyName);

	
};

