#include "FMODwrapper.h"

namespace tbyte
{
	// Add support for SFX channel
	// Add support for BGM channel

	SoundSystem::SoundSystem()
	{
		// Create FMOD System
		m_Status = FMOD::System_Create(&FMODSystem);

		if (m_Status != FMOD_OK)
		{
			printf("FMOD Error! (%d) %s\n", m_Status, FMOD_ErrorString(m_Status));
			exit(-1);
		}

		// Initialize FMOD System
		m_Status = FMODSystem->init(100,			  // Max Channels
									FMOD_INIT_NORMAL, // FLAGS
									0);				  // Extra Driver Data?
	
		if (m_Status != FMOD_OK)
		{
			printf("FMOD Error! (%d) %s\n", m_Status, FMOD_ErrorString(m_Status));
			exit(-1);
		}

		// Create Channel Groups
		m_Status = FMODSystem->createChannelGroup("Music Channel", &MusicChannel);

		if (m_Status != FMOD_OK)
		{
			printf("FMOD Error! (%d) %s\n", m_Status, FMOD_ErrorString(m_Status));
			exit(-1);
		}

		m_Status = FMODSystem->createChannelGroup("Sound Channel", &SoundChannel);
		if (m_Status != FMOD_OK)
		{
			printf("FMOD Error! (%d) %s\n", m_Status, FMOD_ErrorString(m_Status));
			exit(-1);
		}
	}
	SoundSystem::~SoundSystem()
	{
		// Release System Resources upon destruction
		FMODSystem->release();

		// Release Sound Resources
		for(std::vector<SoundFile *>::iterator it=SoundList.begin(); // place iterator at beginning
			it != SoundList.end(); // run while iterator is not at the end
			++it				// advance iterator
			)
		{
			(*it)->FMODSoundInstance->release();
		}

		// if this class stores them in a container, loop through it and call DestroySound() on each of them
	}

	FMOD::Sound * SoundSystem::CreateSoundFX(const char * a_cFilePath, bool a_bLoop=false)
	{
		SoundList.emplace_back(new SoundFile);

		SoundList.back()->FMODSoundInstance;

		// Initialize the sound file
		m_Status = FMODSystem->createSound(a_cFilePath, FMOD_DEFAULT, 0, &SoundList.back()->FMODSoundInstance);

		// Assign loop flag
		if (a_bLoop)
		{
			SoundList.back()->FMODSoundInstance->setMode(FMOD_LOOP_NORMAL);
		}

		// Return the pointer to the sound for management purposes
		return SoundList.back()->FMODSoundInstance;
	}

	void SoundSystem::PlaySoundFX(FMOD::Sound * a_Sound, bool a_bIsMusic)
	{
		// Create a Channel
		FMOD::Channel * SFXChannel;

		// Play the Sound
		m_Status = FMODSystem->playSound(a_Sound, 0, false, &SFXChannel);

		// Assign the Channel
		SFXChannel->setChannelGroup(a_bIsMusic ? MusicChannel : SoundChannel);
	}

	void SoundSystem::DestroySoundFX(FMOD::Sound* a_Sound)
	{
		// Call FMOD::Sound::release on the sound file/stream
		m_Status = a_Sound->release();
	}

	void SoundSystem::UpdateSystem()
	{
		FMODSystem->update();
	}
}