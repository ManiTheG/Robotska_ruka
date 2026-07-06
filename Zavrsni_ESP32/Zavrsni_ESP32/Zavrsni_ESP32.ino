#include "arduino_secrets.h"


#define BLYNK_TEMPLATE_ID           "TMPL42dGweFsR"
#define BLYNK_TEMPLATE_NAME         "ZavrÅ¡ni rad"
#define BLYNK_AUTH_TOKEN            "P0y11ZxOKy-MwtocqxmNioJhITuyu2Lu"

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Mani";
char pass[] = "12345678";

int buttonValue = 0;
int palacValue = 0;
int kaziprstValue = 0;
int srednjakValue = 0;
int prstenjakValue = 0;
int maliprstValue = 0;

byte palacList[5];
byte kaziprstList[5];
byte srednjakList[5];
byte prstenjakList[5];
byte maliprstList[5];

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);  // will cause BLYNK_WRITE(V0) to be executed
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);
  Blynk.syncVirtual(V5);
}


// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V0)
{
  buttonValue = param.asInt();
}

BLYNK_WRITE(V1)
{
  palacValue = param.asInt();
}

BLYNK_WRITE(V2){
  kaziprstValue = param.asInt();
}

BLYNK_WRITE(V3){
  srednjakValue = param.asInt();
}

BLYNK_WRITE(V4){
  prstenjakValue = param.asInt();
}

BLYNK_WRITE(V5){
  maliprstValue = param.asInt();
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Wire.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


}

void loop()
{
  Blynk.run();

  convertData(palacValue, palacList);
  convertData(kaziprstValue, kaziprstList);
  convertData(srednjakValue, srednjakList);
  convertData(prstenjakValue, prstenjakList);
  convertData(maliprstValue, maliprstList);



  Wire.beginTransmission(10);

  Wire.write(buttonValue);

  for(int i = 0; i < 5 ; i++ ){
    Wire.write(palacList[i]);
  }

  for(int i = 0; i < 5 ; i++ ){
    Wire.write(kaziprstList[i]);
  }

  for(int i = 0; i < 5 ; i++ ){
    Wire.write(srednjakList[i]);
  }

  for(int i = 0; i < 5 ; i++ ){
    Wire.write(prstenjakList[i]);
  }

  for(int i = 0; i < 5 ; i++ ){
    Wire.write(maliprstList[i]);
  }

  Wire.endTransmission();
  delay(1000);  //test interval

}

void convertData(int value, byte data[]){
  for(int i = 0; i<5; i++){

    if((value-255)>=0){
      data[i]=255;
      value-=255;
    }
    else{
      data[i]=value;
      value=0;
    }
  }

}


