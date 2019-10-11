#include <ElementaryParticle.h>



ElementaryParticle::ElementaryParticle(string name, int mass, bool boson){
	ime = name;
	masa=mass;
	bozon=boson;
}
void ElementaryParticle::printInfo(){
	cout<<"Ime: "<<ime<<", Masa: "<<masa<<", Bozon: "<<bozon<<endl;
}
		

