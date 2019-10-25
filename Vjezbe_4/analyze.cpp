#include<Analyzer.h>


using namespace std;

int main(){
	Analyzer* a1=new Analyzer();
	a1->readTextFile();
	cout<<a1->DecayParticle1_Name<<endl;
	return 0;
}
