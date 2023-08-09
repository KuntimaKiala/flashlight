#include <GL/glut.h>
#include <cmath>
#include <cuda_runtime.h>

// CUDA kernel to calculate flashlight intensity
__global__ void calculateFlashlightIntensity(float* result, int width, int height, float x, float y, float radius, float intensityFactor) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int idy = blockIdx.y * blockDim.y + threadIdx.y;
    int index = idy * width + idx;

    if (idx < width && idy < height) {
        float dx = x - (idx / (float)width) * 2.0f + 1.0f;
        float dy = y - ((height - idy) / (float)height) * 2.0f + 1.0f;
        float distance = sqrtf(dx * dx + dy * dy);

        if (distance < radius) {
            result[index] = intensityFactor * (1.0f - distance / radius);
        } else {
            result[index] = 0.0f;
        }
    }
}

// CUDA calculator class to handle CUDA calculations
class CudaCalculator {
public:
    CudaCalculator(int screenWidth, int screenHeight)
        : screenWidth(screenWidth), screenHeight(screenHeight) {
        cudaMalloc(&cudaIntensity, screenWidth * screenHeight * sizeof(float));
    }

    ~CudaCalculator() {
        cudaFree(cudaIntensity);
    }

    // Calculate intensity using CUDA
    void calculateIntensity(float mouseX, float mouseY, float radius, float intensityFactor) {
        int gridSize = 16;
        dim3 block(gridSize, gridSize);
        dim3 grid((screenWidth + gridSize - 1) / gridSize, (screenHeight + gridSize - 1) / gridSize);

        calculateFlashlightIntensity<<<grid, block>>>(cudaIntensity, screenWidth, screenHeight, mouseX, mouseY, radius, intensityFactor);

        cudaMemcpy(intensity, cudaIntensity, screenWidth * screenHeight * sizeof(float), cudaMemcpyDeviceToHost);
    }

    // Get calculated intensity array
    float* getIntensity() {
        return intensity;
    }

private:
    const int screenWidth;
    const int screenHeight;

    float* cudaIntensity;
    float intensity[800 * 600];
};

// FlashlightApp class to manage the application
class FlashlightApp {
public:
    FlashlightApp()
        : screenWidth(800), screenHeight(600), radius(0.1f), intensityFactor(0.5f), isMouseInsideWindow(false) {
        mouseX = 0.0f;
        mouseY = 0.0f;
        cudaCalculator = new CudaCalculator(screenWidth, screenHeight);
    }

    ~FlashlightApp() {
        delete cudaCalculator;
    }

    // Initialize OpenGL settings
    void init() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    // Display function to render OpenGL scene
    void display() {
        glClear(GL_COLOR_BUFFER_BIT);

        if (isMouseInsideWindow) {
            cudaCalculator->calculateIntensity(mouseX, mouseY, radius, intensityFactor);
            float* intensity = cudaCalculator->getIntensity();

            for (int y = 0; y < screenHeight; y++) {
                for (int x = 0; x < screenWidth; x++) {
                    int index = y * screenWidth + x;
                    glColor3f(intensity[index], 0.0f, 0.0f);
                    glBegin(GL_POINTS);
                    glVertex2f((x / (float)screenWidth) * 2.0f - 1.0f, ((screenHeight - y) / (float)screenHeight) * 2.0f - 1.0f);
                    glEnd();
                }
            }
        }

        glutSwapBuffers();
    }

    // Motion function to handle mouse movement
    void motion(int x, int y) {
        mouseX = (x / (float)screenWidth) * 2.0f - 1.0f;
        mouseY = ((screenHeight - y) / (float)screenHeight) * 2.0f - 1.0f;

        isMouseInsideWindow = (mouseX >= -1.0f && mouseX <= 1.0f && mouseY >= -1.0f && mouseY <= 1.0f);

        glutPostRedisplay();
    }

    // Run the application
    void run(int argc, char** argv) {
        appInstance = this; // Set the app instance
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(screenWidth, screenHeight);
        glutCreateWindow("Flashlight Effect");

        glutDisplayFunc(displayWrapper);
        glutPassiveMotionFunc(motionWrapper);

        init();
        glutMainLoop();
    }

private:
    const int screenWidth;
    const int screenHeight;
    const float radius;
    const float intensityFactor;

    float mouseX;
    float mouseY;
    bool isMouseInsideWindow;

    CudaCalculator* cudaCalculator;
    static FlashlightApp* appInstance;

    static void displayWrapper() {
        appInstance->display();
    }

    static void motionWrapper(int x, int y) {
        appInstance->motion(x, y);
    }
};

FlashlightApp* FlashlightApp::appInstance = nullptr;

int main(int argc, char** argv) {
    FlashlightApp app;
    app.run(argc, argv);
    return 0;
}
