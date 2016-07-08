/* SECTION: DEFINE -------------------------- */
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

#define BT_SELECT_1   mcp.digitalRead(MCP_IN11)
#define BT_START_1    mcp.digitalRead(MCP_IN12)
#define BT_STOP_1     mcp.digitalRead(MCP_IN13)

#define BT_SELECT_2   mcp.digitalRead(MCP_IN21)
#define BT_START_2    mcp.digitalRead(MCP_IN22)
#define BT_STOP_2     mcp.digitalRead(MCP_IN23)

#define BT_SELECT_3   mcp.digitalRead(MCP_IN31)
#define BT_START_3    mcp.digitalRead(MCP_IN32)
#define BT_STOP_3     mcp.digitalRead(MCP_IN33)

#define BT_SELECT_4   mcp.digitalRead(MCP_IN41)
#define BT_START_4    mcp.digitalRead(MCP_IN42)
#define BT_STOP_4     mcp.digitalRead(MCP_IN43)

/* SECTION: VARIBLE ------------------------- */
unsigned char coin = 0;
unsigned char select = 0;
unsigned char timer1 = 0;
unsigned char timer2 = 0;
unsigned char timer3 = 0;
unsigned char timer4 = 0;
unsigned char timeout = 0;

unsigned char is_enable1 =0;
unsigned char is_enable2 =0;
unsigned char is_enable3 =0;
unsigned char is_enable4 =0; 

/* SECTION: MAIN ---------------------------- */
while (1){
	/* SELECT BUTTON */
	if (BT_SELECT_1){
		while(BT_SELECT_1);
		coin = 0;
		select = 1;
		// while(1){
		// 	// Print 7 Segment

		// 	if (BT_START_1){
		// 		while(BT_START_1);
		// 		timer1 = coin2Timer(coin);
		// 		is_enable1 = 1;
		// 		break;
		// 	}
		// 	if ( (BT_STOP_1)&&(timeout) ){
		// 		break;
		// 	}
		// }
	}
	if (BT_SELECT_2){
		while(BT_SELECT_2);

		// coin = 0;
		// while(1){
		// 	if (BT_START_2){
		// 		while(BT_START_2);
		// 		timer2 = coin2Timer(coin);
		// 		is_enable2 = 1;
		// 		break;
		// 	}
		// 	if ( (BT_STOP_2)&&(timeout) ){
		// 		break;
		// 	}
		// }
	}

	/* Selection */
	if (select != 0){
		// Print current coin
	}

	switch (select){
		case 1: 
		if BT_START_1{
			timer1 = coin2Timer(coin);
			is_enable1 = 1;
		}
		if BT_STOP_1 && (timeout == 0){
			select = 0;
		}
	}

	/* PAUSE BUTTON*/
	if BT_START_1{
		while(BT_START_1);
		is_enable1 != is_enable1;
	}
	if BT_START_2{
		while(BT_START_2);
		is_enable2 != is_enable2;
	}


	/* STOP BUTTON */
	if BT_STOP_1{
		while(BT_STOP_1);
		is_enable1 = 0;
		timer1 = 0;
	}
	if BT_STOP_2{
		while(BT_STOP_2);
		is_enable2 = 0;
		timer2 = 0;
	}

	/* Print */

	/* Energization */
	if (timer1 != 0) && (is_enable1 = 1){
		mcp.digitalWrite(MCP_OUT01, HIGH);
	}else{
		mcp.digitalWrite(MCP_OUT01, LOW);
	}
	if (timer2 != 0) && (is_enable2 = 1){
		mcp.digitalWrite(MCP_OUT02, HIGH);
	}else{
		mcp.digitalWrite(MCP_OUT02, LOW);
	}


}


/* SECTION: FUNCTION ------------------------ */
void ISR_Timer(){
	if (timer1 > 0) && (is_enable1 = 1){
		timer1--;
	}
	if (timer2 > 0) && (is_enable2 = 1){
		timer2--;
	}
	if (timeout > 0){
		timeout--;
	}
}

unsigned char coin2Timer(unsigned char coin){

}
