#include "dialog.h"

#define OFFSET_BEFORE_TEXT 20 
#define TEXT_HEIGHT  50
#define SUBTEXT_HEIGHT  30
#define OFFSET_BEFORE_SUBTEXT  10
#define OFFSET_AFTER_TEXT 30
#define OFFSET_BETWEEN_BUTTONS 20
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 60
#define OFFSET_SIDES 100
#define DIALOG_WIDTH 400
#define OFFSET_BOTTOM 20
#define SHADOW_OFFSET 5

void Dialog::addButton(int buttonId, const string &text){
    ActionButton* button = new ActionButton;
    
    button->setButtonId(buttonId)
        ->setText(text)
        ->setWidth(BUTTON_WIDTH)
        ->setHeight(BUTTON_HEIGHT)
        ->setShadowOffset(SHADOW_OFFSET) 
        ->setColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, BACKGROUND_COLOR))
        ->setShadowColor(g_ColorManager.getButtonColor(ORANGE_BUTTON, SHADOW_COLOR));
    
    _buttons.push_back(button);
    
    recalculateValues();
};

int Dialog::isHit(int x, int y){
    if(_visible){
        ActionButton* button;
        
        IW_ARRAY_ITERATE_INT(i, _buttons){
            button = _buttons[i];
            if(button->isHit(x,y)){
                return button->getButtonId();
            }
        }
    }
    return -1;
}


void Dialog::draw(){
    
    if(getVisible()){
        
        //Draw gray overlay over the whole screen
        Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
        Iw2DSetColour(g_ColorManager.getBlack()); //border
        Iw2DFillRect(CIwSVec2(0,0), CIwSVec2(_screenWidth, _screenHeight));
        Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
        
        //orange border
        Iw2DSetColour(g_ColorManager.getOrangeColor()); //fill
        Iw2DFillRect(CIwSVec2(_positionX - 5,_positionY - 5), CIwSVec2(_width + 10, _height + 10));
        
        //white content
        Iw2DSetColour(g_ColorManager.getWhite()); //fill
        Iw2DFillRect(CIwSVec2(_positionX,_positionY), CIwSVec2(_width, _height));
        
        //title
        _font.drawStringWithBlack(_text);
        
        if(_subText.length() > 0)
            _subFont.drawStringWithBlack(_subText);
        
        IW_ARRAY_ITERATE_INT(i, _buttons){
            _buttons[i]->draw();
        }
        
    }
}

void Dialog::recalculateValues(){
    int generalOffsetForButtons;
    //TODO: think about, how to make this code more beautiful and meaningful
    _height = OFFSET_BEFORE_TEXT + TEXT_HEIGHT + OFFSET_AFTER_TEXT + (_subText.length() > 0 ? OFFSET_BEFORE_SUBTEXT + SUBTEXT_HEIGHT : 0);
    
    _height += _buttons.size() * (BUTTON_HEIGHT + OFFSET_BETWEEN_BUTTONS + SHADOW_OFFSET) + OFFSET_BOTTOM;
    
    _positionY = _screenHeight/2 - _height/2;
    
    _font.setStartVector(CIwSVec2(_positionX, _positionY + OFFSET_BEFORE_TEXT));
    _font.setSizeVector(CIwSVec2(_width, TEXT_HEIGHT));
    

    if(_subText.length() > 0){
        _subFont.setStartVector(CIwSVec2(_positionX, _positionY + OFFSET_BEFORE_TEXT + TEXT_HEIGHT + OFFSET_BEFORE_SUBTEXT));
        _subFont.setSizeVector(CIwSVec2(_width, SUBTEXT_HEIGHT));
    }
    
    
    generalOffsetForButtons = _positionY + OFFSET_BEFORE_TEXT + TEXT_HEIGHT + OFFSET_AFTER_TEXT + (_subText.length() > 0 ? OFFSET_BEFORE_SUBTEXT + SUBTEXT_HEIGHT : 0);
    
    
    IW_ARRAY_ITERATE_INT(i, _buttons){
        ActionButton* button = _buttons[i];
        if(button->getVisible()) {
            button->setX(_positionX + OFFSET_SIDES);
            button->setY(generalOffsetForButtons + i * (BUTTON_HEIGHT+OFFSET_BETWEEN_BUTTONS));
            button->setText(button->getText());// TODO:Remove this hack. This is done becase setText reinitializes start and size vectors
        }
    }
};

//Make button invisible
void Dialog::changeButtonVisibility(int buttonId, bool isVisible){
    
    IW_ARRAY_ITERATE_INT(i, _buttons){
        if(_buttons[i]->getButtonId() == buttonId){
            _buttons[i]->setVisible(isVisible);
            recalculateValues();
            return;
        }
        
    }
}

Dialog::Dialog(){
    _screenWidth = Iw2DGetSurfaceWidth();
    _screenHeight = Iw2DGetSurfaceHeight();
    _width = DIALOG_WIDTH;// width is always static
    _positionX = _screenWidth/2 - _width/2;
    
    setVisible(false);
    
    _font.setFont(16);
}

