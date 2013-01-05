#ifndef COMMON_H
#define COMMON_H

#include "IwArray.h"
#include "Iw2D.h"
//Here many small entities are stored. I do not think it is reasonable to move each of them to separate file

enum BoardCellConnection { CONNECTION_TOP, CONNECTION_RIGHT, CONNECTION_DOWN, CONNECTION_LEFT, CONNECTION_NONE};
enum BoardCellType {NONE, CONNECTED, PATH_START};

enum BoardCellColor { COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_BLUE2, COLOR_VIOLET, COLOR_GREEN2,COLOR_YELLOW, COLOR_RED2, COLOR_GREEN3, COLOR_NONE };
enum BoardCellColorType {NORMAL_COLOR, FILL_COLOR};

enum Scenes {MAIN_MENU_SCENE, SETTINGS_SCENE, BOARD_SCENE, LEVEL_CHOOSE_SCENE, CLOSE_APP, HELP_SCENE};

enum ButtonColor {ORANGE_BUTTON, CYAN_BUTTON, VIOLET_BUTTON, BLUE_BUTTON};
enum ButtonColorType {BACKGROUND_COLOR, SHADOW_COLOR};

struct LevelCell {
    int                 x;
    int                 y;
    int                 pathId;
    BoardCellType       type;
    BoardCellColor      color;    
};

struct Level {
    int levelId;
    int levelRows;
    int levelColumns;
    CIwArray<LevelCell*> cells;
};

class GameData {
public:
    bool levelsBucket[500]; //The most stupid way, how to store levels progress :/
    bool levelsBucket2[500];
    bool levelsBucket3[500];
    
};

//Class which helps game to detect, which scene to show and which level is in game right now.
struct GameStateData {
    Scenes      currentScene;
    int         gameLevel;
    Scenes      switchToScene;
};

#endif