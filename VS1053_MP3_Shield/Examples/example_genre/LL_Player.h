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


#include <SD.h>
#include "Adafruit_VS1053.h"
#include "Adafruit_VS1053.h"


class LL_Player {

  Adafruit_VS1053_FilePlayer _musicPlayer;
  int _baudrate;
  String _currentGenre;
  int _currentTrackNumber;
  int _genrePlaylistSize;


public:
  //Setup methods
  LL_Player(int baudrate);
  int begin();

  //Custom play methods for course
  void startContinousPlay(String genre); //Play contrinous in background from one genre
  void updateTrackPlaying();
  void skipToNextTrackInGenre();
  void skipToTrackNr(int tracknumber);


  //Debugging
  void printAllFilesOnSDCard();

  //Callback method for Adafruits class
  String getCurrentTrackName();
  boolean isPlayingMusic();
  boolean startPlayingFile(const char *trackname);
  boolean playFullFile(const char *trackname);
  void stopPlaying(void);
  boolean isPaused(void);
  boolean isStopped(void);
  void pausePlaying();
  void resumePlaying();
  void setVolume(uint8_t left, uint8_t right);
  boolean playFullFile(char *trackname);

  //Callback for frederiks extensions of Adafruit class
  void setBassFrequency(uint16_t frequency);
  void setBassAmplitude(uint16_t amplitude);
  void setTrebleFrequency(uint8_t frequency);
  void setTrebleAmplitude(uint8_t amplitude);


private:
  String getNextTrackName();
  void printDirectory(File dir, int numTabs); //List all stuff on SD card
  int countFilesInDir(String directoryname);
  void continousPlay();
  void setGenre(String genre); //Tell which grenre we want to play
  boolean isPlaylistEmpty();
  void incrementTrackNumber();
  void playTrack();



};
