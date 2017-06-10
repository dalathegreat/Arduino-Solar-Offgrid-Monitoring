/**********************************************************************
   _____       __              __  ___            _ __            
  / ___/____  / /___ ______   /  |/  /___  ____  (_) /_____  _____
  \__ \/ __ \/ / __ `/ ___/  / /|_/ / __ \/ __ \/ / __/ __ \/ ___/
 ___/ / /_/ / / /_/ / /     / /  / / /_/ / / / / / /_/ /_/ / /    
/____/\____/_/\__,_/_/     /_/  /_/\____/_/ /_/_/\__/\____/_/     
                                                                  
v0.04 Initial ethernet code (10.6.2017) Daniel Öster
Use a voltage divider to measure high DC voltage!

Todo:
-Make display in voltage (V+1decimal) instead of mV
-Calibrate on battery bank (*56 current calib)
-Make some power savings attemps/measurments
-Remove Serial Prints once stable

***********************************************************************/
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //MAC address for controller
IPAddress ip(192, 168, 0, 177); //IP address for controller

// Initialize the Ethernet server library
// with the IP address and port you want to use
EthernetServer server(80);

void setup() {
  //Serial debugger
  Serial.begin(9600);

  //Start ethernet connection
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Current IP ");
  Serial.println(Ethernet.localIP());
}

int measureVoltage(){ //function to calculate voltage from divider
  byte VoltagePin = 0; // Pin for voltage measurement (0 = A0) [datarange 0-255]
  int result;
  int value; //analogue read value from voltage measurement 
  value = analogRead(VoltagePin); //Read the battery bank voltage (0 to 1023)
  result =  (value * 0.097) * 56 ; //value*0.097 is same as /1023 to avoid float. *56 is value from voltage divider resistors, needs tuning on real battery array
  return result;
}

void loop() {

// listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of bank voltage
            int sensorReading = measureVoltage();
            client.print("Current battery voltage is ");
            client.print(sensorReading);
            client.print("mV");
            client.println("<br />");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }

}
