#ifndef DIALOG_H
#define DIALOG_H


#include "Iw2D.h"
#include "IwArray.h"
#include "actionbutton.h"
#include "font.h"
#include <string>
using namespace std;

class Dialog {
public:
    Dialog();
    void                            setText(const string &text){_text = text;}
    string                          getText(){return _text;}
    
    void                            setSubText(const string &subText){_subText = subText;}
    string                          getSubText(){return _subText;}
    
    void                            setVisible(bool visible){_visible = visible;}
    bool                            getVisible(){return _visible;}
        
    void                            addButton(int buttonId, const string &text);
    int                             isHit(int x, int y); 
    void                            draw();
    void                            changeButtonVisibility(int buttonId, bool isVisible);
private:
    CIwArray<ActionButton*>         _buttons;
    string                          _text;
    string                          _subText;
    int                             _screenWidth;
    int                             _screenHeight;
    int                             _positionX;
    int                             _positionY;
    int                             _width;
    int                             _height;
    
    Font                            _font;
    Font                            _subFont;
    bool                            _visible;
    void                            recalculateValues();
};


#endif


