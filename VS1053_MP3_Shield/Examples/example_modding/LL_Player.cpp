/****************************************************
"Lab Lib" Music player extension by Graunephar

                       -s`
                     -sdd`
                   -ydddd`
                 -ydddddd`
               :ydddddddo
             :ydddddddo`
           :yddddddd+`   yddddd/           :dddddh
         /hddddddd+`     +dddddh-         .hddddds
       /hddddddh+`       `ydddddds:`   `-oddddddh`
    `/hddddddh+`          `oddddddddddddddddddds`
  `/hddddddh/`              -sddddddddddddddds-
`+hddddddh/                   `:oydddddddyo/`

// It's not a dick
****************************************************/

#include "LL_Player.h"
#include <SPI.h>
#include "Adafruit_VS1053.h"
#include <SD.h>

// define the pins used
//#define CLK 13       // SPI Clock, shared with SD card
//#define MISO 12      // Input data, from VS1053/SD card
//#define MOSI 11      // Output data, to VS1053/SD card
// Connect CLK, MISO and MOSI to hardware SPI pins.
// See http://arduino.cc/en/Reference/SPI "Connections"

// These are the pins used for the breakout example
#define BREAKOUT_RESET  9      // VS1053 reset pin (output)
#define BREAKOUT_CS     10     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    8      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin


LL_Player::LL_Player(int baudrate) : _musicPlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS) {
  _baudrate = baudrate;
  _currentTrackNumber = 0;
}

void LL_Player::printDirectory(File dir, int numTabs) {
   while(true) {

     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }

     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }

     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }

 }


 int LL_Player::begin() {

   Serial.begin(_baudrate);
   while (!Serial) {
   ; // wait for serial port to connect. Needed for native USB port only
   }


   Serial.println("Initializing VS1053 shield");
   if (! _musicPlayer.begin()) { // initialise the music player
      Serial.println("Couldnt connect to VS1053.");
      Serial.println("You properbly have a problem with your connections");
      return 0;
   }

   Serial.println(F("VS1053  found"));

    if (!SD.begin(CARDCS)) {
     Serial.println(F("SD failed, or not present"));
     return 0;  // don't do anything more
   }

   // list files
   SD.open("/");

   // Set volume for left, right channels. lower numbers == louder volume!
   _musicPlayer.setVolume(20,20);

   // Timer interrupts are not suggested, better to use DREQ interrupt!
   //musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int

   // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
   // audio playing
   _musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

    return 1;

 }

/************************************************************/
/* Custom methods for assignment */

//Tell which grenre we want to play
void LL_Player::setGenre(String genre) {
  _currentGenre = genre;
  _currentTrackNumber = 0; //Reset track nr
}

//Play contrinous in background from one genre
void LL_Player::startContinousPlay(String genre) {
    stopPlaying(); // Stop last plating track
    setGenre(genre);
   _genrePlaylistSize = countFilesInDir(_currentGenre);
   Serial.print("Playlist size: ");
   Serial.println(_genrePlaylistSize);
   continousPlay();
}

void LL_Player::skipToNextTrackInGenre() {
  continousPlay();
}

//Playes a specific track number
void LL_Player::skipToTrackNr(int tracknumber) {
  if(tracknumber > _genrePlaylistSize) {
    Serial.println("Your nbr is bigger than the tracks you have provided");
  } else {
    _currentTrackNumber = tracknumber;
    playTrack();
  }
}

//Continous playing next file
void LL_Player::continousPlay() {
  incrementTrackNumber();
  playTrack();
  }

//Starts playing the current track in background
void LL_Player::playTrack() {
  String filepath = getNextTrackName();
  const char * pointertofile = filepath.c_str(); //Beware pointer and conversion magic
  startPlayingFile(pointertofile);
}

//Updates the track which is playing. Should be called continoiusly
void LL_Player::updateTrackPlaying() {
  if(!isPlayingMusic()) {
    Serial.println("Tracked stopped, playing next track");
    continousPlay();
  }
}

/**
* Increments track nr
* Garantees that: nr is never bigger than the playlist size **/
void LL_Player::incrementTrackNumber() {
  _currentTrackNumber++;
  if(isPlaylistEmpty()) _currentTrackNumber = 1; // Reset track nr if no more songs
}

//Calculates if the playlist is empty
boolean LL_Player::isPlaylistEmpty(){
  return _currentTrackNumber > _genrePlaylistSize;
}

//Genrate file names
String LL_Player::getNextTrackName() {
  String result = _currentGenre + "/" + _currentTrackNumber + ".mp3";
  Serial.print("Next track name is: ");
  Serial.println(result);
  return result;
}


int LL_Player::countFilesInDir(String directoryname) {

  File dir = SD.open(directoryname);
  int count = 0;

  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }

     count++; // Count file found
     entry.close();
    }

  return count;

}

/* Debugging methods */

void LL_Player::printAllFilesOnSDCard() {
  Serial.println("Listing files");
  printDirectory(SD.open("/"), 0);
}



/************************************************************/
/* Callbacks for Adafruits class */

 String LL_Player::getCurrentTrackName() {
   File file = _musicPlayer.currentTrack;
   return file.name();
 }

 boolean LL_Player::isPlayingMusic() {
   return _musicPlayer.playingMusic;
 }

 boolean LL_Player::startPlayingFile(const char *trackname) {
   return _musicPlayer.startPlayingFile(trackname); // Beware of pointer magic!!!
 }

 boolean LL_Player::playFullFile(const char *trackname) {
   return _musicPlayer.playFullFile(trackname); //Beware of pointer magic!!
 }

 void LL_Player::stopPlaying(void) {
   _musicPlayer.stopPlaying();
 }

 boolean LL_Player::isPaused(void) {
  return _musicPlayer.paused();
 }

 boolean LL_Player::isStopped(void) {
   return _musicPlayer.stopped();
 }

 void LL_Player::pausePlaying() {
   _musicPlayer.pausePlaying(true);
 }

 void LL_Player::resumePlaying() {
   _musicPlayer.pausePlaying(false);
 }

 void LL_Player::setVolume(uint8_t left, uint8_t right) {
   _musicPlayer.setVolume(left, right);
 }

 //Callback for frederiks extensions of Adafruit class
 void LL_Player::setBassFrequency(uint16_t frequency) {
   _musicPlayer.setBassFrequency(frequency);
 }

 void LL_Player::setBassAmplitude(uint16_t amplitude) {
   _musicPlayer.setBassAmplitude(amplitude);
 }

 void LL_Player::setTrebleFrequency(uint8_t frequency) {
   _musicPlayer.setTrebleFrequency(frequency);
 }

 void LL_Player::setTrebleAmplitude(uint8_t amplitude) {
   _musicPlayer.setTrebleAmplitude(amplitude);
 }
