#include "gamestatemanager.h"

GameStateManager g_GameStateManager;

void GameStateManager::loadState(){
    //try to read from s3storage
    s3eResult result = s3eSecureStorageGet(&_gameData, sizeof(_gameData));
    if(result == S3E_RESULT_ERROR){
        //if error occured, save empty results
        resetGameData();
    }
};

void GameStateManager::saveState(){
    s3eSecureStoragePut(&_gameData, sizeof(_gameData));
};

void GameStateManager::initialize(){
    loadState();
};

bool GameStateManager::isLevelComplete(int levelId){
    return _gameData.levelsBucket[levelId];
};

void GameStateManager::markLevelAsComplete(int levelId){
    //Look in first bucket only
    _gameData.levelsBucket[levelId] = true;
    saveState();
};

void GameStateManager::resetGameData(){
    _gameData = GameData();
    this->saveState();
};

int GameStateManager::getNextLevel(int level) {
    
    //find closest level to current from left or right
    int firstBefore = -1;
    int totalLevels = g_LevelsManager.totalLevels();
    
    for(int i = 1; i < totalLevels+1; i++){
        if(isLevelComplete(i))
            continue;
        
        if(i < level)
            firstBefore = i;
        
        if(i > level)
            return i;
    }
    
    return firstBefore;
};