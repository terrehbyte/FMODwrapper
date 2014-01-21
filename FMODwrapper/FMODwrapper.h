#ifndef _FMODWRAPPER_H_
#define _FMODWRAPPER_H_

// Replace these FMOD inclusion statements with your own!
#include <fmod\fmod.hpp>
#include <fmod\fmod_errors.h>
#include <iostream>

#include <vector>

namespace tbyte
{
	// PURPOSE: To allow FMOD::Sound to be put into vectors that would otherwise call its
	// private constructor.
	class SoundFile
	{
	public:
		FMOD::Sound * FMODSoundInstance;
		// todo: make this a fully-fledged class that has member functions for playing and stopping
		// when created by SoundSystem, give it a pointer to SoundSystem for FMOD::Sound access
	};

	// Instead of the above, consider creating an additional wrapper class that will
	// provide basic functions such as volume control for specific tbyte::SoundFile instances

	// Consider placing all sounds in a container for management
	class SoundSystem
	{
	private:
		FMOD::System *	FMODSystem;

		// Success/Fail of last recorded FMOD action
		FMOD_RESULT		m_Status;

		// Vector of pointers to sounds
		std::vector<SoundFile *> SoundList;

	public:
		SoundSystem();
		~SoundSystem();

		// Sound Channel Groups
		FMOD::ChannelGroup *	MusicChannel;
		FMOD::ChannelGroup *	SoundChannel;

		// Allocate memory to the sound
		SoundFile *	CreateSoundFX(const char * a_cFilePath, const int a_iLoopCount);

		// Playback the sound
		FMOD::Channel *	PlaySoundFX(SoundFile * a_Sound, bool a_bIsMusic);

		// Deallocation of sound file/stream from memory
		void			DestroySoundFX(SoundFile * a_Sound);
		
		// FMOD Update System - Perform necessary system upkeep routines
		void			UpdateSystem();

		// Set Sound Group Volume
		void			SetSoundVolume(const float a_fNewVolume);
		
		// Get Music Group Volume
		void			SetMusicVolume(const float a_fNewVolume);
	
	};
}
#endif