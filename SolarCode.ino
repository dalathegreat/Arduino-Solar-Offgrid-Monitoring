/**********************************************************************
   _____       __              __  ___            _ __            
  / ___/____  / /___ ______   /  |/  /___  ____  (_) /_____  _____
  \__ \/ __ \/ / __ `/ ___/  / /|_/ / __ \/ __ \/ / __/ __ \/ ___/
 ___/ / /_/ / / /_/ / /     / /  / / /_/ / / / / / /_/ /_/ / /    
/____/\____/_/\__,_/_/     /_/  /_/\____/_/ /_/_/\__/\____/_/     
                                                                  
v0.01 Not even compiled (15.5.2017) Daniel Öster
Use a voltage divider to measure high DC voltage

Todo:
-Calibrate DC measurement with 110k / 10k resistors?
-Hardcode the values
-Avoid float datatypes
-Add shield code
-Add network capability
-Make some power savings attemps/measurments
***********************************************************************/

const byte VoltagePin = 23; // Pin for voltage measurement (23 = A0) [datarange 0-255]
byte value = 0;        // analogue read value from voltage measurement [datarange 0-255]
float R1 = 100000.0;    // resistance of R1 (100K) -USE BEFORE CALIBRATING , HARDCODE ONCE GOOD
float R2 = 10000.0;     // resistance of R2 (10K) -USE BEFORE CALIBRATING , HARDCODE ONCE GOOD
float vout = 0.0;
float vin = 0.0;

void setup() {

}

void loop() {
  value = analogRead(VoltagePin); //Read the battery bank voltage (0-255)
  vout = (value * 5.0) / 1024.0; //temporary
  vin = vout / (R2/(R1+R2)); //temporary conversion
  delay(1000); //temporary 1s delay 
}
