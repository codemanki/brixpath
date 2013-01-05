#include "actionbutton.h"

void ActionButton::initFont(){
    getFont()->setFont(getFontSize());
    getFont()->setSizeVector(CIwSVec2(getWidth(), getHeight()));
};


//Checks if button was hit. Considers shadow as well
bool ActionButton::isHit(int x, int y){
    return _visible && (x >= getX() && x <= (getX() + getWidth() + getShadowOffset()) && y >= getY() && y <= (getY() + getHeight() + getShadowOffset()));
};

void ActionButton::draw(){
    int x = getX();
    int y = getY();
    int width = getWidth();
    int height = getHeight();
    int shadowOffset = getShadowOffset();
    bool pressed = getPressed();
    
    if(!getVisible())
        return;
    
    if(!getPressed()){
        Iw2DSetColour(getShadowColor());
        
        //draw shadow
        Iw2DFillRect(CIwSVec2(x + shadowOffset, y + shadowOffset), CIwSVec2(width, height));
    }
    //draw button 
    Iw2DSetColour(getColor());
    Iw2DFillRect(pressed ? CIwSVec2(x + shadowOffset, y + shadowOffset) : CIwSVec2(x, y), CIwSVec2(width, height));
    
    g_ColorManager.resetColor();
    
    getFont()->setStartVector(pressed ? CIwSVec2(x + shadowOffset, y + shadowOffset) : CIwSVec2(x, y));
    
    //draw label
    getFont()->drawString(_text.c_str());
};


ActionButton::ActionButton(){
    setVisible(true);
    setPressed(false);
    setShadowOffset(5);
}