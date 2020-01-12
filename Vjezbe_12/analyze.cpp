#include "Analyzer.h"

using namespace std;

int main(){

	Analyzer *a = new Analyzer();
	a->Loop("background");
	a->Loop("signal");
	a->Draw();

return 0;
}
