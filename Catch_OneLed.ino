#define pinLed 6
#define pinBtn 2

#define pinLedYellow 4

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
  LedOff();
  LastToggleTime=millis();
  BlinkInterval=random(200,3001);

  pinMode(pinLedYellow,OUTPUT);


  MaxBlinks=map(analogRead(A1),0,1023,7,12);
  
}

void loop() {
  if(blinkCnt < MaxBlinks){
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
