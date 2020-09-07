#include "DHT.h"
#include "Wire.h" //allows communication over i2c devices

#define DHTPIN 2        // pin connected to dht11
#define DHTTYPE DHT11   // DHT 11 is the sensor but it can be DHT2, DHT21 etc 

int LED = 3;
int reed_switch = 4;
int reed_status;

 
// Initialization of DHT sensor for 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

const int pressureInput = A0; //select the analog input pin for the pressure transducer
const int pressureZero = 102.4; //analog reading of pressure transducer at 0psi
const int pressureMax = 921.6; //analog reading of pressure transducer at 100psi
const int pressuretransducermaxPSI = 100; //psi value of transducer being used
float pressureValue = 0; //variable to store the value coming from the pressure transducer

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(reed_switch, INPUT);
  Serial.begin(9600); 
  Serial.println("1, 2 testing!");
  dht.begin();
}

void loop() {

  reed_status = digitalRead(reed_switch);
  if (reed_status == 1){
    digitalWrite(LED, LOW);
    Serial.println("DOOR CLOSED");
  }
  else{
    digitalWrite(LED, HIGH);
    Serial.println("DOOR OPEN");
  }
  delay(1000);
  
  pressureValue = analogRead(pressureInput); //reads value from input pin and assigns to variable
  pressureValue = ((pressureValue-pressureZero)*pressuretransducermaxPSI)/(pressureMax-pressureZero); //conversion equation to convert analog reading to psi

  // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds nekuti riri slow
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  } 
  delay(2000);
  Serial.print("Pressure: "); //prints label
  Serial.print(pressureValue, 1); //prints pressure value to serial
  Serial.print("psi\n"); 
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\n");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C\n ");

  delay(250);
}
