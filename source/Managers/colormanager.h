#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include "Iw2D.h"
#include "common.h"

class ColorManager{
    
public:
    void                        initialize();
    void                        resetColor(){ Iw2DSetColour(0xffffffff); };
    
    CIwColour                  getBoardCellBorder() {return _boardCellBorder;};
    CIwColour                  getWhite() {return _whiteColor; };
    CIwColour                  getBlack() {return _blackColor; };
    CIwColour                  getBoardCellBackground(){return _boardCellBackground;}
    CIwColour                  getGeneralBackgroundColor() {return _generalBackgroundColor; };
    CIwColour                  getOrangeColor() {return _orangeColor; };
    CIwColour                  getCyanColor() {return _cyanColor; };
    CIwColour                  getBorderColor() {return _borderColor; };
    CIwColour                  getCellColor(BoardCellColor color, BoardCellColorType type);
    CIwColour                  getButtonColor(ButtonColor buttonColor, ButtonColorType buttonColorType);
private:
    bool                        _colorsLoaded;
    CIwColour                   _whiteColor;
    CIwColour                   _blackColor;
    CIwColour                   _boardCellBorder;
    CIwColour                   _boardCellBackground;
    CIwColour                   _boardCellColors[15][2]; //TODO: somehow get rid of this 15 (right now board can have max 15 paths)
    CIwColour                   _buttonColors[5][2];
    CIwColour                   _generalBackgroundColor;
    CIwColour                   _orangeColor;
    CIwColour                   _cyanColor;
    CIwColour                   _borderColor;
    
    void                        loadBoardColors();
    void                        loadButtonColors();
};

//Global instance. EVIL. But singleton together with static contructors are not supported by compiler :(
extern ColorManager g_ColorManager;

#endif