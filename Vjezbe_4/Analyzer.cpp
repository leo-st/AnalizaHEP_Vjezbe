#include<Analyzer.h>
#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TApplication.h>
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


void Analyzer::convertTextToRootFile(){
	TFile* hfile=TFile::Open("Analysis.root","RECREATE");
	TTree *tree=new TTree("T","Random podaci za neke cestice");
	tree->Branch("EventNumber",&EventNumber);
	tree->Branch("DecayParticle1_Name",&DecayParticle1_Name);
	tree->Branch("DecayParticle1_mass",&DecayParticle1_mass);
	tree->Branch("DecayParticle1_isBoson",&DecayParticle1_isBoson);
	tree->Branch("DecayParticle1_px",&DecayParticle1_px);
	tree->Branch("DecayParticle1_py",&DecayParticle1_py);
	tree->Branch("DecayParticle1_pz",&DecayParticle1_pz);
	tree->Branch("DecayParticle1_E",&DecayParticle1_E);
	tree->Branch("DecayParticle1_TransMomentum",&DecayParticle1_TransMomentum);
	tree->Branch("DecayParticle2_Name",&DecayParticle1_Name);
	tree->Branch("DecayParticle2_mass",&DecayParticle1_mass);
	tree->Branch("DecayParticle2_isBoson",&DecayParticle1_isBoson);
	tree->Branch("DecayParticle2_px",&DecayParticle1_px);
	tree->Branch("DecayParticle2_py",&DecayParticle1_py);
	tree->Branch("DecayParticle2_pz",&DecayParticle1_pz);
	tree->Branch("DecayParticle2_E",&DecayParticle1_E);
	tree->Branch("DecayParticle2_TransMomentum",&DecayParticle1_TransMomentum);
	


	string line;
	fstream newfile;
	newfile.open("Analysis.txt", ios::in);
	if(newfile.is_open()){
		while(getline(newfile, line)){
			stringstream linestream(line);
		linestream>> EventNumber >> DecayParticle1_Name>>DecayParticle1_mass>>DecayParticle1_isBoson>>DecayParticle1_px>>DecayParticle1_py>>DecayParticle1_pz>>DecayParticle1_E>>DecayParticle1_TransMomentum>> DecayParticle2_Name>>DecayParticle2_mass>>DecayParticle2_isBoson>>DecayParticle2_px>>DecayParticle2_py>>DecayParticle2_pz>>DecayParticle2_E>>DecayParticle2_TransMomentum;
			tree->Fill();

		}
		newfile.close();
	}
	hfile->Write();
	hfile->Close();

	
}

