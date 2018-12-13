//
//  sensor.cpp
//

#include "sensor.hpp"
#include "defaultValue.hpp"

//*********************************************
//*
//*       Constructor
//*
//*********************************************
SensorClass::SensorClass(void){
}

//*********************************************
//*
//*       init
//*
//*********************************************
void SensorClass::init(int sensorPin, int loopDelay, int nbMoyenne){
    Serial.println("SensorClass init : debut");

    this->inputPin = sensorPin;
    this->loopDelay = loopDelay;
    this->nbValMoyenne = nbMoyenne;

    Serial.println("SensorClass init : fin");
}

//*********************************************
//*
//*       readValue
//*
//*********************************************
int SensorClass::readValue(void){
    return analogRead(this->inputPin);
}

//*********************************************
//*
//*       getValue
//*
//*********************************************
int SensorClass::getValue(void){
    // les limites de mesure du capteur sont definies dans defaultValue.hpp
    return map(this->value,0,1023,TEMPERATURE_MIN_CATEUR*100,TEMPERATURE_MAX_CATEUR*100);
}

//*********************************************
//*
//*       execute
//*
//*********************************************
int SensorClass::execute(void){
    long tmpTimestamp=millis();

    if (tmpTimestamp > (lastExecution + loopDelay)){
        value = calculeMoyenne(readValue());
        //Serial.print("Temperature ambiante : ");
        //Serial.println(value);
    }
}

//*********************************************
//*
//*       calculeMoyenne
//*
//*********************************************
int SensorClass::calculeMoyenne(int valeur){
    somme = somme - moyenne + valeur;
    moyenne = somme / nbValMoyenne;
    return moyenne;
}

