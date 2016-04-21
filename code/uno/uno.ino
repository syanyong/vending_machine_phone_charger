// Brief: Vending Machine
// Platform: Arduino UNO
// Author: Sarucha Yanyong
#include "TimerOne.h"

// Define ------------------------------------------------- //
#define PIN_LED       13    // Built-in LED Pin
#define PIN_DATAIN    3
#define PIN_BT_START  4
#define PIN_BT_PAUSE  5
#define PIN_BT_STOP   6
#define PIN_OUT       13 // Relay = 7
#define BT_START      !digitalRead(PIN_BT_START)
#define BT_PAUSE      !digitalRead(PIN_BT_PAUSE)
#define BT_STOP       !digitalRead(PIN_BT_STOP)

// Variables -------------------------------------------- //
unsigned int targetSec = 0;
unsigned short pauseButtonFlag = 1;
volatile unsigned int coin = 0;
volatile unsigned int secCount = 0;
char buffer[20];

// Function --------------------------------------------- //
/* 
 *  @brief: Table for convert Coin to Second.
 */
int coin2Sec(int coin){
  return coin*2;
}

// MAIN ------------------------------------------------- //
void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_OUT, OUTPUT);
  pinMode(PIN_BT_START, INPUT);
  pinMode(PIN_BT_PAUSE, INPUT);
  pinMode(PIN_BT_STOP, INPUT);

  Timer1.initialize(1000000);       // 1 Second
  Timer1.attachInterrupt(callback); // A ttaches callback() as a timer overflow interrupt

  attachInterrupt(digitalPinToInterrupt(PIN_DATAIN), callbackExtInput, RISING);
}

void loop() {
  coin = 0;
  // Getting Coin
  Serial.println("READY");
  do{
    sprintf(buffer, "COIN %d\n", coin);
    Serial.write(buffer);
    if  (BT_STOP){
      coin = 0;
    }
  }while(!BT_START);
  sprintf(buffer, "GET COIN %d\n", coin);
  Serial.write(buffer);

  // Prepare
  targetSec = coin2Sec(coin);
  sprintf(buffer, "TARGET SEC %d\n", targetSec);
  Serial.write(buffer);
  
  // Countingdown
  secCount = 0;
  while( (!BT_STOP) && (targetSec != 0) ){
    sprintf(buffer, "COUNTING %d\n", secCount);
    Serial.write(buffer);

    // Drive Output as High
    if (!pauseButtonFlag) {
      digitalWrite(PIN_OUT, LOW);
    }else{
      digitalWrite(PIN_OUT, HIGH);
    }
    
    if (BT_PAUSE) {             // Pause
      while(BT_PAUSE);          // Wait for release.
      Serial.println("PAUSE");
      Serial.println(pauseButtonFlag);
      if (pauseButtonFlag) {
        Timer1.stop();
      }else{
        Timer1.resume();
      }
      pauseButtonFlag = !pauseButtonFlag;
    }

    if (secCount > targetSec){  // Timeout
      Serial.println("Timeout");
      break;
    }
    
  }
  // Drive Output as High
  digitalWrite(PIN_OUT, LOW);
  Serial.println("EXIT");
}

// Callback function
void callback()
{
  secCount++;
}

void callbackExtInput(){
  coin++;
}

