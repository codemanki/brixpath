#ifndef LEVELSMANAGER_H
#define LEVELSMANAGER_H

#include "s3e.h"
#include "IwArray.h"
#include "Iw2D.h"
#include "s3eFile.h"
#include "common.h"
#include "parson.h"
#include "boardhelper.h"
#include <string>
using namespace std;

class LevelsManager{
    
public:
    void                    initializeFromFile(const string &filename);
    int                     totalLevels() {return _totalLevels; };
    Level*                  loadLevel(int levelId);
    ~LevelsManager();
private:
    int                     _totalLevels;
    CIwArray<Level*>        _levels;
    
    JSON_Value*             _root_value;
    JSON_Array*             _jsonLevels;
    
    Level*                  getLevelFromCache(int levelId);
    Level*                  parseLevel(JSON_Object* level);
        
};

extern LevelsManager g_LevelsManager;

#endif