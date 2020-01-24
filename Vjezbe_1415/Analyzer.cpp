#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void Analyzer::Loop()
{
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
   }
}

void Analyzer::Theoretical_noHiggs()
{
	
	TCanvas *c = new TCanvas("c3","c3",500,500);
	c->cd();
	TH1F *exp_noHiggs = new TH1F("exp_noHiggs","",200,0,700);
	
	TRandom *r = new TRandom3();
	t_statistic = new TH1F("t_statistic","",100,0,20);

	TF1 *theoretical_pdf = new TF1("thoretical_pdf","[0]/TMath::Exp(x/[1])",0,700);
	theoretical_pdf->SetParameter(0,1000.0);
	theoretical_pdf->FixParameter(1,100.0);

	for(int i=0;i<1000;i++)
		{
		for(int j=0;j<10000;j++)
			{
				//r->Exp(100);
				exp_noHiggs->Fill(r->Exp(100));	
			}
		for(int k=10;k<690;k=k+5){
			double masa_higgs = k/1.0;
			exp_noHiggs->Fit(theoretical_pdf,"q","",masa_higgs-10,masa_higgs + 10);
			t_statistic->Fill(theoretical_pdf->GetChisquare());}
			

			
		}
	t_statistic->Scale(1./t_statistic->Integral());
	t_statistic->Draw("hist");
	c->SaveAs("t_stat.png");
}

void Analyzer::Expected_p_value_scan()
{
	TCanvas *c1 = new TCanvas("c1","c1",500,500);
	c1->cd();

	TH1F *imaHiggsa = new TH1F ("imaHiggsa","",200,0,700);
	double a = -1., b=-190.0, c = 0.02, sigma=0.00236;
	TRandom *r = new TRandom3();

	double p_value;

	TF1 *theoretical_pdf = new TF1("thoretical_pdf","[0]/TMath::Exp(x/[1])",0,700);
	theoretical_pdf->SetParameter(0,1000.0);
	theoretical_pdf->FixParameter(1,100.0);

	gr = new TGraph();

	double chi_ima;
	int br=1;

	for(int m = 10;m<690;m+=5)
	{
		imaHiggsa = new TH1F ("imaHiggsa","",200,0,700);
		for(int j=0;j<10000;j++)
		{
			if(r->Rndm()>(a*(m*1.0+b)*(m*1.0+b)+c))
				imaHiggsa->Fill(r->Exp(100));	
			else
			        imaHiggsa->Fill(r->Gaus(m*1.0,sigma));
		}
			
			double masa_higgs = m/1.0;
			imaHiggsa->Fit(theoretical_pdf,"q","",masa_higgs-10,masa_higgs + 10);
			
			chi_ima = (theoretical_pdf->GetChisquare());
			p_value=t_statistic->Integral(t_statistic->GetXaxis()->FindBin(chi_ima),200)/t_statistic->Integral();

		
			gr->SetPoint(br,m,p_value);
			br++;
			
			
		
		
	}
   TAxis *axis = gr->GetXaxis();

   axis->SetLimits(100.,700.);                 // along X
   //gr->GetHistogram()->SetMaximum(20.);   // along          
   //gr->GetHistogram()->SetMinimum(-20.);
c1->SetLogy();
gr->Draw();

//imaHiggsa->Draw();

c1->SaveAs("p_value.png");
}

void Analyzer::PlotMass()
{

TCanvas *c4 = new TCanvas("c4","c4",500,500);
TCanvas *c5 = new TCanvas("c5","c5",500,500);
TLorentzVector p1,p2,h;
rekonstr_masa = new TH1F("rekonstr_masa","",200,0,700);
TF1 *theoretical_pdf = new TF1("thoretical_pdf","[0]/TMath::Exp(x/[1])",0,700);
	theoretical_pdf->SetParameter(0,1000.0);
	theoretical_pdf->FixParameter(1,100.0);

if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

     p1.SetPxPyPzE(particle1_px,particle1_py,particle1_pz,particle1_E);
     p2.SetPxPyPzE(particle2_px,particle2_py,particle2_pz,particle2_E);
     h=p1+p2;
     rekonstr_masa->Fill(h.M());
   }

int br=1;

gr1 = new TGraph();
for(int m = 10;m<690;m+=5)
	{		
			
			double masa_higgs = m/1.0;
			rekonstr_masa->Fit(theoretical_pdf,"q","",masa_higgs-10,masa_higgs + 10);
			
			double chi_ima = (theoretical_pdf->GetChisquare());
			double p_value=t_statistic->Integral(t_statistic->GetXaxis()->FindBin(chi_ima),200)/t_statistic->Integral();

		
			gr1->SetPoint(br,m,p_value);
			br++;
			
			
		
		
	}
c5->cd();
TAxis *axis1 = gr1->GetXaxis();
axis1->SetLimits(100.,700.);                 // along X
   //gr->GetHistogram()->SetMaximum(20.);   // along          
   //gr->GetHistogram()->SetMinimum(-20.);
c5->SetLogy();
gr1->SetMinimum(0.00001);
gr1->Draw();
c5->SaveAs("izmjereni_p.png");

c4->cd();

rekonstr_masa->Fit(theoretical_pdf);
rekonstr_masa->Draw();
c4->SaveAs("rekonstr_masa.png");
}
