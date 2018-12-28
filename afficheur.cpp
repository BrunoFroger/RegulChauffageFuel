

//   afficheur.cpp

#include <arduino.h>
#include "variables.hpp"

//*********************************************
//*
//*       Constructor
//*
//*********************************************
myDisplay::myDisplay()
{
}

//*********************************************
//*
//*       Destructor
//*
//*********************************************
myDisplay::~myDisplay()
{
}

//*********************************************
//*
//*       afficheurInit
//*
//*********************************************
void myDisplay::init(void){
    //Serial.println("afficheur init : debut");
    // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

    display.setTextColor(WHITE);
    buttonIsPressed = 0;
    displayMode=0;
    //Serial.println("afficheur init : fin");
}

//*********************************************
//*
//*       checkButton
//*
//*********************************************
void myDisplay::checkButton(void){
    int stateButton = digitalRead(BUTTON_PIN);
    if (stateButton == 1 && buttonIsPressed == 0){
        // le bouton est appuyé
        buttonIsPressed = 1;
        buttonPushDuration=millis();
        //Serial.println("appui bouton");
    }else if (stateButton == 0 && buttonIsPressed == 1){
        //Serial.println("bouton relaché");
        buttonIsPressed = 0;
        buttonPushDuration= millis() - buttonPushDuration;
        if (buttonPushDuration >= DUREE_APPUI_LONG){
            buttonLongPressed = true;
            Serial.println("appui long");
        } else {
            buttonLongPressed = false;
            Serial.println("appui court");
        }
        //Serial.print("Duree appui : ");
        //Serial.println(buttonPushDuration);
        if (buttonLongPressed){
            // appui long on passe a la dizaine
            displayMode = 10 * displayMode + 1;
        } else{
            // appui long on incremente de 10
            displayMode++;
        }
        Serial.print("display mode : ");
        Serial.println(displayMode);
    }
}

char tmp[10];
//*********************************************
//*
//*       AffTemperature
//*
//*********************************************
char * myDisplay::affTemperature(int valeur){
    boolean negatif = false;
    if (valeur < 0){
        valeur = -valeur;
        negatif = true;
    }
    int tmp1 = valeur / 100;
    int tmp2 = valeur - (tmp1 * 100);
    if (negatif){
        sprintf(tmp,"-%d.%d",tmp1,tmp2);
    }else{
        sprintf(tmp,"%d.%d",tmp1,tmp2);
    }
    //Serial.println(tmp);
    return tmp;
}

//*********************************************
//*
//*       DisplayValeurs
//*
//*********************************************
void myDisplay::displayValeurs(void){
    display.clearDisplay();
    int valConsigne = regulation.getModeConsigne();
    String modeName = regulation.getModeName();
    int mesure = tempSensor.getValue();
    int difference = valConsigne - mesure;
    int cdeMoteur = regulation.getCommandeChauffage();

    display.setTextSize(1);

    display.setCursor(0,0);
    display.println("regulation chauffage");

    display.setCursor(0,8);
    display.print("mode ");
    display.print(modeName);

    display.print(" (");
    display.print(affTemperature(valConsigne));
    display.println(")");

    display.setCursor(0,16);
    display.print("mes  ");
    display.println(affTemperature(mesure));

    display.setCursor(64,16);
    display.print(" (");
    display.print(affTemperature(difference));
    display.println(")");

    display.setCursor(0,24);
    display.print("chauffage  ");
    display.print(cdeMoteur);

    display.println(" %");

    display.display();
}


//*********************************************
//*
//*       DisplayBanniere
//*
//*********************************************
void myDisplay::displayBanniere(void){
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(0,0);
    display.println("Regulation");

    display.setTextSize(1);
    display.setCursor(0,24);
    display.print("(c) B. Froger, (");
    display.print(VERSION);
    display.println(")");

    display.display();
}

//*********************************************
//*
//*       displayModeEco
//*
//*********************************************
/*void myDisplay::displayModeEco(void){
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Mode ECO");


    display.display();
}*/

//*********************************************
//*
//*       displayModeConfort
//*
//*********************************************
/*void myDisplay::displayModeConfort(void){
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Mode CONFORT");


    display.display();
}*/

//*********************************************
//*
//*       displayConfig
//*
//*********************************************
void myDisplay::displayConfig(void){
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Configuration");
    display.setCursor(0,8);
    if (displayMode == 31){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.print("Mode : ");
    display.println(regulation.getModeName());
    display.setCursor(0,16);
    if (displayMode == 32){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.println("Configure Modes");
    display.setCursor(0,24);
    if (displayMode == 33){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.println("retour");

    display.display();
}


//*********************************************
//*
//*       MenuConfigureModes
//*
//*********************************************
void myDisplay::MenuConfigureModes(void){
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Configuration");
    display.setCursor(0,8);
    if (displayMode == 321){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.println("Mode CONFORT");
    display.setCursor(0,16);
    if (displayMode == 322){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.println("Mode ECO");
    display.setCursor(0,24);
    if (displayMode == 323){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.println("retour");

    display.display();
}

//*********************************************
//*
//*       configureMode
//*
//*********************************************
void myDisplay::configureMode(int mode){
    display.clearDisplay();
    int consigne = regulation.getModeConsigne(mode);
    String nom = regulation.getModeName(mode);
    char sens = regulation.getModeSens(mode);
    int increment = regulation.getModeIncrement(mode);
    display.setTextSize(1);
    display.setCursor(0,0);
    if (displayMode == 3210){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.print("Mode ");
    display.println(nom);

    display.setCursor(0,8);
    if (displayMode == 3211){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.print("Consigne = ");
    display.println(consigne);

    display.setCursor(0,16);
    if (displayMode == 3212){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.print("sens ");
    display.println(sens);

    display.setCursor(0,24);
    if (displayMode == 3213){
        display.print("* ");
    }else{
        display.print("  ");
    }
    display.print("increment ");
    display.println(increment);

    display.display();
}

//*********************************************
//*
//*       update
//*
//*********************************************
void myDisplay::update(void){
    switch(displayMode){
        case 0 : // affichage de la banniere
            displayBanniere();
            displayMode=1;
            break;
        case 1 : // n'affiche rien si banniere affichee
            break;
        case 2 : // ecran des valeurs de regulation
            displayValeurs();
            break;
        //*********************************************
        // gestion du menu de configuration
        //*********************************************
        case 3 : // menu de configuration aucune ligne selectionnée
        case 31 : // menu de configuration ligne 1 selectionnnée
        case 32 : // menu de configuration ligne 2 selectionnnée
        case 33 : // menu de configuration ligne 3 selectionnnée
            displayConfig(); 
            break;
        case 34 : // en fin de menu configuration on repasse au debut
            displayMode = 31; // on repasse sur ligne 1 du menu
            break;
        case 311 : // appui long sur ligne 1 du menu de configuration (switch mode)
            // on switch la regulation du mode CONFORT (jour) au mode ECO (nuit)
            regulation.switchMode();
            displayMode=31;
            break;
        case 320 : // menu configuration des modes 
        case 321 : // menu configuration des modes ligne 1 selectionnée
        case 322 : // menu configuration des modes ligne 2  selectionnée
        case 323 : // menu configuration des modes ligne 3 selectionnée
            MenuConfigureModes();
            break;
        case 324 : // fin du menu de configuration des mode ; retour en ligne 1
            displayMode = 320;
            break;
        case 331 : // appui long sur retour dans menu configuration des modes
            displayMode=3;
            break;
        //*********************************************
        // gestion du menu parametrage CONFORT
        //*********************************************
        case 3210 : // menu configuration mode CONFORT 
        case 3211 : // menu configuration mode CONFORT ligne 1 selectionnée
        case 3212 : // menu configuration mode CONFORT ligne 2 selectionnée
        case 3213 : // menu configuration mode CONFORT ligne 3 selectionnée
            configureMode(MODE_CONFORT);
            break;
        case 32101 : // sortie du menu configuration mode CONFORT
            displayMode = 320;
            break;
        case 32111 : // increment ou decrement de la consigne CONFORT
            regulation.modifyConsigne(MODE_CONFORT);
            displayMode = 3211;
            break;
        case 32121 : // switch sens de progression des valeurs + <=> - du mode CONFORT
            regulation.switchModeSens(MODE_CONFORT);
            displayMode = 3212;
            break;
        case 32131 : // switch changement de l'increment du mode CONFORT
            regulation.switchModeIncrement(MODE_CONFORT);
            displayMode = 3213;
            break;
        case 3214 : // fin du menu configuration du mode CONFORT, on repasse en ligne 1
            displayMode = 3210;
            break;
        //*********************************************
        // gestion du menu parametrage ECO
        //*********************************************
        case 3220 : // menu configuration mode ECO 
        case 3221 : // menu configuration mode ECO ligne 1 selectionnée
        case 3222 : // menu configuration mode ECO ligne 2 selectionnée
        case 3223 : // menu configuration mode ECO ligne 3 selectionnée
            configureMode(MODE_ECO);
            break;
        case 32201 : // sortie du menu configuration mode ECO
            displayMode = 320;
            break;
        case 32211 : // increment ou decrement de la consigne
            regulation.modifyConsigne(MODE_ECO);
            displayMode = 3221;
            break;
        case 32221 : // switch sens de progression des valeurs + <=> - du mode ECO
            regulation.switchModeSens(MODE_ECO);
            displayMode = 3222;
            break;
        case 32231 : // switch changement de l'increment du mode ECO
            regulation.switchModeIncrement(MODE_ECO);
            displayMode = 3223;
            break;
        case 3224 : // fin du menu configuration du mode ECO, on repasse en ligne 1
            displayMode = 3220;
            break;
        default:
            Serial.print("Ecran inexistant : ");
            Serial.println(displayMode);
            displayMode=0;
    }
}


