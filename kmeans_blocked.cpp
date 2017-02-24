#include<iostream>
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<getopt.h>
#include<time.h>
#include<fcntl.h>
#include<unistd.h>
#include<omp.h>
#include<assert.h>

#include"kmeans.h"

using namespace std;

int n,c,d;
int bsize;
/*We can have variable bsize along different dimensions but currently we are taking them to be the same */


void print_clusters(float ** cluster)
{
	int i,j;
	for(i=0;i<c;i++)
	{
		for(j=0;j<d;j++)
			printf("%f ",cluster[j][i]);
		printf("\n");
	}	

}

static void usage(char *argv0) {
    const char *help =
        "Usage: %s [switches] -i filename -n num_clusters\n"
        "       -n Number of points    : No of input data points\n"
        "       -d Dimensionality    : Dimensionality of each point\n"
        "       -c Number of clusters : No of clusters required\n" 
        "	-b Block Size  : Block Size \n" 
        "       -h             : print this help information\n";
    fprintf(stderr, help, argv0);
    exit(-1);
}


float ** initialise_clusters(float ** points,int n,int c ,int d)
{
	float **clusters;
	int i,j;
	
	/*Storing clusters in transpose form */
	clusters   = (float**)malloc(d * sizeof(float*));
        assert(clusters != NULL);
        int len= c*d;
        clusters[0] = (float*) malloc(len * sizeof(float));
        assert(clusters != NULL);
        for (i=1; i<d; i++)
            clusters[i] = clusters[i-1] + c;
         
        for(i=0;i<c;i++)
	{
		for(j=0;j<d;j++)
		{
			clusters[j][i]=points[i][j];
		}
	}
	return clusters;

}
int main(int argc, char *argv[])
{
	/*
	  n-no of points
	  c- no of clusters
	  d- dimensionality of each point 
	 */
	/* Input the co-ordinates */
	int option;
	char   *input_file;
	FILE *input;
	while ((option = getopt(argc, argv,"n:d:c:i:b:")) != -1) {
        		switch (option) {
             			case 'n' : n=atoi(optarg);
				break;
             			case 'd' : d=atoi(optarg);
                 		break;
             			case 'c' : c=atoi(optarg);
                 		break;
                 		case 'i' : input_file=optarg;
                 		break;
                 		case 'b': bsize=atoi(optarg);
                 		break;
             			default: usage(argv[0]);
                 		exit(EXIT_FAILURE);
        		}
    		}
	
        /*Input points*/
	float ** points =input_points(input_file,n,d);
	/*Initialise clusters*/
	float ** clusters=initialise_clusters(points,n,c,d);
	
	/*Initialise membership*/
	int * member=(int*)(malloc)(sizeof(int)*n);
	int i,j;
	for(i=0;i<n;i++)
		member[i]=-1;
	
	clock_t clustering_timing=clock();
	kmeans_block(points,clusters,member,n,c,d,bsize);
	clustering_timing=clock()-clustering_timing;
	double time=(double)clustering_timing/CLOCKS_PER_SEC;
	print_clusters(clusters);
	printf("Time taken for clustering = %f sec\n",time);
}
