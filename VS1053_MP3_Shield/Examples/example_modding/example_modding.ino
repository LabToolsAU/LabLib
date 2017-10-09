/***************************************************
  This is an example for the Adafruit VS1053 Codec Breakout

  Designed specifically to work with the Adafruit VS1053 Codec Breakout
  ----> https://www.adafruit.com/products/1381

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

/****************************************************
Extended for "Lab Lib" by Frederik Kold and Graunephar

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


// include SPI, MP3 and SD libraries
#include "LL_Player.h"

#define BAUDRATE 9600 // The baudrate used by llplayer to send error messeges

LL_Player musicPlayer = LL_Player(BAUDRATE);

  int volume = 20;
  int bassAmp = 0;
  int bassFreq = 2;
  int trebleAmp = 0;
  int trebleFreq = 0;

void setup() {


    Serial.begin(BAUDRATE); // we want to use the same baud rate as ll player so we can outout to the same console

    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
    }

    setupLLPlayer();

  // Play one file, don't return until complete
  Serial.println(F("Playing First track"));
  musicPlayer.startPlayingFile("long.mp3");
}

void loop() {
  // File is playing in the background
  if (musicPlayer.isStopped()) {
    Serial.println("Done playing music");
    while (1) {
      delay(10);  // we're done! do nothing...
    }
  }

  if (Serial.available()) {
    char c = Serial.read();

    // if we get an 's' on the serial console, stop!
    if (c == 's') {
      musicPlayer.stopPlaying();
    }

    if (c == '+'){
      volume = volume - 1;
      musicPlayer.setVolume(volume, volume);
      Serial.println("Volume Up");
    }

    if (c == '-'){
      volume = volume + 1;
      musicPlayer.setVolume(volume, volume);
      Serial.println("Volume Down");
    }

    if (c == 't'){
      trebleFreq = trebleFreq + 1;
      musicPlayer.setTrebleFrequency(trebleFreq);
      Serial.println("Treble Freq Up: ");
      Serial.print(trebleFreq);
    }

    if (c == 'g'){
      trebleFreq = trebleFreq - 1;
      musicPlayer.setTrebleFrequency(trebleFreq);
      Serial.println("Treble Freq down: ");
      Serial.print(trebleFreq);
    }

    if (c == 'y'){
      trebleAmp = trebleAmp + 1;
      musicPlayer.setTrebleAmplitude(trebleAmp);
      Serial.println("Treble Amp Up: ");
      Serial.print(trebleAmp);
    }

    if (c == 'h'){
      trebleAmp = trebleAmp - 1;
      musicPlayer.setTrebleAmplitude(trebleAmp);
      Serial.println("Treble Amp down: ");
      Serial.print(trebleAmp);
    }

    if (c == 'i'){
      bassAmp = bassAmp + 1;
      musicPlayer.setBassAmplitude(bassAmp);
      Serial.println("Bass Amp Up: ");
      Serial.println(bassAmp);
    }

    if (c == 'k'){
      bassAmp = bassAmp - 1;
      musicPlayer.setBassAmplitude(bassAmp);
      Serial.println("Bass Amp down: ");
      Serial.print(bassAmp);
    }

    if (c == 'o'){
      bassFreq = bassFreq + 1;
      musicPlayer.setBassFrequency(bassFreq);
      Serial.println("bass Freq Up: ");
      Serial.print(bassFreq);
    }

    if (c == 'l'){
      bassFreq = bassFreq - 1;
      musicPlayer.setBassFrequency(bassFreq);
      Serial.println("Bass Freq down: ");
      Serial.print(bassFreq);
    }

    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (! musicPlayer.isPaused()) {
        Serial.println("Paused");
        musicPlayer.pausePlaying();
      } else {
        Serial.println("Resumed");
        musicPlayer.resumePlaying();
      }
    }
  }

  delay(100);
}

//Initializing up all the things in the LL_Player
void setupLLPlayer() {
  if(!musicPlayer.begin()) {
    ; //The Adafruit VS1053 shield is not configured correctly. Halt here.
    while(1);
  };
}
