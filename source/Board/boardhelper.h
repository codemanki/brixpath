#ifndef BOARDHELPER_H
#define BOARDHELPER_H

#include "boardcell.h"


class BoardHelper{
    
private:
    static bool                    isPathComplete(BoardCell* cell);
public:
    static bool                    canCellsBeJoined(BoardCell* first, BoardCell* second);
    static void                    connectTwoCells(BoardCell* first, BoardCell* second);
    static void                    touchedCell(BoardCell* cell, CIwArray<BoardCell*>*    cells);
    static bool                    isWinningSituation(CIwArray<BoardCell*>* cells, CIwArray<int>* boardPaths);
    static BoardCellType           getTypeByString(char* type);
    static BoardCellColor          getColorByString(char* color);
    static BoardCellColor          getColorByPathId(int pathId);
};
#endif