#include "board.h"
#include <math.h>

// clears all vars and loads cells from Level
void Board::resetBoardAndLoadCells(Level* level){
    resetBoard(level->levelRows, level->levelColumns);
    
    IW_ARRAY_ITERATE_INT(i, level->cells){
        LevelCell* cell = level->cells[i];
        getCell(cell->y, cell->x)->setCellColor(cell->color)->setCellType(cell->type)->setPathId(cell->pathId);
    }
};

//Flushes all previous information about level, calculates
void Board::resetBoard(int rows, int columns)
{
    if(_cells.size() > 0)
        _cells.clear();
    
    _markAsComplete = false;
    _levelComplete = false;
    _rows = rows;
    _columns = columns;
    _propagateDragging = false;
    
    //calculate left top corner
    
    _cellWidth = 70;
    _cellHeight = 70;
    
    //Lets be agile :)
    if(_columns > 3)
        _cellWidth = 60;
    if(_columns > 6)
        _cellWidth = 50;
    
    if(_rows > 3)
        _cellHeight = 60;
    if(_rows > 6)
        _cellHeight = 50;
    
    calculateStartPoint();
    
    //Fill board with empty cells and position them properly
    for(int row = 0; row < _rows; row++){
        
        for(int column = 0; column < _columns; column++){
            
            BoardCell* cell = new BoardCell;
            int spacesX = column * SPACE_BETWEEN_CELLS;
            int spacesY = row * SPACE_BETWEEN_CELLS;
            
            cell->setCellType(NONE);
            
            cell->setCellPositionColumn(column);
            cell->setCellPositionRow(row);
            
            cell->setX(_x + spacesX + _cellWidth * column);
            cell->setY(_y + spacesY + _cellHeight * row);
            
            cell->setHeight(_cellHeight);
            cell->setWidth(_cellWidth);
            
            _cells.push_back(cell);
        }
    }
    

}

//Tries to position board as beautiful as possible. Position depends on number of cells horizontally and vertically
void Board::calculateStartPoint(){

    _width = _columns * (_cellWidth +  SPACE_BETWEEN_CELLS) - SPACE_BETWEEN_CELLS; //calculate border size
    _height = _rows * (_cellHeight +  SPACE_BETWEEN_CELLS) - SPACE_BETWEEN_CELLS;

    _x = (Iw2DGetSurfaceWidth()/2) - _width/2; //and position border in the center of screen
    _y = (Iw2DGetSurfaceHeight()/2) - _height/2;
};

BoardCell* Board::getCell(int row, int column){
    return _cells[row*_columns + column];
}

void Board::loadLevel(int levelId){
    _level = g_LevelsManager.loadLevel(levelId);
    
    resetBoardAndLoadCells(_level);
    
    buildCache();
};

//Very "smart" method. Gets all board paths into array only once, excludes repeats
void Board::buildCache(){
    if(_boardPaths.size() > 0)
        _boardPaths.clear();
    
    IW_ARRAY_ITERATE_INT(i, _cells){
        
        if(_cells[i]->getCellType() == PATH_START){
            bool insert = true;
            int id = _cells[i]->getPathId();
            
            IW_ARRAY_ITERATE_INT(j, _boardPaths){
                if(id == _boardPaths[j]){
                    insert = false;
                    break;
                }
            };

            if(insert){
                _boardPaths.push_back(id);
            }
        }
    }
};

void Board::drawBoard(){
    IW_ARRAY_ITERATE_INT(i, _cells){
        _cells[i]->draw();
    }
}

void Board::screenTouched(CTouch* touch){
    
    if(!touch->holding) {
        //start dragging
        IW_ARRAY_ITERATE_INT(i, _cells){
            
            if(_cells[i]->isHit(touch->x, touch->y)){
                BoardHelper::touchedCell(_cells[i], &_cells);
                
                _propagateDragging = true;
                _touchingCell = _cells[i]; //use is currently on this cell
                break;
            }
            
        }
    
    } else if (touch->holding && _propagateDragging){
        //continue dragging
        
        IW_ARRAY_ITERATE_INT(i, _cells){
            
            if(_cells[i]->isHit(touch->x, touch->y) && BoardHelper::canCellsBeJoined(_touchingCell, _cells[i])){
                //Connect cell where he was before he got to new one, and new one 
                BoardHelper::connectTwoCells(_touchingCell, _cells[i]);
                _touchingCell = _cells[i];
                break;
            }
        }
    }
    
    //Check for winning situation
    _markAsComplete = BoardHelper::isWinningSituation(&_cells, &_boardPaths);
    
    //See comment in screenReleased
    if(_markAsComplete){
        //Save level completion
        g_GameStateManager.markLevelAsComplete(_level->levelId);
    }
};

void Board::screenReleased(){
    if(_propagateDragging){
        _propagateDragging = false;
    };
    //This logic is used together with isWinningSituation.
    //Point of this, is not ot show message about victory before user releases screen. (it looks ugly)
    if(_markAsComplete){
        _markAsComplete = false;
        _levelComplete = true;
    }
};