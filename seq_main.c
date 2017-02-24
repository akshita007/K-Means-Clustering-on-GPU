#include "kmeans.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>


float ** initialise_new_clusters(int n,int c ,int d)
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
         
        for(j=0;j<d;j++)
	{
		for(i=0;i<c;i++)
		{
			clusters[j][i]=0;
		}
	}
	return clusters;

}

void kmeans_cpu(float **points,float **clusters,int *member,int n,int c,int d)
{
	int change;
	int i,j,k;
	float dist,p; 
	float **newCluster=initialise_new_clusters(n,c,d);
	int *newClusterSize=(int*)(malloc)(sizeof(int)*c);
	for(i=0;i<c;i++)
		newClusterSize[i]=0;

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
					p=(points[i][k]-clusters[k][j]);
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
				newCluster[k][pos]+=points[i][k];
			}
		}
		for(j=0;j<c;j++)
		{
			for(k=0;k<d;k++)
			{
				if(newClusterSize[j]>0)
				clusters[k][j]=newCluster[k][j]/newClusterSize[j];
				newCluster[k][j]=0;
			}
			newClusterSize[j]=0;
		}
	}while(change >0);
}

