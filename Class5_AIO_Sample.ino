// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_MQTT.h>      //delete this line and add library 
#include "Adafruit_MQTT_SPARK.h"    //leave this line


/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "add your username here"//accounts.adafruit.com)..."            //this is your username
#define AIO_KEY         "paste your key here"              //replace with your AIO key


/************ Global State (you don't need to change this!) ******************/
TCPClient TheClient;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");    //temp feed

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");      //subscribe to button feed

/*************************** Sketch Code ************************************/

int led = D7;       //setup LED pin
int temp;       //setup temp variable


void setup()
{
    Serial.begin(9600);
    delay(10);
    
    Serial.println(F("Adafruit MQTT demo"));
    
    // Setup MQTT subscription for onoff feed.
    mqtt.subscribe(&onoffbutton);
    
     pinMode(led, OUTPUT);
}

void loop()
{
    if( mqtt.Update() )
    {
        // this is our 'wait for incoming subscription packets' busy subloop
        // try to spend your time here
        Adafruit_MQTT_Subscribe *subscription;
        while ((subscription = mqtt.readSubscription(5000)))
        {
            if (subscription == &onoffbutton)
            {
                Serial.print(F("Got: "));
                //Serial.println(onoffbutton.lastread);
                //Serial.println((int)onoffbutton.lastread);  // this yeilds some crazy number
                
                Serial.println((char *)onoffbutton.lastread);  // this brings in a character
               int toggleLED=(atoi ((char *)onoffbutton.lastread)); // this converts the character to a interger so you can do logic on it
               
                if (toggleLED==1){
                    digitalWrite(led, HIGH);        //turn LED on if the toggle  button in AIO is on
                    Serial.print(F("LED on"));
                }
                else{
                    digitalWrite(led,LOW);          //otherwise turn it off
                     Serial.print(F("LED off"));
                }
                
            }
        }
        
        // Now we can publish stuff!
        temp = random(55, 89);          //setup a simulated temperature sensor
        Serial.print(F("\nSending temp val "));
        Serial.print(temp);
        Serial.print("...");
        if (!temperature.publish(temp))        //publish the temp
        {
            Serial.println(F("Failed"));
        }
        else
        {
            Serial.println(F("OK!"));
        }
  
        // ping the server to keep the mqtt connection alive
        // NOT required if you are publishing once every KEEPALIVE seconds
        /*
        if(! mqtt.ping())
        {
            mqtt.disconnect();
        }
        */
    }
}








