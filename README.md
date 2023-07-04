# KappaPad / General purpose Keypad version.

This version of the KappaPad is a customizable multi button keypad intended for general purposes. Unlike other keypads with mechanical switches, this keypad has fixed metal pads and uses capacitive sensing to determine when they are being pressed.

![Keypad Image](images/Full.png?raw=true)

## Usage

Just plug it into a computer, and it will work as an USB keyboard, with the keys bound to the user preferences, which are customizable from the Arduino Sketch. It also features a mode changing switch, that cycles through different key layouts also defined by the user.

## How to Make One

There aren't any plans to sell these, but it is fairly simple to build your own. Here is an example of how to build one, but you don't have to follow it exactly. Just use the materials you have on hand.

### Physical Construction

The base should ideally be a non-slip surface on the bottom. The keypad pictured has a base made out of scrap plastic, with rubber feet on the bottom that I got online. Components were attached with mostly hot glue, and the Arduino shield that I modified to fit some larger screws in, to screw in place to the plastic, securing and protecting the Arduino Leonardo. 

### Electronics

Components Used

* Mini Breadboard
* Ultra mini Breadboard
* Clone of Arduino Leonardo*
* 220 Ohm Resistors
* 330 kOhm Resistors
* Wire
* Normal LED
* 2 leg switch
* RGB LED (Common cathode in this case)

All of the electronics were connected by the breadboards. An Arduino Leonardo - compatible board was used as the microcontroller. 

Other boards that can act as a USB keyboard can be used, such as Arduino Pro Micro, Arduino Zero, Arduino Due, and Teensy. 

The optional LEDs will light up depending on which key was pressed and the mode the keypad is in. 

The keys were made out of a cut single sided copper PCB plate (Bakelite virgin plate), with wires soldered to them, to provide a reliable electrical connection. 
Any metal objects can be used for the keys. The size and material of the objects will determine the treshold values when calibrating the keypad.

### Software

The Arduino Sketch is located in the Main directory of this repository. It requires the [CapacitiveSensor library](https://github.com/PaulStoffregen/CapacitiveSensor), so install that first. 

Upload the sketch to the board using the appropriate board type. (Use Arduino Leonardo if you have a Pro Micro.) After uploading, note that your board may recieve a different serial port number.

### How to get it working

1. Define your connection layout

Plan ahead, depending on the board that you get, you can only have a certain amount of keys. In the case of the Arduino Leonardo, I could have made 8 keys, with the switch and rgb led, but I didnt have enough space for the status LED, so I settled for 7 keys. So make a plan of what you want and can do, so no materials, money and specially time is wasted.

Here's the general wiring for one key:
![Closeup of Electronics](images/singleKeyWiring.png?raw=true)

For each key you'll need a 330 kOhm resistor, and 2 pins of the board.

For the RGB led you'll need 3 220 Ohm resistors, and 3 pins of the board.

For the optional last state led, another 220 Ohm resistor and a pin of the board.

2. Test your connections

Use jumper cables and the protoboard to test your connections with test mode enabled before you cut cables, so you can check if your components are working properly. To test the keys before making them permanent, you can just hold the cable to the key with one hand and pressing it with the other, or hold it with tape (recommended). 

3. Adjust the threshold values

In this test step, depending on the materials you used to make the keys, you'll need to change the threshold values in the key definition parameters: check the readings (sensed capacity) of the keys in testing mode. In the serial monitor, you should see a stable value when you're not touching the key (NT), and a higher value when touching it (T). The idea is that you adjust the threshold value between those 2 values (NT< Threshold< T), so that you don't get false positives when using the keypad.

Remember to reupload the sketch everytime you make changes to the code, and to turn off the testing mode when you're done to improve the performance of the keypad, as the serial communications can delay the inputs.

4. Make your connections permanent
   
You can leave the project as is, but I opted to cut down cables to size and solder the keys as to make the keypad more reliable and portable, so I can take it to other places, and it's just more neat looking. 

5. Configure your keys 
   
Depending on your needs, you can adjust the key layout of the different modes, to use whichever keys you need to press. You could use it with [AutoHotKey](https://www.autohotkey.com/) and use the keypad for some cool user defined macros, but that's up to you!

6. Customize it!

Make changes to the code (if you're comfortable with doing so) and maybe even implement a new functionality, behaviour, etc. In my case, I made a function that detects when 2 keys are pressed at the same time, which tells me if im keylocking when I play with a very specific playstyle in osu!, so yeah, you can do very specific things with this and that's what I find the coolest about this project.

### Common issues

For troubleshooting all of these, enable the testing mode of the keypad by uncommenting the line 69:
```
//#define TESTING 
```
As to avoid key constant key presses that can be really annoying to work with, and enabling the Serial monitor to verify the readings of the keys.

* 65534 / Ultra high key readings
Happens if you have a bad connection in the key wirings. Try raplacing the cables for jumper cables in the connection of the key where you get the high reading, and test the connections again.

* Multiple key readings in one tap
Make sure the connection part between the key and the cable (being solder, tape, or a crimpled cable) is working as intented, and try again. 

* Can't compile
Verify the following things:
    * You have the correct board model (Arduino Uno NOT COMPATIBLE)    
    * You have installed the [CapacitiveSensor library](https://github.com/PaulStoffregen/CapacitiveSensor)

I'll try my best to solve any other questions in the issues tab.


