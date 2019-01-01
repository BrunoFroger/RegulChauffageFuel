//
//  sensor.cpp
//

#include <stdio.h>
#include "sensor.hpp"
#include "defaultValue.hpp"
#include "variables.hpp"
#include "simulation.hpp"

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
void SensorClass::init(String nom, int sensorPin, int loopDelay, int nbMoyenne){
    //Serial.println("SensorClass init : debut");

    this->inputPin = sensorPin;
    this->loopDelay = loopDelay;
    this->nbValMoyenne = nbMoyenne;
    this->name = nom;

    //Serial.println("SensorClass init : fin");
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
    #ifdef __SIMULATION
        // return the simulated value
        return getSimulatedValue();
    #else
        // les limites de mesure du capteur sont definies dans defaultValue.hpp
        return map(this->value,0,1023,TEMPERATURE_MIN_CATEUR,TEMPERATURE_MAX_CATEUR);
    #endif
}

//*********************************************
//*
//*       execute
//*
//*********************************************
int SensorClass::execute(void){
    long tmpTimestamp=millis();

    if (tmpTimestamp > (lastExecution + loopDelay)){
        lastExecution=tmpTimestamp;
        //Serial.println("###################");
        //Serial.println("mesure temperature");
        this->value = calculeMoyenne(readValue());
        //Serial.print("Temperature ambiante : ");
        //Serial.println(value);
        //Serial.println("###################");
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

