#include "interactions.h"


// the constructor 
CPUAnimBitmap::CPUAnimBitmap(int w, int h, void *d = nullptr) : _width(w), _height(h), dataBlock(d){

    pixels = new unsigned char[_width * _height * 4]; // pixels flattened 
    clickDrag = NULL; 
}


// the destructor
CPUAnimBitmap::~CPUAnimBitmap() {
        delete [] pixels;
    }

// this funxtions gives the address of the where the pixels are stored
unsigned char* CPUAnimBitmap::get_ptr( void ) const   { 
    return pixels; 
    
}

long CPUAnimBitmap::image_size( void ) const { 
    return _width * _height * 4; 
    
}



void CPUAnimBitmap::click_drag( void (*f)(void*,int,int,int,int)) {
            clickDrag = f;
}

// we reserve a memory to put the bitmap data
CPUAnimBitmap**  CPUAnimBitmap::get_bitmap_ptr( void ) {
    // NB: Static member here
    static CPUAnimBitmap*   gBitmap;
    return &gBitmap;

}