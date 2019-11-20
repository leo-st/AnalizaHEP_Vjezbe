#include<Statistics.h>
#include <stdlib.h>    
#include <time.h>  
#include <cmath>


Statistics::Statistics(){
	cout<<"Objekt je uspjesno kreiran!"<<endl;
}

void Statistics::CalculatePi(int br){
	srand (time(NULL));
	double rand_x, rand_y, origin_dist, pi;
	int circle_points = 0, square_points = 0;
	
	for(int i=0;i<br*br;i++){
		rand_x = double(rand() % (br + 1)) / br; 
        rand_y = double(rand() % (br + 1)) / br;
		
		origin_dist = rand_x * rand_x + rand_y * rand_y;
		
		if(origin_dist<=1){
			circle_points++;
		}
		square_points++;
	}
	pi=double(4*circle_points)/square_points;
	
	cout<<"Predikcija broja PI: "<<pi<<endl;
}

void Statistics::NormalDistribution(int x, double mi, double sigma){
	double P=0.0;
	P=(1.0/(sigma*sqrt(2*3.14)))*exp((-1.0)*pow(x-mi,2)/(2*pow(sigma,2)));
	cout<<"Funkcijska vrijednost od x je: "<<P<<endl;

}
