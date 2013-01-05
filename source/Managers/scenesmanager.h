#ifndef SCENESMANAGER_H
#define SCENESMANAGER_H

#include "common.h"

class BoardScene;
class HelpScene;
class LevelChooseScene;
class MainMenuScene;
class SettingsScene;
class Scene;

class ScenesManager{
public:
    ScenesManager(GameStateData* gameStateData);
    bool                            handleSceneSwitch(); //handles scene switch and returns boolean, if scene has changed
    Scene*                          getActiveScene(){return _activeScene;};
private:
    MainMenuScene*                  _mainMenuScene;
    LevelChooseScene*               _levelChooseScene;
    SettingsScene*                  _settingsScene;
    BoardScene*                     _boardScene;
    HelpScene*                      _helpScene;
    Scene*                          _activeScene;
    GameStateData*                   _gameStateData;
};
#endif