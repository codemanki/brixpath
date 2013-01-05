#ifndef FONT_H
#define FONT_H

#include "Iw2D.h"
#include "fontmanager.h"
#include "colormanager.h"
#include <string>

using namespace std;
class Font {
    
public:
    Font();
    void                            setFont(int size);
    void                            setStartVector(CIwSVec2 xy);
    void                            setSizeVector(CIwSVec2 size);
    void                            setHorzAlign(CIw2DFontAlign horzAlign);
    void                            setVertAlign(CIw2DFontAlign vertAlign);
    void                            drawString(const string &text);
    void                            drawStringWithBlack(const string &text);
    void                            resetFont();
    int                             getTextWidth(const string &text);
private:
    CIw2DFont*                      _font;
    int                             _fontSize;
    CIwSVec2                        _xy;
    CIwSVec2                        _size;
    CIw2DFontAlign                  _horzAlign;
    CIw2DFontAlign                  _vertAlign;
};


#endif