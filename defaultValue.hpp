//
//   defaultValues.hpp
//



#ifndef __DEFAULT_VALUE
#define __DEFAULT_VALUE

// default values for main loop
#define MAIN_LOOP_DELAY   5
#define VERSION           "1.0"

// default value for capteur de temperature
#define TEMPERATURE_PIN    A0
#define TEMPERATURE_LOOP_DELAY 50
#define TEMPERATURE_NB_MOYENNE  5
#define TEMPERATURE_MIN_CATEUR  0
#define TEMPERATURE_MAX_CATEUR  40

//default value for regulation
#define REGULATION_COMMANDE_CHAUFFAGE_PIN 9
#define REGULATION_SEUIL    10
#define REGULATION_COEF     100
#define MODE_ECO            0
#define MODE_CONFORT        1

//default values for display
#define BUTTON_PIN          2
#define DUREE_APPUI_LONG    300

#endif
