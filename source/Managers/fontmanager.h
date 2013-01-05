#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "Iw2D.h"
 
//Because of resourse arhitecture, we cannot just determine 1 font and use any size. in brixpath.group every pair of font+size should be defined separately
class FontManager{
    
public:
    void                             initialize();
    CIw2DFont*                       getFont(int size);
    ~FontManager();
private:
    bool                             _fontsLoaded;
    CIw2DFont*                       _font_8;
    CIw2DFont*                       _font_12;
    CIw2DFont*                       _font_14;
    CIw2DFont*                       _font_16;
    CIw2DFont*                       _font_20;
    CIw2DFont*                       _font_24; 
};

extern FontManager g_FontManager;

#endif