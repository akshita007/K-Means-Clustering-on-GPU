#include<iostream>
#include<limits.h>
#include<stdlib.h>
#include<stdio.h>
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

int main()
{
	/*
	  n-no of points
	  c- no of clusters
	  d- dimensionality of each point 
	 */
	scanf("%d%d%d",&n,&c,&d);
	
	/* Input the co-ordinates */
	
	float * point =(float*)(malloc)(sizeof(float) *n*d);
	float * cluster=(float*)(malloc)(sizeof(float)*c*d);
	int * member=(int*)(malloc)(sizeof(int)*n);
	
	
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<d;j++)
		{
			scanf("%f",&point[i*d+j]);
			
		}
		member[i]=0;
	}
	/*Random initialisation using the first k points */
	for(i=0;i<c;i++)
	{
		for(j=0;j<d;j++)
		{
			cluster[i*d+j]=point[i*d+j];
		}
		
	}
	
	kmeans_cpu(point,cluster,member);
	print_clusters(cluster);
}
