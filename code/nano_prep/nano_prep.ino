/* INCLUDE */
#include "sudosx_MAX7219.h"
#include "Adafruit_MCP23017.h"


/* DEFINE */
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
    setupMAX7219();
//    setupIOEx();

    printSeg(1, 1);
    printSeg(2, 2);
    printSeg(3, 3);
    printSeg(4, 4);
} 


void loop() {
  _delay_ms(200);
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

