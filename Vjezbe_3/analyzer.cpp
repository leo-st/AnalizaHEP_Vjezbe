#include <ElementaryParticle.h>
#include <iostream>
#include <fstream>


int main(){
	srand (time(NULL));
	ofstream myfile;
	myfile.open("Analysis.txt");
	double xr,yr,zr;

	ElementaryParticle * hb,*ep1,*ep2;
	hb = new ElementaryParticle("Bozon", 125, true);
	ep1 = new ElementaryParticle();
	ep2 = new ElementaryParticle();
	hb->printInfo();

	for(int i=0;i<10000;i++){
		xr=rand()%200-100.0;
		yr=rand()%200-100.0;
		zr=rand()%200-100.0;

		hb->SetCetverovektor(xr,yr,zr);
		
		hb->bosonDecay(ep1,ep2);
		
		myfile<<i<<"\t"<<ep1->ime<<"\t"<<ep1->masa<<"\t"<<ep1->bozon<<"\t"<<ep1->p1<<"\t"<<ep1->p2<<"\t"<<ep1->p3<<"\t"<<ep1->E<<"\t"<<ep1->setTransverseMomentum()<<"\t"<<ep2->ime<<"\t"<<ep2->masa<<"\t"<<ep2->bozon<<"\t"<<ep2->p1<<"\t"<<ep2->p2<<"\t"<<ep2->p3<<"\t"<<ep2->E<<"\t"<<ep2->setTransverseMomentum()<<endl;


	}
	myfile.close();
	hb->~ElementaryParticle();
	ep1->~ElementaryParticle();
	ep2->~ElementaryParticle();	


	return 0;
}
