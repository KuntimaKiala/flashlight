#ifndef INTERACTIONS_H
#define INTERACTIONS_H
#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <iostream>



class CPUAnimBitmap{

    public :
        
        
        void    *dataBlock;
        unsigned char    *pixels;
        int     dragStartX, dragStartY;


        CPUAnimBitmap( int w, int h, void *d = nullptr ) ;
        ~CPUAnimBitmap(); 
        void (*clickDrag)(void*,int,int,int,int);
        unsigned char* get_ptr( void ) const;
        long image_size( void ) const ;

        void click_drag( void (*f)(void*,int,int,int,int));
        // static method used for glut callbacks
        static CPUAnimBitmap** get_bitmap_ptr( void ) ;
    
    private :
        int     _width, _height;
        void (*_fAnim)(void*,int);
        void (*_animExit)(void*);
        

} ;


#endif 