#include<iostream>

using namespace std;


class ElementaryParticle{
	public:
		ElementaryParticle(string name, int mass, bool boson);

		string ime;
		double masa;
		bool bozon;

		void printInfo();
		
};
