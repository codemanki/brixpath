#include "Font.h"

void Font::setFont(int size){
    _fontSize = size;
    _font = g_FontManager.getFont(_fontSize);
};

void Font::setStartVector(CIwSVec2 xy){
    _xy = xy;
};

void Font::setSizeVector(CIwSVec2 size){
    _size = size;
};

void Font::setHorzAlign(CIw2DFontAlign horzAlign){
    _horzAlign  = horzAlign;
};

void Font::setVertAlign(CIw2DFontAlign vertAlign){
    _vertAlign = vertAlign;
};

void Font::resetFont(){
    setFont(8);
};

void Font::drawString(const string &text){
    Iw2DSetFont(_font);
    
    Iw2DDrawString(text.c_str(),
                   _xy, _size,
                   _horzAlign, _vertAlign);
};

//Method to quickly draw text with black color. Used for plain text everywhere
void Font::drawStringWithBlack(const string &text){
    Iw2DSetColour(g_ColorManager.getBlack());
    
    Iw2DSetFont(_font);
    
    Iw2DDrawString(text.c_str(),
                   _xy, _size,
                   _horzAlign, _vertAlign);
    
    g_ColorManager.resetColor();
};

//Method, returns number of pixels which passed string will take place using current font.
int Font::getTextWidth(const string &text){
    int width;
    
    Iw2DSetFont(_font);
    width = Iw2DGetStringWidth(text.c_str());
    resetFont(); //reset font, so it won't affect other labels
    
      return width;
};

Font::Font(){
    setHorzAlign(IW_2D_FONT_ALIGN_CENTRE);
    setVertAlign(IW_2D_FONT_ALIGN_CENTRE);
    resetFont();
}
