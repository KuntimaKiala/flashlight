#include "FlashlightApp.h"
#include "constants.h"
FlashlightApp::FlashlightApp()
{
    px = 0.0 ;
    py = 0.0 ;
    cudaCalculator = new Kernel(constant::width, constant::height) ;
}

FlashlightApp::~FlashlightApp()
{

}