// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>    // make sure you add this manually in the web IDE


// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D5
#define PIXEL_COUNT 10
#define PIXEL_TYPE WS2812       //2811 is fine for ours, but if you use a different brand you need to look this up in the library file
#define BRIGHTNESS 30           // 0 - 255 (note, these are super bright, so lower is fine for the bench)

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


void setup() {
strip.setBrightness(BRIGHTNESS);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
bruteforce();
delay (1000);
wipeoff();
delay (1000);

}

void bruteforce(){
    strip.setPixelColor(0, 0,0,255); //first number is the index of the LED in the strip. the next 3 are the RGB color code
    strip.setPixelColor(1, 85,0,255);
    strip.setPixelColor(2, 127,0,180);
    strip.setPixelColor(3, 170,0,90);
    strip.setPixelColor(4, 255,0,0);
    strip.setPixelColor(5, 255,43,0);
    strip.setPixelColor(6, 213,85,0);
    strip.setPixelColor(7, 170,128,0);
    strip.setPixelColor(8, 128,255,0);
    strip.setPixelColor(9, 85,255,0);
        strip.show();
}

void wipeoff(){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0,0,0);    //0,0,0 is the RGB code
    strip.show();
}
}
