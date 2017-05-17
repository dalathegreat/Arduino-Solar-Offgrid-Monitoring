/**********************************************************************
   _____       __              __  ___            _ __            
  / ___/____  / /___ ______   /  |/  /___  ____  (_) /_____  _____
  \__ \/ __ \/ / __ `/ ___/  / /|_/ / __ \/ __ \/ / __/ __ \/ ___/
 ___/ / /_/ / / /_/ / /     / /  / / /_/ / / / / / /_/ /_/ / /    
/____/\____/_/\__,_/_/     /_/  /_/\____/_/ /_/_/\__/\____/_/     
                                                                  
v0.02 Voltage measurement completed (without float!) (17.5.2017) Daniel Öster
Use a voltage divider to measure high DC voltage
Todo:
-Calibrate on battery bank (*56 current calib)
-Add shield code
-Add network capability
-Make some power savings attemps/measurments
***********************************************************************/

const byte VoltagePin = 0; // Pin for voltage measurement (0 = A0) [datarange 0-255]    
int voltage = 0;

void setup() {
Serial.begin(9600); //Serial debugger
}

void loop() {
  voltage = measureVoltage(); // Update the voltage measurement
  delay(1000); // 1s delay
  Serial.println(voltage);
}

int measureVoltage(){ //function to calculate voltage from divider
  int result;
  int value; //analogue read value from voltage measurement 
  value = analogRead(VoltagePin); //Read the battery bank voltage (0 to 1023)
  result =  (value * 0.097) * 56 ; //value*0.097 is same as /1023 to avoid float. *56 is value from voltage divider resistors, needs tuning on real battery array
  return result;
}
