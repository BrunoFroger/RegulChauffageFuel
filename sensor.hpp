//
//      sensor.hpp
//


#ifndef __SENSOR
#define __SENSOR

#include <arduino.h>

class SensorClass{

public:
    SensorClass(void);
    void init(int inputPin, int loopDelay, int nbMoyenne);
    int getValue(void);
    int execute(void);
    void setLoopDelay(int);

private:
    int readValue(void);
    int calculeMoyenne(int valeur);

    int value;
    int loopDelay;
    int inputPin;
    int nbValMoyenne;
    int moyenne;
    int somme;
    long lastExecution=0;
};


#endif