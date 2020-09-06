#include "DHT.h"
//#include "Wire.h" //allows communication over i2c devices
//#include "LiquidCrystal_I2C.h" //allows interfacing with LCD screens

#define DHTPIN 2     // pin connected to dht11

#define DHTTYPE DHT11   // DHT 11 is the sensor but it can be DHT2, DHT21 etc 

// Initialization of DHT sensor for 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

//const int pressureInput = A0; //select the analog input pin for the pressure transducer
//const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
//const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
//const int pressuretransducermaxPSI = 100; //psi value of transducer being used
//const int baudRate = 9600; //constant integer to set the baud rate for serial monitor
//const int sensorreadDelay = 250; //constant integer to set the sensor read delay in milliseconds

//float pressureValue = 0; //variable to store the value coming from the pressure transducer

void setup() {
  Serial.begin(9600); 
  Serial.println("DHT11 test!");
 
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds nekuti riri slow
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
}
