#include<Analyzer.h>

Analyzer::Analyzer(){
}

void Analyzer::readTextFile(){
	string line;
	fstream newfile;
	newfile.open("Analysis.txt", ios::in);
	if(newfile.is_open()){
		while(getline(newfile, line)){
			stringstream linestream(line);
		linestream>> EventNumber >> DecayParticle1_Name>>DecayParticle1_mass>>DecayParticle1_isBoson>>DecayParticle1_px>>DecayParticle1_py>>DecayParticle1_pz>>DecayParticle1_E>>DecayParticle1_TransMomentum>> DecayParticle2_Name>>DecayParticle2_mass>>DecayParticle2_isBoson>>DecayParticle2_px>>DecayParticle2_py>>DecayParticle2_pz>>DecayParticle2_E>>DecayParticle2_TransMomentum;


		}
		newfile.close();
	}
}

