/**********************************************************************
   _____       __              __  ___            _ __            
  / ___/____  / /___ ______   /  |/  /___  ____  (_) /_____  _____
  \__ \/ __ \/ / __ `/ ___/  / /|_/ / __ \/ __ \/ / __/ __ \/ ___/
 ___/ / /_/ / / /_/ / /     / /  / / /_/ / / / / / /_/ /_/ / /    
/____/\____/_/\__,_/_/     /_/  /_/\____/_/ /_/_/\__/\____/_/     
                                                                  
v0.03 Initial ethernet code (18.5.2017) Daniel Öster
Use a voltage divider to measure high DC voltage

Todo:
-Calibrate on battery bank (*56 current calib)
-Make some power savings attemps/measurments
***********************************************************************/
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //MAC address for controller
IPAddress ip(192, 168, 0, 177); //IP address for controller

void setup() {
  //Serial debugger
  Serial.begin(9600);

  //Start ethernet connection
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Current IP ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  int voltage = 0;
  voltage = measureVoltage(); // Update the voltage measurement
  delay(1000); // 1s delay
}

int measureVoltage(){ //function to calculate voltage from divider
  byte VoltagePin = 0; // Pin for voltage measurement (0 = A0) [datarange 0-255]
  int result;
  int value; //analogue read value from voltage measurement 
  value = analogRead(VoltagePin); //Read the battery bank voltage (0 to 1023)
  result =  (value * 0.097) * 56 ; //value*0.097 is same as /1023 to avoid float. *56 is value from voltage divider resistors, needs tuning on real battery array
  return result;
}
