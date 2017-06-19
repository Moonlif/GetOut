#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
	:m_system(NULL)
	, m_sound(NULL)
	, m_channel(NULL)
	, m_nSoundLength(0), m_curruntTime(0), m_isPlaying(false)
{
	//���� �ý��� �����Ѵ�
	System_Create(&m_system);

	//�ý��� �ʱ�ȭ
	m_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

	//ä�� �� ��ŭ �޸� ���� �� ���带 �����Ѵ�
	m_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	m_channel = new Channel*[TOTAL_SOUND_CHANNEL];

	//�޸� ����ϰ� �� �� �о��ش�
	ZeroMemory(m_sound, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	ZeroMemory(m_channel, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

}


cSoundManager::~cSoundManager()
{
	//���� ����
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

	//�޸� �����
	SAFE_DELETE_ARRAY(m_channel);
	SAFE_DELETE_ARRAY(m_sound);

	//�ý��� ����
	if (m_system != NULL)
	{
		m_system->release();
		m_system->close();
	}

	m_mTotalSounds.clear();
}


void cSoundManager::Update()
{
	//���� �ý����� ��������� ������Ʈ ���ش�
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