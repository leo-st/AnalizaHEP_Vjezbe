#include "Analyzer.h"

using namespace std;

int main(){

	Analyzer *a = new Analyzer();
	a->Loop();
	a->Theoretical_t_gauss();
	a->ah_test(166.1,6.5);

return 0;
}
