#define pinLed 6
#define pinBtn 2

#define pinLedYellow 4
#define pinBuzzer 5

#define WAIT_FOR_NEW_GAME 31
#define START_OF_GAME     32
#define GAME_IS_ON        33
#define GAME_OVER         34
int CurrState;

bool IsLedOn;
unsigned long LastToggleTime;
int BlinkInterval;

int CurrBtn;
int LastBtn;
unsigned long LastPressTime;
int score=0;

int MaxBlinks=5;
int blinkCnt=0;
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A1));

  pinMode(pinBtn,INPUT_PULLUP);
  LastPressTime=millis();

  pinMode(pinLed,OUTPUT);
  pinMode(pinLedYellow,OUTPUT);
  pinMode(pinBuzzer,OUTPUT);

  CurrState=WAIT_FOR_NEW_GAME;

}

void loop() {
  switch(CurrState){
    case WAIT_FOR_NEW_GAME:wait_to_start(); break;
    case START_OF_GAME    :start_game();    break;
    case GAME_IS_ON       :game_on();       break;
    case GAME_OVER        :game_over();     break;

  }
}
      
void wait_to_start(){
  digitalWrite(pinLed,HIGH);
  digitalWrite(pinLedYellow,HIGH);
  /*
  //זיהוי שחרור של הכפתור
    CurrBtn=digitalRead(pinBtn);
    if((CurrBtn == HIGH) && (LastBtn == LOW)&&(millis() - LastPressTime > 50)){
      LastPressTime=millis();
      // btn is released
      CurrState=START_OF_GAME;
    }
    LastBtn=CurrBtn;
*/

  //עבודה עם חיישן קול
  if(analogRead(A3) > 100){
      CurrState=START_OF_GAME;
  }
}
void start_game(){
  score=0;
  blinkCnt=0;
  LedOff();
  LastToggleTime=millis();
  BlinkInterval=random(200,3001);
  MaxBlinks=map(analogRead(A0),0,1023,7,12);

  beep();
  CurrState=GAME_IS_ON;
}
void game_on(){
  if(blinkCnt <= MaxBlinks){
    if(millis()-LastToggleTime > BlinkInterval){
      BlinkInterval=random(200,3001);
      LedToggle();
      LastToggleTime=millis();
      if(IsLedOn){
        blinkCnt++;
      }
    }

    CurrBtn=digitalRead(pinBtn);
    if((CurrBtn == LOW) && (LastBtn == HIGH)&&(millis() - LastPressTime > 50)){
      LastPressTime=millis();
      // btn is pressed
      score += (IsLedOn) ? 1 : -1 ;
      score = max(0,score);
      score = min(5,score);
    }
    LastBtn=CurrBtn;


    int ledValY = map(score,0,5,0,128);
    analogWrite(pinLedYellow,ledValY);
  }
  else {
    CurrState=GAME_OVER;
  }
}
void game_over(){
     int ledValY = map(score,0,5,0,128);
    analogWrite(pinLedYellow,ledValY);
    CurrState=WAIT_FOR_NEW_GAME;
}

void beep(){
  digitalWrite(pinBuzzer,HIGH);
  delay(400);
  digitalWrite(pinBuzzer,LOW);
}
void LedToggle(){
  if(IsLedOn){
    LedOff();
  } else {
    LedOn();
  }
}
void LedOn(){
  digitalWrite(pinLed,HIGH);
  IsLedOn=true;
}
void LedOff(){
  digitalWrite(pinLed,LOW);
  IsLedOn=false;
}
