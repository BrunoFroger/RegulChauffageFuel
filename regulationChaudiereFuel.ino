//
//  Regulation chaudiere fuel
//
//  Created by    : Bruno FROGER
//  creation date : 2018-12-02
//
// Pour Arduino Nano
// processeur ATMega328P (old Bootloader)
//

#include <arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "variables.hpp"


SensorClass tempSensor;
//SensorClass consigne;
//SensorClass chaudiereSortie;
//SensorClass chaudiereRetour;
SensorClass tempExterieure;
Regulation regulation;
myDisplay display;

//*********************************************
//*
//*       S E T U P
//*
//*********************************************
void setup() {
  
  // initialize serial communication
  Serial.begin(38400);
  int timeoutInitSerial = 100;
  while (timeoutInitSerial-- > 0)
  {
    if (Serial)
      break;
    delay(10);
  }
  Serial.println("Serial initialized");

  tempSensor.init("tempInerieure",TEMPERATURE_PIN, TEMPERATURE_LOOP_DELAY,TEMPERATURE_NB_MOYENNE);
  //consigne.init(CONSIGNE_PIN, CONSIGNE_LOOP_DELAY, CONSIGNE_NB_MOYENNE);
  regulation.init();
  display.init();

}

//*********************************************
//*
//*       L O O P
//*
//*********************************************
void loop() {

  tempSensor.execute();
  //consigne.execute();
  regulation.execute();

  display.update();
  display.checkButton();

  delay(MAIN_LOOP_DELAY);
}


