// configuration settings
int LED_PIN = D1;
int LOOP_DELAY = 5000; // time is in milliseconds

void setup() {
    // LED pin setup
    pinMode(LED_PIN, OUTPUT);
    Particle.function("ledToggle",ledToggle);
}

void loop() {
    // We are sending the temperature and humidity level in one publish
    double analogValue = random (0,4093);
    float voltage = random(0.0,33)/10;
    double degreesC = random (13,35);
    double degreesF = degreesC * 1.8 + 32;
    
    Particle.publish("climate_reading", (String)voltage + ":" + (String)degreesF);
    delay(LOOP_DELAY);
}

int ledToggle(String command) {

    if (command=="on") {
        digitalWrite(LED_PIN,HIGH);
        return 1;
    }
    else if (command=="off") {
        digitalWrite(LED_PIN,LOW);
        return 0;
    }
    else {
        return -1;
    }

}
