AIM: Write and test CUDA program to implement Monte Carlo algorithm

Code:
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cuda.h>

__global__ void monteCarloPi(int *insideCircle, int numPoints) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < numPoints) {
        float x = (rand() % 10000) / 10000.0f * 2.0f - 1.0f;
        float y = (rand() % 10000) / 10000.0f * 2.0f - 1.0f;
        if (x * x + y * y <= 1.0f) {
            atomicAdd(insideCircle, 1);
        }
    }
}

int main() {
    int numPoints = 1000000;
    int *d_insideCircle, *h_insideCircle;
    h_insideCircle = (int *)malloc(sizeof(int));
    *h_insideCircle = 0;

    cudaMalloc((void **)&d_insideCircle, sizeof(int));
    cudaMemcpy(d_insideCircle, h_insideCircle, sizeof(int), cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int numBlocks = (numPoints + threadsPerBlock - 1) / threadsPerBlock;
    monteCarloPi<<<numBlocks, threadsPerBlock>>>(d_insideCircle, numPoints);

    cudaMemcpy(h_insideCircle, d_insideCircle, sizeof(int), cudaMemcpyDeviceToHost);

    float pi = 4.0f * (*h_insideCircle) / numPoints;
    std::cout << "Estimated value of Pi: " << pi << std::endl;

    cudaFree(d_insideCircle);
    free(h_insideCircle);

    return 0;
}
