#include <EEPROM.h>
#include <FastLED.h>

#define NUM_LEDS  15
#define LED_PIN   7
#define BUTTON 2

CRGB leds[NUM_LEDS];
uint8_t paletteIndex = 0;
byte selectedEffect=0;

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
    0, 120,  0,  0,
   22, 179, 22,  0,
   51, 255,104,  0,
   85, 167, 22, 18,
  135, 100,  0,103,
  198,  16,  0,130,
  255,   0,  0,160
};
 
 DEFINE_GRADIENT_PALETTE( greenblue_gp ) { 
    0,    0,  194,  255,     //light blue
   46,    3,    0,  246,     //dark blue
  176,   55,  222,   70,     //bright green
  255,    0,  194,  255      //light blue
};

DEFINE_GRADIENT_PALETTE( orangepink_gp ) { 
    0,  255,  100,    0,     //orange
   90,  255,    0,  255,     //magenta
  150,  255,  100,    0,     //orange
  255,  255,  100,    0      //orange
};

DEFINE_GRADIENT_PALETTE( browngreen_gp ) { 
    0,    6,  255,    0,     //green
   71,    0,  255,  153,     //bluegreen
  122,  200,  200,  200,     //gray
  181,  110,   61,    6,     //brown
  255,    6,  255,    0      //green
};

DEFINE_GRADIENT_PALETTE (heatmap_gp) {
    0,   0,   0,   0,   //black
  128, 255,   0,   0,   //red
  200, 255, 255,   0,   //bright yellow
  255, 255, 255, 255    //full white 
};

DEFINE_GRADIENT_PALETTE (fire_gp) {
  0,   0,   0,   0,   
  64, 255,   144, 4,   
  168, 250, 10, 10,   
  200, 252, 107, 4,
  255, 247, 252, 4   
};

DEFINE_GRADIENT_PALETTE (red_gp) {
  0, 255, 10, 10,     
  168, 252, 4, 0,   
  200, 0, 0, 0,
  255, 255, 5, 15   
};

DEFINE_GRADIENT_PALETTE (green_gp) {
  0,   76, 152, 10,     
  168, 75, 225, 15,   
  200, 93, 115, 39,
  255, 165, 255, 5   
};

DEFINE_GRADIENT_PALETTE (white_gp) {
  0,   224, 227, 180,     
  168, 155, 155, 155,   
  200, 255, 255, 255,
  255, 50, 50, 50   
};

CRGBPalette16 sunsetPalette = Sunset_Real_gp;
CRGBPalette16 greenBluePalette = greenblue_gp;
CRGBPalette16 orangePinkPalette = orangepink_gp;
CRGBPalette16 browngreenPalette = browngreen_gp;
CRGBPalette16 heatmapPalette = heatmap_gp;
CRGBPalette16 firePalette = fire_gp;
CRGBPalette16 redPalette = red_gp;
CRGBPalette16 greenPalette = green_gp;
CRGBPalette16 whitePalette = white_gp;

void setup() {
 FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
 FastLED.setBrightness(150);
 
 pinMode(2,INPUT_PULLUP);  
 attachInterrupt (digitalPinToInterrupt (BUTTON), changeEffect, CHANGE); 
}

void loop() {
  EEPROM.get(0,selectedEffect); 
  
  if (selectedEffect == 9) { 
    selectedEffect=0;
    EEPROM.put(0,0); 
  } 
  
    switch(selectedEffect) {
        case 0: {
          activateEffect(firePalette);
          break;
        }
        case 1: {
          activateEffect(greenBluePalette);
          break;
        }
        case 2: {
          activateEffect(sunsetPalette);
          break;
        }
        case 3: {
          activateEffect(orangePinkPalette);
          break;
        }
        case 4: {
          activateEffect(heatmapPalette);
          break;
        }
        case 5: {
          activateEffect(redPalette);
          break;
        }
        case 6: {
          activateEffect(greenPalette);
          break;
        }
        case 7: {
          activateEffect(whitePalette);
          break;
        }
        case 8: {
          activateEffect(browngreenPalette);
          break;
        }
     }
}

void activateEffect(CRGBPalette16 palette) {
  fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, palette, 255, LINEARBLEND);
  
  EVERY_N_MILLISECONDS(10){
    paletteIndex++;
  }
  
  FastLED.show();
}

void changeEffect() {
  if (digitalRead (BUTTON) == LOW) {
    selectedEffect++;
    EEPROM.put(0, selectedEffect);
    asm volatile ("  jmp 0");
  }
}
