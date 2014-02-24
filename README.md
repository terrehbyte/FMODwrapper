#FMODwrapper

This FMOD wrapper was designed for easy integration into other projects by consisting of only a header. Like many of my other projects, this was built primarily with me in mind, but can be expanded for other people's uses as well if anyone wishes to contribute.

#Installation

###Visual Studio 2010

This installation guide assumes that you are capable of at least including the header and library files necessary for using FMOD Version 1.02.12 (the most up-to-date version at the time of writing).

1. Include FMOD.hpp and FMOD_errors.h. These always come before the wrapper header.
2. Include the wrapper header.

#Basic Usage

1. Include the wrapper header file where appropiate.
2. Instantiate an instance of the SoundManager class.
3. Store an instance of FMOD::Sound by calling "CreateSoundFX(const char * a\_cFilePath, bool a \_bLoop)" on the SoundManager instance. The first argument specifies the filepath to the sound file. The second argument is a bool that specifies whether or not the sound is supposed to loop endlessly.
4. Play a sound by calling the member function, "PlaySoundFX(FMOD::Sound * a\_Sound, bool a\_bIsMusic)". The first argument points to the instance of FMOD::Sound that was created in step 3. The second argument specifies whether or not the sound played will reside within the SFX sound group or the BGM sound group.
5. If a game loop exists, call "UpdateSystem()" on the SoundManager instance once per frame.

For more information, see the included test project.

#Contributions

Forks and pull requests are more than welcome and are encouraged.

Keeping in mind that this originated as a class project, a loose coding standard applies. Hungarian notation is primarily used for primitive types such as 'int' or 'bool'. There is no notation for this library's classes. That said, they should be stored in the "tbyte" namespace. I should probably come up with a better namespace for this considering there is no direct connection to me.

#License & Attributions

The wrapper code in this repo for the FMOD Programmer's API is licensed under the zlib license.

See the [LICENSE file](https://github.com/terrehbyte/FMODwrapper/blob/master/LICENSE.md) for license rights.

FMOD Wrapper, copyright (c) 2014 Terry Nguyen.

FMOD Studio, copyright © Firelight Technologies Pty, Ltd., 1994-2013.

FMOD Sound System, copyright © Firelight Technologies Pty, Ltd., 1994-2013.


Melodic Power Track C64, from skrjablin - Attribution 3.0 Unported (CC BY 3.0)


Ogg Vorbis codec. BSD license. - Copyright (c) 2002, Xiph.org Foundation


For Android platform code. - Copyright (C) 2010 The Android Open Source Project All rights reserved.
