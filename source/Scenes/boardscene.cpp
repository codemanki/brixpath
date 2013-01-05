#include "boardscene.h"

void BoardScene::draw(){
    
    if(drawBackground()){
        
        IW_ARRAY_ITERATE_INT(i, _menuButtons){ 
            _menuButtons[i]->draw();   
        }
        
        //Check for level completeness
        isLevelComplete();

        board->drawBoard();
        
        _completeDialog->draw(); //dialog will detect if it is not visible.
    }

};

void BoardScene::isLevelComplete(){
    
    if(board->isLevelComplete()){
        //If current level is completed, detect next level and show dialog
        _completeDialog->setVisible(true);
        _nextLevelToLoad =g_GameStateManager.getNextLevel(getGameState()->gameLevel);
        _completeDialog->changeButtonVisibility(2, _nextLevelToLoad != -1); //if user successfully completed all levels, do not show Next level button
        
    }
    
};

void BoardScene::capture(){
    initBackground(DROPDOWN, 200, 50, 600, 500);
    
    board  = new Board;
    board->loadLevel(getGameState()->gameLevel);
};

BoardScene::BoardScene(){
    //Dialog which is shown, when user completes level
    _completeDialog = new Dialog();
    _completeDialog->setText("Level complete!");
    _completeDialog->addButton(0, "Next level");
    _completeDialog->addButton(1, "Level choose");
    
    loadGraphics();
};

void BoardScene::touchReleased(){
    board->screenReleased();
};

void BoardScene::touched(CTouch *touch){
    bool buttonTouched = false;

    //If completion dialog is visible, do not react on touches outside it
    if(_completeDialog->getVisible()){
        int buttonId = _completeDialog->isHit(touch->x,touch->y);
        
        if(buttonId != -1){
            buttonTouched = true;
            _completeDialog->setVisible(false);
        }
        
        switch (buttonId) {
            case 0:
                //Next level
                getGameState()->gameLevel = _nextLevelToLoad;
                board->loadLevel(_nextLevelToLoad);
                _nextLevelToLoad = -1;
                break;
                
            case 1:
                //Switch to choose level
                getGameState()->switchToScene = LEVEL_CHOOSE_SCENE;
                
                //Just to be sure, that we won't get into troubles, reset level
                getGameState()->gameLevel = -1;
                break;
                
        }
        
    }
    
    if(!buttonTouched && !_completeDialog->getVisible())
    {
        ActionButton* button;
        IW_ARRAY_ITERATE_INT(j, _menuButtons){
            button = _menuButtons[j];
            if(button->isHit(touch->x, touch->y)){
                buttonTouched = true;
                switch(button->getButtonId())
                {
                    case 0:
                        //Reset button pressed, simply reload level
                        board->loadLevel(getGameState()->gameLevel); 
                        break;
                    case 1:
                        //Back button pressed, return to Level choose.
                        getGameState()->switchToScene = LEVEL_CHOOSE_SCENE;
                        getGameState()->gameLevel = -1;
                        break;
                
                }
            }
        
        }
    }
    
    //No button was affected, pass touch to board
    if(!buttonTouched)
        board->screenTouched(touch);
    
};
void BoardScene::loadGraphics(){
    
    ActionButton* button = new ActionButton();
    
    button->setButtonId(0)
        ->setX(825)
        ->setY(100)
        ->setWidth(150)
        ->setHeight(60)
        ->setFontSize(16)
        ->setText("Restart")
        ->setColor(g_ColorManager.getButtonColor(BLUE_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(BLUE_BUTTON, SHADOW_COLOR));
    
    _menuButtons.push_back(button);
    
    button = new ActionButton();
    
    button->setButtonId(1)
        ->setX(825)
        ->setY(200)
        ->setWidth(150)
        ->setHeight(60)
        ->setFontSize(16)
        ->setText("< Back")
        ->setColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, SHADOW_COLOR));
    
    _menuButtons.push_back(button);
};