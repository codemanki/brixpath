#include "levelsmanager.h"

LevelsManager g_LevelsManager;

void LevelsManager::initializeFromFile(const string &filename){
    s3eFile* handle = s3eFileOpen(filename.c_str(), "rb");
    
    int filesize = s3eFileGetSize(handle);
    char* _readBuffer = new char[filesize];
    s3eFileRead(_readBuffer, filesize, 1, handle);
    s3eFileClose(handle);
    
    //load initial structure
    JSON_Object *main_object;
    _root_value = json_parse_string(_readBuffer);
    main_object = json_value_get_object(_root_value);
    _jsonLevels = json_object_dotget_array(main_object, "levels");
    _totalLevels = json_array_get_count(_jsonLevels);
    
};

//Method returns and caches level from json in order not to load json each time level is required
Level*  LevelsManager::loadLevel(int levelId){
    Level* level = getLevelFromCache(levelId);
    JSON_Object *jsonLevel;
    
    if(level != NULL){
        return level;
    }
    
    for (int j = 0; j < totalLevels(); j++) {
        jsonLevel = json_array_get_object(_jsonLevels, j);
        if(json_object_dotget_number(jsonLevel, "id") == levelId){
            level = parseLevel(jsonLevel);
            _levels.push_back(level);
        }
    }
    return level;
};

Level*  LevelsManager::getLevelFromCache(int levelId){
    IW_ARRAY_ITERATE_INT(i, _levels){
        if(_levels[i]->levelId == levelId){
            return _levels[i];
        }
    };
    
    return NULL;
};

Level* LevelsManager::parseLevel(JSON_Object* jsonLevel){
    Level* parsedLevel = new Level();
    JSON_Array* cells;
    JSON_Object* cell;
    
    
    cells = json_object_dotget_array(jsonLevel, "cells");
    
    //parse level settings such as id, number of rows and columns
    parsedLevel->levelId = (int)json_object_dotget_number(jsonLevel, "id");
    parsedLevel->levelRows = (int)json_object_dotget_number(jsonLevel, "rows");
    parsedLevel->levelColumns = (int)json_object_dotget_number(jsonLevel, "columns");
    
    for (unsigned j = 0; j < json_array_get_count(cells); j++) {
        
        LevelCell* levelCell = new LevelCell();
        cell = json_array_get_object(cells, j);
        
        levelCell->x = json_object_dotget_number(cell, "x");
        levelCell->y = json_object_dotget_number(cell, "y");
        levelCell->pathId = json_object_dotget_number(cell, "pathId");
        //parse
        levelCell->color = BoardHelper::getColorByPathId(levelCell->pathId);
        levelCell->type = BoardHelper::getTypeByString((char *)json_object_dotget_string(cell, "type"));
        
        parsedLevel->cells.push_back(levelCell);
    }
    
    return parsedLevel;
};

LevelsManager::~LevelsManager(){
    json_value_free(_root_value);
};