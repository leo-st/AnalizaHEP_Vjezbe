#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void Analyzer::Loop()
{
	double suma=0;
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      suma+=height;
      
   }
   t_obs=suma/100.0;
}
void Analyzer::Theoretical(){
	TH1F *t_statistic = new TH1F("gauss","",100,160,170);
	TRandom* tr = new TRandom3();

	for(int i=0;i<1000000;i++){
		double sum=0.0;
		for(int j=0;j<100;j++){
			sum+=tr->Gaus(164.7, 7.1);
		} 
		t_statistic->Fill(sum/100);

	}

	 TCanvas *c = new TCanvas("slika","");
	 c->cd();
	 t_statistic->Draw();
	 
	 double p_value = t_statistic->Integral(t_statistic->GetXaxis()->FindBin(t_obs),100)/t_statistic->Integral();
	 cout<<p_value<<endl;
	 c->SaveAs("proba.pdf");

}
