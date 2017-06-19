#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
	:m_system(NULL)
	, m_sound(NULL)
	, m_channel(NULL)
	, m_nSoundLength(0), m_curruntTime(0), m_isPlaying(false)
{
	//사운드 시스템 생성한다
	System_Create(&m_system);

	//시스템 초기화
	m_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

	//채널 수 만큼 메모리 버퍼 및 사운드를 생성한다
	m_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	m_channel = new Channel*[TOTAL_SOUND_CHANNEL];

	//메모리 깔끔하게 한 번 밀어준다
	ZeroMemory(m_sound, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	ZeroMemory(m_channel, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

}


cSoundManager::~cSoundManager()
{
	//사운드 삭제
	if (m_channel != NULL || m_sound != NULL)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; ++i)
		{
			if (m_channel != NULL)
				m_channel[i]->stop();
			if (m_sound != NULL)
				m_sound[i]->release();
		}
	}

	//메모리 지운다
	SAFE_DELETE_ARRAY(m_channel);
	SAFE_DELETE_ARRAY(m_sound);

	//시스템 해제
	if (m_system != NULL)
	{
		m_system->release();
		m_system->close();
	}

	m_mTotalSounds.clear();
}


void cSoundManager::Update()
{
	//사운드 시스템을 계속적으로 업데이트 해준다
	m_system->update();
}


void cSoundManager::AddSound(string keyName, string soundName, bool background, bool loop)
{
	if (loop)
	{
		if (background)
		{
			m_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL,
				0, &m_sound[m_mTotalSounds.size()]);
		}
		else
		{
			m_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL,
				0, &m_sound[m_mTotalSounds.size()]);
		}
	}
	else
	{
		if (background)
		{
			m_system->createStream(soundName.c_str(), FMOD_DEFAULT,
				0, &m_sound[m_mTotalSounds.size()]);
		}
		else
		{
			m_system->createSound(soundName.c_str(), FMOD_DEFAULT,
				0, &m_sound[m_mTotalSounds.size()]);
		}
	}

	m_mTotalSounds.insert(make_pair(keyName, &m_sound[m_mTotalSounds.size()]));
}

void cSoundManager::Play(string keyName, float volume)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;
	
	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_system->playSound(FMOD_CHANNEL_FREE, *(iter->second), false, &m_channel[count]);
			m_channel[count]->setVolume(volume);
			break;

		}
	}

}

void cSoundManager::Stop(string keyName)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->stop();
			break;
		}
	}
}

void cSoundManager::Pause(string keyName)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::Resume(string keyName)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->setPaused(false);
			break;
		}
	}
}

void cSoundManager::SetVolume(string keyName, float volume)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->setVolume(volume);
			break;
		}
	}
}
unsigned int cSoundManager::GetSoundLength(string key)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (key != iter->first) continue;
		
		Sound** sound = new Sound*[0];
		sound[0] = *iter->second;
		sound[0]->getLength(&m_nSoundLength, FMOD_TIMEUNIT_MS);
		return m_nSoundLength;
	}
	return NULL;
}
unsigned int cSoundManager::GetCurruntTime(string key)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (key != iter->first) continue;
		m_channel[count]->getPosition(&m_curruntTime, FMOD_TIMEUNIT_MS);
		return m_curruntTime;
	}

	return NULL;

}
bool cSoundManager::GetIsPlaying(string key)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (key != iter->first) continue;
		m_channel[count]->isPlaying(&m_isPlaying);
		return m_isPlaying;
	}

	return NULL;
}
void cSoundManager::Mute(string keyName)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			m_channel[count]->setMute(true);
			break;
		}
	}
}

Channel* cSoundManager::GetPlayingChannel(string keyName)
{
	arrSoundsIter iter = m_mTotalSounds.begin();

	int count = 0;

	for (iter; iter != m_mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)	break;
	}
	return m_channel[count];
}