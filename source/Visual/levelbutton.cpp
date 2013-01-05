#include "levelbutton.h"

void LevelButton::draw(){
    //draw body
    Iw2DSetColour(g_ColorManager.getBoardCellBorder());
    Iw2DDrawRect(CIwSVec2(getX(), getY()), CIwSVec2(getWidth(), getHeight()));
    
    g_ColorManager.resetColor();
    
    //fill either with gray or red (if level is completed)
    if(_completed)
        Iw2DSetColour(g_ColorManager.getCellColor(COLOR_RED, NORMAL_COLOR));
    else
        Iw2DSetColour(g_ColorManager.getBoardCellBackground());
    
    
    Iw2DFillRect(CIwSVec2(getX() + 1, getY() + 1), CIwSVec2(getWidth() - 1, getHeight() - 1));
    
    g_ColorManager.resetColor();
    
    if(_completed)
        Iw2DSetColour(g_ColorManager.getWhite());
    else
        Iw2DSetColour(g_ColorManager.getBlack());
    
    getFont()->setStartVector(CIwSVec2(getX() + getWidth()/20, getY() + getHeight()/20));
    
    getFont()->drawString(getText().c_str());
    
    g_ColorManager.resetColor();
};
