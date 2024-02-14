#include <DHT.h>
#include <DHT_U.h>
#include "Adafruit_seesaw.h"
#include "Adafruit_Thermal.h"
//#include "adalogo.h"
//#include "adaqrcode.h"

#include "SoftwareSerial.h"
#define TX_PIN 6  // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 3  // Arduino receive   GREEN WIRE   labeled TX on printer

int numero = 1;

SoftwareSerial mySerial(RX_PIN, TX_PIN);  // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);

Adafruit_seesaw ss;

int light = 0;

#define DHTPIN 5

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  mySerial.begin(19200);
  printer.begin();

  Serial.println("seesaw Soil Sensor example!");

  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while (1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }

  dht.begin();
}

void loop() {
  light = analogRead(A0);
  delay(100);
  int temperature = dht.readTemperature();
  delay(100);
  int humidity = dht.readHumidity();
  delay(100);
  //float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);
  delay(100);

  //Serial.print()

  //printer.doubleHeightOn();
  printer.justify('L');
  printer.print("ID : "); printer.println(numero); 
  printer.print("\n");
  printer.justify('C');
  printer.inverseOn();

  printer.println(" Soil sensor ");
  printer.inverseOff();
  printer.justify('L');
  printer.print("Soil Temperature: "); printer.print(temperature); printer.println(" degrees");
  printer.print("Soil humidity: "); printer.println(capread); 
  printer.print("\n");
  printer.justify('C');
  printer.inverseOn();

  printer.println(" Light sensor ");
  printer.inverseOff();
  printer.justify('L');
  printer.print("Luminosity : "); printer.println(light); 
  printer.print("\n"); 
  printer.justify('C');
  printer.inverseOn();
  
  printer.println(" DHT sensor ");
  printer.inverseOff();
  printer.justify('L');
  printer.print("Temperature : "); printer.print(temperature); printer.println(" degrees");
  printer.print("Humidity : "); printer.println(humidity);
  printer.print("\n"); printer.println("/////////////////////////////");


  printer.sleep();      // Tell printer to sleep
  //delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault(); // Restore printer to defaults
  
  numero++;

  //delay(1000);
  delay(1800000);
}

