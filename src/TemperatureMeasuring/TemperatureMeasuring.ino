/*
  Chris Nethercott
  Temperature Measuring
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Pin Numbers
#define ONE_WIRE_BUS_PIN 6

//Library Stuff
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

//Sets the addresses for each probe on the one wire bus
DeviceAddress blackProbe = { 0x28, 0xFF, 0x1A, 0xAA, 0x62, 0x15, 0x03, 0x20 }; //Black Address
DeviceAddress redProbe   = { 0x28, 0xFF, 0xA9, 0xB4, 0x62, 0x15, 0x03, 0x0C }; //Red Address
DeviceAddress greenProbe = { 0x28, 0xFF, 0xF5, 0xB3, 0x62, 0x15, 0x03, 0x3E }; //Green Address

// Variables
int delayTime;

void setup() {
  sensors.begin();
  sensors.setResolution(blackProbe, 10);
  sensors.setResolution(redProbe, 10);
  sensors.setResolution(greenProbe, 10);

  delayTime = 2000;
}

void loop() {
  
  sensors.requestTemperatures();

  delay(delayTime);
  lcd.begin(16, 2);
  lcd.print("DGS Racing");
  lcd.setCursor(0, 1);
  lcd.print("Black = ");
  printTemperature(blackProbe);

  delay(delayTime);
  lcd.clear();
  lcd.print("DGS Racing");
  lcd.setCursor(0, 1);
  lcd.print("Red   = ");
  printTemperature(redProbe);

  delay(delayTime);
  lcd.clear();
  lcd.print("DGS Racing");
  lcd.setCursor(0, 1);
  lcd.print("Green = ");
  printTemperature(greenProbe);
}

void printTemperature(DeviceAddress deviceAddress) {

  float tempC = sensors.getTempC(deviceAddress);

  if (!tempC == -127.00) {
    lcd.print(tempC);
  }
  else {
    lcd.print("Error"); 
  }
}

