#include "scene.h"


Scene::Scene(){
    _animationStepX = 20;
    _animationStepY = 20;
};

void Scene::initBackground(BackgroundAnimationType type, int x, int y, int width, int height){
    _animationType = type;
    _animationX = x;
    _animationY = y;
    _animationReady = false;
    
    _animationHeight = height;
    _animationHeightCurrent = 0;
    _animationWidth = width;

    //background frame animation supports two effects, it can either "grow" from left top corner, or drop down
    switch (type){
    
        case DIAGONAL:
            _animationWidthCurrent = 0;
            break;
        case DROPDOWN:
            _animationWidthCurrent = width;
            break;
    };
    
    
};

bool Scene::drawBackground(){
    
    if(!_animationReady){
        //Step for frame animation. Increase corresponding coordinates
        int xDiff = _animationWidth - _animationWidthCurrent;
        int yDiff = _animationHeight - _animationHeightCurrent;

        _animationHeightCurrent += (yDiff > _animationStepY) ? _animationStepY : yDiff;
        
        if(_animationType == DIAGONAL){
            _animationWidthCurrent += (xDiff > _animationStepY) ? _animationStepY : xDiff;
        }
        
        _animationReady = _animationWidthCurrent >= _animationWidth && _animationHeightCurrent >= _animationHeight;
    }
    
    
    drawBackgroundBox(_animationX, _animationY, _animationWidthCurrent, _animationHeightCurrent);
    return _animationReady;
};

void Scene::drawBackgroundBox(int x, int y, int width, int height){
    //Most awful method in whole game :D
    //Draws many rectangles, each of them is smaller than previous, that is how frame is faked.
    
    int cyanWidth = 5;
    int orangeWidth = 8;
    int borderWidth = 2;
    int offsetCord = cyanWidth + borderWidth*2 + orangeWidth;
    int offsetSize = cyanWidth*2 + borderWidth*4 + orangeWidth*2;


    Iw2DSetColour(g_ColorManager.getBorderColor()); //border
    Iw2DFillRect(CIwSVec2(x - offsetCord, y - offsetCord), CIwSVec2(width + offsetSize, height + offsetSize));
    
    offsetCord-=borderWidth;
    offsetSize-=borderWidth*2;
    
    Iw2DSetColour(g_ColorManager.getOrangeColor()); //orange
    Iw2DFillRect(CIwSVec2(x - offsetCord, y - offsetCord), CIwSVec2(width + offsetSize, height + offsetSize));
    
    offsetCord-=orangeWidth;
    offsetSize-=orangeWidth*2;
    
    
    Iw2DSetColour(g_ColorManager.getBorderColor()); //border
    Iw2DFillRect(CIwSVec2(x - cyanWidth - borderWidth, y - cyanWidth - borderWidth), CIwSVec2(width + cyanWidth*2 + borderWidth*2, height + cyanWidth*2 + borderWidth*2));
    
    offsetCord-=borderWidth;
    offsetSize-=borderWidth*2;
    
    Iw2DSetColour(g_ColorManager.getCyanColor()); //cyan
    Iw2DFillRect(CIwSVec2(x - cyanWidth, y - cyanWidth), CIwSVec2(width + cyanWidth*2, height + cyanWidth*2));
    
    
    offsetCord-=cyanWidth;
    offsetSize-=cyanWidth*2;
    
    Iw2DSetColour(g_ColorManager.getGeneralBackgroundColor());
    Iw2DFillRect(CIwSVec2(x, y), CIwSVec2(width, height));
}