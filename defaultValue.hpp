//
//   defaultValues.hpp
//



#ifndef __DEFAULT_VALUE
#define __DEFAULT_VALUE


//-----------------------------------------
//
// Simulation values
//
//-----------------------------------------
// uncomment next line for simulated version
//#define __SIMULATION 
// temperature exterieure provisoire       
#define TEMP_EXT            1000


//-----------------------------------------
//
// default values for main loop
//
//-----------------------------------------
#define MAIN_LOOP_DELAY   5
#define VERSION           "1.0"

//-----------------------------------------
//
//    default value for capteur de temperature
//
//-----------------------------------------
// broche sur laquelle est branché la sonde de temperature
#define TEMPERATURE_PIN    A0
// delay pour la boucle d'acquisition de la temperature
#ifdef __SIMULATION
    #define TEMPERATURE_LOOP_DELAY 4000
#else
    #define TEMPERATURE_LOOP_DELAY 500
#endif
// nombre de valeur pour calcul de la moyenne
#define TEMPERATURE_NB_MOYENNE  5
// temperatures extremes du capteurs de temperature
// correspondant a 0 et 1023 de la mesure analogique 
#define TEMPERATURE_MIN_CATEUR  -3272
#define TEMPERATURE_MAX_CATEUR  10035

//-----------------------------------------
//
//     default value for regulation
//
//-----------------------------------------
// delay pour la boucle de regulation
#ifdef __SIMULATION
    #define REGULATION_LOOP_DELAY   2000
#else
    #define REGULATION_LOOP_DELAY   200
#endif
// seuil de declencheemnt de la regulation en centiemes de degres
#define REGULATION_SEUIL    10
// coeficient multiplicatuer de la difference de temperature
#define REGULATION_COEF     1
// differents mode de regulation ECO ou CONFORT
#define MODE_ECO            0
#define MODE_CONFORT        1
// broche sur laquelle est branché le moteur
#define PIN_MOTOR           9

//-----------------------------------------
//
//     default values for display
//
//-----------------------------------------
// broche sur laquelle est branche le bouton
#define BUTTON_PIN          2
// seuil pour considerer qu'un appui sur un 
// bouton est long ou court en ms
#define DUREE_APPUI_LONG    300

#endif
