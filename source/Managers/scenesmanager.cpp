#include "scenesmanager.h"

#include "mainmenu.h"
#include "boardscene.h"
#include "levelchoosescene.h"
#include "settingsscene.h"
#include "helpscene.h"


ScenesManager::ScenesManager(GameStateData* gameStateData){
    _gameStateData = gameStateData;
    
    _mainMenuScene = new MainMenuScene();
    _levelChooseScene = new LevelChooseScene();
    _boardScene = new BoardScene();
    _helpScene = new HelpScene();
    _settingsScene = new SettingsScene();
    
    _mainMenuScene->setState(_gameStateData);
    _levelChooseScene->setState(_gameStateData);
    _boardScene->setState(_gameStateData);
    _helpScene->setState(_gameStateData);
    _settingsScene->setState(_gameStateData);
    
    _activeScene = _mainMenuScene;

};

bool ScenesManager::handleSceneSwitch(){
    if(_gameStateData->currentScene != _gameStateData->switchToScene){
        switch(_gameStateData->switchToScene){
            case MAIN_MENU_SCENE:
                _activeScene = _mainMenuScene;
                break;
                
            case LEVEL_CHOOSE_SCENE:
                _activeScene = _levelChooseScene;
                break;
            case BOARD_SCENE:
                _activeScene = _boardScene;
                break;
            case SETTINGS_SCENE:
                _activeScene = _settingsScene;
                break;
            case HELP_SCENE:
                _activeScene = _helpScene;
                break;
            default:
                break;
        }
        
        _activeScene->capture();
        
        _gameStateData->currentScene = _gameStateData->switchToScene;
        return true;
    }
    return false;
}