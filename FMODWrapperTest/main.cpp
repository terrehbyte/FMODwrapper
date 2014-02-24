#include <fmod\fmod.hpp>
#include <fmod\fmod_errors.h>
#include <FMODwrapper.h>

#include <iostream>
void main ()
{
	tbyte::SoundSystem MyFirstSoundSystem;

	tbyte::SoundFile * MyFirstSound = MyFirstSoundSystem.CreateSoundFX("test.ogg", -1);

	MyFirstSoundSystem.PlaySoundFX(MyFirstSound, true);

	bool bRunning = true;

	printf("Close the console window to end this example.");

	while(bRunning)
	{
		MyFirstSoundSystem.UpdateSystem();
	}
}