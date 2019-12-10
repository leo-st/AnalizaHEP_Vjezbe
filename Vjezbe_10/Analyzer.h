

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <TGraphErrors.h>

using namespace std;


class Analyzer {
public :

   virtual void  Fit();
private:
	TCanvas *c1;
	TGraphErrors *gr;


};

