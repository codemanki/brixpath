#ifndef CORE_H
#define CORE_H
//Instead of keeping code inside main.cpp, it is located here

#include "math.h"
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"
#include "IwGxFont.h"
#include "IwResManager.h"
#include "s3ePointer.h"
#include "s3eKeyboard.h"

#include "CInput.h"
#include "font.h"

#include "scene.h"

#include "levelsmanager.h"
#include "colormanager.h"
#include "gamestatemanager.h"
#include "scenesmanager.h"

struct AnimationOptions {
    int maxClicks; //how many clicks animation on screen to support
    int step; // animation speed, 3 pixels per time
    int limit; //width of animation rectangle. if more, rectangle dissapears
    int distance; //minimum distance between previous click and current, so current one will be drawn
};

//Describes animation for click :)
struct clickAnimation {
    int x;
    int y;
    int currentWidth;
};

class Brixpath {

public:
    Brixpath();
    ~Brixpath();
    
    void                            init();
    void                            loop();
    bool                            quitRequest(){return _gameStateData.switchToScene == CLOSE_APP;};
    void                            clean();
    
private:
    void                            drawBackgroundPattern();
    void                            customAnimation();
    void                            animateClick(CTouch *touch);
    void                            handleSceneSwitch();
    
    bool                            _holding; //is user holding finger
    
    Scene*                          _scene;
    CIw2DImage*                     _backgroundImage;
    
    GameStateData                   _gameStateData;
    CIwArray<clickAnimation>        _clicksToAnimate;
    AnimationOptions                _animationOptions;
    ScenesManager*                  _sceneManager;
};


#endif