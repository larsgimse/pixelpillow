#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 7

/* const int rod = 12;
const int gul = 11;
const int gronn = 10; */

 // Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

int temp = sensors.getTempCByIndex(0);
 
void setup(void)
{

//  pinMode(rod, OUTPUT);
//  pinMode(gul, OUTPUT);
//  pinMode(gronn, OUTPUT);
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  Serial.print("Temperature is: ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?
  int temp = sensors.getTempCByIndex(0); 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
  //temp = sensors.requestTemperatures();
/*  delay(1000);
  if (temp >= 26) {
    digitalWrite(rod, HIGH);
    digitalWrite(gul, LOW);
    digitalWrite(gronn, LOW);
  }
  else if (temp >= 23 && temp < 26) {
    digitalWrite(rod, LOW);
    digitalWrite(gul, HIGH);
    digitalWrite(gronn, LOW);
  }
  else if (temp < 23) {
    digitalWrite(rod, LOW);
    digitalWrite(gul, LOW);
    digitalWrite(gronn, HIGH);
  }
    */
}
