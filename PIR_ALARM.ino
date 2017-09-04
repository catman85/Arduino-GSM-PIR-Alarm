///---Impotant Notes---///
/*we have two LEDs in use. One lights up
when we connect to the GSM network ("connLed") and the other one when the 
PIR sensor detects an intruder("alarmLed")*/

/*pirPin is the output of the PIR sensor
timeToCall is the time to call the users phone number
(the user is not supposed to answer this call).*/


/* YOUR_NUMBER is were you put your phone number with the international calling code in the front
https://en.wikipedia.org/wiki/List_of_mobile_phone_number_series_by_country */

/*Library used: 
https://github.com/MarcoMartines/GSM-GPRS-GPS-Shield
all the contents of this repositiry must be within a folder inside: "sketchbook/libraries/".*/

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"


char num[]="YOUR_NUMBER";
CallGSM call;


int connLed = 13;
int alarmLed = 12;
int pirPin = 6;
/*I had some issues when using the digital pins 0123 in the TinyShine GSM shield for
the PIR output. (The GSM module refused to connect to the network). Thus, Interrupts were not
implemented.*/

int val = 0;
int timeToCall = 7000;
boolean alarm=false;



void setup(){
  
    Serial.begin(9600);
    pinMode(connLed,OUTPUT);
    pinMode(alarmLed,OUTPUT);
    pinMode(pirPin, INPUT);
    
    if (gsm.begin(9600)) {
        Serial.println("\nstatus=READY");
        Serial.print("Going to call: ");
        Serial.println(num);
        blink(5);
    } 
    else{ 
        Serial.println("\nstatus=IDLE");
    }   
    
    

}

void loop(){
  val = digitalRead(pirPin);
  Serial.println(val);
  onChange();
}

void onChange(){
  if (val == 1){
    digitalWrite(alarmLed,HIGH);
    delay(1000);
    callNum();
  }else{
    digitalWrite(alarmLed,LOW);
    hangUp();
  }
}  


void callNum(){
  if(call.CallStatus() == CALL_NONE){
    Serial.println("Calling...");
    call.Call(num);
    delay(timeToCall);
  }
}
 
void hangUp(){
     Serial.println("Hanging up");
     call.HangUp();
    
}

//blink function
void blink(int rep){//blinks LEDS
  //blink yellow
     for(int i=0;i<rep;i++){
          digitalWrite(connLed, HIGH);
          delay(100);
          digitalWrite(connLed, LOW);
          delay(100);
     }
}

