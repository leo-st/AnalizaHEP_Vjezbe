#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>

void Analyzer::Loop(TString filename)
{

 TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/ElectronTraining/Electrons.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/ElectronTraining/Electrons.root");
      }
     
      f->GetObject(filename,tree);

	
   Init(tree);



      	
     
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
	
	if(filename=="background"){
	    	h1_trans_mom_poz->Fill(ele_pt);
		h1_scl_eta_poz->Fill(scl_eta);
		h1_ele_hadronicOverEm_poz->Fill(ele_hadronicOverEm);
		h1_ele_gsfchi2_poz->Fill(ele_gsfchi2);
		h1_ele_fbrem_poz->Fill(ele_fbrem);
		h1_ele_ep_poz->Fill(ele_ep);
		h1_ele_eelepout_poz->Fill(ele_eelepout);
		h1_ele_pfChargedHadIso_poz->Fill(ele_pfChargedHadIso);}
	else{
		h1_trans_mom_sig->Fill(ele_pt);
      		h1_scl_eta_sig->Fill(scl_eta);
		h1_ele_hadronicOverEm_sig->Fill(ele_hadronicOverEm);
		h1_ele_gsfchi2_sig->Fill(ele_gsfchi2);
		h1_ele_fbrem_sig->Fill(ele_fbrem);
		h1_ele_ep_sig->Fill(ele_ep);
		h1_ele_eelepout_sig->Fill(ele_eelepout);
		h1_ele_pfChargedHadIso_sig->Fill(ele_pfChargedHadIso);}
   }


}

void Analyzer::Draw()
{
	TCanvas *c = new TCanvas("c3","c3",1800,900);
	c->Divide(4,2);
	c->cd(1);
	h1_trans_mom_sig->SetLineColor(kRed);
	h1_trans_mom_poz->Draw();
	h1_trans_mom_sig->Draw("same");
	c->cd(2);
	h1_scl_eta_sig->SetLineColor(kRed);
	h1_scl_eta_poz->Draw();
	h1_scl_eta_sig->Draw("same");
	c->cd(3);
	h1_ele_hadronicOverEm_sig->SetLineColor(kRed);
	h1_ele_hadronicOverEm_poz->Draw();
	h1_ele_hadronicOverEm_sig->Draw("same");
	c->cd(4);
	h1_ele_gsfchi2_sig->SetLineColor(kRed);
	h1_ele_gsfchi2_poz->Draw();
	h1_ele_gsfchi2_sig->Draw("same");
	c->cd(5);
	h1_ele_fbrem_sig->SetLineColor(kRed);
	h1_ele_fbrem_poz->Draw();
	h1_ele_fbrem_sig->Draw("same");
	c->cd(6);
	h1_ele_ep_sig->SetLineColor(kRed);
	h1_ele_ep_poz->Draw();
	h1_ele_ep_sig->Draw("same");
	c->cd(7);
	h1_ele_eelepout_sig->SetLineColor(kRed);
	h1_ele_eelepout_poz->Draw();
	h1_ele_eelepout_sig->Draw("same");
	c->cd(8);
	h1_ele_pfChargedHadIso_sig->SetLineColor(kRed);
	h1_ele_pfChargedHadIso_poz->Draw();
	h1_ele_pfChargedHadIso_sig->Draw("same");

c->SaveAs("slika.png");
	
}

void Analyzer::MVATraining(TString metoda)

{
TMVA::Tools::Instance();
   // Here the preparation phase begins
   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/ElectronTraining/Electrons.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/ElectronTraining/Electrons.root");
      }
     
      
	
   TTree *signalTree     ;
   TTree *background     ; 

   f->GetObject("signal",signalTree);
	
   Init(signalTree);

   f->GetObject("background",background);
	
   Init(background);



   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";
   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   dataloader->AddVariable( "ele_pt","var_1","", 'F' );
   dataloader->AddVariable( "scl_eta", "var_2", "", 'F' );
   dataloader->AddVariable( "ele_fbrem",                "var_3", "", 'F' );
  
   
   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree    ( signalTree,     1. );
   dataloader->AddBackgroundTree( background, 1. );
  
  
   dataloader->PrepareTrainingAndTestTree( "","",
                                        "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
   if (metoda=="MLP")
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

   if (metoda=="BDTG") // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );
   
   // For an example of the category classifier usage, see: TMVAClassificationCategory
   //
   // --------------------------------------------------------------------------------------------------
   //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
   // STILL EXPERIMENTAL and only implemented for BDT's !
   //
   //     factory->OptimizeAllMethods("SigEffAt001","Scan");
   //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
   //
   // --------------------------------------------------------------------------------------------------
   // Now you can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events
   factory->TrainAllMethods();
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
   // --------------------------------------------------------------
   // Save the output
   outputFile->Close();
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   //if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );
   //return 0;
}
