#include "stdafx.h"
#include "cSoundManager.h"


cSoundManager::cSoundManager()
	:_system(NULL)
	, _sound(NULL)
	, _channel(NULL)
	, _soundLength(0), _curruntTime(100), _isPlaying(false)
{
	//사운드 시스템 생성한다
	System_Create(&_system);

	//시스템 초기화
	_system->init(TOTAL_SOUND_CHANNEL, FMOD_INIT_NORMAL, 0);

	//채널 수 만큼 메모리 버퍼 및 사운드를 생성한다
	_sound = new Sound*[TOTAL_SOUND_CHANNEL];
	_channel = new Channel*[TOTAL_SOUND_CHANNEL];

	//메모리 깔끔하게 한 번 밀어준다
	ZeroMemory(_sound, sizeof(Sound*) * (TOTAL_SOUND_CHANNEL));
	ZeroMemory(_channel, sizeof(Channel*) * (TOTAL_SOUND_CHANNEL));

}


cSoundManager::~cSoundManager()
{
	//사운드 삭제
	if (_channel != NULL || _sound != NULL)
	{
		for (int i = 0; i < TOTAL_SOUND_CHANNEL; ++i)
		{
			if (_channel != NULL)
				_channel[i]->stop();
			if (_sound != NULL)
				_sound[i]->release();
		}
	}

	//메모리 지운다
	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	//시스템 해제
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}

	_mTotalSounds.clear();
}


void cSoundManager::Update()
{
	//사운드 시스템을 계속적으로 업데이트 해준다
	_system->update();
}


void cSoundManager::AddSound(string keyName, string soundName, bool background, bool loop)
{
	if (loop)
	{
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL,
				0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL,
				0, &_sound[_mTotalSounds.size()]);
		}
	}
	else
	{
		if (background)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT,
				0, &_sound[_mTotalSounds.size()]);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT,
				0, &_sound[_mTotalSounds.size()]);
		}
	}

	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void cSoundManager::Play(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;
	
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//맵 정렬이 add순서가 아닌 key값으로 자동정렬 되기 때문에 세컨드로 불러옴. 
			//
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			_channel[count]->setVolume(volume);

			//현재시간 받아오기

			/*_channel[count]->getPosition(&_curruntTime, FMOD_TIMEUNIT_MS);
			_channel[count]->isPlaying(&_isPlaying);*/
			//시간 받아오기
			Sound** sound = new Sound*[0];
			sound[0] = *iter->second;
			sound[0]->getLength(&_soundLength, FMOD_TIMEUNIT_MS);


			break;
		}
	}
}

void cSoundManager::Stop(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();
			break;
		}
	}
}

void cSoundManager::Pause(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);
			break;
		}
	}
}

void cSoundManager::Resume(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);
			break;
		}
	}
}

void cSoundManager::SetVolume(string keyName, float volume)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setVolume(volume);
			break;
		}
	}
}
void cSoundManager::Mute(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setMute(true);
			break;
		}
	}
}

Channel* cSoundManager::GetPlayingChannel(string keyName)
{
	arrSoundsIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)	break;
	}
	return _channel[count];
}