#ifndef BOARDSCENE_H
#define BOARDSCENE_H

#include "scene.h"
#include "common.h"
#include "board.h"
#include "dialog.h"
#include "actionbutton.h"

class BoardScene : public Scene   {
    Board*                          board;
public:
    BoardScene();
    virtual void                    touched(CTouch* touch);
    virtual void                    draw();
    virtual void                    capture();
    virtual void                    touchReleased();
private:
    void                            drawCell(bool filled, int x, int y, CIwColour* fillColour);
    void                            loadGraphics();
    void                            isLevelComplete();
    Dialog*                         _completeDialog;
    CIwArray<ActionButton*>         _menuButtons;
    int                             _nextLevelToLoad;
};


#endif


