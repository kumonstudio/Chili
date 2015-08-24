

// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// mp3 includes
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>

// mp3 variables
SFEMP3Shield MP3player;
byte result;
int lastPlayed = 0;

// touch behaviour definitions
//#define firstPin 0
//#define lastPin 11

#define x1 10
#define x2 12
#define w1 13
#define w2 13
// sd card instantiation
SdFat sd;

// define LED_BUILTIN for older versions of Arduino
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

int coco = 0;
int how = 0;
int wei = 0;
int shin = 0;
int kk = 0;
int stx = 0;
int st2 = 0;

void setup(){ 
  
  Serial.begin(57600);
  
  pinMode(w1, OUTPUT);
  pinMode(w2, OUTPUT);
  pinMode(x1, OUTPUT);
  pinMode(x2, OUTPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
   
  //while (!Serial) ; {} //uncomment when using the serial monitor 
  Serial.println("Bare Conductive Touch MP3 player");

  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  result = MP3player.begin();
  MP3player.setVolume(10,10);
 
  if(result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
   }
   
   
   digitalWrite(w1, LOW);
   digitalWrite(w2, LOW);
   digitalWrite(x1, LOW);
   digitalWrite(x2, HIGH);
   
   
   
}

void loop(){
  readTouchInputs();
  actionx();
}

void readTouchInputs(){
    
    MPR121.updateTouchData();

    // only make an action if we have one or fewer pins touched
    // ignore multiple touches
    
    if(MPR121.getNumTouches()<=1){
        if(MPR121.isNewTouch(3)){
          
          digitalWrite(LED_BUILTIN, HIGH);
          digitalWrite(w1, HIGH);
          digitalWrite(w2, HIGH);
            
            
            wei = millis();
            how = wei-coco;
            coco = wei;

            shin = map(how, 10, 2200, 0, 9);
            shin = int(constrain(shin, 0, 9));
            
            
            //shin = 0;
            if(shin==0 && stx==0){
              stx = 1;
              kk = 0;
            }
            
            
            
           
            if(!MP3player.isPlaying()){
              MP3player.stopTrack();
              MP3player.playTrack(shin);
             // wei = millis();
              //coco = wei;
              
            }
  
     
        } else {
          if(MPR121.isNewRelease(3)){
            digitalWrite(LED_BUILTIN, LOW);
            digitalWrite(w1, LOW);
            digitalWrite(w2, LOW);
           } 
        
        
        
        }
        
        
     } else {
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(w1, LOW);
      digitalWrite(w2, LOW);
    
    }
    
    

}


void actionx(){

  //Serial.println(kk);
  if(stx == 1){
    
    
 
      digitalWrite(x1, HIGH);  
      digitalWrite(x2, HIGH);
      delay(1000);
    
      digitalWrite(x1, LOW);  
      digitalWrite(x2, LOW);
      delay(1000);
   
      digitalWrite(x1, LOW);  
      digitalWrite(x2, HIGH);
      delay(1000);
      stx = 0;
    
    
    /*    
    kk++;
    if(kk<1000){
      digitalWrite(x1, HIGH);  
      digitalWrite(x2, HIGH);
      
    } else if(kk>=1000 && kk<2000){
      digitalWrite(x1, LOW);  
      digitalWrite(x2, LOW);
    
    } else if(kk>=2000 && kk<2002){
      digitalWrite(x1, LOW);  
      digitalWrite(x2, HIGH);
    
    } else {
      stx = 0;
    }
    */


  }
  

  
}


