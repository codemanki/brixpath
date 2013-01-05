#ifndef SETTINGS_H
#define SETTINGS_H

#include "scene.h"
#include "common.h"
#include "actionbutton.h"
#include "IwArray.h"
#include "gamestatemanager.h"

class SettingsScene : public Scene {
    
public:
    SettingsScene();
    virtual                         ~SettingsScene();
    
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


