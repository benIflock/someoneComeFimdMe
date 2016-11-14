/*
this send serial software commands to the GSM shield - on startup it purges the sim 
then other commands can be sent directly through the serial monitor

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("and we're on!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("AT");
  delay(2000);
    Serial.println( "AT+CMGF=1" ); 
delay(2000);
Serial.print( "AT+CMGDA=" ); 
Serial.write(34);
Serial.print("DEL ALL");
Serial.write(34);
Serial.write(13);
Serial.write(10);
delay(6000);
Serial.println( "should have deleted everyone" );
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
}

