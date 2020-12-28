////////////////////////////////////////////////////////////
// This class has been automatically generated on         //
// Thu Dec 10 10:02:43 2020 by ROOT version 6.14/09       //
// from TTree Events/Events                               //
// found on file: tree_1.root                             //
////////////////////////////////////////////////////////////

// #define UL17_Analyzer_NANO_AOD_cxx
// #include "UL17_Analyzer_NANO_AOD.h"

#define UL17_Analyzer_NANO_AOD_with_LepJetClean_cxx
#include "UL17_Analyzer_NANO_AOD_with_LepJetClean.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
       if (argc < 2){ 
                std::cout<<"pass the text file containing root file names "<<std::endl;
                exit(0);
        }

        gROOT->ProcessLine("#include <vector>");
        gROOT->ProcessLine("#include <map>");

        // UL17_Analyzer_NANO_AOD a(argv[1]);
        UL17_Analyzer_NANO_AOD_with_LepJetClean  a(argv[1]);

        TString InputTxtFile = argv[1];
        TString OutputFileName = InputTxtFile.ReplaceAll(".txt","");
        
        // a.Loop(OutputFileName.Data(), 2, 400.0  , 70.0  , "BeforeCleaning");
        a.Loop(OutputFileName.Data());

} 


// void UL17_Analyzer_NANO_AOD::Loop(TString OutputFileName)

void UL17_Analyzer_NANO_AOD_with_LepJetClean::Loop(TString OutputFileName)
{
//======================================================================================================================================//
//   In a ROOT session, you can do:	
//      root> .L UL17_Analyzer_NANO_AOD.C
//      root> UL17_Analyzer_NANO_AOD t
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
//========================================================================================================================================//

   if (fChain == 0) return;
  
    TString xsec_str = OutputFileName ;
// Output root file is declared and named ============================

   OutputFileName = OutputFileName + "_Full_Selection_26-12-20.root";
   // OutputFileName = OutputFileName + "_NoMatchLep_11-12-20.root";

   TFile* f2 = new TFile(OutputFileName.Data(),"recreate");  

// Output root file is declared and named ============================

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   cout <<"\n Yo man It works";

// ================================Histograms are defined and declared for the root files ===========================

   // Define_Mt_Histo() ;  
   // Histo_Cut_Efficiency_Flow() ;
   // Histo_Muon_ID_Study() ;

   // Define_2DMass_Histo();    // for gen level plots

   Define_Histo_For_Global_Var() ;
   Define_Kinematic_Histo_for_RecoObject();
   Define_DelatR_Histo_for_RecoObject() ;
   Define_Kinematic_Histo_for_HiggsJet() ;
   // Define_Histograms_For_LeptonJet_Cleaning_Effect() ;


   // Define_Tag_Jet_Histo() ;    // for tagged jets plots at reco level
   // Define_Reco_tagjetHisto() ;   
   // dR_tagjetHisto() ;     

   // Category_Object_Histo() ;     // for category I plots
   // Category_Object_dRHisto() ;     
   // Category_Object_MtHisto() ; 

//=================================== Histograms are defined and declared for the root files =============================

   float Eta = 0.0 ; 	
   int count = -1 ;
   int id = -1 ;       //   id for defining particle type,, mu= 0, ele = 2, AK4qjet = 4, AK8jet= 12(W) 
   int nLepton = 0 ;
   int check = -1 ;
   TString  UseSortedJets = "Yes" ;
   TString  Filling_at_Preselection = "No" ; // Put it Yes for preselection filling
   TString  MET  = "MET" ;

// Event Loop started here and main analyzing code starts ==============================================================================

    Luminosity_Normalization(OutputFileName) ;


   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      Long64_t ientry = LoadTree(jentry);
      
      // if (ientry > 1000) break;  // Run it to check for small events otherwise COMMENT IT !!!!

      nb = fChain->GetEntry(jentry);   nbytes += nb;

      Cut_Efficiency_Flow->Fill(0.5, factor);     // for Total events in MC sample

	    // cout << "\n\n For Event,   " << jentry ;
      Clear_Vector() ;

      //========= Preselection of event requiring atleast of lepton and jet =====================================================================
      if ( PV_npvsGood == 0 ) continue;


      Cut_Efficiency_Flow->Fill(1.5, factor);     // for Primary Vertex Passed events
      Cut_Efficiency_Flow->Fill(2.5, factor);     // for MuTrigger Passed events

      Good_PV_Histo ->Fill( PV_npvsGood,factor);

      
      nLepton = nElectron + nMuon ;

	  // if (!( nLepton > 0  && nFatJet > 0  ))   continue ;


      //================================================= GENERAL SELECTION OF OBJECTS=================================================
	  
	  ////////////////////////////////////////////////////
	  //  0  for nMET"}, 
      //  index 1   for nElectron  Filling Population Plot
      //  index 2   for nMuon  Filling Population Plot
      //  index 3   for nJet  Filling Population Plot
      //  index 4   for nFatJet  Filling Population Plot
      //  index 5   for nForwJet  Filling Population Plot
      //  index 6   for nCleanJet  Filling Population Plot
      //  index 7   for nbjet  Filling Population Plot
	  //  Prog_ID for defining particle type,, 
	  //   0   for MET ..    // 1   for MET_su
	  //   2   for Electron1 //   3   for Electron2
	  //   4   for Muon1     //   5   for Muon2
	  //   6   for Jet1      //   7   for Jet2
	  //   8   for FatJet1   //   9   for FatJet2_
	  //   10  for ForwJet1  //   11  for ForwJet2
	  //   12  for CleanJet1 //   13  for CleanJet2
	  //   14  for bJet1     //   15  for bJet2
	  ///////////////////////////////////////////////////

      //===================================================== Electron Selection =======================================================================

      // cout << "\n No. of electron = " << nElectron ;

      Check_Electrons_For_Event_N_Fill(Filling_at_Preselection) ;

      h_object_no.at(1) ->Fill(n_ele.size() , factor );          //  index 1   for nElectron  Filling Population Plot


      //===================================== Muon Selection ==============================================================================

      // cout << "\n No. of muon = " << nMuon ;

	    check = -1 ;

	    Check_Muons_For_Event_N_Fill( Filling_at_Preselection) ;

	    h_object_no.at(2) ->Fill(n_Mu.size() , factor );       //  index 2   for nMuon  Filling Population Plot


      //===============================  Muon Selection Ends =======================================================================

      // // ========================Study Jet Lepton Cleaning =============================================
    
      // Study_JetLepton_Cleaning_Effect() ;

      // continue ;

      //=============================== Fat Jet Selection =====================================================================================================

      // cout << "\n No. of fatjet = " << nFatJet << endl;


      Check_CleanFatJet_For_Event_N_Fill( Filling_at_Preselection + "FatJetSorting");  // For Cleaned jet

      h_object_no.at(4) ->Fill(n_AK8Jet.size(), factor );       //  index 4   for nFatJet  Filling Population Plot


      //====== FatJet Selection Ends=====================================================================================================
      //====== MET  Selection =====================================================================================================
      
      // MET = Filling_at_Preselection + "MET" ;

      Fill_Lepton_Hist_Preselction_LvL( Filling_at_Preselection + "MET"  , 0 , 0) ; // both entries 0 for YesMET to Fill or NoMET  

      //====== MET Selection Ends=====================================================================================================
      //============================== Jet Selection =======================================================================

      // cout << "\n No. of jet = " << nJet ;

      Check_CLeanedJet_For_Event_N_Fill( Filling_at_Preselection) ;  /// PUT "Yes" for filling 

      if ( n_jet.size() > 0 ) Jet_sorting_pT_based_After_Cleaning("Yes") ;

      h_object_no.at(3) ->Fill(n_jet.size(), factor );      //  index 3   for nJet  Filling Population Plot
      h_object_no.at(5) ->Fill(n_forwjet.size(), factor );  //  index 5   for nForwJet  Filling Population Plot

      // if you want to continue with the sorted jets Put "Yes" or else "No"


      if (UseSortedJets.Contains("Yes"))
      {
         n_jet = jet_sort ;
         n_AK8Jet = fatjet_sort ;

      }

      // ==================== Generate Clean Jet from fatJet using dR > 1.2 and Check is for deltaR plots ======================///////////////////

      // if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_N_Cleaning_Jet_from_FatJet("CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots

      if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_For_LeptonClean_Jet_from_FatJet(Filling_at_Preselection +"CHECKNCLEAN"); // PUT NO if don't want to plot Dr plots


      h_object_no.at(6) ->Fill(n_cleanjet.size(), factor );   //  index 6   for nCleanJet  Filling Population Plot


	    //====== Jet Selection Ends=====================================================================================================
	  

      // ========================Check DeltaR for Cleaned Jets wrt Muon =============================================

      // cout << "\n For Event,   " << jentry ;

      // if ( n_Mu.size() > 0 ) Check_deltaR_For_Muon_wrt_LepCleanJets("Yes" ) ;

      //////============= Jet Tagging Selections ======================================///////////////////////////////////////////////

      if ( n_AK8Jet.size() > 0 ) HiggsJet_Selection_Using_PUPPI_Variables( 7, 70.0) ;

	    Hist_for_Leading_HiggsJet.at(16) ->Fill( Higgsjets.size(), factor );
	    // if ( Higgsjets.size() > 0 && ( n_Mu.size() > 0 ) ) Check_deltaR_For_Muon_wrt_LepCleanJets( "CHECK") ;  


      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      
      ///////-========-HERE WE AFTER SELECTION OF EACH PBJECTS AND TEST WE CHECK SELECTIONS AND FILL SELECTION FLOW HISTOGRAMS  =====---/////////////////////////
      //////====================== ALSO FILL EACH OBJECT AT THIS TIME BUDDY ============================//////////////////////////


      if ( n_forwjet.size() == 0)  continue ; 

      Cut_Efficiency_Flow -> Fill( 3.5, factor);   // Forward Jet tag

      if ( MET_pt < 10.0 )   continue ;

      Cut_Efficiency_Flow -> Fill( 4.5, factor);    // METcut 

      if ( n_Mu.size() == 0 )  continue ;

      Cut_Efficiency_Flow -> Fill ( 5.5, factor);   // Muon tag in the event

      if ( n_AK8Jet.size() == 0) continue ;  

      Cut_Efficiency_Flow -> Fill (6.5, factor);   // Fatjet tag

      if ( n_cleanjet.size() == 0 ) continue ;

      //=== PRESELECTION LEVEL CLEARED ================///////////////////
      Scalar_Sum_pT_Function() ; // Fiiled and calculated after preselection 
      Good_PV_Pr_Histo ->Fill( PV_npvsGood,factor);

      Fill_Object_Hist_After_Preselction_LvL( "Yes" ) ;

      Cut_Efficiency_Flow -> Fill ( 7.5, factor);  // Clean jet tag


      if ( Higgsjets.size() == 0 ) continue ;

      Cut_Efficiency_Flow -> Fill ( 8.5, factor); // Higgjet Tag
      Cut_Efficiency_Flow -> Fill ( 9.5, factor); // Higgjet Pt Tag  

      if ( Higgsjets.size() > 0 ) Fill_HiggsJet_Hist_Preselction_LvL( "FillHiggsJet") ;
    

      Cut_Efficiency_Flow -> Fill ( 10.5, factor); // ST cut






   }  // EVENT LOOP ENDED HERE AND MAIN ANALYZING CODE ENDS !!!!!!!!!====================!!!!!!!!!!!!!!!!!

    
   // Muon_Scale_file->Close();
   // PileUp_file->Close();

   f2->Write();   // output file is written here and closed
   f2->Close();
}


 // "Forward Jet Tag"    ,     //3   
 // "MET Cut" ,                //4     
 // "Muon Cut",                //5
 // "AK8 Jet Tag" ,            //6
 // "Clean Jet Tag",           //7     
 // "Higgs Tag",               //8     
 // "Higgs_Pt Cut",            //9   
 // "St Cut"  ,                //10    
 // "bjet tag",                //11    
 // "dR check",                //12    
 // "Lep Iso",                 //13    