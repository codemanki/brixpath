#include "FontManager.h"
FontManager g_FontManager;

void FontManager::initialize(){
    g_FontManager._font_8 = Iw2DCreateFontResource("04B_8");
    g_FontManager._font_12 = Iw2DCreateFontResource("04B_12");
    g_FontManager._font_14 = Iw2DCreateFontResource("04B_14");
    g_FontManager._font_16 = Iw2DCreateFontResource("04B_16");
    g_FontManager._font_20 = Iw2DCreateFontResource("04B_20");
    g_FontManager._font_24 = Iw2DCreateFontResource("04B_24");
};


CIw2DFont* FontManager::getFont(int size){
    
    switch(size){
        default:
        case 8:
            return g_FontManager._font_8;
            break;
            
        case 12:
            return g_FontManager._font_12;
            break;
            
        case 14:
            return g_FontManager._font_14;
            break;
            
        case 16:
            return g_FontManager._font_16;
            break;
            
        case 20:
            return g_FontManager._font_20;
            break;
            
        case 24:
            return g_FontManager._font_24;
            break;
    }
    
};

FontManager::~FontManager(){
    delete _font_8;
    delete _font_12;
    delete _font_14;
    delete _font_16;
    delete _font_20;
    delete _font_24;
};