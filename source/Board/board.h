#ifndef BOARD_H
#define BOARD_H

#include "IwArray.h"
#include "boardhelper.h"
#include "boardcell.h"
#include "CInput.h"
#include "levelsmanager.h"
#include "gamestatemanager.h"

class Board {
    
private:
    static const int        SPACE_BETWEEN_CELLS = 3; //in pixels :) 
    static const int        INITIAL_CELL_SIZE = 70;
    CIwArray<BoardCell*>    _cells; //all cells of board
    CIwArray<int>           _boardPaths; //cached array of all paths present right now on board
    int                     _cellWidth; //calculated size of cell. depends on total amount of cells
    int                     _cellHeight;
    int                     _rows;
    int                     _columns;
    int                     _x;
    int                     _y;
    int                     _width;
    int                     _height;
    bool                    _propagateDragging;
    BoardCell*              _touchingCell;
    bool                    _levelComplete;
    bool                    _markAsComplete;
    Level*                  _level;
    
    //methods
    void                    buildCache();
    void                    calculateStartPoint();
    void                    resetBoard(int rows, int columns);
    void                    resetBoardAndLoadCells(Level* level);
public:
    BoardCell*              getCell(int row, int column);
    void                    drawBoard();
    void                    loadLevel(int levelId);
    void                    screenTouched(CTouch* touch);
    void                    screenReleased();
    
    int                     getX(){return _x;}
    int                     getY(){return _y;}
    
    int                     getWidth(){return _width;}
    int                     getHeight(){return _height;}
    
    bool                    isLevelComplete(){ //one time flag. This logic prevents from unneeded loops
                                if(_levelComplete){
                                    _levelComplete = false;
                                    return true;
                                }
                                return false;
                            }
    
};

#endif