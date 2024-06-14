#define pinLed 6
bool IsLedOn;
unsigned long LastToggleTime;
int BlinkInterval;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A1));

  pinMode(pinLed,OUTPUT);
  LedOff();
  LastToggleTime=millis();
  BlinkInterval=random(200,3001);
}

void loop() {

  if(millis()-LastToggleTime > BlinkInterval){
    BlinkInterval=random(200,3001);
    LedToggle();
    LastToggleTime=millis();
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
