//
// regulation.hpp
//



#ifndef __REGULATION
#define __REGULATION

#include <arduino.h>
#include <Servo.h>
#include "defaultValue.hpp"

typedef struct {
    int consigne;
    String nom;
    char sens;
    int increment;
} modeData;

class Regulation{

public:
    Regulation(void);
    void init(void);
    void execute(void);
    int getCommandeChauffage(void);
    String getModeName(void);
    String getModeName(int);
    int getModeConsigne(void);
    int getModeConsigne(int);
    char getModeSens(int);
    int getModeIncrement(int);
    void switchMode(void);
    void switchModeSens(int);
    void switchModeIncrement(int);
    void modifyConsigne(int);

private:
    long lastExecution=0;
    int loopDelay;
    int valeurCommandeChauffage;
    int mode;
    modeData tblModes[2];
};


#endif
