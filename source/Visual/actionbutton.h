#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include "common.h"
#include "Iw2D.h"
#include "font.h"
#include "colormanager.h"
#include <string>
using namespace std;

class ActionButton {
    Font                    _font; //Font used for label, also determined by _fontSize
    int                     _shadowOffset;
    int                     _buttonId; //Used for differing buttons
    int                     _x; // Top left corner coordinates
    int                     _y;
    int                     _width;
    int                     _height;
    int                     _fontSize;
    string                  _text;
    bool                    _pressed; //If button is pressed, shadow is not drawn and button slightly moves
    bool                    _visible; //In case button is not visible, it won't be drawn at all :)
    
    CIwColour               _color;
    CIwColour               _shadowColor;
    
public:
    ActionButton();
    void                    initialize();
    bool                    isHit(int x, int y);
    void                    draw();
    
    ActionButton*           setPressed(bool state) { _pressed = state; return this; };
    bool                    getPressed() { return _pressed; }; 
    
    ActionButton*           setShadowOffset(int shadowOffset){_shadowOffset = shadowOffset; return this; }
    int                     getShadowOffset(){return _shadowOffset;}
    
    ActionButton*           setButtonId(int buttonId){_buttonId = buttonId; return this; }
    int                     getButtonId(){return _buttonId;}
    
    ActionButton*           setX(int x){_x = x; return this; }
    int                     getX(){return _x;}
    
    ActionButton*           setY(int y){_y = y; return this; }
    int                     getY(){return _y;}
    
    ActionButton*           setWidth(int width){_width = width; initFont(); return this; } //font depends on button's width and height.
    int                     getWidth(){return _width;}
    
    ActionButton*           setHeight(int height){_height = height; initFont(); return this; }
    int                     getHeight(){return _height;}
    
    ActionButton*           setFontSize(int fontSize){_fontSize = fontSize; initFont(); return this; }
    int                     getFontSize(){return _fontSize;}
    
    ActionButton*           setText(const string &text){_text = text; return this; }
    string                  getText(){return _text;}
    
    ActionButton*           setColor(CIwColour color){_color = color; return this; }
    CIwColour              getColor(){return _color;}
    
    ActionButton*           setShadowColor(CIwColour shadowColor){_shadowColor = shadowColor; return this; }
    CIwColour              getShadowColor(){return _shadowColor;}
    
    Font*                   getFont(){return &_font;}
    
    ActionButton*           setVisible(int visible){_visible = visible; return this; }
    int                     getVisible(){return _visible;}
private:
    void initFont();
};

#endif


