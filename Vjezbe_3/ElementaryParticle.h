#include<iostream>

using namespace std;


class ElementaryParticle{
	public:
		ElementaryParticle(string name, int mass, bool boson);

		double p1;
		double p2;
		double p3;
		double E;


		string ime;
		double masa;
		bool bozon;

		void SetCetverovektor(double, double, double);

		void setTransverseMomentum();

		void printInfo();
		
};
