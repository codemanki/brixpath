#include "helpscene.h"

void HelpScene::draw(){
    
    drawLogo();
    
    if(drawBackground())
    {
        drawButtons();
        drawContent();
    }
    
};

void HelpScene::capture(){
    initBackground(DIAGONAL, 100, 160, 700, 400);
};


HelpScene::HelpScene(){
    
    _logo = Iw2DCreateImageResource("logo");
    _helpImage = Iw2DCreateImageResource("helpScene");
    
    ActionButton* button = new ActionButton();
    button->setButtonId(0)
        ->setX(825)
        ->setY(200)
        ->setWidth(150)
        ->setHeight(60)
        ->setFontSize(20)
        ->setText("< Back")
        ->setColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, SHADOW_COLOR));
    
    _buttons.push_back(button);
    
    _helpText = "Welcome to BrixPath! This is easy to play and addictive game. Rules are simple: \n 1) Connect all squares with digits with each other (1 to 1, 2 to 2 etc. )\n 2) All gray squares should be filled \n Here's an example:";
    
    _font.setFont(14);
    _font.setStartVector(CIwSVec2(100, 150));
    _font.setSizeVector(CIwSVec2(600, 220));
};

void HelpScene::touchReleased(){
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        if(button->getPressed()){
            if(button->getButtonId() == 0){
                getGameState()->switchToScene = MAIN_MENU_SCENE;
            }
        }
        button->setPressed(false);
    }
    
};

void HelpScene::touched(CTouch *touch){
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        button->setPressed(button->isHit(touch->x, touch->y));
    }
};

void HelpScene::drawLogo(){
    Iw2DDrawImage(_logo, CIwSVec2(270, 10));
};

void HelpScene::drawContent(){
    Iw2DDrawImage(_helpImage, CIwSVec2(150, 360));
     _font.drawStringWithBlack(_helpText);
};

void HelpScene::drawButtons(){
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        button->draw();
    }
};

HelpScene::~HelpScene(){
    delete _logo;
    delete _helpImage;
};

