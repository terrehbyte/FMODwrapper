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

		std::vector<SoundFile *> SoundList;

	public:
		SoundSystem();
		~SoundSystem();

		// Allocate memory to the sound
		FMOD::Sound *	CreateSoundFX(const char * a_cFilePath, bool a_bLoop);

		// Playback the sound
		void			PlaySoundFX(FMOD::Sound * a_Sound, bool a_bIsMusic);

		// Deallocation of sound file/stream from memory
		void			DestroySoundFX(FMOD::Sound* a_Sound);
		
		void			UpdateSystem();
	
	};
}
#endif