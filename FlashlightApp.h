#ifndef FLASHLIGHTAPP_H
#define FLASHLIGHTAPP_H
#include <GL/glut.h>
#include <cmath>
#include <cuda_runtime.h>
#include "kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#pragma once

struct Pixel {

    Pixel(int u, int v) :x(u) , y(v) {} ; 
    float x ;
    float y ;
} ;



class FlashlightApp
{
public:
    FlashlightApp();
    ~FlashlightApp();
    void display() ;
    void mouseMotion(int x, int y) ;
    void keyboard(unsigned char Key, int x, int y) ;
    void init() ;
    void run(int argc, char** argv) ;
    
private: 
    Pixel* pixel;
    bool toggle = !constant::isFalse ;
    bool isMouseInsideWindow = !constant::isFalse ;
    Kernel* kernel ;
    void printInstructions() ;
    static void displayWrapper() ;
    static void mousemotionWrapper(int x, int y) ;
    static  void keyboardWrapper(unsigned char Key, int x, int y) ;  
   
    
   
    static FlashlightApp* appInstance;
    
    

};

#endif