#ifndef _H_KMEANS
#define _H_KMEANS

float** input_points(char *,int ,int);
void kmeans_cpu(float **,float **,int *,int ,int ,int);
float ** initialise_new_clusters(int,int,int);
#endif
