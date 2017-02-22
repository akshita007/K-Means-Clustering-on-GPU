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

using namespace std;

int n,c,d;

void kmeans_cpu(float *point,float *cluster,int *member)
{
	int change;
	int i,j,k;
	float dist,p; 
	float *newCluster=(float*)(malloc)(sizeof(float)*c*d);
	int *newClusterSize=(int*)(malloc)(sizeof(int)*c);
	for(i=0;i<c;i++)
	{
		for(j=0;j<d;j++)
			newCluster[i*d+j]=0;
		newClusterSize[i]=0;
	}	
	do
	{
		change=0;
		for(i=0;i<n;i++)
		{
			float min_dist=INT_MAX;
			int pos=0;
			for(j=0;j<c;j++)
			{
				dist=0;
				for(k=0;k<d;k++)
				{
					p=(point[i*d+k]-cluster[j*d+k]);
					dist=dist+p*p;
				}
				if(dist<min_dist)
				{
					min_dist=dist;
					pos=j;
				}
			}
			if(member[i]!=pos){
				member[i]=pos;
				change=change+1;
			}
			newClusterSize[pos]++;
			for(k=0;k<d;k++)
			{
				newCluster[pos*d+k]+=point[i*d+k];
			}
		}
		for(i=0;i<c;i++)
		{
			for(k=0;k<d;k++)
			{
				if(newCluster[i*d+k]>0)
				cluster[i*d+k]=newCluster[i*d+k]/newClusterSize[i];
				newCluster[i*d+k]=0;
			}
			newClusterSize[i]=0;
		}
	}while(change >0);
}


void print_clusters(float * cluster)
{
	int i,j;
	for(i=0;i<c;i++)
	{
		for(j=0;j<d;j++)
			printf("%f ",cluster[i*d+j]);
		printf("\n");
	}	

}

static void usage(char *argv0) {
    const char *help =
        "Usage: %s [switches] -i filename -n num_clusters\n"
        "       -n Number of points    : No of input data points\n"
        "       -d Dimensionality    : Dimensionality of each point\n"
        "       -c Number of clusters : No of clusters required\n" 
        "       -h             : print this help information\n";
    fprintf(stderr, help, argv0);
    exit(-1);
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
	while ((option = getopt(argc, argv,"n:d:c:i:")) != -1) {
        		switch (option) {
             			case 'n' : n=atoi(optarg);
				break;
             			case 'd' : d=atoi(optarg);
                 		break;
             			case 'c' : c=atoi(optarg);
                 		break;
                 		case 'i' : input_file=optarg;
                 		break;
             			default: usage(argv[0]);
                 		exit(EXIT_FAILURE);
        		}
    		}
    	input = fopen(input_file,"r");
	
	float * point =(float*)(malloc)(sizeof(float) *n*d);
	float * cluster=(float*)(malloc)(sizeof(float)*c*d);
	int * member=(int*)(malloc)(sizeof(int)*n);
	
	
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<d;j++)
		{
			fscanf(input,"%f",&point[i*d+j]);
			
		}
		member[i]=0;
	}
	
	fclose(input);
	
	/*Random initialisation using the first k points */
	for(i=0;i<c;i++)
	{
		for(j=0;j<d;j++)
		{
			cluster[i*d+j]=point[i*d+j];
		}
		
	}
	
	clock_t clustering_timing=clock();
	kmeans_cpu(point,cluster,member);
	clustering_timing=clock()-clustering_timing;
	double time=clustering_timing/CLOCKS_PER_SEC;
	print_clusters(cluster);
	printf("Time taken for clustering = %f sec\n",time);
}
