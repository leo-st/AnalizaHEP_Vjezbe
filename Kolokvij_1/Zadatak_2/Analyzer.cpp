#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <THStack.h>
#include <TLegend.h>

void Analyzer::Loop()
{
	THStack *hs = new THStack("hs","hs");
	TCanvas *c1 = new TCanvas("c1", "c1");
	c1->Divide(3,1);
	
	TH1F *h1 = new TH1F("Ele_pt", "",50,0,200);
	
	TH1F *h2 = new TH1F("Scl_eta", "",50,0,200);
	
	TH1F *h3 = new TH1F("Ele_ep", "",10,0,20);
	TH1F *h4 = new TH1F("Ele_eelepout", "",10,0,20);
	
	h1->SetStats(0);
	h2->SetStats(0);
	h3->SetStats(0);
	h4->SetStats(0);
	
	TH2F* masa_kin_sig = new TH2F("masa_kin","",100,10,120,10,-2.8,2.8);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<100000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      h1->Fill(ele_pt);
      h2->Fill(scl_eta);
      masa_kin_sig->Fill(ele_pt, scl_eta);
      h3->Fill(ele_ep);
      h4->Fill(ele_eelepout);
      
   }
   c1->cd(1);
   h1->GetXaxis()->SetTitle("ele_pt");
   h1->GetYaxis()->SetTitle("broj dogadaja");
   h1->SetLineColor(kRed);
   h1->Draw();
   
   c1->cd(2);
   masa_kin_sig->GetXaxis()->SetTitle("ele_pt");
   masa_kin_sig->GetYaxis()->SetTitle("scl_eta");
   masa_kin_sig->Draw("colz");
   
   c1->cd(3);
   	Double_t norm1 = h3->GetEntries();
	h3->Scale(1/norm1);
   	
   	Double_t norm2 = h4->GetEntries();
	h4->Scale(1/norm2);
   	
  	h3->SetLineStyle(kDashed);
  	h3->SetLineColor(kRed);
  	
  	h4->SetLineColor(kBlue);
  	h4->SetFillColor(kBlue);
  	
  	h3->GetYaxis()->SetTitle("broj dogadaja");
  	h3->Draw();
  	h4->Draw("same");
  	TLegend* t1 = new TLegend(0.6, 0.7, 0.89, 0.89);
   t1->SetHeader("ELE","C");
   t1->AddEntry(h3, "ele_ep");
   t1->AddEntry(h4, "ele_eelepout");
   t1->Draw();
   
   c1->SaveAs("histo.pdf");
}
