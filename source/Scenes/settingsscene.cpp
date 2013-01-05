#include "settingsscene.h"

void SettingsScene::draw(){
    drawLogo();
    
    if(drawBackground())
    {
        drawButtons();
    }
    
};

void SettingsScene::capture(){
    initBackground(DIAGONAL, 200, 160, 600, 400);
};


SettingsScene::SettingsScene(){
    
    _logo = Iw2DCreateImageResource("logo");

    ActionButton* button = new ActionButton();
    button->setButtonId(0)
        ->setX(250)
        ->setY(200)
        ->setWidth(450)
        ->setHeight(60)
        ->setFontSize(20)
        ->setText("Reset progress")
        ->setColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, SHADOW_COLOR));
    
    _buttons.push_back(button);
    
    button = new ActionButton();
    button->setButtonId(1)
        ->setX(400)
        ->setY(300)
        ->setWidth(200)
        ->setHeight(60)
        ->setFontSize(20)
        ->setText("< Back")
        ->setColor(g_ColorManager.getButtonColor(CYAN_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(CYAN_BUTTON, SHADOW_COLOR));
    
    _buttons.push_back(button);
};

void SettingsScene::touchReleased(){
    
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        if(!button->getPressed())
            continue;
        switch(button->getButtonId()){
            case 0:
                g_GameStateManager.resetGameData();
                break;
                
            case 1:
                getGameState()->switchToScene = MAIN_MENU_SCENE;
                break;
        }
        button->setPressed(false);
    }
    
};

void SettingsScene::touched(CTouch *touch){
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        button->setPressed(button->isHit(touch->x, touch->y));
    }
};

void SettingsScene::drawLogo(){
    Iw2DDrawImage(_logo, CIwSVec2(270, 10));
};

void SettingsScene::drawButtons(){
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        button->draw();
    }
};


SettingsScene::~SettingsScene(){
    delete _logo;
};

