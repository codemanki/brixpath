#ifndef MAINMENU_H
#define MAINMENU_H


#include "scene.h"
#include "common.h"
#include "actionbutton.h"
#include "gamestatemanager.h"
#include "levelsmanager.h"
#include "IwArray.h"

class MainMenuScene : public Scene   {
public:
    MainMenuScene();
    ~MainMenuScene();
    
    virtual void                    touched(CTouch* touch);
    virtual void                    draw();
    virtual void                    capture();
    virtual void                    touchReleased();

private:
    CIwArray<ActionButton*>         _buttons;
    CIw2DImage*                     _logo;
    
    void                            drawLogo();
    void                            drawButtons();
};


#endif


