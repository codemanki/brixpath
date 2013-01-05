#include "boardhelper.h"
#include <math.h>

/*When user moves finger on screen from one cell to another, this method detect if those two cells can be connected. Uses couple simple rules:

 1. Same cell can not be connect to itself. Used for preventing loop connections.
 2. Only up+down or left-right neighbor cells can be joined.
 3. No paths intersection.
 4. User can move finger from cells 1 to 2. And then move it back from 2 to 1. In this case, this is allowed. This logic will be detected and no loop will occure.
 5. No loop could be in the path. 
 6. User cannot connect empty cell to another. Only vice versa.
 */
bool BoardHelper::canCellsBeJoined(BoardCell* first, BoardCell* second){
    int fX = first->getCellPositionColumn();
    int fY = first->getCellPositionRow();
    
    int sX = second->getCellPositionColumn();
    int sY = second->getCellPositionRow();
    
    int firstPathId = first->getPathId();
    int secondPathId = second->getPathId();
    
    BoardCell* traverse = first;
    
    //same cell couldn't not be connected
    if(first == second)
        return false;
    
    //First, check coordinates. Cells cannot be joined on diagonal
    if(ABS(fX-sX) > 1 || ABS(fY-sY) > 1 ||  (fX != sX &&  fY != sY) ){
        return false;
    }
    
    ///cannot connect cells with different paths
    if(secondPathId> 0 && secondPathId  !=  firstPathId )
        return false;
    
    ///special case, when user drags backwards, so first inconnection equals second
    if(first->getInConnectionCell() == second)
        
        return true;
    
    //exclude cycles, this check is probably overriden by "cannot connect cells with different paths" guard, but keep for now
    while(traverse->getInConnectionCell() != NULL){
        if(traverse->getInConnectionCell() == second) //we got cycle
            return false;
        else if (traverse->getCellType() == PATH_START) // ooops, we have one more pathstart in chain. 
            return false;
        else
            traverse = traverse->getInConnectionCell();
    }
    
    if(first->getCellType() == NONE)
        return false;
    
    return true;
};

void BoardHelper::connectTwoCells(BoardCell* first, BoardCell* second){
    //if user moves backwards:
    if(first->getInConnectionCell() == second){
        second->resetCell(false);
    } else {
        first->setOutConnectionCell(second);
        
        second->resetCell(false);
        second->setUpInConnection(first);
    }
    

};

void BoardHelper::touchedCell(BoardCell* cell, CIwArray<BoardCell*>* cells){
    //Check special situation.
    if(cell->getCellType() == PATH_START){
        
        //start dragging
        IW_ARRAY_ITERATE_INT(i, *cells){
            BoardCell* currentCell = (*cells)[i];
            //if we are clicking on path_start, we should terminate all existing paths (with same id)
            if(currentCell->getCellType() == PATH_START && currentCell != cell && currentCell->getPathId() == cell->getPathId()){
                currentCell->resetCell(false);
            }

        }
        
    }
    cell->resetCell(false);
};

/*
 Checks if level is completed:
 1. There should be NO empty (NONE) cells on board.
 2. All Path starts should be connected to each other.
 */
bool BoardHelper::isWinningSituation(CIwArray<BoardCell*>* cells, CIwArray<int>* boardPaths){
    CIwArray<int> completedPaths;
    
    //No NONE cells
    IW_ARRAY_ITERATE_INT(i, *cells){
        if((*cells)[i]->getCellType() == NONE)
            return false;
        
    }
    //Get all path starts and see if they are connected to each other.
    IW_ARRAY_ITERATE_INT(j, *cells){
        BoardCell* c = (*cells)[j];
        if(c->getCellType() == PATH_START && !completedPaths.contains(c->getPathId())){ 
            if(BoardHelper::isPathComplete(c)) {
                completedPaths.push_back(c->getPathId());
            }
        }
    }
    
    return (completedPaths.size() == (*boardPaths).size());
};
//Method takes cell (path start) and figures out is it connected to other path start, (is it hea dor tail of path) with same id.
bool BoardHelper::isPathComplete(BoardCell* cell){
    
    bool moveOut = (cell->getOutConnectionCell() != NULL);
    BoardCell* traverse = moveOut ? cell->getOutConnectionCell() : cell->getOutConnectionCell(); //in which direction to traverse.
    
    while(traverse != NULL){
        if (traverse->getCellType() == PATH_START && traverse->getPathId() == cell->getPathId())
            return true;
        else
            traverse = moveOut ? traverse->getOutConnectionCell() : traverse->getOutConnectionCell() ;
    }
    
    return false;
        
};

//Used for JSON parsing.
BoardCellType BoardHelper::getTypeByString(char* type){
    if(strcmp(type, "CONNECTED") == 0)
        return CONNECTED;
    
    if(strcmp(type, "PATH_START") == 0)
        return PATH_START;
    
    return NONE;
};

//Right now path id has always the same color. Used for JSON parsing.
BoardCellColor BoardHelper::getColorByPathId(int pathId){
    switch (pathId){
        case 1:
            return COLOR_RED;
            break;
        case 2:
            return COLOR_BLUE;
            break;
        case 3:
            return COLOR_GREEN;
            break;
        case 4:
            return COLOR_BLUE2;
            break;
        case 5:
            return COLOR_VIOLET;
            break;
        case 6:
            return COLOR_GREEN2;
            break;
        case 7:
            return COLOR_YELLOW;
            break;
        case 8:
            return COLOR_RED2;
            break;
        case 9:
            return COLOR_GREEN3;
            break;
    }
    
    return COLOR_NONE;
};

