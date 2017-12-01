# include <LEDA/geo/circle.h>
# include <LEDA/geo/point.h>
# include <iostream>
# include <stdio.h>
# include <vector>
# include <ctime>
# include <cfloat>
# include <cstdlib>
using namespace std ;
using leda :: circle ;
using leda :: point;
int main ()
{	
	int i,j,k,l,n=0;
	double x,y;
	//FILE *fp;								//for taking input from a .txt file
	//fp=fopen("input.txt","r");
	//fscanf(fp,"%d",&n);
	scanf("%d\n",&n);
	leda::point P[2*n];
	for(i=0;i<n;i++){							//get the points and store them in an array
		//fscanf(fp,"%lf %lf\n",&x,&y);
		scanf("%lf %lf",&x,&y);
		leda::point p(x,y);
		P[i]=p;
	}
	//fclose(fp);
	leda::circle c (P[0],DBL_MAX);						//initialize a dummy circle that encloses all the points
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++){
			for(k=j+1;k<n;k++){					//for every triplets of points
				if(collinear(P[i] , P[j] , P[k] ))continue;	//if they are collinear don't do anything (this case will be considered in pair of points)
				leda::circle c1 ( P[i] , P[j] , P[k] );		//else make a circle with the triplets
				if(c1.radius()>c.radius())continue;
				for(l=0;l<n;l++){
					if(c1.outside(P[l]))break;
				}
				if(l==n)c=c1;					//if the new circle encloses all points and is smaller that dummy then update the dummy circle to store the smallest circle
			}
		}
	}
	for(i=0;i<n;i++){							//for every pair of points
		for(j=i+1;j<n;j++){
			leda::circle c1 ( midpoint(P[i],P[j]), P[i] );		//make a circle with points as diametrically opposite
			if(c1.radius()>c.radius())continue;
			for(l=0;l<n;l++){
				if(c1.outside(P[l]))break;
			}
			if(l==n)c=c1;						//if the new circle encloses all points and is smaller that dummy then update the dummy circle to store the smallest circle
		}
	}
	printf("%lf,%lf\n%lf\n",c.center().xcoord(),c.center().ycoord(),c.radius());
	
	//fp=fopen("output.txt","w");
	//fprintf(fp,"%lf,%lf\n%lf",c.center().xcoord(),c.center().ycoord(),c.radius());
	//fclose(fp);
	return 0;
}

