#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "Iw2D.h"
#include "common.h"
#include "s3eSecureStorage.h"
#include "levelsmanager.h"

class GameStateManager{
    
public:
    void                    initialize();
    
    bool                    isLevelComplete(int levelId);
    void                    markLevelAsComplete(int levelId);
    
    void                    resetGameData();
    
    int                     getNextLevel(int level);
private:
    GameData                _gameData;
    
    void                    loadState();
    void                    saveState();
};

extern GameStateManager g_GameStateManager;

#endif