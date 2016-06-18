/* INCLUDE */
#include <SPI.h>
#include "Adafruit_MCP23017.h"


/* DEFINE */
#define PIN_SS1       10
#define PIN_SS2       9

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


void setup() {
    initMAX7219();
    setupIOEx();
} 


void loop() {

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

/*
 * @brief: Initial IC MAX7219 (7 Segment driver)
 */
void initMAX7219(){
  SPI.begin();
  pinMode(PIN_SS1, OUTPUT);
  pinMode(PIN_SS2, OUTPUT);
  
  /* Enable Testing Mode */
  spiSend (PIN_SS1, 0xF, 0x1);
  spiSend (PIN_SS2, 0xF, 0x1);
  _delay_ms(250);
  /* Disable Testing Mode */
  spiSend (PIN_SS1, 0xF,0x0);
  spiSend (PIN_SS2, 0xF,0x0);
  /* Go normal operation */
  spiSend (PIN_SS1, 0xC,0x1);
  spiSend (PIN_SS2, 0xC,0x1);
  /* Set Scan Limit */
  spiSend (PIN_SS1, 0xB,0x7);
  spiSend (PIN_SS2, 0xB,0x7);
  /* Decode mode that you shall be send the number charecter. */
  spiSend (PIN_SS1, 0x9,0xFF);
  spiSend (PIN_SS2, 0x9,0xFF);
  /* Set Intensity */
  spiSend (PIN_SS1, 0xA, 0x6);
  spiSend (PIN_SS2, 0xA, 0x6);

}


/*
 * @brief: Send data via SPI (Serial Peripheral Interface).
 */
void spiSend(uint8_t pin_ss, uint8_t command, unsigned short value)
{
  digitalWrite(pin_ss, LOW); //chip select is active low
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(pin_ss,HIGH);
}


/*
 * @brief: Print 7 Segment, support four 4DIGIT.
 */
void printSeg(uint8_t seg_no, unsigned short num){
    for (int8_t i=0; i <= 3; i++)
    {
        byte character = num % 10; //get the value of the rightmost digit
        if (num == 0 && i > 0)
        character = 0xf;
        switch(seg_no){
            case 0: spiSend(PIN_SS1, 4-i, character);
            break;
            case 1: spiSend(PIN_SS1, 8-i, character);
            break;
            case 2: spiSend(PIN_SS2, 4-i, character);
            break;
            case 3: spiSend(PIN_SS2, 8-i, character);
            break;
        }
      num = num/10;
    }
}

//void test7seg(unsigned short *i){
//    printSeg(0, *i);
//    printSeg(1, 9999-*i);
//    _delay_ms(100);
//    *i++;
//    if (*i > 9999){
//      *i=0;
//    }
//}

//void testIO(){
////  mcp.digitalWrite(MCP_OUT01, HIGH);
////  _delay_ms(200);
////  mcp.digitalWrite(MCP_OUT01, LOW);
////  _delay_ms(200);   
////    tmp = mcp.digitalRead(MCP_IN23);
////  tmp = mcp.readGPIOAB();
////  Serial.println( mcp.digitalRead(MCP_IN23) );
//  tmp = mcp.readGPIOAB() & 0x0FFF ;
//  Serial.println(tmp);
//  
//}




