#include <ElementaryParticle.h>
#include <cmath>



ElementaryParticle::ElementaryParticle(string name, int mass, bool boson){
	ime = name;
	masa=mass;
	bozon=boson;
}
ElementaryParticle::ElementaryParticle(){
	ime="";
	masa=0;
	bozon=false;
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

void ElementaryParticle::bosonDecay(ElementaryParticle *a,ElementaryParticle *b){
	double r=rand()%100;
	if(bozon==false){
		cout<<"RASPAD NIJE MOGUC!!!"<<endl;
		return;
	}
	if(r<21.4 && r>=6.4){
		a->bozon=true;
		a->ime="W Bozon";
		a->masa=91.2;
		b->bozon=true;
		b->ime="W Bozon";
		b->masa=91.2;
	}
	else if(r<6.4 && r>=2.6){
		a->bozon=false;
		a->ime="Tau lepton";
		a->masa=1.776;
		b->bozon=false;
		b->ime="Tau lepton";
		b->masa=1.776;
	}
	else if(r<2.6 && r>=0){
		a->bozon=true;
		a->ime="Z bozon";
		a->masa=91.186;
		b->bozon=true;
		b->ime="Z bozon";
		b->masa=91.186;
	}
	else{
		a->bozon=false;
		a->ime="b quark";
		a->masa=4.18;
		b->bozon=false;
		b->ime="b quark";
		b->masa=4.18;
	}
	while(true){
		r=(rand()%100)/100.0;
		cout<<r<<endl;
		if(r>0.3 && r<0.7){
			a->SetCetverovektor(this->p1*r,this->p2*r,this->p3*r);
			b->SetCetverovektor(this->p1*(1-r),this->p2*(1-r),this->p3*(1-r));
			break;
		}
	}
	a->printInfo();
	a->setTransverseMomentum();
	b->printInfo();
	b->setTransverseMomentum();

}
