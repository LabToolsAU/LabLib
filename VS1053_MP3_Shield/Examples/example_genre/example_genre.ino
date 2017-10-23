/****************************************************
Written for "Lab Lib" by  Graunephar

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

#define BAUDRATE 9600 // The baudrate used by llplayer to send error messeges
#define DELAY 60000 // If you choose new genres to wuickly things will crash

LL_Player llplayer = LL_Player(BAUDRATE);

unsigned long timestamp = millis();

String genres[] = {"jazz", "dakkeduk", "hip-hop"};
const int nrOfGenres = 3; //The number of genres in playlist

void setup() {

  Serial.begin(BAUDRATE); // we want to use the same baud rate as ll player so we can outout to the same console

  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }

  setupLLPlayer();

  llplayer.startContinousPlay("dakkeduk"); // Start playing from new genre

}


void loop() {

  delay(10);

   /*
   * PRO TIP: Use millis not delays in your code
   * Otherwise continous track update will not happen ;) */

   llplayer.updateTrackPlaying(); //should be called continbously in order to guarante continous play.

   //Changing genre after 60 seconds
   if(millis() > timestamp + DELAY) {
     String newgenre = randomGenrePicker();
     llplayer.startContinousPlay(newgenre); // Start playing from new genre
     timestamp = millis();
  }

}

//Pick a random genre from an array of genres, has a tendency to choose the second element in the array
String randomGenrePicker() {
  int rando = random(0, nrOfGenres); //Generate random nr netween 0 and the size of the playlist
  Serial.print("New Genre picked: ");
  Serial.println(genres[rando]);
  return genres[rando];
}

//Initializing up all the things in the LL_Player
void setupLLPlayer() {
  if(!llplayer.begin()) {
    ; //The Adafruit VS1053 shield is not configured correctly. Halt here.
    while(1);
  };
}
