#define acs712 A1

long lastsample = 0;
int sampleMax = 0;
int sampleCount = 0;

//volts per count = 5/1024 = 0.0048828125
float vpc = 4.8828125; //volts per count * 1000 => convert to milli volts

void setup()
{
  Serial.begin(115200);

}

// 0.707 Method
void loop() {

  if (millis() > lastsample + 1) {
    //take sample.
    
    int thisSample = analogRead(acs712) - 512;
    if(thisSample > sampleMax){ // find peak reading
      sampleMax = thisSample;
    }

    sampleCount++;

    lastsample = millis();
  }

  // take 1000 samples
  if (sampleCount == 1000) {
    //averaging stuff

    float peakMv = (sampleMax * vpc); // Peak milli voltage (in milli voltage)
    float avgMv = peakMv * 0.707; // average Peak milli voltage => Equate to RMS voltage
    // ACS unit sensitivity is 66 milli vots per amp
    float amperage = avgMv / 185;  //66 for 30A  185 for 20A  185 for 5A


    Serial.println("The final RMS Amperage is: " + String(amperage) + " Appox WATTAGE is: " + String(amperage * 230) + ".");

    // reset sample count after done sampling
    sampleMax = 0;
    sampleCount = 0;
  }
}
