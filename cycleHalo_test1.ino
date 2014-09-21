#include <Adafruit_NeoPixel.h>

// NeoPixel output
#define PIN         6
#define NUMPIX      16

// Ring Commands
#define SET_LED           0x01  // sets specific LED to a colour
#define SET_SEGMENT       0x02  // sets segment from origin to end to a colour
#define SET_BRIGHTNESS    0x03  // sets brightness of a segment
#define SET_FADE_SEGMENT  0x04  // fades segment to desired colour
#define BEAT_EFFECT       0x05  // dims and brightens an a segment n times
#define COLOR_WHIP        0x06  // gradually sets colour of segment waiting delay between lighting each lighting

// Front-light Commands
#define SET_FLIGHT_ON 0x10
#define SET_FLIGHT_OFF 0x12
#define SET_FLIGHT_BLINK 0x13    //sets the light to blink with ontime and offtime

// Switch
#define ENABLE_SWITCH


Adafruit_NeoPixel ring = Adafruit_NeoPixel(NUMPIX, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 2; // delay for half a second

void setup() {
  ring.begin(); // This initializes the NeoPixel library.
  // Reset lights
  ring.clear();
  ring.show();
  delay(500);
  digitalWrite(13, HIGH);
  
// for(int i=0;i<NUMPIX;i++){
//   ring.setPixelColor(i, ring.Color(255,255,50));
//   ring.show();
//   }
  
}

void loop() {
  // For a set of Neoring the first NeoPixel is 0, second is 1, all the way up to the count of ring minus one.
  int num_pix = 16;
  int width = 4;

  uint32_t prim_color = ring.Color(20, 250, 20);
  uint32_t sec_color = ring.Color(30, 50, 50);

  two_colour_fade(width, prim_color, sec_color, 2, 1.0);
  ring.show();
  delay(2000);

  for(float progress = 1.0; progress >= 0.0; progress -= 0.01)
  {
    two_colour_fade(width, prim_color, sec_color, 2, progress);
    ring.show();
    delay(50);
  }

  display_beat(2, 50, 255, 5);

  ring.clear();
  ring.show();
  delay(1000);

  width  = 4;

  two_colour_fade(width, prim_color, sec_color, 12, 1.0);
  ring.show();
  delay(2000);
  for(float progress = 1.0 ;progress >= 0.0; progress -= 0.01)
  {
    two_colour_fade(width, prim_color, sec_color, 12, progress);
    ring.show();
    delay(50);
  }

  display_beat(2, 50, 255, 5);

  ring.clear();
  ring.show();
  delay(1000);

  width  = 8;
  prim_color = ring.Color(255, 0, 0);
  
  two_colour_fade(width, prim_color, sec_color, 4, 0);
  ring.show();
  delay(1000);

  display_beat(2, 50, 255, 5);

  ring.clear();
  ring.show();
  delay(1000);
}

// width, colour 1, colour 2, position, progress
void two_colour_fade(int width, uint32_t colour_prim, uint32_t colour_sec, int origin, float progress) {
  
  // clean up values
  origin %= ring.numPixels();
  width %= ring.numPixels();

  // get end coordinate
  int end_coord = (origin + width);
  // get colour accent coordinates
  float accent_width = int((width * progress)+0.5);

  set_segment(origin, end_coord, colour_prim);

  float accent_orig = (origin + int(((width - accent_width) / 2) + 0.9));

  accent_width = int(width - (accent_orig - origin)*2);

  set_segment(int(accent_orig), int(accent_orig + accent_width), colour_sec);

}

void set_segment(int origin, int end, uint32_t colour){

  for(int i = origin; i < end; i++){
    ring.setPixelColor(i%ring.numPixels(), colour);
  }

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<ring.numPixels(); i++) {
      ring.setPixelColor(i, c);
      ring.show();
      delay(wait);
  }
}

void display_beat(long delay_time, int min_br, int max_br, int times){

  for (int n =0 ; n < times; n++){
    
    for (int i=0;i<max_br-min_br;i++){
      ring.setBrightness(max_br-i);
      delay(delay_time);
      ring.show();
    }

    for (int i=min_br;i<max_br;i++){
      ring.setBrightness(i);
      delay(delay_time);
      ring.show();
    }
  }

  ring.setBrightness(max_br);


}