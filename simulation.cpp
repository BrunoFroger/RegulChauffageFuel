//
// simulation.cpp
//

#include "defaultValue.hpp"

#ifdef __SIMULATION

#include "sensor.hpp"
#include "variables.hpp"
#include "regulation.hpp"

int sensorValue=1800;
//*********************************************
//*
//*       getSimulatedValue
//*
//*********************************************
int getSimulatedValue(void){

    // algorithme provisoire de simulation de la mesure
    // - le potentiometre simulera la temperature exterieure
    // - la valeur mesuree est calculée en fonction de 
    //      - la commande de chauffage (augmente la temperature)
    //      - la temperature exterieure (dimunue la temperature)

    // calcul en fonction de la temperature exterieure
    int tempExterieure = 1000;
    int differenceExt, variationExt;
    int cdeChauffage = regulation.getCommandeChauffage();
    boolean useExtTemp = true;
    differenceExt = tempExterieure - sensorValue;
    if (useExtTemp){
        variationExt =  differenceExt / 20;
    } else {
        variationExt = 0;
    }

    // calcul en fonction de la consigne
    int consigne = regulation.getModeConsigne();
    int differenceCons, variationCons;
    //consigne = map(consigne,0,4000,0,1023);
    boolean useConsigne = true;
    differenceCons = consigne - sensorValue;
    if (useConsigne){
        variationCons = differenceCons / 5;
    }else{
        variationCons = 0;
    }

    // calcul de la variatin due au chauffage
    int variationChauffage = cdeChauffage / 1;

    // calcule de la variation globale
    int variation = variationExt + variationChauffage + variationCons;

    // affiahge des valeurs calculees
    Serial.println("--- get sensor --");
    Serial.print("Ext mes  = ");
    Serial.print(tempExterieure);
    Serial.print(" ; diff ext   = ");
    Serial.print(differenceExt);
    Serial.print(" ; var ext  = ");
    Serial.println(variationExt);

    Serial.print("Consigne    = ");
    Serial.print(consigne);
    Serial.print(" ; diff cons = ");
    Serial.print(differenceCons);
    Serial.print(" ; var cons = ");
    Serial.println(variationCons);

    Serial.print("cde chauffage = ");
    Serial.print(cdeChauffage);
    Serial.print(" ; var chauffage = ");
    Serial.println(variationChauffage);

    Serial.print("Ancienne valeur = ");
    Serial.print(sensorValue);
    sensorValue += variation;
    Serial.print(" ; Variation globale = ");
    Serial.print(variation);
    Serial.print(" ; nouvelle valeur = ");
    Serial.println(sensorValue);

    Serial.println("-----------------");
    return sensorValue;
}


#endif