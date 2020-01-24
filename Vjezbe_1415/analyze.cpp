#include "Analyzer.h"

using namespace std;

int main(){

	Analyzer *a = new Analyzer();
	//a->Loop();
	a->Theoretical_noHiggs();
	a->Expected_p_value_scan();
	a->PlotMass();
	
return 0;
}
