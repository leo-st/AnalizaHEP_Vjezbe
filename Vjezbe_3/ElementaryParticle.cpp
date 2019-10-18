#include <ElementaryParticle.h>
#include <cmath>


ElementaryParticle::ElementaryParticle(string name, int mass, bool boson){
	ime = name;
	masa=mass;
	bozon=boson;
}
void ElementaryParticle::printInfo(){
	cout<<"Ime: "<<ime<<", Masa: "<<masa<<", Bozon: "<<bozon<<endl;
}
		

void ElementaryParticle::SetCetverovektor(double a,double b,double c){
	p1=a;
	p2=b;
	p3=c;
	E=sqrt(p1*p1+p2*p2+p3*p3+masa*masa);
}
void ElementaryParticle::setTransverseMomentum(){
	cout<<"Transverzalna količina gibanja je: "<<sqrt(p1*p1+p2*p2)<<endl;
}

