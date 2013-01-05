#include "levelchoosescene.h"

#define LEVELS_PER_ROW 13

void LevelChooseScene::draw(){
    if(drawBackground()){
        
        IW_ARRAY_ITERATE_INT(i, _levelButtons){
            _levelButtons[i]->draw();
        }
        
        IW_ARRAY_ITERATE_INT(j, _menuButtons){
            _menuButtons[j]->draw();
        }
        
        Iw2DSetColour(g_ColorManager.getBlack());
        _font.drawString("Go ahead and choose a level to play:");
        g_ColorManager.resetColor();
    }
};

void LevelChooseScene::capture(){
    initBackground(DIAGONAL, 50, 50, 750, 500);
    updateLevelButtons();
};


LevelChooseScene::LevelChooseScene(){
    _font.setFont(16);
    _font.setStartVector(CIwSVec2(100, 80));
    _font.setSizeVector(CIwSVec2(600, 10));
    
    loadLevelGrid();
    loadGraphics();
    
    updateLevelButtons();
};

//Dump levels state and change buttons state
void LevelChooseScene::updateLevelButtons(){
    IW_ARRAY_ITERATE_INT(i, _levelButtons){
        LevelButton* levelbutton = _levelButtons[i];
        
        levelbutton->setCompleted(g_GameStateManager.isLevelComplete(levelbutton->getButtonId()));

    }
};


void LevelChooseScene::touched(CTouch *touch){
    ActionButton* button;
    IW_ARRAY_ITERATE_INT(i, _levelButtons){
        button = _levelButtons[i];
        if(button->isHit(touch->x, touch->y)){
            getGameState()->switchToScene = BOARD_SCENE;
            getGameState()->gameLevel = button->getButtonId();
        }
        
    }
    
    IW_ARRAY_ITERATE_INT(j, _menuButtons){
        button = _menuButtons[j];
        if(button->isHit(touch->x, touch->y)){
            if(button->getButtonId() == 0)
            {
                getGameState()->switchToScene = MAIN_MENU_SCENE;
            }
        }
        
    }
};

void LevelChooseScene::loadGraphics(){
    ActionButton* backButton = new ActionButton();
    
    backButton->setButtonId(0);
    backButton->setX(825);
    backButton->setY(200);
    backButton->setWidth(150);
    backButton->setHeight(60);
    backButton->setFontSize(16);
    backButton->setText("< Back");
    backButton->setColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, BACKGROUND_COLOR));
    backButton->setShadowColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, SHADOW_COLOR));
    
    _menuButtons.push_back(backButton);
};
void LevelChooseScene::loadLevelGrid(){
    int totalLevels = g_LevelsManager.totalLevels();
    int startingPositionX = 100;
    int startingPositionY = 150;
    int space = 10;
    int sizeX = 40;
    int sizeY = 40;
    LevelButton* levelButton;
    
    for(int i = 0; i < totalLevels; i++){
        int row = i / LEVELS_PER_ROW;
        int column = i % LEVELS_PER_ROW;
        int levelId = i + 1;
        
        int x = startingPositionX + ((column-1) * space) + column * sizeX;
        int y = startingPositionY + ((row-1) * space) + row * sizeY;

        char text[20];
        sprintf(text, "%i", levelId);
        
        levelButton = new LevelButton();
        levelButton->setButtonId(levelId);
        levelButton->setX(x);
        levelButton->setY(y);
        levelButton->setWidth(sizeX);
        levelButton->setHeight(sizeY);
        levelButton->setText(text);
        levelButton->setShadowOffset(0);
        _levelButtons.push_back(levelButton);
    }


}

