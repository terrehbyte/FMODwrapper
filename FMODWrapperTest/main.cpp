// Remember to go to FMODwrapper.h and redefine the "#include"
// directives so the wrapper can access the FMOD library!
#include "FMODwrapper.h"

#include <iostream>
void main ()
{
	tbyte::SoundSystem MyFirstSoundSystem;

	FMOD::Sound * MyFirstSound = MyFirstSoundSystem.CreateSoundFX("example.flac", true);

	MyFirstSoundSystem.PlaySoundFX(MyFirstSound, true);

	bool bRunning = true;

	printf("Close the console window to end this example.");

	while(bRunning)
	{
		MyFirstSoundSystem.UpdateSystem();
	}
}