#include "mainmenu.h"

void MainMenuScene::draw(){
    
    drawLogo();
    
    if(drawBackground())
    {
        drawButtons();
    }
    
};

void MainMenuScene::capture(){
    initBackground(DIAGONAL, 200, 160, 600, 400);
};

MainMenuScene::MainMenuScene(){

    _logo = Iw2DCreateImageResource("logo");
    //create buttons
    
    ActionButton* button = new ActionButton();
    button->setButtonId(0)
        ->setX(400)
        ->setY(175)
        ->setWidth(200)
        ->setHeight(60)
        ->setFontSize(20)
        ->setText("Play")
        ->setColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, SHADOW_COLOR));
    
    _buttons.push_back(button);

    button = new ActionButton();
    button->setButtonId(1)
        ->setX(400)
        ->setY(275)
        ->setWidth(200)
        ->setHeight(60)
        ->setFontSize(20)
        ->setText("Help")
        ->setColor(g_ColorManager.getButtonColor(CYAN_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(CYAN_BUTTON, SHADOW_COLOR));

    _buttons.push_back(button);
    
    button = new ActionButton();
    button->setButtonId(2)
        ->setX(400)
        ->setY(375)
        ->setWidth(200)
        ->setHeight(60)
        ->setFontSize(20)
        ->setText("Settings")
        ->setColor(g_ColorManager.getButtonColor(VIOLET_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(VIOLET_BUTTON, SHADOW_COLOR));
    
    _buttons.push_back(button);
    
    button = new ActionButton();
    button->setButtonId(3)
        ->setX(400)
        ->setY(475)
        ->setWidth(200)
        ->setHeight(60)
        ->setFontSize(20)
        ->setText("Quit")
        ->setColor(g_ColorManager.getButtonColor(BLUE_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(BLUE_BUTTON, SHADOW_COLOR));
    
    _buttons.push_back(button);
};

void MainMenuScene::touchReleased(){
    
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        if(!button->getPressed())
            continue;

        switch(button->getButtonId() ){
            case 0:
                getGameState()->switchToScene = LEVEL_CHOOSE_SCENE;
            break;
                
            case 1:
                getGameState()->switchToScene = HELP_SCENE;
            break;
                
            case 2:
                getGameState()->switchToScene = SETTINGS_SCENE;
            break;
                
            case 3:
                getGameState()->switchToScene = CLOSE_APP;
            break;
        }

        button->setPressed(false);
    }

};

void MainMenuScene::touched(CTouch *touch){
    
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        button->setPressed(button->isHit(touch->x, touch->y));
    }
    
};

void MainMenuScene::drawLogo(){
    Iw2DDrawImage(_logo, CIwSVec2(270, 10));
};

void MainMenuScene::drawButtons(){
    
    IW_ARRAY_ITERATE_INT(i, _buttons){
        _buttons[i]->draw();
    }
    
};

MainMenuScene::~MainMenuScene(){
    delete _logo;
};

