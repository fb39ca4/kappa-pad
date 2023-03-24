//Dependencies
#include <CapacitiveSensor.h>
#include <Keyboard.h>

/*
In my case, I used an arduino leonardo, so if you need help with the pin numbers and properties,
here's a pinout: https://ja-bots.com/wp-content/uploads/2019/06/arduino-leonardo4.png
*/

//Pin definitions
const int STATUS_LED_PIN = 13; /* PWM pin preferably*/
const int SWITCH_PIN = 12;

/* PWM pins preferably aswell*/
extern const int RGB_RED_LED_PIN = 9;
extern const int RGB_GREEN_LED_PIN = 10;
extern const int RGB_BLUE_LED_PIN = 11;

/* If you don't connect the LEDS to PWM pins on the arduino, 
you must change the analogWrite functions to digitalWrite 
(Ctrl+F in both this file and the CapacitiveKey.h one)
and set the second parameter to LOW or HIGH for OFF and ON respectively */

//Other variables
extern const int NUMBER_OF_MODES = 4;     // Defines the number of modes that the keypad will have
extern const int RGB_LED_MODE = 0;            // Defines the mode of the RGB LED (only changeable via here, code reupload needed)
int MODE=0;                       // Control variable that cycles between the modes of the keypad (changeable by the switch)

/* The variables declared with extern are global, used in the CapacitiveKey.h file aswell */

/*
The RGB LED MODES are defined as it follows:
    by default in all modes : 
    The led briefly shines an unique color the moment the mode is changed, as to show which mode we are on
    0 - NONREACTIVE > The led only does the default behaviour
    1 - REACTIVE    > The led briefly shines an unique color the moment a key is pressed
*/

//Functions
extern void setRgbLedColor(int red, int green, int blue){
  analogWrite(RGB_RED_LED_PIN, red);
  analogWrite(RGB_GREEN_LED_PIN, green);
  analogWrite(RGB_BLUE_LED_PIN, blue);
} 

//Here we include the file, after we declare all of the global variables (for scoping reasons)
#include "capacitiveKey.h"

//Keys ^

/*   CapacitiveKey parameters in order
(Send,Sense,led,Threshold,Key1,Key2,Key3) */

// If you need to make changes to this function, go to the CapacitiveKey.h file
/* Refer to this link https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h for more keyCodes */

CapacitiveKey key1 = CapacitiveKey(22,1  ,20 ,'z'      ,'s','x'    );
CapacitiveKey key2 = CapacitiveKey(21,2  ,20 ,'x'     ,'d','c'   );
CapacitiveKey key3 = CapacitiveKey(19,4  ,20 ,'p'     ,32,0   );
CapacitiveKey key4 = CapacitiveKey(7,6   ,20 ,KEY_ESC    ,'o','n'  );
CapacitiveKey key5 = CapacitiveKey(23,0  ,20 ,KEY_F7      ,'a',KEY_ESC   );
CapacitiveKey key6 = CapacitiveKey(20,3  ,20 ,KEY_F2    ,32,0   );
CapacitiveKey key7 = CapacitiveKey(18,5  ,20 ,KEY_F6    ,'x',0    );

/*  Uncomment the #define line to enable testing mode
This enables serial monitor output, to check the key readings values
The keypad starts disabled, so no inputs will be sent unless you change the mode again. */

//#define TESTING 

void setup() 
{
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(RGB_RED_LED_PIN, OUTPUT);
  pinMode(RGB_BLUE_LED_PIN, OUTPUT);
  pinMode(RGB_GREEN_LED_PIN, OUTPUT);
  Keyboard.begin();

  #ifdef TESTING
  Serial.begin(115200);
  MODE=NUMBER_OF_MODES-1;
  #endif
}

void loop() 
{
  MODE%=NUMBER_OF_MODES; //Cycles the mode number from 0 to NUMBER_OF_MODES-1.

  /* Check if the switch has been pulsated, we use a pullup resistor so we check for LOW */
  if (digitalRead(SWITCH_PIN)==LOW)
  {
    MODE+=1;    //Increase the mode by 1
    // Defult behaviour of RGB LED
    switch(MODE)
    { 
    /* If the LEDS are connected to PWM pins, you can modify their brightness,
    changing the parameters from 0 to 255, where 0 is off and 255 is the brightest */

      case (1):
        setRgbLedColor(0, 1, 0); 
        break;

      case (2):
      setRgbLedColor(0, 0, 20); 
      break;

      //if you have more modes, add some more colors here to know when you change to them, or else you will see default color

      case (NUMBER_OF_MODES-1):
        setRgbLedColor(1, 0, 0); 
        break;

      default:
        setRgbLedColor(20,0,20); //You will see this color when you cycle back to state 0,
        break;
    }
    delay(500); //Delay as to only increase the mode by 1
    setRgbLedColor(0,0,0);
  }

  #ifdef TESTING
  Serial.print("Mode #");Serial.print(MODE);Serial.print(" - ");
  Serial.print(key1.sample);Serial.print(" ");
  Serial.print(key2.sample);Serial.print(" ");
  Serial.print(key3.sample);Serial.print(" ");
  Serial.print(key4.sample);Serial.print(" ");
  Serial.print(key5.sample);Serial.print(" ");
  Serial.print(key6.sample);Serial.print(" ");
  Serial.print(key7.sample);Serial.println();
  #endif

  // Comment any of the keys if you need them to be disabled, but leave them instantiated on the Keys ^ part
  key1.keyUpdate(MODE);
  key2.keyUpdate(MODE);
  key3.keyUpdate(MODE);
  key4.keyUpdate(MODE);
  key5.keyUpdate(MODE);
  key6.keyUpdate(MODE);
  key7.keyUpdate(MODE); 

  //Control of the Status LED
  if(MODE==NUMBER_OF_MODES-1){analogWrite(STATUS_LED_PIN, 15);}
  else{analogWrite(STATUS_LED_PIN, 0);}    
}
