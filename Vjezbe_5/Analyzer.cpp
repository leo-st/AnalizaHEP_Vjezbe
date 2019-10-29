#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{	
	TCanvas *c= new TCanvas("c","c",900,900);
	TH1F *h1= new TH1F("DecayParticle1_TransMomentum", "naslov",50,0,100);
	
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	h1->Fill(DecayParticle1_TransMomentum);
   }
   h1->Draw();
   c->SaveAs("test.pdf");
}

