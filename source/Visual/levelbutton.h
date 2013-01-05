#ifndef LEVELBUTTON_H
#define LEVELBUTTON_H


#include "common.h"
#include "Iw2D.h"
#include "font.h"
#include "colormanager.h"
#include "actionbutton.h"

class LevelButton: public ActionButton {
    bool                     _completed;
public:
    void                     draw();
    
    void                     setCompleted(bool completed) { _completed = completed; };
    bool                     isCompleted() { return _completed; };
};

#endif


