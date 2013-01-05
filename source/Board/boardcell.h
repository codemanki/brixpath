#ifndef BOARDCELL_H
#define BOARDCELL_H

#include "Iw2D.h"
#include "colormanager.h"
#include "common.h"
#include "font.h"


class BoardCell  {
    
private:
    BoardCellConnection         _cellConnectionType;
    BoardCellType               _cellType;
    BoardCell*                  _inConnectionCell; //Which cell is parent to current?
    BoardCell*                  _outConnectionCell; //And current is connected to her child
    Font*                       _font;
    BoardCellColor              _cellColor;
    int                         _cellPositionColumn; //Coordinates on board
    int                         _cellPositionRow;
    int                         _pathId;
    int                         _x; //Coordinates on screen
    int                         _y;
    int                         _width;
    int                         _height;
    char                        _textBuffer[5]; //Path id
    
    //methods
    BoardCellConnection         calculateConnection(BoardCell *cellTo);
    void                        drawConnections(BoardCell* cell);
public:
    BoardCell();

    BoardCell*                  setInConnectionCell(BoardCell* _in){_inConnectionCell = _in; return this;}
    BoardCell*                  getInConnectionCell(){return _inConnectionCell;}
    
    
    BoardCell*                  setOutConnectionCell(BoardCell* _out){_outConnectionCell = _out; return this;}
    BoardCell*                  getOutConnectionCell(){return _outConnectionCell;}
    
    
    BoardCell*                  setCellPositionColumn(int column) { _cellPositionColumn = column; return this;}
    int                         getCellPositionColumn() {return _cellPositionColumn; }
    
    BoardCell*                  setCellPositionRow(int row) {_cellPositionRow = row; return this;}
    int                         getCellPositionRow() {return _cellPositionRow; }
    
                                //ugly way to do int2string conversion
    BoardCell*                  setPathId(int pathId) {_pathId = pathId; sprintf(_textBuffer, "%i", _pathId); return this;} 
    int                         getPathId() {return _pathId;}
    
    BoardCell*                  setCellType(BoardCellType _type) {_cellType = _type; return this;}
    BoardCellType               getCellType(){return _cellType;};
    
    BoardCell*                  setCellColor(BoardCellColor color) {_cellColor = color; return this;}
    BoardCellColor              getCellColor() {return _cellColor;}
    
    
    BoardCell*                  setX(int x) {_x = x; return this;}
    BoardCell*                  setY(int y) {_y = y; return this;}
    
    BoardCell*                  setWidth(int width) {_width = width; return this;}
    BoardCell*                  setHeight(int height) {_height = height; return this;}
    
    bool                        isHit(int x, int y);
    void                        resetCell(bool resetCurrent);
    void                        setUpInConnection(BoardCell* cell);
    void                        draw();
    
};

#endif
