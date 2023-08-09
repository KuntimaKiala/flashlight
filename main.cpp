#include <iostream>
#include "FlashlightApp.h" 




FlashlightApp* FlashlightApp::appInstance = nullptr;
int main(){

    FlashlightApp app;
    char* text = "FashLight Effect App" ;
    app.run(1, &text);
    return 0 ;
}