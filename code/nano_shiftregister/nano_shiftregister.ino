#define DATA    5
#define CLOCK   6
#define LATCH   7
#define ENABLE  8
#define LED     13

int toggle = 0;
int tmp = 0x01;

void shift_out(uint8_t data) {
    for(uint8_t i = 0; i < 8; i++) {
        /* Write bit to data port. */
        if (0 == (data & _BV(7 - i))) {
            digitalWrite(DATA, HIGH);
        } else {
            digitalWrite(DATA, LOW);
        }

        /* Pulse clock input to write next bit. */
        digitalWrite(CLOCK, HIGH);
        digitalWrite(CLOCK, LOW);
    }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LATCH, LOW);
  for(uint8_t i = 0; i < 8; i++) {
    if ( i == 6){
      digitalWrite(DATA, HIGH);
    }else{
      digitalWrite(DATA, LOW);
    }
    
    digitalWrite(CLOCK, LOW);
    digitalWrite(CLOCK, HIGH);
  }
  digitalWrite(LATCH, HIGH);
  if (toggle){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
  toggle = !toggle;
  _delay_ms(500);
//  digitalWrite(LED, LOW);
  
//  d
//  digitalWrite(DATA, LOW);
//  digitalWrite(CLOCK, LOW);
//  digitalWrite(LATCH, LOW);
//  _delay_ms(50);
//  digitalWrite(LED, HIGH);
////  for(uint16_t i = 0; i < 0xff; i++) {
//        /* Shift high byte first to shift registers. */
//        shift_out(i >> 8);
//        shift_out(i & 0xff);
//
//        /* Pulse latch to0                                                                                                                                                                                                                                                        transfer data from shift registers */
//        /* to storage registers. */
    
//
         
//    }
}
