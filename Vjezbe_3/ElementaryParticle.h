#include<iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>

using namespace std;


class ElementaryParticle{
	public:
		ElementaryParticle(string name, int mass, bool boson);
		ElementaryParticle();

		double p1;
		double p2;
		double p3;
		double E;


		string ime;
		double masa;
		bool bozon;

		void SetCetverovektor(double, double, double);

		double setTransverseMomentum();

		void bosonDecay(ElementaryParticle *a,ElementaryParticle *b);

		void printInfo();
		
};
