
#include<Analyzer.h>
#include<TROOT.h>
#include<TChain.h>
#include<TFile.h>
#include<TApplication.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Show(){
	TCanvas *c= new TCanvas("c","c");
	TH1F *lower= new TH1F("Lower", "lower",9,0,9);
	TH1F *upper= new TH1F("Upper", "upper",9,0,9);
	lower->SetStats(0);
	upper->SetStats(0);
	double lower_array[9] = {0.017,0.071,0.141,0.219,0.304,0.395,0.491,0.594,0.705};
	double upper_array[9] = {0.295,0.406,0.509,0.605,0.696,0.781,0.859,0.929,0.983};
	for(int i=1;i<10;i++){
		lower->SetBinContent(i,lower_array[i-1]);
		upper->SetBinContent(i,upper_array[i-1]);
	}
	c->cd(1);
	lower->SetMaximum(1.0);
	lower->SetMinimum(0.0);
	upper->SetMaximum(1.0);
	upper->SetMinimum(0.0); 
	lower->Draw();
	upper->Draw("same");
	c->SaveAs("proba.pdf");

}

double Analyzer::Binomial(int r, double p, int N){

	return (Factorial(N)/(Factorial(r)*Factorial(N-r)))*pow(p,r)*pow(1-p,N-r);
}

long int Analyzer::Factorial(int n){
	if(n<=1){
		return 1;
	}
	else{
		return Factorial(n-1)*n;
	}
}

double Analyzer::CPUpper(int r, double cl, int N ){
	int rzauvik=r;
	double sum=0.0;
	double korak=0.001;
	r=r+1;
	while(true){
		while(r<=N){
			sum+=Binomial(r, korak, N);
			
			r++;
		}
		r=rzauvik+1;
		if(sum>1.0-((1.0-cl)/2)){
			cout<<"P+ : "<<korak<<endl;
			break;
		}
		else{
			korak+=0.001;
			sum=0.0;
		}
		
		
	}
	return korak;	
}
double Analyzer::CPLower(int r, double cl, int N ){
	int rzauvik=r;
	double sum=0.0;
	double korak=1.000;
	r=r-1;
	while(true){
		while(r>=0){
			sum+=Binomial(r, korak, N);
			
			r--;
		}
		r=rzauvik-1;
		if(sum>1.0-((1.0-cl)/2)){
			cout<<"P- : "<<korak<<endl;
			break;
		}
		else{
			korak-=0.001;
			sum=0.0;
		}
		
		
	}
	return korak;	
}

void Analyzer::ClopperPearson(int N, double cl){
	int r=1;
	while(r<10){
		cout<<"["<<CPLower(r,cl,N)<<" , "<<CPUpper(r,cl,N)<<"]"<<endl;
		r++;
	}

}

