#include <ElementaryParticle.h>


int main(){
	srand (time(NULL));
	/*ElementaryParticle ep1, ep2;
	ep1.ime="Bozon";
	ep1.masa=4;
	ep1.bozon=true;

	ep2.ime="Kvark";
	ep2.masa=0.1;
	ep2.bozon=false;
	
	ep1.printInfo();
	ep2.printInfo();*/

	ElementaryParticle * ep1,*ep2,*ep3;
	ep1 = new ElementaryParticle("Bozon", 125, true);
	ep2 = new ElementaryParticle();
	ep3 = new ElementaryParticle();
	ep1->printInfo();
	ep2->printInfo();

	ep1->SetCetverovektor(36.5,42.1,72.3);
	ep1->setTransverseMomentum();
	ep1->bosonDecay(ep2,ep3);
	return 0;
}
