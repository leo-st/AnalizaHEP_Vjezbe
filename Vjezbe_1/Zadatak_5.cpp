#include<iostream>
#include<cmath>

using namespace std;

double _my_cube(double x){
	return pow(x,3); 
}

int main(){
	double x;
	cin>>x;

	cout<<_my_cube(x)<<endl;


return 0;
}


