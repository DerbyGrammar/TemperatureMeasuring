/*
  Chris Nethercott
  Temperature Measuring
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Pin Nymbers
#define ONE_WIRE_BUS_PIN 6

//Library Stuff
OneWire oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature sensors(&oneWire);

//Sets the addresses for each probe on the one wire bus
DeviceAddress black_probe = { 0x28, 0xFF, 0x1A, 0xAA, 0x62, 0x15, 0x03, 0x20 }; //Black Address
DeviceAddress red_probe   = { 0x28, 0xFF, 0xA9, 0xB4, 0x62, 0x15, 0x03, 0x0C }; //Red Address
DeviceAddress green_probe = { 0x28, 0xFF, 0xF5, 0xB3, 0x62, 0x15, 0x03, 0x3E }; //Green Address

void setup()
{
  sensors.begin();
  sensors.setResolution(black_probe, 10);
  sensors.setResolution(red_probe, 10);
  sensors.setResolution(green_probe, 10);
}

void loop()
{
  //delay(delay_time);
  sensors.requestTemperatures();

  delay(2000);
  lcd.begin(16, 2);
  lcd.print("DGS Racing");
  lcd.setCursor(0, 1);
  lcd.print("Black = ");
  printTemperature(black_probe);

  delay(2000);
  lcd.clear();
  lcd.print("DGS Racing");
  lcd.setCursor(0, 1);
  lcd.print("Red   = ");
  printTemperature(red_probe);

  delay(2000);
  lcd.clear();
  lcd.print("DGS Racing");
  lcd.setCursor(0, 1);
  lcd.print("Green = ");
  printTemperature(green_probe);
}

void printTemperature(DeviceAddress deviceAddress)
{

  float tempC = sensors.getTempC(deviceAddress);

  if (tempC == -127.00)
  {
    lcd.print("Failed");
  }
  else
  {
    lcd.print(tempC);
  }
}

