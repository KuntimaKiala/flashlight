#ifndef KERNEL_H 
#define KERNEL_H
#include <cmath>
#include <iostream>
#include <string>
#include "constants.h"
#pragma once 

struct  Kernel
{

public :
    Kernel(int width, int height) ;
    ~Kernel();
    void cudaLauncher(float x, float y, float radius, float intensityFactor);
    static void debugging (const std::string & text)  {std::cout<<text<< std::endl ;} ;
private :
    const int Width ;
    const int Height ;
    float* cudaIntensity
    float hostIntensity[constant::width*constant::height] ;

};


#endif 