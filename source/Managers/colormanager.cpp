#include "ColorManager.h"

ColorManager g_ColorManager;

void ColorManager::initialize(){
    
    if(!_colorsLoaded) {
        _whiteColor.Set(255, 255, 255);
        
        _blackColor.Set(0, 0, 0);
        
        _boardCellBorder.Set(199, 198, 194);
        
        _boardCellBackground.Set(238, 237, 232);
        
        _generalBackgroundColor.Set(245, 244, 239);
        
        _orangeColor.Set(240, 90, 56);
        
        _cyanColor.Set(2, 181, 204);
        
        _borderColor.Set(11, 9, 11);
        
        loadBoardColors();
        
        loadButtonColors();
    }
    
    _colorsLoaded = true;
};

void ColorManager::loadBoardColors(){
    _boardCellColors[COLOR_RED][NORMAL_COLOR].Set(202, 0, 60); // #CA003C
    _boardCellColors[COLOR_RED][FILL_COLOR].Set(147, 12, 46); // #930C2E
    
    _boardCellColors[COLOR_GREEN][NORMAL_COLOR].Set(65, 205, 84); // #41CD54
    _boardCellColors[COLOR_GREEN][FILL_COLOR].Set(48, 145, 59); // #30913B
    
    _boardCellColors[COLOR_BLUE][NORMAL_COLOR].Set(60, 149, 224);// #3C95E0
    _boardCellColors[COLOR_BLUE][FILL_COLOR].Set(41, 105, 158); // #29699E
    
    
    _boardCellColors[COLOR_BLUE2][NORMAL_COLOR].Set(51, 181, 229); // #33B5E5
    _boardCellColors[COLOR_BLUE2][FILL_COLOR].Set(0, 153, 204); // #0099CC
    
    _boardCellColors[COLOR_VIOLET][NORMAL_COLOR].Set(170, 102, 204); // #AA66CC
    _boardCellColors[COLOR_VIOLET][FILL_COLOR].Set(153, 51, 204);// #9933CC
     
    _boardCellColors[COLOR_GREEN2][NORMAL_COLOR].Set(153, 204, 0);// #99CC00
    _boardCellColors[COLOR_GREEN2][FILL_COLOR].Set(102, 153, 0);// #669900
    
    _boardCellColors[COLOR_YELLOW][NORMAL_COLOR].Set(255, 187, 51);// #FFBB33
    _boardCellColors[COLOR_YELLOW][FILL_COLOR].Set(255, 136, 0); //#FF8800
    
    _boardCellColors[COLOR_RED2][NORMAL_COLOR].Set(255, 68, 68); //#FF4444
    _boardCellColors[COLOR_RED2][FILL_COLOR].Set(204, 0, 0); //#CC0000
    
    _boardCellColors[COLOR_GREEN3][NORMAL_COLOR].Set(131, 175, 155); //#83AF9B
    _boardCellColors[COLOR_GREEN3][FILL_COLOR].Set(117, 157, 139); //#759D8B
};

void ColorManager::loadButtonColors(){
    _buttonColors[ORANGE_BUTTON][BACKGROUND_COLOR].Set(250, 105, 0);
    _buttonColors[ORANGE_BUTTON][SHADOW_COLOR].Set(224, 94, 0);
    
    _buttonColors[CYAN_BUTTON][BACKGROUND_COLOR].Set(105, 210, 231);
    _buttonColors[CYAN_BUTTON][SHADOW_COLOR].Set(94, 188, 207);
    
    _buttonColors[VIOLET_BUTTON][BACKGROUND_COLOR].Set(170, 102, 204);
    _buttonColors[VIOLET_BUTTON][SHADOW_COLOR].Set(153, 51, 204);
    
    _buttonColors[BLUE_BUTTON][BACKGROUND_COLOR].Set(60, 149, 224);
    _buttonColors[BLUE_BUTTON][SHADOW_COLOR].Set(41, 105, 158);

}
CIwColour ColorManager::getButtonColor(ButtonColor buttonColor, ButtonColorType buttonColorType){
    return _buttonColors[buttonColor][buttonColorType];
}
CIwColour ColorManager::getCellColor(BoardCellColor color, BoardCellColorType type) {
    return _boardCellColors[color][type];
};