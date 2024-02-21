// EXAMPLE USAGE

void blink();
int ledPin = D7;
int statepin=D5;
const byte interruptPin = 2;

volatile int state = LOW;
int a;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(statepin, OUTPUT);

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(interruptPin, blink, FALLING);
}

void loop() {
  digitalWrite(ledPin, state);
  //Particle.publish("Button Press",String (state),60,PRIVATE);
  if (state==1){
      digitalWrite (statepin,HIGH);
      Particle.publish("Button Press",String ("ON"),60,PRIVATE);
  }
  else{
      digitalWrite(statepin, LOW);
            Particle.publish("Button Press",String ("OFF"),60,PRIVATE);

  }
  delay(2000);

}

void blink() {
  state = !state;
  //Particle.publish("Button Press",String (state),60,PRIVATE);
}
