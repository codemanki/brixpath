#ifndef LEVELCHOOSERLEVEL_H
#define LEVELCHOOSERLEVEL_H


#include "scene.h"
#include "font.h"
#include "common.h"
#include "board.h"
#include "IwArray.h"
#include "levelbutton.h"
#include "levelsmanager.h"
#include "actionbutton.h"
#include "gamestatemanager.h"

class LevelChooseScene : public Scene   {
public:
    LevelChooseScene();
    virtual void                    touched(CTouch* touch);
    virtual void                    draw();
    virtual void                    capture();
    virtual void                    touchReleased(){}; //how not to override?
    
    CIwArray<LevelButton*>          _levelButtons;
    CIwArray<ActionButton*>         _menuButtons;
    Font                            _font;
private:
    void                            loadLevelGrid();
    void                            loadGraphics();
    void                            updateLevelButtons();
};


#endif


