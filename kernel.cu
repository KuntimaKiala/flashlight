#include "kernel.h"

__global__ 
void calculateFlashlightIntensity(float* cudaIntensity, int width, int height, float x, float y, float radius, float intensityFactor){

    const int idx = blockIdx.x*gridDim.x + threadIdx.x ;
    const int idy = blockIdx.y*gridDim.y + threadIdx.y ; 
    const int index = idx + idy*width;

    if (idx < width && idy < height) {
        float dx = x - (idx / (float)width) * 2.0f + 1.0f;
        float dy = y - ((height - idy) / (float)height) * 2.0f + 1.0f;
        float distance = sqrtf(dx * dx + dy * dy);


        if (distance < radius) {
            cudaIntensity[index] = intensityFactor * (1.0f - distance / radius);
        } else {
            cudaIntensity[index] = 0.0f;
        }
    }


}



__host__ 
Kernel::Kernel(int width, int height ) : Width(width), Height(height) {
    //float* intensity = new float[Width * Height];
    cudaMalloc(&cudaIntensity, Width*Height*sizeof(float))  ;
}  


__host__
Kernel::~Kernel() {
    //delete [] intensity ;
    cudaFree(cudaIntensity);
   
}

 float * Kernel::getIntensity() {
  
    return hostIntensity;
;
 }



__host__   
void Kernel::cudaLauncher(float x, float y, float radius, float intensityFactor) {
    
    dim3 block(constant::threads, constant::threads) ;
    dim3 grid( (Width + block.x - 1)/block.x, (Height + block.y - 1)/block.y) ;

   
    std::cout << Width << " " << Height << std::endl ;
    
    
    calculateFlashlightIntensity<<<grid,block>>>(cudaIntensity,Width, Height,x,y,radius,intensityFactor) ;
    

    cudaMemcpy(hostIntensity, cudaIntensity, Height*Width* sizeof(float), cudaMemcpyDeviceToHost);
    
    
    debugging("bro") ;
    //cudaFree(cudaIntensity);
    

}


