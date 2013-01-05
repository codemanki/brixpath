#include "boardcell.h"
#include <stdlib.h>

void BoardCell::draw() {
    //since only one font is used, magic numbers are used here :)
    _font->setStartVector(CIwSVec2(_x + 11, _y + 12));
    _font->setSizeVector(CIwSVec2(_width - 20, _height - 20));
    
    g_ColorManager.resetColor();

    //Draw border
    Iw2DSetColour(g_ColorManager.getBoardCellBorder());
    Iw2DDrawRect(CIwSVec2(_x, _y), CIwSVec2(_width, _height));
    g_ColorManager.resetColor();
    
    //If this is just empty cell, draw background
    if(getCellType() == NONE){
        // background
        Iw2DSetColour(g_ColorManager.getBoardCellBackground());
        Iw2DFillRect(CIwSVec2(_x + 1, _y + 1), CIwSVec2(_width - 1,_height - 1));
        g_ColorManager.resetColor();
    }
    
    //If this cell is connected or is a path start, we should fill it with appropriate color
    if(getCellType() == CONNECTED || getCellType() == PATH_START) {
        Iw2DSetColour(g_ColorManager.getCellColor(_cellColor, NORMAL_COLOR));
        Iw2DFillRect(CIwSVec2(_x + 1, _y + 1), CIwSVec2(_width - 1, _height - 1));
        g_ColorManager.resetColor();
    }
    
    //This is path start and it is connected to something (in and out are checked, because start path can be a head OR a tail of path)
    if(getCellType() == PATH_START || getInConnectionCell() != NULL || getOutConnectionCell() != NULL) {
        Iw2DSetColour(g_ColorManager.getCellColor(getCellColor(), FILL_COLOR));
        Iw2DFillRect(CIwSVec2(_x + _width/4, _y + _height/4), CIwSVec2(_width/2, _height/2));
        g_ColorManager.resetColor();
    }

    //Draw inner shadow, which looks like a path
    drawConnections(getInConnectionCell());
    drawConnections(getOutConnectionCell());
    
    //and draw path number on path start
    if(getCellType() == PATH_START && getPathId() > 0) {
        _font->drawString(_textBuffer);
    }
    
}
void BoardCell::drawConnections(BoardCell* cell){
    if(cell == NULL)
        return;
    
    Iw2DSetColour(g_ColorManager.getCellColor(getCellColor(), FILL_COLOR));
    
    //TODO:optimize this, so it won't be called each time
    BoardCellConnection connection = calculateConnection(cell);
    
    //TODO:REFACTOR THIS. This code gets info about to which neighbor current cell is connected and draw cute path
    switch (connection){
        case CONNECTION_RIGHT:
            Iw2DFillRect(CIwSVec2(_x + _width - _width/2, _y + _width/4), CIwSVec2(_width/2, _height/2));
            break;
            
        case CONNECTION_LEFT:
            Iw2DFillRect(CIwSVec2(_x + 1, _y + _height/4), CIwSVec2(_width/2, _height/2));
            break;
            
        case CONNECTION_DOWN:
            Iw2DFillRect(CIwSVec2(_x + _width/4, _y + _height/4), CIwSVec2(_width/2,_height - _height/4));
            break;
            
        case CONNECTION_TOP:
            Iw2DFillRect(CIwSVec2(_x + _width/4, _y + 1), CIwSVec2(_width/2, _height/4));
            break;
            
        default:
            break;
    }
    g_ColorManager.resetColor();
}

//By connectedTo cell, detect where is it located relatively to current cell
BoardCellConnection BoardCell::calculateConnection(BoardCell *cellTo){
    if(cellTo->getCellPositionRow() == this->getCellPositionRow()){
        //cellTo is located to left
        if(cellTo->getCellPositionColumn() < this->getCellPositionColumn())
            return CONNECTION_LEFT;
        else
            return CONNECTION_RIGHT;
    }
    
    if(cellTo->getCellPositionColumn() == this->getCellPositionColumn()){
        //cellTo is located to left
        if(cellTo->getCellPositionRow() < this->getCellPositionRow())
            return CONNECTION_TOP;
        else
            return CONNECTION_DOWN;
    }
    
    return CONNECTION_NONE;
}

BoardCell::BoardCell(){
    _font = new Font;
    _font->setFont(16);
    
    setPathId(0);
    setOutConnectionCell(NULL);
    setInConnectionCell(NULL);
}

bool BoardCell::isHit(int x, int y){
    return (x >= _x && x <= (_x + _width) && y >= _y && y <= (_y + _height));
}

//Smart way of resetting some values
void BoardCell::resetCell(bool resetCurrent = false){
    
    //This method is used, when user drags back, or for example clicks middle of the path.
    //Here we reset current cell and all child cells which are connected to this one.
    
    if(resetCurrent && getCellType() == CONNECTED){
        //This is just a regulare connected cell. Make it normal and disconnect from parent cell
        setCellType(NONE);
        setCellColor(COLOR_NONE);
        setPathId(0);
        setInConnectionCell(NULL);
    } else if (resetCurrent && getCellType() == PATH_START) {
        //For start path, we should not reset properties, only connections.
        if(getInConnectionCell() != NULL){
            setInConnectionCell(NULL);
        }
    }
    //And reset&disconnect all child cells
    if(getOutConnectionCell() != NULL){
        getOutConnectionCell()->resetCell(true);
        setOutConnectionCell(NULL);
    }

};
//This cell is just connected to some other. Passed in cell is the "parent"
void BoardCell::setUpInConnection(BoardCell* cell){
    resetCell(true);
    
    //Do not inherit properties if path_start
    if(getCellType() != PATH_START) {
        //Inherit color and path id, so we can connect it to parent cell
        setPathId(cell->getPathId());
        setCellType(CONNECTED);
        setCellColor(cell->getCellColor());
    }
    setInConnectionCell(cell);
}