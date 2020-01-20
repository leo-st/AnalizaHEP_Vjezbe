#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TRandom3.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>
#include <TMath.h>

void Analyzer::Loop()
{
double suma=0;
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	suma=suma + height;
      
   }
t_obs = suma/100;

}

void Analyzer::Theoretical_t_gauss()
{
	double p_value;
	TCanvas *c = new TCanvas("c3","c3",500,500);
	c->cd();
	TH1F *t_statistic = new TH1F("gauss","",100,160,170);
	TRandom *r = new TRandom3();
	double suma=0;

	for(int i=0;i<1000000;i++)
		{
		for(int j=0;j<100;j++)
			{
				suma=suma + r->Gaus(164.7,7.1);
			}
		suma=suma/100;
		t_statistic->Fill(suma);
		suma=0;}	
	t_statistic->Draw();

	p_value=t_statistic->Integral(t_statistic->GetXaxis()->FindBin(t_obs),100)/t_statistic->Integral(); //100 je broj binova
	double z_score = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value);
	cout<<"p vrijednost je: "<<p_value<<", a signifikantnost: "<<z_score<<endl;
			
	c->SaveAs("t_stat.png");
}

void Analyzer::ah_test(double sr, double gr)
{
	double p_value_null, p_value_alt, z_null, z_alt;
	TCanvas *c = new TCanvas("c3","c3",500,500);
	c->cd();
	TH1F *alternative = new TH1F("gauss","",100,160,170);
	TH1F *spain = new TH1F("gauss","",100,160,170);
	TRandom *r = new TRandom3();
	double suma_s=0,suma_alt=0;

	for(int i=0;i<1000000;i++)
		{
		for(int j=0;j<100;j++)
			{
				suma_s=suma_s + r->Gaus(168.0,7.0);
				suma_alt=suma_alt + r->Gaus(sr,gr);
			}
		suma_s=suma_s/100;
		suma_alt=suma_alt/100;
		spain->Fill(suma_s);
		alternative->Fill(suma_alt);
		suma_s=0;
		suma_alt=0;}	

	p_value_null=spain->Integral(spain->GetXaxis()->FindBin(t_obs),100)/spain->Integral(); //100 je broj binova
	z_null = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value_null);
	cout<<p_value_null<<"       "<<z_null<<endl;
	p_value_alt=alternative->Integral(alternative->GetXaxis()->FindBin(t_obs),100)/alternative->Integral(); //100 je broj binova
	z_alt = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value_alt);
	cout<<p_value_alt<<"        "<<z_alt<<endl;

	spain->SetLineColor(kRed);
	spain->SetTitle("Alternativnu hipotezu odbacujemo s CL od 99.7 %");
	spain->Draw();
	alternative->Draw("same");

	

	TLine *line = new TLine(t_obs,0,t_obs,30000);
	line->Draw();

	TLegend *legend = new TLegend(0.1,0.8,0.3,0.9);
	//legend->SetHeader("Header","C");

	legend->AddEntry(spain,"spanjolska","l");
	legend->AddEntry(alternative,"italija","l");
	legend->Draw();

	c->SaveAs("t_stat_italy.png");
}
