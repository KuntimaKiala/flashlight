#include <iostream>
#include "FlashlightApp.h" 
#include "kernel.h"




int main(){

    FlashlightApp app;
    char* text = "FashLight Effect App" ;
    //Kernel kernel(2,2) ;
    //float * intensity  = (float*)malloc( sizeof(float) * 4 );

    //kernel.cudaLauncher(intensity, 1,1,1,1) ;
    app.run(1, &text);
    return 0 ;
}