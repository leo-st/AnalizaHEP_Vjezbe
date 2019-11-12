#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <THStack.h>

void Analyzer::PlotMass(){
	TCanvas *c2 = new TCanvas("c2","c2");
	THStack *hs = new THStack("hs","hs");
	hs->Add(higgs);
	hs->Add(qqZZ);
	
	c2->cd();
   	hs->Draw();
   	c2->SaveAs("higgs_histo.pdf");

	masa_kin_sig->Draw("colz");
	c2->SaveAs("2D.pdf");

}

void Analyzer::PlotD(){
	TCanvas *c3 = new TCanvas("c3","c3");
	c3->cd();
	higgs_signal->Scale(1/higgs_signal->Integral());
	qqZZ_poz->Scale(1/qqZZ_poz->Integral());
	higgs_signal->Draw("hist");
	qqZZ_poz->SetLineColor(kRed);
	qqZZ_poz->Draw("same hist");
	c3->SaveAs("kinematicki_diskriminator.pdf");
}

void Analyzer::Loop(TString fileName)
{
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/"+fileName+"/ZZ4lAnalysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/"+fileName+"/ZZ4lAnalysis.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/public/data/"+fileName+"/ZZ4lAnalysis.root:/ZZTree");
      dir->GetObject("candTree",tree);

   	Init(tree);
	TLorentzVector l1, l2, l3, l4, z1, z2, h;
		


	TCanvas *c1 = new TCanvas("c1","c1");
	c1->Divide(2,2);
	
	TH1F *h1 = new TH1F("TransMomentum","",100,0,120); 
	TH1F *h2 = new TH1F("PseudoRapidity","",100,-2.8,2.8);
	TH1F *h3 = new TH1F("Azimutal","",100,-4,4);
	TH1F *h4 = new TH1F("BDT","",100,-2,10);
	
	TH1F *h5 = new TH1F("TransMomentum","",100,0,120);
	TH1F *h6 = new TH1F("PseudoRapidity","",100,-2.8,2.8);
	TH1F *h7 = new TH1F("Azimutal","",100,-4,4);
	TH1F *h8 = new TH1F("BDT","",100,-2,10);
	
	TH1F *h9 = new TH1F("TransMomentum","",100,0,120);
	TH1F *h10 = new TH1F("PseudoRapidity","",100,-2.8,2.8);
	TH1F *h11 = new TH1F("Azimutal","",100,-4,4);
	TH1F *h12 = new TH1F("BDT","",100,-2,10);
	
	TH1F *h13 = new TH1F("TransMomentum","",100,0,120);
	TH1F *h14 = new TH1F("PseudoRapidity","",100,-2.8,2.8);
	TH1F *h15 = new TH1F("Azimutal","",100,-4,4);
	TH1F *h16 = new TH1F("BDT","",100,-2,10);

	

	
	
	h1->SetStats(0);
	h2->SetStats(0);
	h3->SetStats(0);
	h4->SetStats(0);
	h5->SetStats(0);
	h6->SetStats(0);
	h7->SetStats(0);
	h8->SetStats(0);
	h9->SetStats(0);
	h10->SetStats(0);
	h11->SetStats(0);
	h12->SetStats(0);
	h13->SetStats(0);
	h14->SetStats(0);
	h15->SetStats(0);
	h16->SetStats(0);
	
	
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
      
   h1->Fill(LepPt->at(0));
	h2->Fill(LepEta->at(0));
	h3->Fill(LepPhi->at(0));
	h4->Fill(LepBDT->at(0));
	
	h5->Fill(LepPt->at(1));
	h6->Fill(LepEta->at(1));
	h7->Fill(LepPhi->at(1));
	h8->Fill(LepBDT->at(1));  
	
	h9->Fill(LepPt->at(2));
	h10->Fill(LepEta->at(2));
	h11->Fill(LepPhi->at(2));
	h12->Fill(LepBDT->at(2));  
	
	h13->Fill(LepPt->at(3));
	h14->Fill(LepEta->at(3));
	h15->Fill(LepPhi->at(3));
	h16->Fill(LepBDT->at(3));   
	
	l1.SetPtEtaPhiM(LepPt->at(0), LepEta->at(0), LepPhi->at(0), 0);
	l2.SetPtEtaPhiM(LepPt->at(1), LepEta->at(1), LepPhi->at(1), 0);
	l3.SetPtEtaPhiM(LepPt->at(2), LepEta->at(2), LepPhi->at(2), 0);
	l4.SetPtEtaPhiM(LepPt->at(3), LepEta->at(3), LepPhi->at(3), 0);

	z1=l1+l2;
	z2=l3+l4;

	h=z1+z2;

	D=1/(1+(70*p_QQB_BKG_MCFM/p_GG_SIG_ghg2_1_ghz1_1_JHUGen));
	
	if(fileName=="ggH125")	{	higgs->Fill(h.M());
	higgs_signal->Fill(D);
	masa_kin_sig->Fill(h.M(), D);
}
	
	if(fileName=="qqZZ")	{
	qqZZ->Fill(h.M());
	qqZZ_poz->Fill(D); }
	  
   }
   c1->cd(1);
   
   h1->GetXaxis()->SetTitle("Transverzalna kolicina gibanja");
   h1->GetYaxis()->SetTitle("Broj dogadaja");
   h1->SetLineColor(kRed);
   h5->SetLineColor(kBlue);
   h9->SetLineColor(kGreen);
   h13->SetLineColor(kYellow);
   
   h9->Draw();
   h5->Draw("same");
   h1->Draw("same");
   h13->Draw("same");
   
   TLegend* t1 = new TLegend(0.6, 0.7, 0.89, 0.89);
   t1->SetHeader("TransMomentum","C");
   t1->AddEntry(h1, "lepton #1");
   t1->AddEntry(h5, "lepton #2");
   t1->AddEntry(h9, "lepton #3");
   t1->AddEntry(h13, "lepton #4");
   t1->Draw();
   

   
   c1->cd(2);
   
   h2->GetXaxis()->SetTitle("Pseudorapiditet");
   h2->GetYaxis()->SetTitle("Broj dogadaja");
   h2->SetLineColor(kRed);
   h6->SetLineColor(kBlue);
   h10->SetLineColor(kGreen);
   h14->SetLineColor(kYellow);
   
   h2->Draw();
   h6->Draw("same");
   h10->Draw("same");
   h14->Draw("same");
   
   
   c1->cd(3);
   h3->GetXaxis()->SetTitle("Azimutalni kut");
   h3->GetYaxis()->SetTitle("Broj dogadaja");
   h3->SetLineColor(kRed);
   h7->SetLineColor(kBlue);
   h11->SetLineColor(kGreen);
   h15->SetLineColor(kYellow);
   
   h3->Draw();
   h7->Draw("same");
   h11->Draw("same");
   h15->Draw("same");
   
   c1->cd(4);
   h4->GetXaxis()->SetTitle("BDT rezultat");
   h4->GetYaxis()->SetTitle("Broj dogadaja");
   h4->SetLineColor(kRed);
   h8->SetLineColor(kBlue);
   h12->SetLineColor(kGreen);
   h16->SetLineColor(kYellow);
   
   h4->Draw();
   h8->Draw("same");
   h12->Draw("same");
   h16->Draw("same");
   
   c1->SaveAs("histo"+fileName+".pdf");
   
}
