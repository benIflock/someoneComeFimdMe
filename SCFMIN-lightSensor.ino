
/*
 SMS receiver

 This sketch, for the Arduino GSM shield, waits for a SMS message
 and displays it through the Serial port.

 Circuit:
 * GSM shield attached to and Arduino
 * SIM card that can receive SMS messages

 created 25 Feb 2012
 by Javier Zorzano / TD

 This example is in the public domain.

 http://arduino.cc/en/Tutorial/GSMExamplesReceiveSMS

*/

// include the GSM library
#include <GSM.h>
//include morse library
  #include <Lewis.h>

// PIN Number for the SIM
#define PINNUMBER ""

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;
Lewis Morse;
// Array to hold the number a SMS is retreived from
char senderNumber[20];
int lightValue = 0;
const int  lightSensor = A0;
void setup()
{
  pinMode(A0, INPUT);
  //do the morse on 6, with 10 wpm count
    Morse.begin(6, 6, 10);
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
       ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("SMS Messages Receiver");
  // connection state
  boolean notConnected = true;

  // Start GSM connection
  while (notConnected)
  {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  //init GSM
  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");
  Serial.println("initialization done.");
//does a little flash to let you know its happy


   Morse.print('ok');
}

//lets do this!
void loop()
{
  lightValue = analogRead(lightSensor);
  char c;
  int index = 0 ;
  char msgStr;
  
 //is it daytime?
 if(lightValue > 5){
 //its daytime so only flash when messaged:
   // If there are any SMSs available()
  if (sms.available())
  {
    // Any messages starting with # should be discarded
    if (sms.peek() == '#')
    {
      Serial.println("Discarded SMS");
      sms.flush();
    }

    // Read message bytes and print them
    while (c = sms.read()){
      Serial.print(c);
      Morse.print(c);
}
    Serial.println("\nEND OF MESSAGE");

    // Delete message from modem memory
   sms.flush();
    Serial.println("MESSAGE DELETED");
  }
 
 }else{
 //its probably night time:
 
   // If there are any SMSs available()
  if (sms.available())
  {
  
 

    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    // An example of message disposal
    // Any messages starting with # should be discarded
    if (sms.peek() == '#')
    {
      Serial.println("Discarded SMS");
      sms.flush();
    }

    // Read message bytes and print them
    while (c = sms.read()){
      Serial.print(c);
      Morse.print(c);
}
    Serial.println("\nEND OF MESSAGE");

    // Delete message from modem memory
   sms.flush();
    Serial.println("MESSAGE DELETED");
  }else{
  //send a warninbg flash
  Morse.print(1);
  
  }
 
 
 
 
 
 }
  
  delay(1000);

}



