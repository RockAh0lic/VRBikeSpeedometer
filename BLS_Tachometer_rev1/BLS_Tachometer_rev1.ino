#include <SoftwareSerial.h> // bluethoot serial library

// CONFIGURATION ZONE
// ****************************************************
// digital pins configuration
int digitalBluetoothRXpin = 5;
int digitalBluetoothTXpin = 6;
byte analogTachometerPin = A3;
// number of magnets existing on the spinning wheel
byte magnets = 4;
// how many samples should be taken for RPM calculation
// (more samples = higher precision, longer computing time)
byte samples = 1;
// enabled to automatically control RPM precision based 
// on RPM 
bool automaticSampler = true;
// time in milliseconds to wait for another 
// reading before zeroing out the RPM value
int readTimeOut = 200;
// ****************************************************

// analog read variables
short int analogValue;

// digital read variables
bool digitalValue, oldDigitalValue;
int serialData;

// rpm sample variables
// sample ratio; 1 sample per X RPM
byte rpmSampleInterval = 50; // used for automatic sampler
// maximum number of samples allowed
byte maxSamples = 100;
byte sampleCounter, oldSampleCounter;
bool ignoreFirstSample = true; // should be always true
float sampleTimeCounter;

// rpm variables
float rpmCurrentTime, rpmRefferenceTime, rpmDeltaTime;
float currentRPM, summedRPM, instantRPM;

// time variables
float refferenceTime, currentTime, deltaTime;

// software serial, required for bluetooth module
SoftwareSerial BLS(digitalBluetoothTXpin,
                   digitalBluetoothRXpin); // RX, TX

void setup()
{
  BLS.begin(9600);
  Serial.begin(115200);
  pinMode(analogTachometerPin,INPUT);
}

void loop()
{
  calculateRPM();
  calculateDeltaTime();
  
  sampleTimeCounter += deltaTime;
  if(sampleTimeCounter > readTimeOut) 
  {
    sampleTimeCounter = 0;

    if(sampleCounter == oldSampleCounter)
    {
      currentRPM = 0;
      printRPM(currentRPM, 0);
      ignoreFirstSample = true;
    }
  }

  // read and write from bls after
  // all callculations are done
}

void calculateDeltaTime()
{
  currentTime = millis();
  
  if(refferenceTime > 0)
    deltaTime = currentTime - refferenceTime;
    
  refferenceTime = millis();
}

void calculateRPM()
{
  analogValue = analogRead(analogTachometerPin);
  if(analogValue < 500)
  digitalValue = 0;
  else 
  digitalValue = 1;
  
  oldSampleCounter = sampleCounter;
  if(oldDigitalValue==0 && digitalValue==1)
  {
    // update current time
    rpmCurrentTime = micros();
    
    // calculate rpm
    rpmDeltaTime = rpmCurrentTime - rpmRefferenceTime;
    instantRPM = (1000000 * 60/ rpmDeltaTime)/magnets;
    summedRPM += instantRPM;
    
    // update refference time
    rpmRefferenceTime = micros();

    // increment the sample tracker
    sampleCounter ++;
    // reset the sample time counter
    sampleTimeCounter = 0;
  }
  oldDigitalValue = digitalValue;

  if(sampleCounter >= samples)
  { 
    // calculate the sampled rpm
    currentRPM = summedRPM/samples;

    // ignore the first sample
    if(ignoreFirstSample == true)
    {
      ignoreFirstSample = false;
    }
    else
    {
      // print rpm calculations
      printRPM(currentRPM, samples);
    }

    // update samples if automatic 
    // sampler is active
    if(automaticSampler == true)
    {
      samples = instantRPM / rpmSampleInterval;

      // Clamp rpm sample value
      samples = constrain(samples, 1, maxSamples);
    }
    
    // reset the sample counter
    sampleCounter = 0;
    // reset the RPM sum
    summedRPM = 0;
  }
}

void printRPM(int rpm, int samples)
{
  Serial.print("RPM : ");
  Serial.print(currentRPM);
  Serial.print(" @ ");
  Serial.print(samples);
  Serial.println(" samples ");

    BLS.println((int)currentRPM);
}



