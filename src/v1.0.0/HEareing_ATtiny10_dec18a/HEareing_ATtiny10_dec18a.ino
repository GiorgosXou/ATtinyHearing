#ifdef F_CPU
#undef F_CPU
#define F_CPU 125000L
#endif

//NOTES:for 125khz) Issue in general when running on 125khz
//"Deferent Values for Higher Clock Speeds ... ?"
#define F7S 12000
#define F7_ 10000 // ISSUE
#define E7_ 9600
#define D7S 8700
#define D7_ 8300  // ISSUE
#define C7S 7700
#define C7_ 6300
#define B6_ 5700
#define A6S 5300
#define A6_ 5000
#define G6S 4600
#define G6_ 4200
#define F6S 4000
#define F6_ 3800
#define E6_ 3500
#define D6S 3300
#define D6_ 3100
#define C6S 2700
#define C6_ 2600
#define B5_ 2400
#define A5S 2200
#define A5_ 2050
#define G5S 1900
#define G5_ 1800
#define F5S 1700
#define F5_ 1600
#define E5_ 1500
#define D5S 1400
#define D5_ 1300
#define C5S 1200
#define C5_ 1100

#define NOTES 106 //137 - MAX

const PROGMEM uint16_t t[NOTES] = {500   ,D6S-100,D6S-100,D6_-100,30,D6S-100 , 40 , D6S-100,D6S-100,D6_-100,30,D6S-100 , 40 , D6S-100,D6S-100,F6_,30,C6S,30,C6S,30,C6S,30,C6S , 80 , D6S-100,D6S-100,D6_-100,30,D6S-100 , 40 , D6S-100,D6S-100,D6_-100,30,D6S-100, 40 , D6S-100,D6S-100,F6_+100,30,C6S+100,30,C6S+100,30,C6_,30,C6S+100 , 80 , F6_,F6_,E6_,30,F6_ , 40 , F6_,F6_,E6_,30,F6_ , 40 , F6_,F6_,G6_+100,40,C6S+100,40,C6S+100,40,C6_+100,40,C6S+100 , 80 , G6_,C6S+100,C6S+100,C6_+100,C6S+100 , 80 , G6_,40,C6S+100,40,C6S+100,40,C6S+100,40,C6S+100,40,G6_,40,D6S,40,F6_,40,G6_,40,G6S,40,G5S+100,40,G5S+100,40,G5S+100,40,G5S+100};
const PROGMEM byte d[NOTES] =     { 0    ,     45,     45,     75, 0,    180 ,  0 ,      45,     45,     75, 0,    180 ,  0 ,      45,     45, 75, 0, 65, 0, 65, 0, 65, 0,190 ,  0 ,      45,     45,     75, 0,    180 ,  0 ,      45,     45,     75, 0,   180 ,  0 ,      45,     45,     80, 0,     65, 0,     65, 0, 65, 0,    190 ,  0 , 55, 55, 90, 0, 180 ,  0 ,  55, 55, 95, 0, 180,  0 ,  55, 55,    180, 0,     50, 0,     50, 0,     70, 0,    210 ,  0 ,  100,     80,     80,     80,   190 ,  0 , 100, 0,     60, 0,     60, 0,     60, 0,     60, 0, 80, 0, 70, 0, 50, 0, 80, 0, 50, 0,     50, 0,     50, 0,     50, 0,    150};

void setup() {
  DDRB = 3; // pinMode(PIN, OUTPUT);
}

byte i = 0;
void loop() {

  playTone();
  if (i < (NOTES-1)) { i++; }else{ i = 0; }

}


void playTone()
{ 
  // CLOCKspeed /  ToneHz / 2
  unsigned long halfPeriod = 125000L / (pgm_read_word(&t[i]))  / 2;
  unsigned int startTime = 0; // millis() - ISSUE

  // - Tone
  while (startTime < pgm_read_byte(&d[i]) ) 
  {
    PORTB = 0b0010; // pin3 HIGH
    delayMicroseconds(halfPeriod);
    PORTB = 0b0000; // pin3 LOW
    delayMicroseconds(halfPeriod);
    startTime++;
  }

  // - Pause
  if (pgm_read_byte(&d[i]) == 0)
  {
    delay(pgm_read_word(&t[i])); // puase time
  }

  // - Pause between each Note
  delay(1);
}
