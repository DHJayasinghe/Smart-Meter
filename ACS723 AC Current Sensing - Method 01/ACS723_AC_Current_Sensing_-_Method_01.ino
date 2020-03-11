#define acs712 A1

long lastsample = 0;
long samplesum = 0;
int sampleCount = 0;

//volts per count = 5/1024 = 0.0048828125
float vpc = 4.8828125; //volts per count * 1000 => convert to milli volts

void setup()
{
  Serial.begin(115200);

}

// RMS Method
void loop() {

  if (millis() > lastsample + 1) {
    //take sample.
    samplesum += sq(analogRead(acs712) - 512);
    sampleCount++;

    lastsample = millis();
  }

  // take 1000 samples
  if (sampleCount == 1000) {
    //averaging stuff

    float mean = samplesum / sampleCount;
    float value = sqrt(mean); // RMS value
    float mv = (value * vpc); // RMS voltage (in milli voltage)
    // ACS unit sensitivity is 66 milli vots per amp
    float amperage = mv / 185;  //66 for 30A  185 for 20A  185 for 5A


    Serial.println("The final RMS Amperage is: " + String(amperage) + " Appox WATTAGE is: " + String(amperage * 230) + ".");

    // reset sample count after done sampling
    samplesum = 0;
    sampleCount = 0;
  }
}
