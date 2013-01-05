#ifndef _SCENE_H_
#define _SCENE_H_

#include "Iw2D.h"
#include "CInput.h"
#include "common.h"
#include "colormanager.h"

enum BackgroundAnimationType {DIAGONAL, DROPDOWN};

class Scene {
protected:
    Scene();
public:
    //virtual                         ~Scene();
    virtual void                    draw() = 0; // called in loop, scene draws its state
    virtual void                    capture() = 0; // when switching to scene, method is called to inform scene about it
    virtual void                    touched(CTouch* touch) = 0; // user touched screen, passing touch object
    virtual void                    touchReleased() = 0;
    
    void                            setState(GameStateData* gameState) {_gameState = gameState;};
    GameStateData*                  getGameState(){return _gameState;};
    
    void                            initBackground(BackgroundAnimationType type, int x, int y, int width, int height); //draw background frame
    bool                            drawBackground(); //draw frame; return true when frame animation is ended
private:
    //Background frame animation stuff
    BackgroundAnimationType         _animationType;
    int                             _animationX;
    int                             _animationY;
    int                             _animationWidth;
    int                             _animationHeight;
    int                             _animationWidthCurrent;
    int                             _animationHeightCurrent;
    int                             _animationReady;
    int                             _animationStepX;
    int                             _animationStepY;
    
    GameStateData*                  _gameState;
    void                            drawBackgroundBox(int x, int y, int width, int height);
};
#endif