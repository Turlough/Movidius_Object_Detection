/*
 * Raw control data captured from the IR remote
 * for the Miele Scout Robot Floor cleaner.
 * Send single character commands over Serial to the Arduino.
 * 
 * Commands can be sent via USB, or separately to the Rx pin, e.g. via an ESP8266
 * (remember to disconnect the Rx pin while uploading this sketch)
 * Set the baud rate of the ESP8266 to 9600.
 * 
 * Connect an IR LED to PWM pin 3. 
 * The command characters will cause control sequences to be transmitted by the LED using PWM
 * 
 * The following codes are recognised:
 * 
 * MANUAL CONTROL CODES
 * --------------------
 * w, a, s, d for up, left, back, right. 
 * Note that 'continuation' codes will be sent after these commands-
 * these mimic holding the remote buttons down.
 * q terminates the 'continuation' code transmission
 * 
 * AUTO CONTROL CODES (no continuation codes need be sent for these.
 * ------------------
 * b sends 'return to base' sequence.
 * v sends 'start/pause' sequence
 * 
 */


#include <IRremote.h>

IRsend irsend;
int khz = 38; // 38kHz carrier frequency for the NEC protocol

//Manual control codes
unsigned int forward[] = {8900,4400, 600,1600, 600,550, 600,500, 600,500, 650,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600,1650, 600,500, 600,500, 600,550, 600,1600, 600,550, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 600,500, 600,1650, 600,1600, 600,1650, 600,1600, 600};  // NEC 807F10EF
unsigned int backward[] = {8900,4400, 600,1650, 600,500, 600,500, 650,500, 600,500, 600,550, 600,500, 600,500, 600,550, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600,1600, 650,1600, 600,1600, 650,500, 600,500, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 650,1600, 600,1600, 650,500, 600,1600, 600,1650, 600,1600, 600,1650, 600};
unsigned int right[] = {8900,4400, 600,1650, 600,500, 600,500, 600,550, 600,500, 600,500, 600,550, 600,500, 600,500, 650,1600, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600,1650, 600,500, 600,1650, 600,500, 600,1600, 600,550, 600,500, 600,500, 650,500, 600,1600, 600,550, 600,1600, 600,500, 650,1600, 600,1600, 650,1600, 600,1600, 600};
unsigned int left[] = {8950,4350, 650,1600, 600,500, 600,550, 600,500, 600,500, 650,500, 600,500, 600,550, 600,500, 600,1650, 550,1650, 550,1750, 500,1750, 450,1750, 500,1650, 550,1700, 550,1650, 550,1700, 550,550, 550,1650, 600,550, 550,550, 550,600, 550,550, 550,550, 550,600, 550,1650, 550,600, 550,1650, 550,1650, 600,1650, 550,1650, 600}; 
//The 'continue' code
unsigned int fff[] = {8900,2200, 600}; 

//Start/Pause and return to base
unsigned int start[] = {8950,4350, 600,1650, 600,500, 600,550, 550,550, 600,500, 600,500, 600,550, 600,500, 600,550, 550,1650, 600,1650, 600,1600, 600,1600, 600,1650, 600,1600, 600,1650, 550,550, 600,550, 550,1650, 600,500, 600,550, 550,550, 600,550, 550,550, 550,1650, 600,1650, 600,500, 600,1650, 550,1650, 600,1650, 550,1650, 550,1700, 550}; 
unsigned int base[] = {8900,4400, 600,1600, 650,500, 600,500, 600,550, 600,500, 600,500, 600,550, 600,500, 600,500, 600,1650, 600,1600, 600,1650, 600,1600, 600,1650, 600,1600, 600,1650, 600,500, 600,1600, 650,1600, 600,500, 600,550, 600,500, 600,500, 600,550, 600,1600, 600,550, 550,550, 600,1650, 550,1650, 550,1700, 550,1650, 550,1700, 550};

//boolean for whether or not to send continuation code in loop()
bool isContinue = false;
//Read from serial
int incoming = 0;

//Keyboard codes, wasd plus q,b. Q sets isContinue to false. B = return to base. V = start/pause
const int w = 0x77;
const int a = 0x61;
const int s = 0x73;
const int d = 0x64;
const int q = 0x71;
const int b = 0x62;
const int v = 0x76;


void setup(){
  Serial.begin(9600);
  Serial.println("Ready for input");
}

void loop() {
    delay(50);
    sendContinue();
    
   if (Serial.available() > 0) {
        // read the incoming byte:
        incoming = Serial.read();
//        Serial.print("Received: ");
//        Serial.println(incoming, HEX);
        switch(incoming){
          case w: 
            Serial.println("key w: forward");
            command(forward, sizeof(forward));
            isContinue = true;
            break;
          case a: 
            Serial.println("key a: left");
            command(left, sizeof(left));
            isContinue = true;
            break;
          case s: 
            Serial.println("key s: backward");
            command(backward, sizeof(backward));
            isContinue = true;
            break;
          case d: 
            Serial.println("key d: right");
            command(right, sizeof(right));
            isContinue = true;
            break;
          case q: 
            Serial.println("key q: Stop continuing");
            isContinue = false;
            break;
          case b: 
            Serial.println("key b: return to base");
            command(base, sizeof(base));
            isContinue = false;
            break;
          case v: 
            Serial.println("key v: start/pause");
            command(start, sizeof(start));
            isContinue = false;
            break;
        }
  }
}

//sends continuation command for manual controls while isContinue is true
void sendContinue(){
  if(isContinue){
    delay(50);
    Serial.print(".");
    command(fff, sizeof(fff));
  }
}

//wrapper function for sending a command
void command(int arr[], int len){
  irsend.sendRaw(arr, len / sizeof(arr[0]), khz); 
}
