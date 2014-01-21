// Remember to go to FMODwrapper.h and redefine the "#include"
// directives so the wrapper can access the FMOD library!
#include "FMODwrapper.h"

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