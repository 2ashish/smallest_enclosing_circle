# include <LEDA/geo/circle.h>
# include <LEDA/geo/point.h>
# include <iostream>
# include <stdio.h>
# include <vector>
# include <ctime>
# include <cfloat>
# include <cstdlib>
# include <algorithm> 
using namespace std ;
using leda :: circle ;
using leda :: point;

leda::circle cir2(vector<leda::point> &P,int k,int j){		//P[j+1] and P[k+1] are the points that must lie on the circle
	leda::circle c[k+1];
	leda::circle cq(midpoint(P[k+1],P[j+1]),P[k+1]);	//initialize a circle defined by P[k+1] and P[j+1]
	c[0]=cq;
	for(int i=1;i<=k;i++){
		if(c[i-1].inside(P[i]))c[i]=c[i-1];		//if point P[i] lies within the previous circle then the circle will remain unchanged 
		else {leda::circle cq(P[i],P[j+1],P[k+1]);c[i]=cq;}
	}							// else the circle is defined by the points P[i],P[j+1] and P[k+1]
return c[k];
}

leda::circle cir1(vector<leda::point> &P,int j){		//P[j+1] is the point that must lie on the circle
	leda::circle c[j+1];
	leda::circle cq(midpoint(P[1],P[j+1]),P[1]);		//initialize a circle defined by P[1] and P[j+1]
	c[1]=cq;
	for(int i=2;i<=j;i++){
		if(c[i-1].inside(P[i]))c[i]=c[i-1];		//if point P[i] lies within the previous circle then the circle will remain unchanged 
		else c[i]=cir2(P,i-1,j);			// else find a circle such that it encloses points P[1],P[2]....P[i] and P[i] and P[j+1] lies on it
	}
return c[j];
}

int main ()
{								//randomized incremental algorithm
	int i,j,k,l,n=0;
	double x,y;
	//FILE *fp;						// for taking input from a .txt file
	//fp=fopen("input.txt","r");
	//fscanf(fp,"%d\n",&n);
	scanf("%d",&n);
	vector<leda::point> P(n+1);				//vector of points
	for(i=1;i<=n;i++){
		//fscanf(fp,"%lf %lf\n",&x,&y);
		scanf("%lf %lf",&x,&y);
		leda::point p(x,y);
		P[i]=p;
	}
	srand(time(NULL));
	random_shuffle(P.begin()+1,P.end());			//randomly permute the points
	//fclose(fp);
	leda::circle c[n+2];
	leda::circle cq(midpoint(P[1],P[2]),P[1]);		//initialize a circle defined by first two points
	c[2]=cq;
	for(i=3;i<=n;i++){
		if(c[i-1].inside(P[i]))c[i]=c[i-1];		//if point P[i] lies within the previous circle then the circle will remain unchanged 
		else c[i]=cir1(P,i-1);				// else find a circle such that it encloses points P[1],P[2]....P[i] and P[i] lies on it
	}							//at nth iteration i.e. c[n] will store the smallest enclosing circle
	printf("%lf,%lf\n%lf\n",c[n].center().xcoord(),c[n].center().ycoord(),c[n].radius());
	return 0;
}

