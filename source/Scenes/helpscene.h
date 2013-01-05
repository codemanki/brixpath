#ifndef HELPSCENE_H
#define HELPSCENE_H

#include "scene.h"
#include "common.h"
#include "actionbutton.h"
#include "IwArray.h"
#include "font.h"
#include <string>
using namespace std;
class HelpScene : public Scene   {
public:
    HelpScene();
    virtual                         ~HelpScene();
    virtual void                    touched(CTouch* touch);
    virtual void                    draw();
    virtual void                    capture();
    virtual void                    touchReleased();
    
private:
    CIwArray<ActionButton*>         _buttons;
    string                          _helpText;
    Font                            _font;
    CIw2DImage*                     _logo;
    CIw2DImage*                     _helpImage;
    void                            drawLogo();
    void                            drawButtons();
    void                            drawContent();
};


#endif


