#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <TF1.h>
#include <TLine.h>

void Analyzer::Fit(){
   c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
   c1->Divide(2,1);
   c1->cd(1);
   const Int_t n = 5;
   Double_t x[n]  = {1.0,2.0,3.0,4.0,5.0};
   Double_t y[n]  = {9.8,21.2,34.5,39.9,48.5};
   Double_t ex[n] = {0.0,0.0,0.0,0.0,0.0};
   Double_t ey[n] = {1.0,1.9,3.1,3.9,5.1};

	TF1 *funkcija = new TF1("funkcija","x/[0]",0,6);
	funkcija->SetParameter(0,0.1);
	
	
	TF1 *chisqe = new TF1("chisqe","TMath::Power(([0]-x*[1]),2)/([2]*[2])+TMath::Power(([3]-x*[4]),2)/([5]*[5])+TMath::Power(([6]-x*[7]),2)/([8]*[8])+TMath::Power(([9]-x*[10]),2)/([11]*[11])+TMath::Power(([12]-x*[13]),2)/([14]*[14])",9.4,11.0);
	
	chisqe->SetParameter(0,y[0]);
	chisqe->SetParameter(1,x[0]);
	chisqe->SetParameter(2,ey[0]);
	chisqe->SetParameter(3,y[1]);
	chisqe->SetParameter(4,x[1]);
	chisqe->SetParameter(5,ey[1]);
	chisqe->SetParameter(6,y[2]);
	chisqe->SetParameter(7,x[2]);
	chisqe->SetParameter(8,ey[2]);
	chisqe->SetParameter(9,y[3]);
	chisqe->SetParameter(10,x[3]);
	chisqe->SetParameter(11,ey[3]);
	chisqe->SetParameter(12,y[4]);
	chisqe->SetParameter(13,x[4]);
	chisqe->SetParameter(14,ey[4]);
	
	


   gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetTitle("TGraphErrors Example");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gStyle->SetOptFit();
   gr->Fit(funkcija);
   
   
   gr->Draw("AP");


	cout<<1.0/chisqe->GetMinimumX()<<endl;

	double tau_hat,sigma_m,sigma_p,tau_hat1,sigma_m1,sigma_p1;
	tau_hat=1.0/chisqe->GetMinimumX();
	sigma_m=tau_hat-1.0/(chisqe->GetX(chisqe->GetMinimum()+1.0,1.0,tau_hat-0.01));
	sigma_p=1.0/(chisqe->GetX(chisqe->GetMinimum()+1.0,tau_hat,10.0))-tau_hat;

	//cout<<"dsads"<<tau_hat<<endl;
	cout<<sigma_m<<endl;
	cout<<sigma_p<<endl;

	tau_hat1=chisqe->GetMinimumX();
	sigma_m1=tau_hat1-chisqe->GetX(chisqe->GetMinimum()+1.0,1.0,tau_hat1-0.01);
	sigma_p1=chisqe->GetX(chisqe->GetMinimum()+1.0,tau_hat1,10.0)-tau_hat1;
   
   c1->cd(2);
   chisqe->Draw();
   c1->Update();
	TLine *l1 = new TLine(1./tau_hat,1.95,1./tau_hat,chisqe->GetMinimum());
	TLine *l2 = new TLine(tau_hat1-sigma_m1,1.95,tau_hat1-sigma_m1,chisqe->GetMinimum()+1.0);
	TLine *l3 = new TLine(tau_hat1-sigma_p1,1.95,tau_hat1-sigma_p1,chisqe->GetMinimum()+1.0);
	l1->Draw("same");
	l2->Draw("same");
	l3->Draw("same");
   
   cout<<1.0/chisqe->GetMinimumX()<<endl;
   
   c1->SaveAs("opca1.pdf");
	double theta, br=0.0, naz=0.0, greska=0.0, pod_kor=0.0, pod_kv=0.0;
	for(int i=0;i<5;i++){
		br=br+(2.0*x[i]*y[i])/(ey[i]*ey[i]);
		naz=naz+(2.0*x[i]*x[i])/(ey[i]*ey[i]);
	}
	theta=br/naz;
	cout<<1.0/theta<<endl;

//9.8 ± 1.0 , 21.2 ± 1.9 , 34.5 ± 3.1 , 39.9 ± 3.9 , 48.5 ± 5.1

}





