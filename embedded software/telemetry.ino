#include <Adafruit_GPS.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <SoftwareSerial.h>

// variables
unsigned char messageBuffer[8]; // for the CAN messages

void stopButtonPressed()
{

}

void manageLights(unsigned char messageBuffer)

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