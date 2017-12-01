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

leda::circle cir2(vector<leda::point> &P,int k,int j){
	leda::circle c[k+1];
	leda::circle cq(midpoint(P[k+1],P[j+1]),P[k+1]);
	c[0]=cq;
	for(int i=1;i<=k;i++){
		if(c[i-1].inside(P[i]))c[i]=c[i-1];
		else {leda::circle cq(P[i],P[j+1],P[k+1]);c[i]=cq;}
	}
return c[k];
}

leda::circle cir1(vector<leda::point> &P,int j){
	leda::circle c[j+1];
	leda::circle cq(midpoint(P[1],P[j+1]),P[1]);
	c[1]=cq;
	for(int i=2;i<=j;i++){
		if(c[i-1].inside(P[i]))c[i]=c[i-1];
		else c[i]=cir2(P,i-1,j);
	}
return c[j];
}

int main ()
{	
	int i,j,k,l,n=0;
	clock_t t;
	while(n<500000){
		n+=2000;
		t=clock();
		vector<double> v(2*n+5,0);
		vector<leda::point> P(n+1);
		srand(time(NULL));
		for(i=1;i<=n;i++){
			v[2*i]=((double)(rand()%1000000))/10000;
			v[2*i+1]=((double)(rand()%1000000))/10000;
			//cout<<v[2*i]<<" "<<v[2*i+1]<<'\n';
			leda::point p(v[2*i],v[2*i+1]);
			P[i]=p;
			}
		srand(time(NULL));
		random_shuffle(P.begin()+1,P.end());
		leda::circle c[n+2];
		leda::circle cq(midpoint(P[1],P[2]),P[1]);
		c[2]=cq;
		for(i=3;i<=n;i++){
			if(c[i-1].inside(P[i]))c[i]=c[i-1];
			else c[i]=cir1(P,i-1);
		}
		t=clock()-t;
		cout<<n<<" "<<((float)t)/CLOCKS_PER_SEC<<'\n';	
	}
	//cout << " Radius is " << c.radius() << endl ;
	//cout << " Center is " << c.center().xcoord() << " " << c.center().ycoord() << endl ;
	//cout << " Leda linking successful ";
	return 0;
}

