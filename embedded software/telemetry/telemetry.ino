#include <Adafruit_GPS.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <SoftwareSerial.h>

// variables
unsigned char messageBuffer[8]; // for the CAN messages
unsigned long lastMillis = 0;
unsigned long lastMessageSentMillis = 0;

// pins
const int stopButtonIn = 4; // stop button in pin
const int canIn = A0; // CAN in pin

    // extra pins, not used currently
const int outputPin1 = 5;
const int outputPin1 = 6;
const int outputPin1 = 7;
const int outputPin1 = 8;
const int outputPin1 = 9;


// constants
const int loopDelay = 100; // main loop delay in ms
const int checkWait = 60000; // wait 60 sec before connection with car is deemed unreachable
const int lightFlashPeriod = 500; // lights flash at this rate in ms, per solar car regulations


void stopButtonPressed()
{

}

// flashes the lights in a recognizable pattern in case of an error
void flashErrorLights(){
  
}

void manageLights(unsigned char messageBuffer)
{
  
}

// this method reads incoming can messages from the car
void readCan()
{
    if(CAN_MSGAVAIL == CAN.checkReceive()){  // if there is a message waiting in the CAN buffer
        CAN.readMsgBuf(&len, messageBuffer); // then read the message and the length into memory
        if(CAN.getCanId() == receivingID && messageBuffer[1] == 0x55){ // is the CAN message's ID == the receiving id (aka its coming from the car to us)                                                              
            manageLights(messageBuffer); //this message has been deemed to be about either the brake lights or BMS lights, pass to manageLights
        }
    }
}

const int stopButtonIn = 4;

const int canIn = A0;
const int loopDelay = 20; //delay for main loop in ms
const int light
