
//  afficheur.hpp

#ifndef __AFFICHEUR_HPP
#define __AFFICHEUR_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class myDisplay
{
  public:
    myDisplay(void);
    ~myDisplay();
    void init(void);
    void update(void);
    void checkButton(void);
    
  private:

    Adafruit_SSD1306 display = Adafruit_SSD1306();
    int buttonIsPressed;
    int buttonPushDuration;
    long displayMode;
    //int displayModeNiv2;
    boolean buttonLongPressed;

    void displayValeurs(void);
    void displayBanniere(void);
    void displayConfig(void);
    //void displayModeEco(void);
    //void displayModeConfort(void);
    void MenuConfigureModes(void);
    void configureMode(int);
    char * affTemperature(int);
;};

#endif