#ifndef _FMODWRAPPER_H_
#define _FMODWRAPPER_H_

#ifndef _FMOD_HPP
#error FMODwrapper.h was included before fmod.hpp (if included at all)
#endif

#ifndef _FMOD_ERRORS_H
#error FMODwrapper.h was included before fmod_errors.h (if included at all)
#endif

#include <iostream>
#include <vector>

namespace tbyte
{
	// Consider placing all sounds in a container for management
	class SoundSystem
	{
	private:
		FMOD::System *	FMODSystem;

		// Success/Fail of last recorded FMOD action
		FMOD_RESULT		m_Status;

		// Vector of pointers to sounds
		std::vector<FMOD::Sound *> SoundList;

	public:
		SoundSystem();
		~SoundSystem();

		// Sound Channel Groups
		FMOD::ChannelGroup *	MusicChannel;
		FMOD::ChannelGroup *	SoundChannel;

		// Allocate memory to the sound
		FMOD::Sound *	CreateSoundFX(const char * a_cFilePath, const int a_iLoopCount);

		// Playback the sound
		FMOD::Channel *	PlaySoundFX(FMOD::Sound * a_Sound, bool a_bIsMusic);

		// Deallocation of sound file/stream from memory
		void			DestroySoundFX(FMOD::Sound * a_Sound);
		
		// FMOD Update System - Perform necessary system upkeep routines
		void			UpdateSystem();

		// Set Sound Group Volume
		void			SetSoundVolume(const float a_fNewVolume);
		
		// Get Music Group Volume
		void			SetMusicVolume(const float a_fNewVolume);
	
	};

	// Add support for SFX channel
	// Add support for BGM channel

	inline SoundSystem::SoundSystem()
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
	inline SoundSystem::~SoundSystem()
	{
		// Release System Resources upon destruction
		FMODSystem->release();

		// Release Sound Resources
		for(std::vector<FMOD::Sound *>::iterator it=SoundList.begin(); // place iterator at beginning
			it != SoundList.end(); // run while iterator is not at the end
			++it				// advance iterator
			)
		{
			(*it)->release();
		}

		// if this class stores them in a container, loop through it and call DestroySound() on each of them
	}

	inline FMOD::Sound * SoundSystem::CreateSoundFX(const char * a_cFilePath, const int a_iLoopCount=0)
	{
		// Store pointer to newly created FMOD::Sound
        SoundList.emplace_back(nullptr);

		// Initialize the sound file
		m_Status = FMODSystem->createSound(a_cFilePath, FMOD_DEFAULT, 0, &SoundList.back());

		// Assign loop flag if applicable
		if (a_iLoopCount != 0)
		{
			SoundList.back()->setMode(FMOD_LOOP_NORMAL);
			SoundList.back()->setLoopCount(a_iLoopCount);
		}

		// Return the pointer to the sound for management purposes
		return SoundList.back();
	}

	inline FMOD::Channel * SoundSystem::PlaySoundFX(FMOD::Sound * a_Sound, bool a_bIsMusic)
	{
		// Create a Channel
		FMOD::Channel * SFXChannel;

		// Play the Sound
		m_Status = FMODSystem->playSound(a_Sound, 0, false, &SFXChannel);

		// Assign the Channel
		SFXChannel->setChannelGroup(a_bIsMusic ? MusicChannel : SoundChannel);

		// Return the Channel to offer control to the programmer over playback and volume
		return SFXChannel;
	}

	inline void SoundSystem::DestroySoundFX(FMOD::Sound * a_Sound)
	{
		// Call FMOD::Sound::release on the sound file/stream
		m_Status = a_Sound->release();
	}

	inline void SoundSystem::UpdateSystem()
	{
		// FMOD Update System - Perform necessary system upkeep routines
		FMODSystem->update();
	}

	// Set Sound Group Volume
	inline void SoundSystem::SetSoundVolume(const float a_fNewVolume)
	{
		SoundChannel->setVolume(a_fNewVolume);
	}
		
	// Get Music Group Volume
	inline void SoundSystem::SetMusicVolume(const float a_fNewVolume)
	{
		MusicChannel->setVolume(a_fNewVolume);
	}
}
#endif