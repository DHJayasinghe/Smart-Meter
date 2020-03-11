#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

void setup() {
  Serial.begin(9600);
  
  emon1.current(1, 60.60);             // Current: input pin, calibration.
}

void loop() {
  // put your main code here, to run repeatedly:
  double Irms = emon1.calcIrms(100);  // Calculate Irms only
  Serial.print(Irms);  // Irms
  Serial.print(" ");  
  Serial.print(Irms*230.0);         // Apparent power   
  Serial.println(" Watts");
  delay(100);
}
