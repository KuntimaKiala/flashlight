#include "FlashlightApp.h"

FlashlightApp::FlashlightApp()
{
    pixel->x = 0 ;
    pixel->y =0 ;
    kernel = new Kernel(constant::width, constant::height) ;
    printInstructions() ;
}

FlashlightApp::~FlashlightApp()
{
    delete kernel ;
}

void FlashlightApp::keyboardWrapper(unsigned char Key, int x, int y) {
    appInstance->keyboard(Key, x, y) ;
}

void FlashlightApp::keyboard(unsigned char Key, int x, int y){

    if(Key =='a') {
        toggle = !toggle ;
    }
    else if (Key==27) {
        exit(0) ;
    }
    std::cout << "toggle mode :" << (toggle == true ? " ON" : "OFF" ) <<std::endl ;
    
    
}


void FlashlightApp::displayWrapper() {
    appInstance->display() ;
}
void FlashlightApp::display(){

    glClear(GL_COLOR_BUFFER_BIT);
    if (isMouseInsideWindow==true){
        if (toggle == false) return ;

        kernel->cudaLauncher(pixel->x, pixel->y, constant::radius, constant::intensityFactor) ;
        float * intensity = kernel->getIntensityAddress() ; 

        for(int idx=0; idx<constant::width; ++idx){
            for(int idy=0; idy<constant::height; ++idy){
               
                int index = idx + idy* constant::width ;
                glColor3f(intensity[index], intensity[index], 0.0f) ;
                glBegin(GL_POINTS);
                glVertex2f((idx / (float)constant::width) * 2.0f - 1.0f, ((constant::height - idy) / (float)constant::height) * 2.0f - 1.0f);
                glEnd();

            }

        }

    }
    glutSwapBuffers();
    
}

void  FlashlightApp::mousemotionWrapper(int x, int y){
    appInstance->mouseMotion(x, y) ;
}

void  FlashlightApp::mouseMotion(int x, int y){

    if (toggle == false) return ;
    pixel->x = x/(float)constant::width *2.0f -1.0f ;
    pixel->y = (constant::height-y)/(float)constant::height*2.0f -1.0f ;

    isMouseInsideWindow = (pixel->x >= -1.0f && pixel->x <= 1.0f && pixel->y >= -1.0f && pixel->y <= 1.0f);
    std::cout << "mouse motion (" << pixel->x << "," << pixel->y << ")" <<std::endl ;
    glutPostRedisplay();

}


void  FlashlightApp::init(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}




void  FlashlightApp::run(int argc, char** argv) {
        appInstance = this; // Set the app instance
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(constant::width, constant::height);
        glutCreateWindow("Flashlight Effect");
        
        
        
        glutKeyboardFunc(keyboardWrapper) ;
        glutPassiveMotionFunc(mousemotionWrapper);
        glutDisplayFunc(displayWrapper);

        init();
        glutMainLoop();

}


void FlashlightApp::printInstructions() {

    std::cout << "press [a] to start"  <<std::endl;
    std::cout << "press [ESC] to end"  <<std::endl;
    
}