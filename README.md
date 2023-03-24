# KappaPad / General purpose Keypad version.

_Todo_ Introductory video

This version of the KappaPad is a customizable multi button keypad intended for general purposes. Unlike other keypads with mechanical switches, this keypad has fixed metal pads and uses capacitive sensing to determine when they are being pressed.

![Keypad Image](images/Full.png?raw=true)

## Usage

Just plug the keypad into a computer, and it should work as an USB keyboard, with the keys bound to the user preferences, customizable from the Arduino Sketch. It also features a mode changing switch, that cycles through different key layouts also defined by the user.

## How to Make One

There aren't any plans to sell these, but it is fairly simple to build your own. Here is an example of how to build one, but you don't have to follow it exactly. Just use the materials you have on hand.

### Physical Construction

The base should ideally be a non-slip surface on the bottom. The keypad pictured has a base made out of scrap plastic, with rubber feet on the bottom that I got from AliExpress. Components were attached with mostly hot glue, and the Arduino shield that I modified to fit some larger screws in, to screw in place to the plastic, securing and protecting the Arduino Leonardo from dust. 

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

All of the electronics were connected by the breadboards. An Arduino Leonardo - compatible board was used as the microcontroller. Other boards that can act as a USB keyboard can be used, such as Arduino Pro Micro, Arduino Zero, Arduino Due, and Teensy. 

The optional LEDs will light up depending on which key was pressed and the mode of the LEDS (I disabled them because they distract me too much, but added a mode where they shine depending on the key that was pressed). 

The keys were made out of cut single sided copper PCB plate (Bakelite virgin plate), with wires soldered to provide a reliable electrical connection. 
Any metal objects can be used for the keys. The size and material of the objects will determine the treshold values when calibrating the keypad.

### Software

The Arduino Sketch is located in the Main directory of this repository. It requires the [CapacitiveSensor library](https://github.com/PaulStoffregen/CapacitiveSensor), so install that first. 

Upload the sketch to the board using the appropriate board type. (Use Arduino Leonardo if you have a Pro Micro.) After uploading, note that your board may recieve a different serial port number.

### How to get it working

1. Define your connection layout
Plan ahead, depending on the board that you get, you can only have a limited set of keys. In the case of the Arduino Leonardo, I could have made 8 keys, with the switch and rgb led, but I didnt have enough space for the status LED, so I settled for 7 keys.

Here's the general wiring for one key. _Todo_
![Closeup of Electronics](images/electronics.jpg?raw=true)

Keep in mind, that for each key you'll need a 330 kOhm resistor.
For the RGB led you'll need 3 220 Ohm resistors and for the optional last state led, another 220 Ohm resistor.

2. Test your connections
Use jumper cables and the protoboard to test the connections with the test mode enabled before you cut cables, so you can check if your components are working properly. To test the keys before soldering them, you can just hold the cable to the key, and hold it with tape. 

3. Adjust the threshold values
In this test step, depending on the materials that you use to make the keys, you'll need to change the threshold values in the key definition parameters. To know an appropiate value, check the readings (sensed capacity) of the keys in the testing mode. In the serial monitor, you should have a stable value when you're not touching the key, and a higher (but also stable) value when touching it. Remember to reupload the sketch everytime you make changes to the code, and to turn off the testing mode to improve the performance of the keypad, as the serial communications can delay the inputs.

4. Make your connections permanent
You can leave the project as is, but I preferred to cut down the cables to size and solder them to the keys as to make the keypad more reliable when I take it to other places, and more neat looking. 

5. Configure your keys 
Depending on your needs, you can adjust the key layout of the different modes, for using the keypad in different scenarios. I normally use it to play Osu!, but will use it to play 4k mania, Spelunky 2, maybe even Hollow knight, you choose! 
(Now that I think of it, you could use it with [AutoHotKey](https://www.autohotkey.com/) and use the keypad for some cool user defined macros)

### Common issues

For troubleshooting all of these, enable the testing mode by uncommenting the 
```
//#define TESTING 
```
code in line 69 (nice), as to avoid key constant key presses that can be really annoying to work with, and check the Serial monitor of the Arduino to see the readings of the keys.

* 65534 / Ultra high key readings
Happens if you have a bad connection in one of the key wirings. Try to replace the cables for jumper cables and test the connections again.

* Multiple key readings in one tap
Make sure the connection part between the key and the cable (being solder, tape, or a crimpled cable) is working as intented, and try again. 

* Can't compile
Verify the following things:
    * You have the correct board model (Arduino Uno NOT COMPATIBLE)    
    * You have installed the [CapacitiveSensor library](https://github.com/PaulStoffregen/CapacitiveSensor)

I'll try my best to solve any other questions in the issues tab.

### Finishing thoughts

That's it! This all started as a 'for fun' project to cope with the fact that I was bad at streams in Osu!, and eventually made it into a full on project that I think will be using regularly for other things.

Here's some gameplay of the keypad in action:
_Todo_


