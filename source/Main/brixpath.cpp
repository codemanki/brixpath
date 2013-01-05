#include "brixpath.h"


void Brixpath::loop(){
    //draw pixel border
    drawBackgroundPattern();
    
    //Read touches from screen
    g_Input.Update();
    
    //check if game state has changed and react on it
    if(_sceneManager->handleSceneSwitch()){
        g_Input.clearTouches();
        _scene = _sceneManager->getActiveScene();
    }
    
    if (g_Input.getTouchCount() != 0)
    {
        //Application supports only single touch, so read only first
        CTouch* touch = g_Input.getTouch(0);
        if (touch != NULL && touch->active)
        {
            //If user holds finger, and moves it, holding flag helps to determine it
            touch->holding = _holding;
            _scene->touched(touch);
            
            if(!_holding){
                //if user is not holding, animate touch
                animateClick(touch);
            }
            
            _holding = true;
        }
        
        //User released finger
        if(touch != NULL && !touch->active){
            _scene->touchReleased();
        }
        
    }
    else
    {
        _holding = false;
        _scene->touchReleased();
    }
    
    _scene->draw();
    
    //animate clicks
    customAnimation();
};


void Brixpath::init()
{
    //Init system stuff
    Iw2DInit();
    IwResManagerInit();
    IwGxFontInit();
    
    //read resources
    IwGetResManager()->LoadGroup("brixpath.group");
    _backgroundImage = Iw2DCreateImageResource("3px");
    
	// Initialize evil classes
	g_Input.Init();
    g_ColorManager.initialize();
    g_FontManager.initialize();
    g_GameStateManager.initialize();
    
    //Load leveles
    g_LevelsManager.initializeFromFile("test.json");
    
    
    _gameStateData.gameLevel = 0;
    _gameStateData.currentScene = MAIN_MENU_SCENE;
    _gameStateData.switchToScene = MAIN_MENU_SCENE;
    
    //levels should be initialize only after Iw2d and similar stuff is initialized;
    _sceneManager = new ScenesManager(&_gameStateData);
    
    _scene = _sceneManager->getActiveScene();
    
    //and start drawing scene
    _scene->capture();
};

void Brixpath::clean()
{
    delete _backgroundImage;
    
    // Shut down the IwGx drawing module
    IwGxFontTerminate();
    IwResManagerTerminate();
    Iw2DTerminate();
};

void Brixpath::drawBackgroundPattern(){
    double width = Iw2DGetSurfaceWidth();
    double height = Iw2DGetSurfaceHeight();
    
    double backgroundImageWidth = _backgroundImage->GetWidth();
    double backgroundImageHeight = _backgroundImage->GetHeight();
    
    int timesX = ceil(width / backgroundImageWidth);
    
    int timesY = ceil(height / backgroundImageHeight);
    
    for(int y = 0; y < timesY; y++){
        for(int x = 0; x < timesX; x++){
            Iw2DDrawImage(_backgroundImage, CIwSVec2(x*backgroundImageWidth, y*backgroundImageHeight));
        }
    }
};

//Visualize clicks
void Brixpath::customAnimation(){
    
    CIwArray<clickAnimation*> toRemove;
    
    IW_ARRAY_ITERATE_INT(i, _clicksToAnimate)
    {
        clickAnimation* ca = &_clicksToAnimate[i];
        
        if(ca->currentWidth > _animationOptions.limit) //if rectangle is bigger than limit, animation should be stopped
            toRemove.push_back(&_clicksToAnimate[i]);
        else
        {
            _clicksToAnimate[i].currentWidth += _animationOptions.step; //increase rectangle size and draw it.
            Iw2DDrawRect(CIwSVec2((int)(ca->x - (ca->currentWidth/2)), (int)(ca->y - (ca->currentWidth/2))), CIwSVec2(ca->currentWidth, ca->currentWidth));
        }
    }
    
    //Remove clicks. This is done in two steps, so _clicksToAnimate array won't be affected by remove in first step above
    IW_ARRAY_ITERATE_INT(j, toRemove)
    {
        _clicksToAnimate.find_and_remove(*toRemove[j]);
    }
    
};

void Brixpath::animateClick(CTouch *_touch){
    clickAnimation touch = {_touch->x, _touch->y, 0};
    bool proceed = true;
    
    //Calculate euclidean distance between points.
    IW_ARRAY_ITERATE_INT(i, _clicksToAnimate)
    {
        clickAnimation* ex = &_clicksToAnimate[i];
        int dist = sqrt(pow((ex->x-touch.x),2) + pow((ex->y-touch.y),2));
        
        if((dist < _animationOptions.distance && ex->currentWidth > 0) && proceed){ //if new click is close to one of currently animated clicks, do not visualize it
            proceed = false;
            break;
            
        }
    }
    
    if(!proceed)
        return;
    
    int size = _clicksToAnimate.size();
    
    //Ooookay, new click is here, but right now too maany clicks are animated. Remove last one, probably it is almost over
    if(size >= _animationOptions.maxClicks && size > 0 ){
        _clicksToAnimate.pop_back();
    }
    //And insert in the beginning
    _clicksToAnimate.insert_slow(touch, 0);
};

//compare clicks
bool operator == (const clickAnimation& lhs, const clickAnimation& rhs)
{
    return (lhs.x == rhs.x && lhs.y == lhs.y && lhs.currentWidth == rhs.currentWidth);
};

Brixpath::Brixpath(){
    _animationOptions = (AnimationOptions){5, 3, 40, 30}; //description in core.h
};
