#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TF1.h>

void Analyzer::Loop()
{

	double suma=0.0;
	double sigma_m, sigma_p,tau_hat;
	TCanvas *c1 = new TCanvas("c1","c1");
	c1->Divide(3,1);

	TH1F *t1 = new TH1F("Time","",20,0,10);
	
	
	TF1 *likelihood = new TF1("likelihood","(([0]/x)*TMath::Exp(-[1]/x))",0,10);
	likelihood->SetParameters(1.0,1.0);
	
	TF1 *pdf = new TF1("PDF","((1.0/[0])*TMath::Exp(-x/[0]))*[1]",0,10);	// zadnje je range x , *[1] jer je to faktor normalizacije
	pdf->SetParameters(4,300);
	
	

	
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      suma+=t;
	t1->Fill(t);
   }
   
   
   TF1 *loglikelihood = new TF1("loglikelihood","-2.0*(1000.0*TMath::Log(1.0/(x))-(1.0/x)*[0])",1.1,1.3);
   loglikelihood->SetParameter(0,suma);

	tau_hat=loglikelihood->GetMinimumX();
	sigma_m=tau_hat-loglikelihood->GetX(loglikelihood->GetMinimum(+1.0,1.0,tau_hat-0.01));
	sigma_p=loglikelihood->GetX(loglikelihood->GetMinimum()+1.0,tau_hat,10.0)-tau_hat;

	cout<<sigma_m<<endl;
	cout<<sigma_p<<endl;
   
   c1->cd(1);
   t1->Draw();
   t1->Fit(pdf);
   
   c1->cd(2);
   likelihood->Draw();
   cout<<suma/1000.0<<endl;
   
   c1->cd(3);
   loglikelihood->Draw();
   cout<<loglikelihood->GetMinimumX()<<endl;
   
   
   
   c1->SaveAs("Time.pdf");
}
