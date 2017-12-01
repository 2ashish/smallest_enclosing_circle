# include <LEDA/geo/circle.h>
# include <LEDA/geo/point.h>
# include <iostream>
# include <vector>
# include <ctime>
# include <cfloat>
# include <cstdlib>
using namespace std ;
using leda :: circle ;
using leda :: point;
int main ()
{	
	int i,j,k,l,n=1350,iter=0;
	clock_t t;
	float t1=0;
	while(n<2000){
		if(n<500)n+=10;
		else n+=100;
		while(iter<2){
		t=clock();
		vector<double> v(2*n,0);
		leda::point P[2*n];
		srand(time(NULL));
		for(i=0;i<n;i++){
			v[2*i]=((double)(rand()%1000000))/10000;
			v[2*i+1]=((double)(rand()%1000000))/10000;
			//cout<<v[2*i]<<" "<<v[2*i+1]<<'\n';
			leda::point p(v[2*i],v[2*i+1]);
			P[i]=p;
			}
		leda::circle c (P[0],DBL_MAX);
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				for(k=j+1;k<n;k++){
					leda::circle c1 ( P[i] , P[j] , P[k] );
					if(c1.radius()>c.radius())continue;
					for(l=0;l<n;l++){
						if(c1.outside(P[l]))break;
					}
					if(l==n)c=c1;
				}
			}
		}
		for(i=0;i<n;i++){
			for(j=i+1;j<n;j++){
				leda::circle c1 ( midpoint(P[i],P[j]), P[i] );
				if(c1.radius()>c.radius())continue;
				for(l=0;l<n;l++){
					if(c1.outside(P[l]))break;
				}
				if(l==n)c=c1;
			}
		}
		t=clock()-t;
		t1+=((float)t)/CLOCKS_PER_SEC;
		iter++;
		}
		iter=0;
		t1/=2;
		cout<<n<<" "<<t1<<'\n';	
		t1=0;
	}
	//cout << " Radius is " << c.radius() << endl ;
	//cout << " Center is " << c.center().xcoord() << " " << c.center().ycoord() << endl ;
	cout << " Leda linking successful ";
	return 0;
}

