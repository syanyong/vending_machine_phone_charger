#define LED     13

// For Shift Register TPIC6B595
#define DATA    5   // SER IN
#define CLOCK   6   // S RCK
#define LATCH   7   // RCK

int toggle = 0;
int tmp = 0x01;

void shiftPush(unsigned char dIn){
  char i;
  for(i = 7;i >= 0; i--){
    if ( (dIn & (0b1<<i)) != 0){
      digitalWrite(DATA, LOW); // It might be inverted.
    }else{
      digitalWrite(DATA, HIGH);
    }
    digitalWrite(CLOCK, LOW);
    digitalWrite(CLOCK, HIGH);
  } 
}
void shiftPrint8bit(unsigned char dIn){
  digitalWrite(LATCH, LOW);
  shiftPush(dIn);
  digitalWrite(LATCH, HIGH);
}
void shiftPrint16bit(unsigned int dIn){
  digitalWrite(LATCH, LOW);
  shiftPush((dIn>>8)&0xFF);
  shiftPush(dIn&0xFF);
  digitalWrite(LATCH, HIGH);  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  
  pinMode(LED, OUTPUT);
}

void loop() {
  for(unsigned char i = 0; i < 8 ;i++){
    shiftPrint16bit(0b01<<i);
    _delay_ms(50);
  }
//  shiftPrint8bit(0b00000010);
//  shiftPrint16bit(0b00000010);
  
  if (toggle){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
  toggle = !toggle;
  _delay_ms(250);

}
