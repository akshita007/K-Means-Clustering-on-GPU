#include "kmeans.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>
#include<math.h>


float ** initialise_dist(int n,int c ,int d)
{
	float **dist;
	int i,j;
	
	/*Storing clusters in transpose form */
	dist   = (float**)malloc(n * sizeof(float*));
        assert(dist != NULL);
        int len= c*n;
        dist[0] = (float*) malloc(len * sizeof(float));
        assert(dist != NULL);
        for (i=1; i<n; i++)
            dist[i] = dist[i-1] + c;
         
        for(j=0;j<n;j++)
	{
		for(i=0;i<c;i++)
		{
			dist[j][i]=0;
		}
	}
	return dist;

}


int minimum(int a ,int b)
{
	return (a<b)?a:b;
}
void kmeans_block(float **points,float **clusters,int *member,int n,int c,int d,int bsize)
{
	int change;
	int i,j,k;
	float p; 
	float **dist=initialise_dist(n,c,d);
	int *newClusterSize=(int*)(malloc)(sizeof(int)*c);
	int *pos=(int*)(malloc)(sizeof(int)*n);
	float *min_dist=(float*)(malloc)(sizeof(float)*n);
	for(i=0;i<c;i++)
		newClusterSize[i]=0;
	int i0,j0,k0;
	
	do
	{
		change=0;
		for(i0=0;i0<n;i0+=bsize)
		{
			for(i=i0;i<minimum(i0+bsize,n);i++){
				min_dist[i]=INT_MAX;
				pos[i]=0;
				}
			
			for(j0=0;j0<c;j0+=bsize)
			{
				for(k0=0;k0<d;k0+=bsize)
				{
					for(i=i0;i<minimum(n,i0+bsize);i++)
					{
						for(j=j0;j<minimum(c,j0+bsize);j++)
						{
							for(k=k0;k<minimum(d,k0+bsize);k++)
							{
								p=points[i][k]-clusters[k][j];
								dist[i][j]+=p*p;
							}
							if(k==d)
							{
								if(min_dist[i]> dist[i][j]){
								min_dist[i]=dist[i][j];
								pos[i]=j;
								}
								dist[i][j]=0;
							}
							if(k==d && j==c-1)//means reached end 
							{
								newClusterSize[pos[i]]++;
							}
						}
					}
				}
			}
		}
		for(k=0;k<d;k++)
		for(j=0;j<c;j++)
			if(newClusterSize[j]>0)
			clusters[k][j]=0;
		for(i=n-1;i>=0;i--)
		{
			if(pos[i]!=member[i])
			{
				member[i]=pos[i];
				change++;
			}
			for(k=0;k<d;k++)
			{
				clusters[k][pos[i]]+=points[i][k]/newClusterSize[pos[i]];
			}
		}
		for(j=0;j<c;j++)
			newClusterSize[j]=0;
			
	}while(change >0);
}

