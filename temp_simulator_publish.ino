int temp;

void setup() {
  Serial.begin(9600);
}

void loop() {


  // print a random number from 10 to 19
  temp = random(55,90);
  Serial.println(temp);             // this will show in serial monitor if you download Arduino/ Putty/ etc
  Particle.publish("Temp",String (temp),60,PRIVATE);
  delay(3000);          //keep this delay to 1000 or more to keep from saturating Particle
}
