/* INCLUDE */
#include "SYLib_MAX7219.h"
#include "Adafruit_MCP23017.h"
#include "TimerOne.h"
// #include "stdio.h" // Debugging


/* DEFINE */
#define PIN_PWN       2

#define SEG1	1
#define SEG2	3
#define SEG3	2
#define SEG4	4

#define BT_SEL1    0
#define BT_STR1    1
#define BT_STP1    2

#define BT_SEL2    3
#define BT_STR2    4
#define BT_STP2    5

#define BT_SEL3    6
#define BT_STR3    7
#define BT_STP3    8

#define BT_SEL4    9
#define BT_STR4    10
#define BT_STP4    11

/* DECLARE */
Adafruit_MCP23017 mcp;


/* VARIABLE */
uint8_t coin = 0;
uint8_t pt_sel = 0;
uint8_t blink_togg = 0;
uint16_t temp = 0;
char _pt[20];

uint8_t io_now[12];
uint8_t io_prv[12];
uint16_t disp[4];

uint8_t tim1 = 0;
uint8_t tim2 = 0;
uint8_t tim3 = 0;
uint8_t tim4 = 0;

uint8_t is_ena1 = 0;
uint8_t is_ena2 = 0;
uint8_t is_ena3 = 0;
uint8_t is_ena4 = 0;


/* MAIN **************************************************/
void setup() {
		_delay_ms(1000);
		Serial.begin(9600);
		Serial.println("Hello World");

		setupMAX7219();
		setupIOExpander();
		setupIntTimer();
		setupIntExt();

} 

void loop() {
	getBTRel(mcp.readGPIOAB(), io_prv, io_now);
	printSeg(SEG1, disp[0]);
	printSeg(SEG2, disp[1]);
	printSeg(SEG3, disp[2]);
	printSeg(SEG4, disp[3]);
	// _printArr(io_now);
	
	/* PAUSE */
	// if (io_now[BT_STR1]){
	// 	is_ena1 = !is_ena1;
	// }
	// if (io_now[BT_STR2]){
	// 	is_ena2 = !is_ena2;
	// }
	// if (io_now[BT_STR3]){
	// 	is_ena3 = !is_ena3;
	// }
	// if (io_now[BT_STR4]){
	// 	is_ena4 = !is_ena4;
	// }

	 // TASK1: SELECTION 
	if (io_now[BT_SEL1]) {
		pt_sel = 1;
	}
	else if (io_now[BT_SEL2]) {
		pt_sel = 2;
	}
	else if (io_now[BT_SEL3]) {
		pt_sel = 3;
	}
	else if (io_now[BT_SEL4]) {
		pt_sel = 4;
	}
	if (pt_sel == 1) {
		selectingScreen(SEG1, coin, &blink_togg);

		if (io_now[BT_STR1] == 1){
			tim1 = coin2Timer(coin);
			coin = 0;
			is_ena1 = 1;
			pt_sel = 0;
		}
	}
	else if(pt_sel == 2){
		selectingScreen(SEG2, coin, &blink_togg);

		if (io_now[BT_STR2] == 1){
			tim2 = coin2Timer(coin);
			coin = 0;
			is_ena2 = 1;
			pt_sel = 0;
		}
	}
	else if(pt_sel == 3){
		selectingScreen(SEG3, coin, &blink_togg);

		if (io_now[BT_STR3] == 1){
			tim3 = coin2Timer(coin);
			coin = 0;
			is_ena3 = 1;
			pt_sel = 0;
		}
	}	
	else if(pt_sel == 4){
		selectingScreen(SEG4, coin, &blink_togg);

		if (io_now[BT_STR4] == 1){
			tim4 = coin2Timer(coin);
			coin = 0;
			is_ena4 = 1;
			pt_sel = 0;
		}	
	}
	else{

	}


	/* STOP BUTTON */
	if (io_now[BT_STP1]){
		is_ena1 = 0;
		disp[0] = 0;
		tim1 = 0;
	}
	if (io_now[BT_STP2]){
		is_ena2 = 0;
		disp[1] = 0;
		tim2 = 0;
	}
	if (io_now[BT_STP3]){
		is_ena3 = 0;
		disp[2] = 0;
		tim3 = 0;
	}
	if (io_now[BT_STP4]){
		is_ena4 = 0;
		disp[4] = 0;
		tim4 = 0;
	}

	/* DISPLAY */
	if (is_ena1 != 0){
		disp[0] = tim1;
	}
	if (is_ena2 != 0){
		disp[1] = tim2;
	}
	if (is_ena3 != 0){
		disp[2] = tim3;
	}
	if (is_ena4 != 0){
		disp[3] = tim4;
	}


	if (tim1 == 0){
		is_ena1 = 0;
	}
	if (tim2 == 0){
		is_ena2 = 0;
	}
	if (tim3 == 0){
		is_ena3 = 0;
	}
	if (tim4 == 0){
		is_ena4 = 0;
	}

}
/* FUNCTION **********************************************/
void selectingScreen(uint8_t seg, uint8_t data, uint8_t* blink_state){
	if (*(blink_state)){
		printSeg(seg, data);
	}else{
		printSegChar(seg, 3, 0xA);
	}
	_delay_ms(20);
	*(blink_state) = !*(blink_state);

	// Overide disp[]
	disp[seg-1] = data;
}

void _printArr(unsigned char *arr){
	Serial.print("<");
	for (unsigned char i = 0 ; i < 12 ; i++){
		sprintf(_pt, "%d, ", *(arr+i));
		Serial.print(_pt);
	}
	Serial.print(">\n");
}

/*
 *	@brief: 
 */
void getBTRel(unsigned int io_in, uint8_t* io_prv, uint8_t* io_now){
	uint8_t ion;
	for (uint8_t i = 0 ; i < 12 ; i++) {
			ion = !( (io_in >> i) & 0x1); //Active Low
			*(io_now+i) = ion;
			// if ( (*(io_prv+i) == 1) && (ion == 0) ){
			// 	*(io_now+i) = 1;
			// } else{
			// 	*(io_now+i) = 0;
			// }
			*(io_prv+i) = ion;
 	}
}

void test7Seg(uint16_t* ts){
	printSeg(SEG1, *ts);
	printSeg(SEG2, *ts + 1);
	printSeg(SEG3, *ts + 2);
	printSeg(SEG4, *ts + 3);
	*ts = *ts +1;
	if (*ts >= 9990){
		*ts = 0;
	}
}

void testBT(){
	if (io_now[BT_SEL1]){
		printSeg(SEG1, 1);
	}
	else if (io_now[BT_STR1]){
		printSeg(SEG1, 2);
	}
	else if (io_now[BT_STP1]){
		printSeg(SEG1, 3);
	}

	if (io_now[BT_SEL2]){
		printSeg(SEG2, 1);
	}
	else if (io_now[BT_STR2]){
		printSeg(SEG2, 2);
	}
	else if (io_now[BT_STP2]){
		printSeg(SEG2, 3);
	}

	if (io_now[BT_SEL3]){
		printSeg(SEG3, 1);
	}
	else if (io_now[BT_STR3]){
		printSeg(SEG3, 2);
	}
	else if (io_now[BT_STP3]){
		printSeg(SEG3, 3);
	}

	if (io_now[BT_SEL4]){
		printSeg(SEG4, 1);
	}
	else if (io_now[BT_STR4]){
		printSeg(SEG4, 2);
	}
	else if (io_now[BT_STP4]){
		printSeg(SEG4, 3);
	}

}

/*
 * @brief: Coin to seconds.
 */
unsigned short coin2Timer(unsigned char coin){
	return coin*10;
}


void setupIOExpander(){
	mcp.begin();

	/*Input*/
	for (unsigned char i = 0; i <= 11; i++){
		mcp.pinMode(i, INPUT); 
		mcp.pullUp(i, HIGH);
	}
	/* Output */
	for (unsigned char i = 12; i <= 15; i++){
		mcp.pinMode(i, OUTPUT);
		mcp.digitalWrite(i, LOW);
	}
}


void setupIntTimer(){
	Timer1.initialize(1000000);       // 1 Second
	Timer1.attachInterrupt(ISRCallback); // Attaches ISRCallback() as a timer overflow interrupt
}


void setupIntExt(){
	pinMode(PIN_PWN, INPUT);
	attachInterrupt(digitalPinToInterrupt(PIN_PWN), ISRCallbackExtInput, FALLING);
}


void ISRCallback()
{
	/* 1 sec */
	// if (tim_min++ > 10){
		if ((tim1 > 0) && (is_ena1==1)){
			tim1--;
		}
		if ((tim2 > 0) && (is_ena2==1)){
			tim2--;
		}
		if ((tim3 > 0) && (is_ena3==1)){
			tim3--;
		}
		if ((tim4 > 0) && (is_ena4==1)){
			tim4--;
		}
	// 	tim_min = 0;
	// }
}


void ISRCallbackExtInput(){
	coin++;
}

