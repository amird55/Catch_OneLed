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
  analogWrite(pinLedYellow,287);

}

void loop() {

  if(millis()-LastToggleTime > BlinkInterval){
    BlinkInterval=random(200,3001);
    LedToggle();
    LastToggleTime=millis();
  }

  CurrBtn=digitalRead(pinBtn);
  if((CurrBtn == LOW) && (LastBtn == HIGH)&&(millis() - LastPressTime > 50)){
    LastPressTime=millis();
    // btn is pressed
    score += (IsLedOn) ? 1 : -1 ;
  }
  LastBtn=CurrBtn;

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
