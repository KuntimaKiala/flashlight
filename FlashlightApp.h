#ifndef FLASHLIGHTAPP_H
#define FLASHLIGHTAPP_H
#include <GL/glut.h>
#include <cmath>
#include <cuda_runtime.h>

#include "kernel.h"
#pragma once

class FlashlightApp
{
public:
    FlashlightApp();
    ~FlashlightApp();

private: 
    float px = 0.0 ;
    float py = 0.0 ;
    Kernel* cudaCalculator;
    static FlashlightApp* appInstance;

};

#endif