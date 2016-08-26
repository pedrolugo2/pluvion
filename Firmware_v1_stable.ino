#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>

//Pins used in NODEMCU
#define DHTPIN_1 D7 // pin where the dht22 is connected
#define hall_pin D4

//Thingspeak variables
String apiKey = "P311PRHCHMLDI8Z7";
const char* server = "api.thingspeak.com";

//// Wifi connection variables
WiFiClient client;

//General variables
unsigned long time_passed = 0;
unsigned long time_passed_0 = 0;
unsigned long last_time_passed = 0;

//DHT22 Variables
volatile float h;
volatile float t;
volatile float hic;
DHT dht1(DHTPIN_1, DHT22,20);


//Tipping Bucket Variables
const float area = 6313.0; //Contribuition area in mm²
const float calibrated_vol = 2.2; //Bucket Calibrated Volume in ml
volatile float tipcount = 0;
volatile float last_tipcount = 0;
float rain = 0;
int real_tipcount = 0;
unsigned long lastmillis = 0;


//Function for reading DHT22
void ReadDHTSensor_1(){
  h = dht1.readHumidity();
  t = dht1.readTemperature();
  hic = dht1.computeHeatIndex(t, h, false);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  h = dht1.readHumidity();
  t = dht1.readTemperature();
  hic = dht1.computeHeatIndex(t, h, false);
  
     Serial.println("Sensor_1");
     Serial.print("Temperature: ");
     Serial.print(t);
     Serial.print(" degrees Celcius, Humidity: ");
     Serial.print(h);
     Serial.println("%. Send to Thingspeak.");
     Serial.print("Feelslike:");
     Serial.print(hic);
     Serial.println(" degrees Celcius.");
     Serial.println("Waiting...");
}

//Function for sending data to Thingspeak
void connect2wifi_send(){
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(t);
           postStr +="&field2=";
           postStr += String(h);
           postStr +="&field3=";
           postStr += String(hic);
           postStr +="&field4=";
           postStr += String(rain);
           postStr += "\r\n\r\n";
           
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);
     client.stop(); 
  }
}
//Function for counting Tips
void tip_fan(){ 
  tipcount++;
 //Serial.println(tipcount);
}

void setup() {
  
  //Initializing DHT22 Sensor
  dht1.begin();
  //Serial Communication for DEBUG
  Serial.begin(115200);
  Serial.println("###### Warm up ######");
  WiFiManager wifiManager;
  wifiManager.autoConnect();
  Serial.println("Connected...");
  ReadDHTSensor_1();
  connect2wifi_send();
  last_time_passed = time_passed;
  attachInterrupt(hall_pin, tip_fan, CHANGE);
}

void loop() {
  time_passed_0 = millis();
  if ((time_passed_0 - lastmillis) >= 1000){  //Debouncing strategy
   detachInterrupt(D4);    //Disable interrupt when calculating
   if (tipcount > last_tipcount){
    real_tipcount++;
    last_tipcount = tipcount;
    rain = real_tipcount * calibrated_vol*1000/area;  /* Convert tip into mm*/
    connect2wifi_send();
   }
//   Serial.print("Tips: ");
//   Serial.println(rain);
   lastmillis = millis(); // Uptade lasmillis
   attachInterrupt(D4, tip_fan, CHANGE); //enable interrupt
  }
  
  time_passed = millis();
  if ((time_passed - last_time_passed) >= 1800000) {
    ReadDHTSensor_1();
    connect2wifi_send();
    last_time_passed = time_passed;
    return;
  }
}

