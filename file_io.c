#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* strtok() */
#include <sys/types.h>  /* open() */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>     /* read(), close() */
#include<assert.h>
#include "kmeans.h"

#define MAX_CHAR_PER_LINE 128


float** input_points(char *input_file,int n,int d)
{ 
	float **points;
	FILE *input=fopen(input_file,"r");
	int i,j;
	
	points   = (float**)malloc(n * sizeof(float*));
        assert(points != NULL);
        int len= n*d;
        points[0] = (float*) malloc(len * sizeof(float));
        assert(points != NULL);
        for (i=1; i<n; i++)
            points[i] = points[i-1] + d;
         
        for(i=0;i<n;i++)
	{
		for(j=0;j<d;j++)
		{
			fscanf(input,"%f",&points[i][j]);
		}
	}
	
	fclose(input);
        return points;
	
}
