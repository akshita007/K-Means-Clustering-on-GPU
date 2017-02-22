# K-Means-Clustering-on-GPU

To run execute :

g++ kmeans_cpu.cpp -o cpu
./cpu -n 5000 -d 5 -c 5 -i image_input

nvcc kmeans_gpu.cu -o gpu (needs a CUDA compiler)
./gpu -n 5000 -d 5 -c 5 -i image_input

see ./cpu -h for details about notation
