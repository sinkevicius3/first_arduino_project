// C++ code
//

#define TRF_RED_LED 2
#define TRF_YEL_LED 3
#define TRF_GRE_LED 4
#define BUTTON 	5
#define PED_RED_LED 6
#define PED_GRE_LED A1
#define PIEZO       A0

#define DISPLAY_A 7
#define DISPLAY_B 8
#define DISPLAY_C 9
#define DISPLAY_D 10
#define DISPLAY_E 11
#define DISPLAY_F 12
#define DISPLAY_G 13

#define TRF_LIGHT_BLINKS 4
#define BLINK_TIME 750

#define TRF_SWITCH_TIME   5000
#define PED_CROSS_TIME    10000  // ms

#define PED_CYCLE_TIME    10000

const int numbers[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 1},
    {0, 1, 1, 0, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1}
};

const int displayPins[7] = {DISPLAY_A, DISPLAY_B, DISPLAY_C, DISPLAY_D, DISPLAY_E, DISPLAY_F, DISPLAY_G};

void setup() {

  // Serial.begin(9600);

  pinMode(TRF_RED_LED, OUTPUT);
  pinMode(TRF_YEL_LED, OUTPUT);
  pinMode(TRF_GRE_LED, OUTPUT);

  pinMode(BUTTON, INPUT);

  pinMode(PED_RED_LED, OUTPUT);
  pinMode(PED_GRE_LED, OUTPUT);

  pinMode(PIEZO, OUTPUT);

  pinMode(DISPLAY_A, OUTPUT);
  pinMode(DISPLAY_B, OUTPUT);
  pinMode(DISPLAY_C, OUTPUT);
  pinMode(DISPLAY_D, OUTPUT);
  pinMode(DISPLAY_E, OUTPUT);
  pinMode(DISPLAY_F, OUTPUT);
  pinMode(DISPLAY_G, OUTPUT);

  digitalWrite(TRF_GRE_LED, 1);
  digitalWrite(PED_RED_LED, 1);
  displayNumber(0);
}

void loop(){
  //blinkLED();
  //Serial.println(digitalRead(BUTTON));

  // for(int i = 0; i < 10; ++i){
  //   displayNumber(i);
  //   delay(1000);
  // }

  simulateTraffic();
}

void simulateTraffic(){

  while(1){
    if(digitalRead(BUTTON)){

        resetDisplay();
        
        delay(TRF_SWITCH_TIME);

        for(int i = TRF_LIGHT_BLINKS - 1; i >= 0; --i){
          digitalWrite(TRF_GRE_LED, 0);
          if(i){
            delay(BLINK_TIME);
            digitalWrite(TRF_GRE_LED, 1);
          }
          delay(BLINK_TIME);
        }

        digitalWrite(TRF_YEL_LED, 1);
        delay(2 * BLINK_TIME);
        digitalWrite(TRF_YEL_LED, 0);
        digitalWrite(TRF_RED_LED, 1);

        delay(TRF_SWITCH_TIME);

        digitalWrite(PED_RED_LED, 0);
        digitalWrite(PED_GRE_LED, 1);

        for(int i = 0; i < PED_CROSS_TIME / 1000 * 5; ++i){
          tone(PIEZO, 1050, 50); // tone(pin, frequency, duration)
          delay(50);
          tone(PIEZO, 880, 50); // tone(pin, frequency, duration)
          delay(50);
          delay(100);
        }

        // delay(PED_CROSS_TIME);

        for(int i = TRF_LIGHT_BLINKS - 1; i >= 0; --i){
          digitalWrite(PED_GRE_LED, 0);
          if(i){
            delay(BLINK_TIME - 50);
            digitalWrite(PED_GRE_LED, 1);
            tone(PIEZO, 1050, 50); // tone(pin, frequency, duration)
            delay(50);
            tone(PIEZO, 880, 50); // tone(pin, frequency, duration)
            delay(50);
          }
          delay(BLINK_TIME - 50);
        }
        
        digitalWrite(PED_RED_LED, 1);

        delay(TRF_SWITCH_TIME);

        digitalWrite(TRF_YEL_LED, 1);
        delay(1000);

        digitalWrite(TRF_RED_LED, 0);
        digitalWrite(TRF_YEL_LED, 0);
        digitalWrite(TRF_GRE_LED, 1);

        for (int i = (PED_CYCLE_TIME / 1000); i >= 0; --i){
          if (i < 10){
            displayNumber(i);
          }
          delay(1000);
        }
    }
  }
}

void displayNumber(int number) {

  if (number < 0 || number > 9) return; 

  for (int i = 0; i < 7; ++i) {
    digitalWrite(displayPins[i], numbers[number][i]);
  }
}

void resetDisplay(){

  for (int dp : displayPins){
    digitalWrite(dp, 0);
  }
}

void blinkLED() {
  
  digitalWrite(TRF_RED_LED, 1);
  delay(500);
  digitalWrite(TRF_RED_LED, 0);
  delay(500);
  
  digitalWrite(TRF_YEL_LED, 1);
  delay(500);
  digitalWrite(TRF_YEL_LED, 0);
  delay(500);
  
  digitalWrite(TRF_GRE_LED, 1);
  delay(500);
  digitalWrite(TRF_GRE_LED, 0);
  delay(500);
  
  digitalWrite(PED_RED_LED, 1);
  delay(500);
  digitalWrite(PED_RED_LED, 0);
  delay(500);
  
  digitalWrite(PED_GRE_LED, 1);
  delay(500);
  digitalWrite(PED_GRE_LED, 0);
  delay(500);
}
