#include<Statistics.h>

int main(){
	
	Statistics* objekt = new Statistics();
	objekt->CalculatePi(10000);
	
	objekt->NormalDistribution(185,178.2,6.4);
	objekt->NormalDistribution(205,178.2,6.4);
	objekt->NormalDistribution(185,160.2,7.2);
	
	return 0;
}
