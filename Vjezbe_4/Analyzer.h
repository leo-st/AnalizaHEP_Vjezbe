#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

class Analyzer{

public:
	Analyzer();
	int EventNumber;
	string DecayParticle1_Name;
	bool DecayParticle1_isBoson;
	double DecayParticle1_mass;
	double DecayParticle1_px;
	double DecayParticle1_py;
	double DecayParticle1_pz;
	double DecayParticle1_E;
	double DecayParticle1_TransMomentum;

	string DecayParticle2_Name;
	bool DecayParticle2_isBoson;
	double DecayParticle2_mass;
	double DecayParticle2_px;
	double DecayParticle2_py;
	double DecayParticle2_pz;
	double DecayParticle2_E;
	double DecayParticle2_TransMomentum;
			
	void readTextFile();
};
