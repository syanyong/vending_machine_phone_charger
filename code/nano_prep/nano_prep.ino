/* INCLUDE */
#include "sudosx_MAX7219.h"
#include "TimerOne.h"
#include "Adafruit_MCP23017.h"


/* DEFINE */
#define PIN_PWN       3

#define MCP_IN11      0
#define MCP_IN12      1
#define MCP_IN13      2

#define MCP_IN21      3
#define MCP_IN22      4
#define MCP_IN23      5

#define MCP_IN31      6
#define MCP_IN32      7
#define MCP_IN33      8

#define MCP_IN41      9
#define MCP_IN42      10
#define MCP_IN43      11

#define MCP_OUT01     12
#define MCP_OUT02     13
#define MCP_OUT03     14
#define MCP_OUT04     15

/* DECLARE */
Adafruit_MCP23017 mcp;

/* VARIABLE */
volatile unsigned char coin = 0;
unsigned short tim1 = 0;
unsigned short tim2 = 0;
unsigned short tim3 = 0;
unsigned short tim4 = 0;

void setup() {
    setupMAX7219();
    setupIOEx();
    setupTimer();
    setupExtInterrupt();

    /* Initial State */
    tim1 = 3600;
    tim2 = 1800;
    printSeg(1, 0);
    printSeg(2, 0);
    printSeg(3, 0);
    printSeg(4, 0);
} 


void loop() {
  printSeg(1, tim1);
  printSeg(2, tim1/60);
  printSeg(3, tim2/60);
  printSeg(4, tim2);
  _delay_ms(100);
}

/* FUNCTION **************************************************/
void setupIOEx(){
  mcp.begin(); 
  
  /* Input */
  mcp.pinMode(MCP_IN11, INPUT); 
  mcp.pullUp(MCP_IN11, HIGH);
  mcp.pinMode(MCP_IN12, INPUT); 
  mcp.pullUp(MCP_IN12, HIGH);
  mcp.pinMode(MCP_IN13, INPUT); 
  mcp.pullUp(MCP_IN13, HIGH);

  mcp.pinMode(MCP_IN21, INPUT); 
  mcp.pullUp(MCP_IN21, HIGH);
  mcp.pinMode(MCP_IN22, INPUT); 
  mcp.pullUp(MCP_IN22, HIGH);
  mcp.pinMode(MCP_IN23, INPUT); 
  mcp.pullUp(MCP_IN23, HIGH);
  
  mcp.pinMode(MCP_IN31, INPUT); 
  mcp.pullUp(MCP_IN31, HIGH);
  mcp.pinMode(MCP_IN32, INPUT); 
  mcp.pullUp(MCP_IN32, HIGH);
  mcp.pinMode(MCP_IN33, INPUT); 
  mcp.pullUp(MCP_IN33, HIGH);

  mcp.pinMode(MCP_IN41, INPUT); 
  mcp.pullUp(MCP_IN41, HIGH);
  mcp.pinMode(MCP_IN42, INPUT); 
  mcp.pullUp(MCP_IN42, HIGH);
  mcp.pinMode(MCP_IN43, INPUT); 
  mcp.pullUp(MCP_IN43, HIGH);
  
  /* Output */
  mcp.pinMode(MCP_OUT01, OUTPUT);
  mcp.pinMode(MCP_OUT02, OUTPUT);
  mcp.pinMode(MCP_OUT03, OUTPUT);
  mcp.pinMode(MCP_OUT04, OUTPUT);

  mcp.digitalWrite(MCP_OUT01, LOW);
  mcp.digitalWrite(MCP_OUT02, LOW);
  mcp.digitalWrite(MCP_OUT03, LOW);
  mcp.digitalWrite(MCP_OUT04, LOW);
}

void setupTimer(){
  Timer1.initialize(1000000);       // 1 Second
  Timer1.attachInterrupt(callback); // Attaches callback() as a timer overflow interrupt
}


void setupExtInterrupt(){
  attachInterrupt(digitalPinToInterrupt(PIN_PWN), callbackExtInput, RISING);
}


void callback()
{
  if (tim1 > 0){
    tim1--;
  }
  if (tim2 > 0){
    tim2--;
  }
}


void callbackExtInput(){
  coin++;
}