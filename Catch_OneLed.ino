#define pinLed 6
bool IsLedOn;
unsigned long LastToggleTime;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A1));

  pinMode(pinLed,OUTPUT);
  LedOff();
  LastToggleTime=millis();
}

void loop() {
  int BlinkInterval=random(1000,3001);

  if(millis()-LastToggleTime > BlinkInterval){
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
