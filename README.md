# MQTT to IR relay, with object detection
This is a work in progress...

## Summary
Having been gifted a [Miele Scout Robot Floor Sweeper](https://www.miele.ie/domestic/robot-vacuum-cleaner-2750.htm), it was time to begin hacking...

### The IR projects
The Miele comes with an IR remote control. 

In this project, we have an IR reader project (*IRrecvDumpV2*) to establish what codes are sent by the Miele remote, and an IR transmitter project (*IRsendRawCodesToMiele*) to send the same codes via an Arduino with an IR LED attached. Details of the IR reader results can be found in the Resources directory, and images of the hardware setup are in the Images directory.

Commands are sent to the Arduino over Serial (at the moment); the Arduino parses the commands and issues control codes via the IR LED. The following codes are used:
* w: forward
* a: left
* s: backward (in practice, the Miele turns 180 degrees- it does not actually reverse)
* d: right
* v: start/pause
* b: return to base
The WASD commands are followed by 'continuation' codes, delivered every 50 milliseconds. This simulates holding down the (orignal) remote buttons. The start and base commands do not require to be followed by continuation codes- send once, and the Miele does the rest.

Details of IR control codes and some comments are in the Resources directory.

### mqtt_subscriber
The Tx pin of the ESP8266 is connected to the Arduino Rx pin, and relays commands over Serial to the IR LED.
Change wifi credentials, broker, etc.

### live-object-detector
The *live-object-detector* directory contains an Inception image categoriser, which I have running on a Raspberry Pi with a [Movidious Compute Stick](https://software.intel.com/en-us/neural-compute-stick). This surveys the room containing the Miele. I have not retrained it yet, but have taken the example code and modified it to publish categories and co-ordinates via MQTT. Replace the public eclipse broker with the url of your own broker. And add authentication. 

Why is this here? Next steps are to retrain the network to recognise the Miele (training data: split a video of the Miele in action into training jpegs), and shoes (training set from [ImageNet](http://image-net.org/synset?wnid=n04199027#). Why shoes? Because visitors wear shoes, and the Miele will need a target to follow... :)

## Next steps
* Increase power of IR LED by using two of them, and a transistor to deliver more current (range is only a few meters when connected directly to the PWM pin)
* Mount the IR LED in a more commanding position.
* Retrain the Movidius, and mount the camera in a better position.
* Invite some visitors to test the ~~death robot~~ Miele on.

## Credits
The [Movidious Compute Stick](https://software.intel.com/en-us/neural-compute-stick) worked with the Pi right out of the box.
The demo apps were easy to use and understand. Sample apps can be found at https://github.com/movidius/ncappzoo.
The version of the *live-object-detector* here is slightly modified to publish object name and co-ordinates via MQTT.

*IRrecvDumpV2*: Aduino project (from the examples in Ken Shirriff's [IRremote library](https://github.com/z3t0/Arduino-IRremote)) for reading raw data from IR controller. This is copied unadultered from the examples directory of the library, and is included for reference.


