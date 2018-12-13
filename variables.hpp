//
// variables.hpp
//



#ifndef __VARIABLES
#define __VARIABLES

#include "sensor.hpp"
#include "regulation.hpp"
#include "afficheur.hpp"
#include "defaultValue.hpp"

extern SensorClass tempSensor;
//extern SensorClass chaudiereSortie;
//extern SensorClass chaudiereRetour;
extern SensorClass tempExterieure;
extern Regulation regulation;
extern myDisplay display;

#endif