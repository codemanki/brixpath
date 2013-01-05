// Include header files for S3E (core system) and IwGx (rendering) modules

#include "brixpath.h"

// Standard C-style entry point. This can take args if required.
int main()
{
    Brixpath* brixpath = new Brixpath();
    
    brixpath->init();
    
    // Loop forever, until the user or the OS performs some action to quit the app
    while(true)
    {
        s3eKeyboardUpdate();
        if  (
             (s3eKeyboardGetState(s3eKeyEsc) & S3E_KEY_STATE_DOWN) ||
             (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN) ||
             (s3eDeviceCheckQuitRequest())
             )
            break;
        
        //If hardware quit request didn't happen, check for software one
        if(brixpath->quitRequest()){
            break;
        }
        
        //clear screen
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        
        brixpath->loop();
 
        IwGxFlush();
        
        // Standard EGL-style flipping of double-buffers
        IwGxSwapBuffers();
        
        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
        
    }
    
    brixpath->clean();
    
    // Return
    return 0;
}
