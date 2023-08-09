#include <iostream>
#include "bitmap.h"
#include "initStatics.h"

int main(){

    char* projectname = "flashlight effect" ;
   
    bitmap GUI;
    //bitmap*   bitmapobj = GUI.bitmap_address();
    GUI.printInstructions() ;
    GUI.window(1,&projectname) ;



}

