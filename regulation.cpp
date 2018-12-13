//
// regulation.cpp
//


#include "regulation.hpp"
#include "sensor.hpp"
#include "variables.hpp"

#define REGULATION_LOOP_DELAY   1000

Servo moteur;

//*********************************************
//*
//*       Constructor
//*
//*********************************************
Regulation::Regulation(void){
}


//*********************************************
//*
//*       I N I T
//*
//*********************************************
void Regulation::init(void){
    Serial.println("Regulation init : debut");
    loopDelay = REGULATION_LOOP_DELAY;
    moteur.attach(REGULATION_COMMANDE_CHAUFFAGE_PIN);
    mode = MODE_CONFORT;
    tblModes[MODE_CONFORT].consigne=2000;
    tblModes[MODE_CONFORT].nom="CONFORT";
    tblModes[MODE_CONFORT].sens='+';
    tblModes[MODE_CONFORT].increment=1;
    tblModes[MODE_ECO].consigne=1700;
    tblModes[MODE_ECO].nom="ECO";
    tblModes[MODE_ECO].sens='+';
    tblModes[MODE_ECO].increment=1;
    Serial.println("Regulation init : fin");
}

//*********************************************
//*
//*       getCommandeChauffage
//*
//*********************************************
int Regulation::getCommandeChauffage(void){
    return valeurCommandeChauffage;
}

//*********************************************
//*
//*       getModeName
//*
//*********************************************
String Regulation::getModeName(void){
    return tblModes[mode].nom;
}

//*********************************************
//*
//*       getModeName
//*
//*********************************************
String Regulation::getModeName(int mode){
    return tblModes[mode].nom;
}

//*********************************************
//*
//*       getModeSens
//*
//*********************************************
char Regulation::getModeSens(int mode){
    return tblModes[mode].sens;
}

//*********************************************
//*
//*       getModeincrement
//*
//*********************************************
int Regulation::getModeIncrement(int mode){
    return tblModes[mode].increment;
}

//*********************************************
//*
//*       getModeConsigne
//*
//*********************************************
int Regulation::getModeConsigne(int mode){
    return tblModes[mode].consigne;
}

//*********************************************
//*
//*       getModeConsigne
//*
//*********************************************
int Regulation::getModeConsigne(void){
    return tblModes[mode].consigne;
}

//*********************************************
//*
//*       switchMode
//*
//*********************************************
void Regulation::switchMode(void){
    if (mode == MODE_CONFORT){
        mode = MODE_ECO;
    }else{
        mode = MODE_CONFORT;
    }
    return mode;
}

//*********************************************
//*
//*       switchModeSens
//*
//*********************************************
void Regulation::switchModeSens(int mode){
    if (tblModes[mode].sens == '+'){
        tblModes[mode].sens = '-';
    }else{
        tblModes[mode].sens = '+';
    }
}

//*********************************************
//*
//*       switchModeIncrement
//*
//*********************************************
void Regulation::switchModeIncrement(int mode){
    switch (tblModes[mode].increment){
        case 1 :
            tblModes[mode].increment = 2;
            break;
        case 2 :
            tblModes[mode].increment = 5;
            break;
        case 5 :
            tblModes[mode].increment = 10;
            break;
        case 10 :
            tblModes[mode].increment = 1;
            break;
    }
}

//*********************************************
//*
//*       modifyConsigne
//*
//*********************************************
void Regulation::modifyConsigne(int mode){
    if (tblModes[mode].sens == '+'){
        tblModes[mode].consigne += tblModes[mode].increment;
    }else{
        tblModes[mode].consigne -= tblModes[mode].increment;
    }
    Serial.print("Nouvelle consigne => ");
    Serial.println(tblModes[mode].consigne);
}

//*********************************************
//*
//*       execute
//*
//*********************************************
void Regulation::execute(void){
    long tmpTimestamp=millis();

    if (tmpTimestamp > (lastExecution + loopDelay)){
        // recuperation de la consigne
        int valConsigne = getModeConsigne();
        // recuperation de la mesure
        int tempMesuree = tempSensor.getValue();
        // calcul de la regulation
        int difference = valConsigne - tempMesuree;
        int delta = abs(difference);
        if (delta > REGULATION_SEUIL){
            // il faut reguler
            valeurCommandeChauffage += difference / REGULATION_COEF;
            if (valeurCommandeChauffage <= 0){
                valeurCommandeChauffage = 0;
            } else if (valeurCommandeChauffage >= 100){
                valeurCommandeChauffage = 100;
            }
            // modifier la position de la commande de chauffage
            // le moteur varie entre 0 et 180 degres
            int tmp = map(valeurCommandeChauffage,0,100,0,180);
            moteur.write(tmp);
            //Serial.print("commande chauffage => ");
            //Serial.println(tmp);
            //analogWrite(REGULATION_COMMANDE_CHAUFFAGE_PIN,valeurCommandeChauffage);
        }
    }
}


