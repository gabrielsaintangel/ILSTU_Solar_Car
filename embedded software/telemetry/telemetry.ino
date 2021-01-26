#include <Adafruit_GPS.h>
#include <mcp_can.h>
#include <mcp_can_dfs.h>
#include <SoftwareSerial.h>
#include <Ada

// variables
unsigned char messageBuffer[8]; // for the CAN messages
unsigned long lastMillis = 0;
unsigned long lastMessageSent = 0; // variable to track the time since last can message sent in millis
unsigned long lastTimeComCheck = 0;
int canID = 0;

// pins
const int stopButtonIn = 4; // stop button in pin
const int canIn = A0; // CAN in pin

// extra pins, not used currently
const int output1 = 5;
const int output2 = 6;
const int output3 = 7;
const int output4 = 8;
const int output5 = 9;



// constants
const int loopDelay = 100; // main loop delay in ms
const int checkComDelay = 500; // delay for checkCom function, checks communication every 500ms
const int checkComCycleLimit = 120; // check communication for 200 cycles, or about one min before deeming unreachable
const int lightFlashPeriod = 500; // for BPS light, from regulations: Must flash between 60 and 120 pulses per minute

// gps stuff
SoftwareSerial mySerial(2, 3);
Adafruit_GPS GPS(&mySerial);

void setup() {
  //pin setup
  pinMode(in1, INPUT); //
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(out5, OUTPUT);
  pinMode(out6, OUTPUT);
  pinMode(canPin, INPUT_PULLUP);

  Serial.begin(57600); // start serial with 57600 baud rate

  // Start the Adafruit GPS module
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA); // specify what information we want
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate


  CAN.begin(CAN_500KBPS);

  delay(2000); // just to make sure can works
  mySerial.begin(9600); // for communicating with the gps
  mySerial.println("$PMTK251,57600*2C"); // configuration message for the gps, with checksum
  mySerial.end(); // end the serial
  delay(500);
  mySerial.begin(57600);
  //its an adafruit gps
  mySerial.println("$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"); //another configuration message, basically says I want this message and this one and the rest are trash
  mySerial.println("$PMTK220,1000*1F"); // this is saying we want an update every 1000 ms

  //GPS.begin(9600);
  //tried to use the ADAfruit gps library
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  //GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);

  for (int i = 0; i < 10 || CAN_OK != CAN.begin(CAN_500KBPS); i++) // count to 10 until the can established connection
  {
    delay(100);
  }
  //Serial.println("CAN BUS Shield init OK!");

  CAN.init_Mask(0, 0, 0x000); //everything gets passsed through, no filter... could be used to fill messages with relevant message so no overflow
  CAN.init_Filt(0, 0, recID); //main recieving id
}

int checkCom() {
  if (digitalRead(canPin) == LOW) { // if we have established a connection to the can system
    return 1;
  }
  else {
    return 0;
  }
}


// error 1 = CAN Error, error 2 = battery error
void throwError(int errorType)

}





int checkStopButton(){
  while(digitalRead(in1)<<7){
    
  }
}

// flashes the lights in a recognizable pattern in case of an error

void manageLights(unsigned char messageBuffer)
{

}

// this method reads incoming can messages from the car
void readCan()
{
  canID = CAN.getCanId();  // get the ID from the read message
  CAN.readMsgBuf(&len, messageBuffer); // then read the message and the length into memory
  if (messageBuffer[1] == 0x55) { //check value
    if (canID == receivingID) { // check lights
      manageLights(messageBuffer); //this message has been deemed to be about either the brake lights or BMS lights, pass to manageLights
    }
    else {
      Serial.print(canID, HEX);
      Serial.print(" ");
      Serial.println((char*)messageBuffer);
    }
  }
}



void loop() {
  if (checkCom)
  {
    if(digitalRead(in1)<<7){ //stop button pressed
      manageLights()
    }
    if (CAN_MSGAVAIL == CAN.checkReceive()) {
      readCan();
    }
    if (GPS.newNMEAreceived()) {
      Serial.write(GPS.read());
    }

  }
}
