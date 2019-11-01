#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <cmath>

void Analyzer::Loop()
{	
	TLorentzVector* v1=new TLorentzVector();
	TCanvas *c= new TCanvas("c","c",900,900);
	c->Divide(2,1);
	TH1F *h1= new TH1F("DecayParticle1_TransMomentum", "naslov",50,0,100);
	TH1F *h2= new TH1F("DecayParticle2_TransMomentum", "naslov",50,0,100);
	TH1F *h3= new TH1F("Higgs_TransMomentum", "Higgs_TransMomentum",50,0,200);
	h1->SetStats(0);
	h2->SetStats(0);
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	h1->Fill(DecayParticle1_TransMomentum);
	h2->Fill(DecayParticle2_TransMomentum);
	v1->SetPxPyPzE(DecayParticle1_px+DecayParticle2_px,DecayParticle1_py+DecayParticle2_py,DecayParticle1_pz+DecayParticle2_pz,sqrt(pow(DecayParticle1_px+DecayParticle2_px,2)+pow(DecayParticle1_py+DecayParticle2_py,2)+pow(DecayParticle1_pz+DecayParticle2_pz,2)+pow(DecayParticle1_mass+DecayParticle2_mass,2)));
	h3->Fill(sqrt(v1->Px()*v1->Px()+v1->Py()*v1->Py()));
   }
   c->cd(1);
   h1->GetXaxis()->SetTitle("Transverzalna kolicina gibanja");
   h1->GetYaxis()->SetTitle("Broj dogadaja");
   h1->SetLineColor(kRed);
   
   h2->SetLineColor(kBlue);
   
   h1->SetTitle("Distribucija transvezalne kolicine gibanja");
   h1->SetFillColor(kRed);
   h1->Draw();
   
   h2->Draw("same");
   
   TLegend* t1 = new TLegend(0.6, 0.7, 0.89, 0.89);
   t1->SetHeader("Personalizirana legenda","C");
   t1->AddEntry(h1, "transverzalna kolicina gibanja 1");
   t1->AddEntry(h2, "transverzalna kolicina gibanja 2");
   t1->Draw();
   c->cd(2);
   h3->Draw();

   c->SaveAs("test.pdf");
}

