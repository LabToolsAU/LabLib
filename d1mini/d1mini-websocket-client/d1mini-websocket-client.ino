// neo pixel control lib
#include <WS2812FX.h>

// wifi modules
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

// websocket includes
#include <WebSocketsClient.h>

#define LED_COUNT 1
#define LED_PIN D4
#define RECONNECT_INTERVAL 1000

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

	switch(type) {
		case WStype_DISCONNECTED:
			Serial.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED: {
			Serial.printf("[WSc] Connected to url: %s\n", payload);
			// send message to server when Connected			
            break;
		}			
		case WStype_TEXT:
			Serial.printf("[WSc] get text: %s\n", payload);
            String cmd = (char*)payload;
			
            if(cmd == "TOGGLE_LIGHTS"){
                toggleLights();
            }

			break;
	}

}

void setup() {
    
  Serial.begin(115200);
  // interresting stuff here - with wifi  

  // we only need this inside the setup, as its a one-time thing
  WiFiManager wifiManager;
  /*
  * Calling autoConnect will attempt to connect to a known wifi network
  * saved in memory on the device. If no known network is found, the D1
  * will create a temporary wifi network, which you can connect to
  * and then input credentials for your wifi (ssid and password)
  * 
  * Calling autoConnect("wifiname"); will give the temporary wifi 
  * (if it is created) a name (e.g. 'wifiname').
  * */
    wifiManager.autoConnect();    
    Serial.println("Connected to wifi");
    // from here we should be connected to wifi, so connect to the websocket server
    // server address, port and URL and ?id= parameter to be parsed on the server side
    webSocket.begin("192.168.0.30", 3000, "/websockets?id=d1mini"); 

    // bind the event handler we created above here
    webSocket.onEvent(webSocketEvent);    

    // if connection is ever lost, we will attempt to reconnect to the 
    // server with the reconnect interval
    webSocket.setReconnectInterval(5000);
    Serial.println("Socket connected, initiating loop!");

      // neopixel magic - dont worry about it right now
    ws2812fx.init();
    ws2812fx.setBrightness(100);
    ws2812fx.setSpeed(200);
    ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
    ws2812fx.start();
}

void loop() {
  ws2812fx.service(); // run the neopixel loop
  webSocket.loop(); // run the websocket loop
}

bool lightsOn = true;

void toggleLights(){
    if(lightsOn == true){
        lightsOn = false;        
        ws2812fx.setBrightness(0);
    } else if (lightsOn == false){
        lightsOn = true;
        ws2812fx.setBrightness(100);
    }
}