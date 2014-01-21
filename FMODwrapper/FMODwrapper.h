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

	// Consider placing all sounds in a container for management
	class SoundSystem
	{
	private:
		FMOD::System *	FMODSystem;

		// Success/Fail of last recorded FMOD action
		FMOD_RESULT		m_Status;

		// Sound Channel Groups
		FMOD::ChannelGroup *	MusicChannel;
		FMOD::ChannelGroup *	SoundChannel;

		// Vector of pointers to sounds
		std::vector<SoundFile *> SoundList;

	public:
		SoundSystem();
		~SoundSystem();

		// Allocate memory to the sound
		FMOD::Sound	*	CreateSoundFX(const char * a_cFilePath, int a_iLoopCount);

		// Playback the sound
		FMOD::Channel *	PlaySoundFX(FMOD::Sound * a_Sound, bool a_bIsMusic);

		// Deallocation of sound file/stream from memory
		void			DestroySoundFX(FMOD::Sound* a_Sound);
		
		void			UpdateSystem();
	
	};
}
#endif