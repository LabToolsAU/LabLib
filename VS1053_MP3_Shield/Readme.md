# Lab Lib player

##About this library
LabLib Player is a wrapper class for the [Adafruit_VS1053_FilePlayer](https://github.com/adafruit/Adafruit_VS1053_Library).

It configures the arduino pins to only use the ["Music maker edition"](https://www.adafruit.com/product/1788) of the board and hides a lot of functions that are not needed. Futhermore it supports dividing the music into genres and manipulation of treble and bass.

Internally it uses an extended version of the Adafruit_VS1053 library. Some of the functions are borrowed from the [SFEMP3 Library](https://github.com/madsci1016/Sparkfun-MP3-Player-Shield-Arduino-Library)

All the music files in this library is pieces of tracks downloaded from [Free Music Archive](http://freemusicarchive.org)

##Setup
In order to make the setup as easy as possible, all the required .cpp and .h files (including the Adafruit_VS1053_FilePlayer) are placed along side the example .ino files. This also means that no libraries needs to be installed in order to use the code from the Arduino IDE.

** Follow the steps below to get the example code running **

1. Press the "Clone or download" button above and download a .zip archive with these files,
1. Copy the files from the directory "SD card files" to the root of a micro SD card
9. Install the shield on top of your Uno or Leonardo
2. Place the SD card in the shield.
5. Open the .ino file in one of the example folders and upload the code to your Arduino.
9. Plug in headphones or speakers and enjoy the sweet music :)


## Documentation of methods

## Constructor
```c++
LL_Player(int baudrate);
```
Constructor, makes a new LL player object

**Parameters**
int baudrate: The baudrate that the LL_Player will use to write error messages and stuff

**Returns:**
A new LL_Player object

**Example:**
```c++
//Make new LL_Player with a baudrate of 9600
LL_Player llplayer = LL_Player(9600);
```


## Starts the LL Player

```c++
int begin();

```

**Returns:**
0: If something is wrong,
1: If everything seems correct

**Notes**
Should be called before trying to do anything else


## Start Continous Play

Starts playing music from a subfolder (genre). Continous to play the music as long as updateTrackPlaying is called regularly. When all files in folder is played it will start over.

```c++
void startContinousPlay(String genre)
```

**Parameters**
A string representing a genre. The string should match a folder with mp3 files on the SD card. The name is case sensitive.


**Example:**

```c++
LL_Player llplayer = LL_Player(9600);
llplayer.startContinousPlay("dubstep");
```

## Update track playing
Should only be used if startContinousPlay is also used.

Checks if no track is playing. If there is no track it plays the next one in the genre folder. Called often to ensure a track is playing.


```c++
void updateTrackPlaying();
```

**Notes**
__SHOULD__ be called ALL the time. No call = no music  


## Skip track

Plays the next track in the genre folder. Plays the first track if there are no tracks left.


```c++
void skipToNextTrackInGenre()
```


## Skip to specific track
Plays a specific track in a genre, if it exists

```c++
void skipToTrackNr(int tracknumber);
```

**Parameters**
An integer with a number between 1 and the number of files in the genre folder.

**Example:**
```c++
llplayer.skipToTrackNr(99);

```

**Notes**
 If number does not exist it writes out an error message to the serial monitor and does nothing. This could probably be done in a more clever way... Meh...

 ## Print all files on SD card

 Does what the name says. Makes debugging easier.

 ```c++
 void printAllFilesOnSDCard();
 ```

**Notes**
The SD cards is formatet with a Fat32 filesystem which means filenames can not be longer that 8 characters. If you need to use this function that is probably the error.  

## Get Name Of Current Track

Gets the name of the track that isn playing

```c++
String getCurrentTrackName()
```

**Returns:**
A String with the name of the track that is playing

**Example:**
```c++
String name = llplayer.getCurrentTrackName();
```


## Check if music is playing
Checks if the shield is currently playing music

```c++
boolean isPlayingMusic()
```

**Returns:**
A boolean
false: if music is not playing
true: if music is playing

**Example:**

```c++
if(llplayer.isPlayingMusic()) //Do stuff
```

## Play specific file

Plays a mp3 file with a specific name in the background.

```c++
boolean startPlayingFile(const char *trackname);
```

**Parameters**
A string (sort of) with a filename (a path) to an mp3 file on the SD card


**Example:**
```c++
  llplayer.startPlayingFile("long.mp3");
```
```c++
  llplayer.startPlayingFile("dukkedak/djsatan.mp3");

```

**Notes**
If you want to know about the type of the parameter you can find more info [here](https://www.cs.bu.edu/teaching/cpp/string/array-vs-ptr/)



## Play full file
Play a file and does not return control before it is finished. Like startPlayingFile other than the fact that the everything else is "paused" until the file has finished playing.

```c++
boolean playFullFile(const char *trackname);

```


**Parameters**
A string (sort of) with a filename (a path) to an mp3 file on the SD card

**Example:**
```c++
  llplayer.playFullFile("long.mp3");
```
```c++
  llplayer.playFullFile("dukkedak/djsatan.mp3");

```

## Stop Playing

Stops the playback completely

```c++
void stopPlaying()

```


## Check if playback is paused

```c++
boolean isPaused()
```

**Returns:**
A Boolean:
true: if playback is paused,
false: if playback is not paused


## Check if playback is stopped

```c++
boolean isStopped();
```

**Returns:**
A Boolean:
true: if playback is paused,
false: if playback is not paused


## Pause Playing
Pauses the playback

```c++
void pausePlaying();
```

## Resume Playing
Resumes the playback after pause

```c++
void resumePlaying();
```


## Set Volume

Sets the volume on the left and the right channel

```c++
void setVolume(int left, int right);
```

**Parameters**
An integer between 0 and 255 with the volume that each channel should be playing.

Actually it is of the type uint8_t. Which means it can be no more than 255.

**Example:**
```c++
llplayer.setVolume(20, 20);
```


## Set Bass frequency
Set the frequency on the bass on the track

```c++
void setBassFrequency(int frequency);
```

**Parameters**
An integer with the frequency for the bass.
Actually it is a uint16_t so it can be no more than 65.536...

**Example:**
```c++
llplayer.setBassFrequency(20);
```

**Notes**
If you wonder about the strange named integer [this](http://www.cplusplus.com/reference/cstdint/) might explain things


## Set Bass amplitude
Set the amplitude on the bass on the track

```c++
void setBassAmplitude(uint16_t amplitude);
```

**Parameters**
An integer with the amplitude for the bass.
Actually it is a uint16_t so it can be no more than 65.536...

**Example:**
```c++
llplayer.setBassAmplitude(20);
```

**Notes**
If you wonder about the strange named integer [this](http://www.cplusplus.com/reference/cstdint/) might explain things

## Set Treble frequency
Set the frequency on the treble on the track

```c++
void setTrebleFrequency(uint8_t frequency);
```

**Parameters**
An integer with the frequency for treble.
Actually it is a uint16_t so it can be no more than 65.536...

**Example:**
```c++
llplayer.setTrebleFrequency(20);
```

**Notes**
If you wonder about the strange named integer [this](http://www.cplusplus.com/reference/cstdint/) might explain things


## Set Treble amplitude
Set the amplitude on the treble on the track

```c++
void setTrebleAmplitude(uint8_t amplitude);
```

**Parameters**
An integer with the amplitude for the treble.
Actually it is a uint16_t so it can be no more than 65.536...

**Example:**
```c++
llplayer.setTrebleAmplitude(20);
```

**Notes**
If you wonder about the strange named integer [this](http://www.cplusplus.com/reference/cstdint/) might explain things
