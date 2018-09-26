# Movidius_Object_Detection
Work in progress...
The [Movidious Compute Stick](https://software.intel.com/en-us/neural-compute-stick) attaches to a Pi with camera. 
Sample apps can be found at https://github.com/movidius/ncappzoo.
The version of the *live-object-detector* here is slightly modified to publish object name and co-ordinates via MQTT.
Replace the 'eclipse' public server with your own Mqtt server.

IR decoder is an arduino project that reads IR codes from an IR control.
Control codes for the [Miele Floor Sweeper](https://www.miele.ie/domestic/robot-vacuum-cleaner-2750.htm) are included.

Next steps (TODO):
* IR transmitter transmitting codes received via MQTT- use an ESP8266 for this, as it is wifi enabled.
* Local MQTT server, (again...)
* Add Miele to the object-detector.
* Track and control the Miele.
