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

#define BT_SELECT_1   ( !mcp.digitalRead(MCP_IN11) )
#define BT_START_1    ( !mcp.digitalRead(MCP_IN12) )
#define BT_STOP_1     ( !mcp.digitalRead(MCP_IN13) )

#define BT_SELECT_2   ( !mcp.digitalRead(MCP_IN21) )
#define BT_START_2    ( !mcp.digitalRead(MCP_IN22) )
#define BT_STOP_2     ( !mcp.digitalRead(MCP_IN23) )

#define BT_SELECT_3   ( !mcp.digitalRead(MCP_IN31) )
#define BT_START_3    ( !mcp.digitalRead(MCP_IN32) )
#define BT_STOP_3     ( !mcp.digitalRead(MCP_IN33) )

#define BT_SELECT_4   ( !mcp.digitalRead(MCP_IN41) )
#define BT_START_4    ( !mcp.digitalRead(MCP_IN42) )
#define BT_STOP_4     ( !mcp.digitalRead(MCP_IN43) )


/* DECLARE */
Adafruit_MCP23017 mcp;


/* VARIABLE */
volatile unsigned char coin = 0;
unsigned char pt_sel = 0;
unsigned short temp = 0;
unsigned short tim1 = 0;
unsigned short tim2 = 0;
unsigned short tim3 = 0;
unsigned short tim4 = 0;
unsigned char is_enable1 = 0;
unsigned char is_enable2 = 0;
unsigned char is_enable3 = 0;
unsigned char is_enable4 = 0;


void setup() {
		Serial.begin(9600);
		setupMAX7219();
		setupIOEx();
		setupTimer();
		setupExtInterrupt();

		/* Initial State */
		printSeg(1, 0);
		printSeg(2, 0);
		printSeg(3, 0);
		printSeg(4, 0);
} 


void loop() {
	// printSeg(1, (BT_SELECT_1) | (BT_START_1<<1) | (BT_STOP_1<<2) );
	Serial.println(pt_sel);
	// Serial.println((BT_SELECT_2) | (BT_START_2<<1) | (BT_STOP_2<<2));
	/* SELECT BUTTON */
	if (BT_SELECT_1) {
		while(BT_SELECT_1);
		pt_sel = 1;
	}
	else if (BT_SELECT_2) {
		while(BT_SELECT_2);
		pt_sel = 2;
	}
	else if (BT_SELECT_3) {
		while(BT_SELECT_3);
		pt_sel = 3;
	}
	else if (BT_SELECT_4) {
		while(BT_SELECT_4);
		pt_sel = 4;
	}
	switch (pt_sel) {
		case 1:
		temp = coin2Timer(coin);
		printSeg(1, temp);
		if BT_START_1{
			tim1 = temp;
			is_enable1 = 1;
			pt_sel = 0;
		}
		else if BT_STOP_1{
			pt_sel = 0;
		}
		break;

		// case 2:
		// temp = coin2Timer(coin);
		// printSeg(2, temp);
		// if BT_START_2{
		// 	tim2 = temp;
		// 	is_enable2 = 1;
		// 	pt_sel = 0;
		// }
		// else if BT_STOP_2{
		// 	pt_sel = 0;
		// }
		// break; 

	}


	/* DISPLAY */
	if (tim1 != 0){
		printSeg(1, tim1);
	}
	if (tim2 != 0){
		printSeg(2, tim2);
	}
	if (tim3 != 0){
		printSeg(3, tim3);
	}	
	if (tim4 != 0){
		printSeg(4, tim4);
	}	

	/* PAUSE BUTTON*/
	if BT_START_1{
		while(BT_START_1);
		is_enable1 = !is_enable1;
	}
	
	// if BT_START_2{
	// 	while(BT_START_2);
	// 	is_enable2 != is_enable2;
	// }

	// if BT_START_3{
	// 	while(BT_START_3);
	// 	is_enable3 != is_enable3;
	// }

	// if BT_START_4{
	// 	while(BT_START_4);
	// 	is_enable4 != is_enable4;
	// }


	// /* STOP BUTTON */
	// if BT_STOP_1{
	// 	while(BT_STOP_1);
	// 	is_enable1 = 0;
	// 	tim1 = 0;
	// }

	// if BT_STOP_2{
	// 	while(BT_STOP_2);
	// 	is_enable2 = 0;
	// 	tim2 = 0;
	// }


	// /* Energizing */
	// if ((tim1 != 0) && (is_enable1 = 1)){
	// 	mcp.digitalWrite(MCP_OUT01, HIGH);
	// }else{
	// 	mcp.digitalWrite(MCP_OUT01, LOW);
	// }

	// if ((tim2 != 0) && (is_enable2 = 1)){
	// 	mcp.digitalWrite(MCP_OUT02, HIGH);
	// }else{
	// 	mcp.digitalWrite(MCP_OUT02, LOW);
	// }



}

/* FUNCTION **************************************************/
/*
 * @brief: Coin to seconds.
 */
unsigned short coin2Timer(unsigned char coin){
	return coin*120;
}

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
	if ((tim1 > 0) && (is_enable1==1)){
		tim1--;
	}
	if (tim2 > 0){
		tim2--;
	}
	if (tim3 > 0){
		tim3--;
	}
	if (tim4 > 0){
		tim4--;
	}
}


void callbackExtInput(){
	coin=10;
}

