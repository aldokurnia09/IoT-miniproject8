#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

// Define Text
#define FIREBASE_HOST "https://firebase-anda.firebaseio.com/"
#define FIREBASE_AUTH "Secret Code Firebase"
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

// Define Interface
FirebaseData firebaseData;
String path = "/Node1";
int Led = 12 ; //LED on pin D6
int Sound = 16; //Sound Sensor on pin D0
int Water = A0; //Water Level Sensor on pin A0

void setup ()
{
  // Begin
  Serial.begin(9600);
  delay(3000);
  
  // Connecting to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //Connect to Wifi
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!"); //Connected to Wifi

  // Connecting to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //Connect to Firebase

  // Define Mode
  pinMode(Led, OUTPUT);
  pinMode(Sound, INPUT);
  pinMode(Water, INPUT);
}
void loop ()
{
  // Sound Sensor
  Firebase.getInt(firebaseData, path + "/sound"); //get sound value from firebase
  int val = digitalRead(Sound); //read sound sensor value
  Serial.print("Sound : ");
  Serial.println(firebaseData.intData()); //print the sound value to serial
  if(val == 1){
    Firebase.setInt(firebaseData, path + "/sound", 1); //send sound value to firebase
    Firebase.setInt(firebaseData, path + "/lamp1", 1); //send lamp value to firebase
    digitalWrite(Led, HIGH);
  }
  else if(val==0){
    Firebase.setInt(firebaseData, path + "/sound", 0); //send sound value to firebase
    Firebase.setInt(firebaseData, path + "/lamp1", 0); //send lamp value to firebase
    digitalWrite(Led, LOW);
  }
  
  // Water Sensor
  int val2 = analogRead(Water); //read water level sensor value
  Serial.print("Water : ");
  Serial.println(val2); //print the water value to serial
  Firebase.setInt(firebaseData, path + "/water", val2); //send water value to firebase

  // Delay
  delay(500);
}
