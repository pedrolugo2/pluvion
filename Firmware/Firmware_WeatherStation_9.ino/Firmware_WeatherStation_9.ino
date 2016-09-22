//filesystem
#include <FS.h>                   //this needs to be first, or it all crashes and burns...



// to make an unique ID
// __TIME__
// https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html


////////////////////////////////////////////////////////
// debug defines
// you may frown upon preprocessor directives ;-)
#define DEBUG_ENABLED true

#if DEBUG_ENABLED
#define DEBUG(text) { Serial.println ( (text) ); }
#else
#define DEBUG(text) {}
#endif
// end DEBUG(text)

#if DEBUG_ENABLED
#define DEBUG_SETUP(baudrate) { Serial.begin( (baudrate) ); }
#else
#define DEBUG_SETUP(baudrate) {}
#endif
// end DEBUG_SETUP(baudrate)
////////////////////////////////////////////////////////

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
// to save custom parameters
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

//Pins used in NODEMCU
#define DHTPIN_1 D1 // pin where the dht22 is connected
#define hall_pin D2
ADC_MODE(ADC_VCC); // debug voltage in

//Thingspeak variables
String apiKey = "P311PRHCHMLDI8Z7";
const char* server = "api.thingspeak.com";

//// Wifi connection variables
WiFiClient client;

//define your default values here, if there are different values in config.json, they are overwritten.
char geo_code[40];

//flag for saving data
bool shouldSaveConfig = false;

//General variables
unsigned long time_passed = 0;
unsigned long time_passed_0 = 0;
unsigned long last_time_passed = 0;
unsigned long zerador = 0;
volatile int chuva_status = 0;

//DHT22 Variables
volatile float h;
volatile float t;
volatile float hic;
DHT dht1(DHTPIN_1, DHT22, 20);


//Tipping Bucket Variables
const float area = 6313.0; //Contribuition area in mm²
const float calibrated_vol = 2.2; //Bucket Calibrated Volume in ml
volatile float tipcount = 0;
volatile float last_tipcount = 0;
float rain = 0;
int real_tipcount = 0;
unsigned long lastmillis = 0;


//Function for reading DHT22
void ReadDHTSensor_1() {
  h = dht1.readHumidity();
  t = dht1.readTemperature();
  hic = dht1.computeHeatIndex(t, h, false);
  if (isnan(h) || isnan(t)) {
    DEBUG("Failed to read from DHT sensor!");
    return;
  }
  DEBUG("Sensor_1");
  DEBUG("Temperature: ");
  DEBUG(t);
  DEBUG(" degrees Celsius, Humidity: ");
  DEBUG(h);
  DEBUG("%. Send to Thingspeak.");
  DEBUG("Feelslike:");
  DEBUG(hic);
  DEBUG(" degrees Celsius.");
  // doesn't need to divide
  DEBUG(ESP.getVcc() / 1000.000);
  DEBUG("Waiting...");
}

//Function for sending data to Thingspeak
void connect2wifi_send() {
  if (client.connect(server, 80)) { //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(hic);
    postStr += "&field4=";
    postStr += String(rain);
    postStr += "&field5=";
    postStr += String(ESP.getVcc() / 1000.000);
    postStr += "&field6=";
    postStr += String(chuva_status);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    client.stop();
  }
}
//Function for counting Tips
void tip_fan() {
  tipcount++;
  //DEBUG(tipcount);
}

void chuva_on() {
#if DEBUG_ENABLED
  DEBUG("Ta chuveno");
  DEBUG(digitalRead(D2));
#endif
  chuva_status  = 1;
  detachInterrupt(D2);    //Disable interrupt when calculating

}


void setup() {

  //Serial Communication for DEBUG
  DEBUG_SETUP(115200);
  DEBUG("###### Warm up ######");
  DEBUG(ESP.getResetReason());
  DEBUG(ESP.getChipId());

  //Initializing DHT22 Sensor
  dht1.begin();


  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_geo("geo", "geo code", geo_code, 40);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //add all your parameters here
  wifiManager.addParameter(&custom_geo);

  wifiManager.autoConnect();

  DEBUG("Connected...");


  //////////////////////////////////////////////
// aqui vai o codigo pra ler e gravar no filesystem, de acordo com o exemplo 
// AutoConnectWithFSParameters.ino
  //////////////////////////////////////////////

  ReadDHTSensor_1();
  connect2wifi_send();
  last_time_passed = time_passed;
  attachInterrupt(hall_pin, tip_fan, CHANGE);
  attachInterrupt(D2, chuva_on, CHANGE);
  //pinMode(D2,INPUT);

}

void loop() {
  time_passed_0 = millis();
  if ((time_passed_0 - lastmillis) >= 1000) { //Debouncing strategy
    detachInterrupt(hall_pin);    //Disable interrupt when calculating
    if (tipcount > last_tipcount) {
      real_tipcount++;
      last_tipcount = tipcount;
      rain = real_tipcount * calibrated_vol * 1000 / area; /* Convert tip into mm*/
      connect2wifi_send();
    }

    //   DEBUG("Tips: ");
    //   DEBUG(rain);
    lastmillis = millis(); // Update lasmillis
    attachInterrupt(hall_pin, tip_fan, CHANGE); //enable interrupt
  }

  time_passed = millis();
  if ((time_passed - last_time_passed) >= 1800000) { //read DHT22 every 30 min
    ReadDHTSensor_1();
    connect2wifi_send();
    last_time_passed = time_passed;
    zerador++;
    return;
  }
  // "zero" rain counter every 24 hours
  if (zerador == 48) {
    tipcount = 0;
    last_tipcount = 0;
    rain = 0;
    real_tipcount = 0;
    zerador = 0;
  }
  if (chuva_status == 1) {
    pinMode(D2, INPUT);
    if (digitalRead(D2) == 1) {
      DEBUG("Parou de chover");
      chuva_status  = 0;
      attachInterrupt(D2, chuva_on, CHANGE);
    }
  }
}

//callback notifying us of the need to save config
void saveConfigCallback () {
  DEBUG("Should save config");
  shouldSaveConfig = true;
}


