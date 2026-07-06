#include "arduino_secrets.h"

#include <Wire.h>
#include <Servo.h>

Servo palacServo;
Servo kaziprstServo;
Servo srednjakServo;
Servo prstenjakServo;
Servo maliprstServo;

int potpinPalac = A0;
int potpinKaziprst = A1;
int potpinSrednjak = A2;
int potpinPrstenjak = A3;
int potpinMaliprst = A4;

int palacMVal;    
int kaziprstMVal;
int srednjakMVal;
int prstenjakMVal;
int maliprstMVal;

int palacDVal;    
int kaziprstDVal;
int srednjakDVal;
int prstenjakDVal;
int maliprstDVal;

volatile bool flag = false;

byte myData[26];

int palacSetter = 1;
int kaziprstSetter = 6;
int srednjakSetter = 11;
int prstenjakSetter =16;
int maliprstSetter = 21;

int buttonState = 1;

int palacValue = 0;
int kaziprstValue = 0;
int srednjakValue = 0;
int prstenjakValue = 0;
int maliprstValue = 0;



void setup(){

  palacServo.attach(53);
  kaziprstServo.attach(51);
  srednjakServo.attach(49);
  prstenjakServo.attach(47);
  maliprstServo.attach(45);
  
  Serial.begin(115200);
  Wire.begin(10);
  Wire.onReceive(receiveEvent);


}

void loop(){

  if(flag == true){

    buttonState = myData[0];

    palacValue = wireDecoder(myData, palacSetter);

    kaziprstValue = wireDecoder(myData, kaziprstSetter);

    srednjakValue = wireDecoder(myData, srednjakSetter);

    prstenjakValue = wireDecoder(myData, prstenjakSetter);

    maliprstValue = wireDecoder(myData, maliprstSetter);
    
    flag = false;

    delay(90);

  }


  if(buttonState==0){

    palacDVal = map(palacValue, 0, 1023, 180, 145);

    kaziprstDVal = map(kaziprstValue, 0, 1023, 180, 145); 

    srednjakDVal = map(srednjakValue, 0, 1023, 175, 141); 

    prstenjakDVal = map(prstenjakValue, 0, 1023, 170, 135); 

    maliprstDVal = map(maliprstValue, 0, 1023, 180, 145); 

    palacServo.write(palacDVal);   
    kaziprstServo.write(kaziprstDVal); 
    srednjakServo.write(srednjakDVal); 
    prstenjakServo.write(prstenjakDVal); 
    maliprstServo.write(maliprstDVal);

  }else{

    palacMVal = analogRead(potpinPalac);
    palacMVal = map(palacMVal, 0, 1023, 180, 145); 

    kaziprstMVal = analogRead(potpinKaziprst);            
    kaziprstMVal = map(kaziprstMVal, 0, 1023, 180, 145); 

    srednjakMVal = analogRead(potpinSrednjak);            
    srednjakMVal = map(srednjakMVal, 0, 1023, 175, 141); 

    prstenjakMVal = analogRead(potpinPrstenjak);            
    prstenjakMVal = map(prstenjakMVal, 0, 1023, 170, 135); 

    maliprstMVal = analogRead(potpinMaliprst);           
    maliprstMVal = map(maliprstMVal, 0, 1023, 180, 145); 

    palacServo.write(palacMVal);   
    kaziprstServo.write(kaziprstMVal); 
    srednjakServo.write(srednjakMVal); 
    prstenjakServo.write(prstenjakMVal); 
    maliprstServo.write(maliprstMVal);

    

  }

  

}

void receiveEvent(int howMany){
  if(howMany==26){
    Serial.println("Podaci proÅ¡li");
    for(int i = 0; i<howMany; i++){

      myData[i] = Wire.read();
      Serial.println(i);
      Serial.println(myData[i]);

    }
  }
  flag = true;
}

int wireDecoder(byte dataList[], int setter){

  int value=0;
  int j = setter;

  while(j < (setter+5)){
    
    value += dataList[j];
  
    j++;

  }

  return value;
}


