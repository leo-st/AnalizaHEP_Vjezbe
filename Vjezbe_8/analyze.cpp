#include<Analyzer.h>

int main(){
	Analyzer* a = new Analyzer();
	a->Loop("ggH125");
	a->Loop("qqZZ");
	a->PlotMass();
	//a->FitMass();
	//a->PlotD();
	a->FitMaxLike();
	return 0;
}
