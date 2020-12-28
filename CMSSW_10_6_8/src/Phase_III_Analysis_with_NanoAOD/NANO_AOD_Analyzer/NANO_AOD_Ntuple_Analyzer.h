 //#define Histo

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include <TMinuit.h>
#include <TRandom.h>
#include <string>
#include <iostream>
#include <fstream>
#include <TMath.h>
#include <stdio.h>
#include <TString.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH1I.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>

//#include "TDCacheFile.h"

#include <TCanvas.h>
#include <TLegend.h>
#include <TList.h>
#include <Riostream.h>
#include <TGraphAsymmErrors.h>
#include <map>

//#include <TRFIOFile.h>

#include "TMath.h"
#include <vector>
#include <TList.h>
#include <TLatex.h>
#include <Riostream.h>
#include <set>
#include <TLorentzVector.h>
#include <TVector3.h>
#include "TKDE.h"

#include <iostream>
#include <array>

//using namespace std;
//using namespace TMath; // To include TMath class functions
//using namespace ROOT;


  // =====Global variables for general purpose
    float dEta = -1.0 , dPhi = -1.0 , dR = 0.0  ;
    
    double factor = 1.0 , lumi_factor ;  

    float  Parent_Mass = 0.0 ;
    
    std::string Sample_Name ;
  
    vector <int> CatI_Objects;            // for Higgs, b, l & MET 
  
    int T_top  = -1 ;
    int Top_W  = -1 ;
    int top_Mu = -1 ;
    int nearest_jet = -1 ;

  
  
    Long64_t                 Entries_data;
  
    double Higgs_SDMassCorr = 0.0, Scalar_Sum_pT = 0.0 ;
  
    //---- Cut arrays for different sets------
      float METCut[5] = { 50.0, 50.0, 50.0, 50.0, 50.0} ;
      float Pt_Cut[5] = { 300.0, 300.0, 300.0, 300.0, 300.0} ;
      float St_Cut[8] = { 1000.0, 800.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0} ;
      float Pt_Bjet_Cut[5] = { 200.0, 300.0, 350.0, 400.0, 500.0 };
    
    // =========Vector Elements ===============
      vector <int> n_AK8Jet;
      vector <int> n_ele;
      vector <int> n_Mu ;
      vector <int> b_jet;
      vector <int> n_cleanjet;
      vector <int> b_jettight;
      vector <int> n_jet;
      vector <int> q_jet;
      vector <int> n_forwjet;
      vector <int> b_jetmedium;
      vector <int> puppib_jetloose;
      vector <int> puppib_jet;
      vector <int> puppib_jettight;
      vector <int> puppin_jet;
      vector <int> puppin_forwjet;
      vector <int> puppib_jetmedium;
      vector <int> jet_copy;
      vector <int> jet_sort;      
      vector <int> fjet_sort;      
      vector <int> fjet_copy;
      vector <int> fatjet_copy  ;
      vector <int> fatjet_sort  ;
      
      vector <int> b_jetloose;

      
      vector <int> gen_Wboson    ;
      vector <int> Higgsjets ;
      
      vector <int> gen_udscquark ;
      vector <int> W_boson;
    
    //================Global variables for muon , bjet and Higgsjet ===============
    
      int Tprime_muon      = -1 ;
      int Tprime_bjet      = -1 ;
      int Tprime_Higgs     = -1 ; 
      int gen_jet_object   = -1 ;
      int gen_topquark     = -1 ;
      int gen_bquark       = -1 ;

      int Higgs_300        = -1 ;
      int Higgs_400        = -1 ;      
      int bjet_L           = -1 ;      
      int bjet_M           = -1 ;            
      int muon_T           = -1 ;            
      int muon_M           = -1 ;                  

      TString jet_type ;
    
    
    // for puppiSD Mass  correction from puppiCorr.root file
       TFile  *fi ;   
       TF1* puppisd_corrGEN   ;    
       TF1* puppisd_corrRECO_cen ;    
       TF1* puppisd_corrRECO_for ; 
    
    // for muon ID scale factors from efficiency root files
       TFile  *Muon_Scale_file ;   
       TH2F*  muon_histo_scale_BCDEF ;
       TH2F*  muon_histo_scale_GH ;
       double muon_ID_factor = 1.0;
    
    //list of histograms
    
      TH1D* Cut_Efficiency_Flow ;

      TH1D* Cut_LepIso_dPt_Flow ;
      TH1D* Cut_MET_Cut_Flow ;
      TH1D* Cut_ST_Cut_Flow ;
      TH1D* Cut_Tau42_Flow ;
      TH1D*  Cut_Higgs_Tagging_Flow ;
      TH1D* Cut_pTHiggs_Flow ;
      TH1D* Cut_SDMass_Flow ;
    
    //=======PileUp Reweighted Scale Factors==========================================
  
      TFile  *PileUp_file ;   
      TH1D*  PieUp_ScaleFactor  ;  
    
      std::map<std::string,double> Luminosity_Normalized_factor = { { "Signal_Files/TprimeB_M1500_V3_", 0.003918872 },  
                                                                   { "list_of_Bkgfiles/Bkg_TTbar_v3_", 0.340461318 },    
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",  275.125841637 },    
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_", 114.422768115 },
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_", 39.277533015 },   
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_", 3.654182189 },    
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_", 0.73909964 },   
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_", 0.22617188 },
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_", 0.04281123 },  
                                                                   { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_", 0.014520617 } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",    4.8467027  } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",   4.8579958   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",   2.5917885   } ,  
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",   0.89134297   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",   0.11482444   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",  0.12691790    } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_", 0.19640666   } ,
                                                                   {"list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",  0.0045575256  }    
                                                                 } ;                                                                                                                       
  
    // ===================create an array of Histograms======================
    // Category wise tag object Histogram // main code
  
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Pt;
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Mt ;  
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Eta ;                          
      std::array< std::array< TH1D*, 5> , 6> h_Histo_Phi ;                          
      std::array< std::array< TH1D*, 2> , 6> h_Histo_Mass ;  
      std::array< std::array< TH1D*, 2> , 6> h_Histo_SD ;  
      std::array< std::array< TH1D*, 2> , 6> h_Histo_tau ; 
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dR ;   
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dEta ;  
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dPhi ;  
      std::array< std::array< TH1D*, 6> , 6> h_Histo_dPt ;   


  
  
    // tag object histogram before Category selection // main code
      std::array< TH1D*, 4> h_tag_N ;  
      std::array< TH1D*, 6> h_tag_Pt ;  
      std::array< TH1D*, 6> h_tag_Eta ;                          
      std::array< TH1D*, 6> h_tag_Mass ;  
      std::array< TH1D*, 6> h_tag_PUPPImass ;
      std::array< TH1D*, 6> h_tag_SD ;  
      std::array< TH1D*, 6> h_tag_Pruned;
      std::array< TH1D*, 6> h_tag_tau21 ;  
      std::array< TH1D*, 6> h_tag_tau32 ;  
      std::array< TH1D*, 6> h_tag_Puppitau21 ;  
      std::array< TH1D*, 6> h_tag_Puppitau32 ;  
      std::array< TH1D*, 6> h_tag_Puppitau42 ;  
      std::array< TH1D*, 6> h_tag_CHStau42 ;  
      std::array< std::array< TH1D*,  6> ,  6> h_dR_tagjet ;
  
  
    // dR, dEta, dPhi Histogram for tagjet - reco object // main code
      std::array< TH1D*, 6>  h_dR_Recomu_tagjet ;
      std::array< TH1D*, 6>  h_dEta_Recomu_tagjet ;
      std::array< TH1D*, 6>  h_dPhi_Recomu_tagjet ;
      std::array< TH1D*, 6>  h_dPt_lep_tagjet ;
      std::array< TH1D*, 6>  h_dR_Recob1_tagjet ;
      std::array< TH1D*, 6>  h_dEta_Recob1_tagjet ;
      std::array< TH1D*, 6>  h_dPhi_Recob1_tagjet ;   
      std::array< TH1D*, 6>  h_dR_Recob2_tagjet ;
      std::array< TH1D*, 6>  h_dEta_Recob2_tagjet ;
      std::array< TH1D*, 6>  h_dPhi_Recob2_tagjet ;
  
  
    // mc level object histogram
      std::array< TH1D*, 7>  h_mcobject_pt;
      std::array< TH1D*, 7>  h_mcobject_eta;
      std::array< TH1D*, 7>  h_mcobject_mass;   
      std::array< std::array< TH1D*, 7> , 7>  h_dR_MC ;
      std::array< std::array< TH1D*, 7> , 7>  h_dPt_MC ;
      std::array< std::array< TH1D*, 5> , 5>  h_dR_MCReco ;
  
  
    // reco object variables histogram // main code
      std::array< TH1D*, 15>  h_object_pt ;
      std::array< TH1D*, 15>  h_object_eta ;
      std::array< TH1D*, 15>  h_object_phi ;      
      std::array< TH1D*, 8>  h_object_no ;
      std::array< TH1D*, 3>  h_AK8_Jetmass ;
      std::array< TH1D*, 3>  h_AK8_PUPPImass ;
      std::array< TH1D*, 3>  h_AK8_PUPPISDmass;
      std::array< TH2F*, 3>  h_AK8_PUPPIvsmass ;
      std::array< TH2F*, 3>  h_AK8_CHSvsmass ;
      std::array< TH1D*, 3>  h_AK8_CHSmass ;
      std::array< TH1D*, 3>  h_AK8_PUPPItau21 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau31 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau32 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau41 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau42 ; 
      std::array< TH1D*, 3>  h_AK8_PUPPItau43 ; 
      std::array< TH1D*, 3>  h_AK8_tau21 ; 
      std::array< TH1D*, 3>  h_AK8_tau32 ; 
      std::array< TH1D*, 3>  h_AK8_CHStau42 ; 
      std::array< std::array< TH1D*, 14> , 14>  h_dR_Reco ;
      std::array< std::array< TH1D*, 14> , 14>  h_dEta_Reco ;
      std::array< std::array< TH1D*, 14> , 14>  h_dPhi_Reco ;   
      std::array< TH1D*, 14>  h_dPt_Reco ;
      std::array< std::array< TH1D*, 2> , 2>  h_dR_Reco_lt04  ;
      std::array< std::array< TH1D*, 2> , 2>  h_dPt_Reco_lt10 ;
      std::array< std::array< TH1D*, 2> , 2>  h_dPt_Reco_lt15 ;


      std::array< TH1D*, 3>  h_MET_var ;
      std::array< TH1D*, 9>  h_object_MT ;



      // dPt_dR_mubjet->GetYaxis()->SetTitle("dPT(mu,jet)");
      // dPt_dR_mubjet         ->GetXaxis()->SetTitle("dR(mu,jet)");
      TH2F* dRHbjet_dRlbjet ;
  
      std::array< TH2F*, 4>  h_AK81vsGenObj ;
      std::array< TH2F*, 4>  h_AK82vsGenObj ;
      std::array< TH2F*, 4>  h_AK83vsGenObj ;
  
      TH1D* Good_PV_Histo ;
      TH1D* Good_PV_Pr_Histo ;
      TH1D* ST_Sum_Presel ;
      TH1D* ST_Sum_Evesel ;

      TH1D* h_jetPt_before_jetclean ;
      TH1D* h_jetPt_after_jetclean  ;
      TH1D* h_jetPt_corr_factors ;
      TH2D* h_leadjetPt_factors;
      TH2D* h_subleadjetPt_factors ;

      TH2D* h_leadjetEta_factors   ;
      TH2D* h_subleadjetEta_factors;
      TH2D* h_leadjetPhi_factors   ;
      TH2D* h_subleadjetPhi_factors      ;




      TH2D*  h_leadjetPt_before_after ;

      TH2D*  h_subleadjetPt_before_after  ;

      TH1D* ST_Sum_LeadObj ;  
    // for muon ID study, we define new sets of histogram for pt, eta, phi, vertex
  
      TH1D* Match_Muon_Eta ;
      TH1D* Match_Muon_Phi ;
      TH1D* Match_Primary_Vertex ;
  
      TH1D* Match_Muon_Pt300 ;  // for pT < 300GeV
      TH1D* Match_Muon_Pt1000 ; // for pT > 300GeV
      TH1D* Muon_Pt_ratio ;

      TH1D* Gen_Match_Jet_Pt ; // make histo for efficiency comparisons of Higgs 

      TH1D* h_dR_ak41_ak8Jet1 ;
      TH1D* h_dR_ak42_ak8Jet1 ;
      TH1D* h_dR_ak43_ak8Jet1 ;
      TH1D* h_dR_ak41_ak8Jet2 ;
      TH1D* h_dR_ak42_ak8Jet2 ;
      TH1D* h_dR_ak43_ak8Jet2 ;

      TH1D* h_Parent_Mass ;
      

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////==============CREATE NEW SETS OF HISTOGRAM FOR PHASE III==================///////////////////  
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // reco object variables histogram // main code
      std::array< TH1D*, 16>  Hist_object_pt ;
      std::array< TH1D*, 16>  Hist_object_eta ;
      std::array< TH1D*, 16>  Hist_object_phi ;   

      // Histograms for leading and subleading fatjet
      std::array< TH1D*, 20>  Hist_for_Leading_FatJet ; 
      std::array< TH1D*, 20>  Hist_for_Subleading_FatJet ; 
      std::array< TH1D*, 22>  Hist_for_Leading_HiggsJet ; 
      
      std::array< TH1D*, 9>   DeltaR_Hist_FatJet_wrt_jet ;   
      std::array< TH1D*, 9>   DeltaR_Hist_Muon_wrt_jet ; 

      std::array< TH1D*, 9>   Hist_for_bTag_Variable ;   



      // Histograms for Lepton-Jet Cleaned Jets  ===== COmparing before and after effects
      std::array< TH1D*, 20>  Hist_for_LeptonCleaned_Jet ; 
      std::array< TH1D*, 16>  Hist_for_LeptonCleaned_FatJet ;


      TH2F* dPt_dR_mu_cleanjet1  ; 
      TH2F* dPt_dR_mu_jet1  ; 

      TH2F* dPt_dR_mu_cleanjet2  ; 
      TH2F* dPt_dR_mu_jet2  ; 

      std::array< TH2D*, 8> Hist_DeltaR_wrt_Pt_LepCleanJet  ;
      std::array< TH2D*, 4> Hist_DeltaPt_wrt_Pt_LepCleanJet ;
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////============== NEW SETS OF HISTOGRAM FOR PHASE III==================/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////




      void  Clear_Vector() {
         //   for clearing objects vector
         n_AK8Jet.clear(); 
         n_ele.clear(); 
         n_Mu.clear();
         n_jet.clear();    // main code
         n_cleanjet.clear();

         q_jet.clear();    // main code
         n_forwjet.clear(); // main code
         b_jetloose.clear();// main code
         b_jet.clear();    // main code
         b_jetmedium.clear();    // main code
         b_jettight.clear();    // main code

         jet_copy.clear();
         jet_sort.clear();         

         fjet_copy.clear();
         fjet_sort.clear();    

         fatjet_copy.clear()  ;
         fatjet_sort.clear()  ;

         puppin_jet.clear();    // main code
         puppin_forwjet.clear(); // main code
         puppib_jetloose.clear();// main code
         puppib_jet.clear();    // main code
         puppib_jetmedium.clear();    // main code
         puppib_jettight.clear();    // main code

         Higgsjets.clear() ;
         W_boson.clear();
         CatI_Objects.clear() ;    

         gen_Wboson.clear();
         gen_udscquark.clear();      
           
      }

    // ======================LepIsoCut Study =======================================================
      std::map<int, TString > Cut_LepIso_Variable = {
                                                   { 1  , "Preselect"},
                                                   { 2  , "TkIsoLoose"} ,
                                                   { 3  , "TkIsoTight"} ,                 
                                                   { 4  , "MiniIsoLoose"} ,                  
                                                   { 5  , "MiniIsoMedium"} ,
                                                   { 6  , "MiniIsoTight"} ,
                                                   { 7  , "MiniIsoVeryTight"} ,
                                                   } ;
      
      std::map<TString, int > LepIso_IDbit = {  
                                        {"TkIsoLoose"           , 11 } ,
                                        {"TkIsoTight"           , 12 } ,
                                        {"MiniIsoLoose"         , 18 } ,
                                        {"MiniIsoMedium"        , 19 } ,
                                        {"MiniIsoTight"         , 20 } ,
                                        {"MiniIsoVeryTight"     , 21 } , 
                                       } ;


      std::map<int, TString > Cut_Check_Variable = {
                                                   { 1  , "Preselect"     },
                                                   { 2  , "MiniIsolation" } ,
                                                   { 3  , "TrackIsolation"} ,                                                   
                                                   { 4  , "dRgt04dPtgt00" } ,                                                    
                                                   { 5  , "dRgt04dPtgt10" } ,
                                                   { 6  , "dRgt03dPtgt05" } ,
                                                   { 7  , "dRgt03dPtgt10" } ,
                                                   { 8  , "dRgt02dPtgt05" } ,
                                                   { 9  , "dRgt02dPtgt10" } ,
                                                   { 10 , "dRgt01dPtgt05" } ,
                                                   { 11 , "dRgt01dPtgt10" } ,
                                                   } ;


      std::map<TString, double > Cut_LepIso_Test_dR  ={
                                                       {  "dRgt04dPtgt00" , 0.4 } ,  // for dr >  0.4 || dpt  >  05.0 
                                                       {  "dRgt04dPtgt10" , 0.4 } ,  // for dr >  0.4 || dpt  >  10.0 
                                                       {  "dRgt03dPtgt05" , 0.3 } ,  // for dr >  0.3 || dpt  >  05.0 
                                                       {  "dRgt03dPtgt10" , 0.3 } ,  // for dr >  0.3 || dpt  >  10.0 
                                                       {  "dRgt02dPtgt05" , 0.2 } ,  // for dr >  0.2 || dpt >   05.0 
                                                       {  "dRgt02dPtgt10" , 0.2 } ,  // for dr >  0.2 || dpt  >  10.0 
                                                       {  "dRgt01dPtgt05" , 0.1 } ,  // for dr >  0.1 || dpt  >  05.0 
                                                       {  "dRgt01dPtgt10" , 0.1 } ,  // for dr >  0.1 || dpt  >  10.0 
                                                    };



      std::map<TString, double > Cut_LepIso_Test_dPt  ={
                                                         {  "dRgt04dPtgt00" , -1.0  } ,  // for dr >  0.4 || dpt  >  5.0 
                                                         {  "dRgt04dPtgt10" , 10.0 } ,  // for dr >  0.4 || dpt  >  10.0 
                                                         {  "dRgt03dPtgt05" , 5.0  } ,  // for dr >  0.3 || dpt  >  05.0 
                                                         {  "dRgt03dPtgt10" , 10.0 } ,  // for dr >  0.3 || dpt  >  10.0 
                                                         {  "dRgt02dPtgt05" , 5.0  } ,  // for dr >  0.2 || dpt  >  05.0 
                                                         {  "dRgt02dPtgt10" , 10.0 } ,  // for dr >  0.2 || dpt  >  10.0 
                                                         {  "dRgt01dPtgt05" , 5.0  } ,  // for dr >  0.1 || dpt  >  05.0 
                                                         {  "dRgt01dPtgt10" , 10.0 } ,  // for dr >  0.1 || dpt  >  10.0                                                                                                                                                                                                                                                                                     
                                                      };                            

 
    
//=============Pile Up factor calculation using PileUp file ==================================================




//================Muon ID Scale factor using efficiency root files ===========================================



//============General Object selections  functions=============



// for checking ===================================

/*
  void Cut_puppibjet(int c_jet, int wp) {     
    if( (*puppijetPt)[c_jet] >= 30.0){
      if (fabs((*puppijetEta)[c_jet]) < 2.4 ){ 
        if (wp == 1 ){
          if ( ((*puppijetDeepCSVTags_b)[c_jet] + (*puppijetDeepCSVTags_bb)[c_jet]) >  0.2219) {
               puppib_jetloose.push_back(c_jet) ;   
               puppib_jet.push_back(c_jet) ;     
               //puppin_jet.push_back(c_jet) ;
          }
          else {
               puppin_jet.push_back(c_jet) ;
          }
        }

        if (wp == 2 ){
          if ( ((*puppijetDeepCSVTags_b)[c_jet] + (*puppijetDeepCSVTags_bb)[c_jet]) >  0.6324) {
               puppib_jetmedium.push_back(c_jet) ;  
               puppib_jet.push_back(c_jet) ;     
               //puppin_jet.push_back(c_jet) ;
          }
          else {
               puppin_jet.push_back(c_jet) ;
          }
        }

        if (wp == 3 ){
          if ( ((*puppijetDeepCSVTags_b)[c_jet] + (*puppijetDeepCSVTags_bb)[c_jet]) >  0.8958) {
               puppib_jettight.push_back(c_jet) ;   
               puppib_jet.push_back(c_jet) ;     
               //puppin_jet.push_back(c_jet) ;
          }
          else {
               puppin_jet.push_back(c_jet) ;
          }
        }

      }

      else{
         puppin_forwjet.push_back(c_jet) ;

      }
    
    }

  }   
*/






////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////AUXILLARY FUNCTIONS FOR  TESTING ////////////////////////////

std::map<std::string,TString> Sample_Type_Jet = {  // to check whether jet type is from signal or from background
                                                               { "Signal_Files/TprimeB_M1000_v3_",                                  "Higgs"          },  
                                                               { "Signal_Files/TprimeB_M1500_v3_",                                  "Higgs"          },  
                                                               { "Signal_Files/TprimeB_M1800_v3_",                                  "Higgs"          },  
                                                               { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  "Top"            }, 
                                                               // { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  "TopWboson"         }, 
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",                   "udscquark"      },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_",                  "udscquark"      },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_",                  "udscquark"      },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_",                  "udscquark"      },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_",                  "udscquark"      },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_",                  "udscquark"      },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_",                 "udscquark"      },  
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_",                 "udscquark"      } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",                   "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",                  "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",                  "Wboson"         } ,  
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",                  "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",                  "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",                 "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_",                "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",                 "Wboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-70To100_v3_",             "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-100To200_v3_",            "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-200To400_v3_",            "Zboson"         } ,  
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-400To600_v3_",            "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600To800_v3_",            "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-800To1200_v3_",           "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-1200To2500_v3_",          "Zboson"         } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-2500ToInf_v3_",           "Zboson"         } ,   
                                                 } ;  



// Gen_Parent_Check() , AK8Jet_Gen_Match(int gen_jet, TString mom )  ============================================



// SD_Mass_Check_Correction ( int index ) ,  Fill_Gen_Matched_AK8Jet( int pass_jet)  ==============================







std::map<std::string,TString> Sample_Type_Muon = {  // to check whether muon is from signal or from background
                                                               { "Signal_Files/TprimeB_M1000_v3_",                                  "PromptLepton"   },  
                                                               { "Signal_Files/TprimeB_M1500_v3_",                                  "PromptLepton"   },  
                                                               { "Signal_Files/TprimeB_M1800_v3_",                                  "PromptLepton"   },  
                                                               { "list_of_Bkgfiles/Bkg_TTbar_v3_",                                  "PromptLepton"   }, 
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-80to120_MuEnr_v3_",                   "FakeLepton"     },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-120to170_MuEnr_v3_",                  "FakeLepton"     },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-170to300_MuEnr_v3_",                  "FakeLepton"     },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-300to470_MuEnr_v3_",                  "FakeLepton"     },    
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-470to600_MuEnr_v3_",                  "FakeLepton"     },   
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-600to800_MuEnr_v3_",                  "FakeLepton"     },
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-800to1000_MuEnr_v3_",                 "FakeLepton"     },  
                                                               { "list_of_Bkgfiles/Bkg_QCD_Pt-1000toInf_MuEnr_v3_",                 "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-70To100_v3_",                   "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-100To200_v3_",                  "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-200To400_v3_",                  "FakeLepton"     } ,  
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-400To600_v3_",                  "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-600To800_v3_",                  "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-800To1200_v3_",                 "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200To2500_v3_",                "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500ToInf_v3_",                 "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-70To100_v3_",             "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-100To200_v3_",            "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-200To400_v3_",            "FakeLepton"     } ,  
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-400To600_v3_",            "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600To800_v3_",            "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-800To1200_v3_",           "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-1200To2500_v3_",          "FakeLepton"     } ,
                                                               { "list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-2500ToInf_v3_",           "FakeLepton"     } ,                                                                
                                                               { "list_of_Bkgfiles/ST_s-channel_4f_leptonDecays_v3_",               "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_t-channel_antitop_4f_inclusiveDecays_v3_",    "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_t-channel_top_4f_inclusiveDecays_v3_",        "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_tW_antitop_5f_inclusiveDecays_v3_",           "FakeLepton"     },
                                                               { "list_of_Bkgfiles/ST_tW_top_5f_inclusiveDecays_v3_",               "FakeLepton"     }
                                                 } ;   



//bool   Muon_Gen_Match (int c_muon) ==============

 
// void   Fill_Gen_Matched_Muon(int mu) ==========



////////////////////////////////////////////////////////////////////////////////////////////////////////
// for Plotting of Histograms==============================
////////////////////////////////////////////////////////////////////////////////////////////////////////


void Fill_RecoObject(int mu , TString fill ) {
   //   id for defining particle type, MET = 0, mu= 1, AK4bjet = 2, AK4qjet = 4, AK4forwjet = 6, puppibjet = 7, puppiqjet = 9, puppiforwjet = 11
   //   AK8jet= 12(W) , 
   int Msize   = ( n_Mu.size() >= 1) ? 1 : n_Mu.size() ;             
   int Asize   = ( n_AK8Jet.size() >= 3) ? 3 : n_AK8Jet.size() ;    
   int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
   int Fsize   = ( n_forwjet.size() >= 2) ? 2 : n_forwjet.size() ;  
   int Qsize   = ( q_jet.size() >= 2 ) ?  2 : q_jet.size() ;
   int Nsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;

   // int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
   // int P_qsize = ( puppin_jet.size() >= 2 ) ?  2 : puppin_jet.size() ;
   // int P_fsize = ( puppin_forwjet.size() >= 1 ) ?  1 : puppin_forwjet.size() ; 

   int b2 = -1 ;

   Fill_NPtEta_Histo(0, 0, 0) ;                                     // for MET & object population


   if( fill == "After topmu") {
     
     b2 = mu ;
     Fill_NPtEta_Histo(1, b2, 0) ;        // for particularly selected muon after Lepton Isoaltion
     // RecoPlots_dRHisto_v2(b2) ;  


   }

   // if( fill == "Before topmu" ) { }
    // for standard filling of muon. Change string value for this options
    for ( int i = 0; i < Msize; i ++)
    {    b2 = n_Mu[i] ;
         Fill_NPtEta_Histo(1, b2, i) ;
         // Match_Muon_Pt300     ->Fill((*muPt)[b2], factor);  // for cut selections
    }
   
   
   for ( int i = 0; i < Bsize; i ++)
   {    b2 = b_jet[i] ;
        Fill_NPtEta_Histo(2, b2, i) ;
   }

   if ( fill == "Before Higgs"){
   for ( int i = 0; i < Asize; i ++) {
        b2 = n_AK8Jet[i] ;
//      if ( WtagMatch(b2) == -1) ;
  //      if ( (*AK8JetPt)[b2] > 20.0)Fill_NPtEta_Histo(12,b2,i) ;
   }
   }

   for ( int i = 0; i < Fsize; i ++)
   {    b2 = n_forwjet[i] ;
        Fill_NPtEta_Histo(6, b2, i) ;
   }

   for ( int i = 0; i < Qsize; i ++)
   {    
;
        b2 = q_jet[i] ;
        Fill_NPtEta_Histo(8, b2, i) ;
   }


   for ( int i = 0; i < Nsize; i ++)
   {   
        b2 = n_jet[i] ;
        Fill_NPtEta_Histo(4, b2, i) ;
   }

   // for ( int i = 0; i < P_qsize; i ++)
   // {    b2 = puppin_jet[i] ;
   //      Fill_NPtEta_Histo(9, b2, i) ;
   // }

   // for ( int i = 0; i < P_fsize; i ++)
   // {    b2 = puppin_forwjet[i] ;
   // {    b2 = puppin_forwjet[i] ;
   //      Fill_NPtEta_Histo(11, b2, i) ;
   // }

   // RecoPlots_dRHisto_v2(0) ;  //skip for just delta r distribution
   RecoPlots_dRHisto() ;     // skip it for dR_Check_step2
}


void   Fill_NPtEta_Histo(int id, int en, int idx)
   {
      float ptau1 = 0.0 ;
      float puppi_mass = 0.0 , CHS_mass = 0.0 ; 

      double muon_scale_factor = muon_ID_factor * factor ;
      //   id for defining particle type, MET = 0, mu= 1, AK4bjet = 2, AK4qjet = 4, AK4forwjet = 6, puppibjet = 7, puppiqjet = 9, puppiforwjet = 11
      //   AK8jet= 12(W) , 
      if (id == 0) {
        h_object_no.at(0) ->Fill(n_Mu.size() ,factor);
        h_object_no.at(1) ->Fill(b_jet.size() ,factor);
        // h_object_no.at(2) ->Fill(n_AK8Jet.size() ,factor) ;
        h_object_no.at(3) ->Fill(n_jet.size() ,factor) ;
        h_object_no.at(4) ->Fill(n_forwjet.size() ,factor) ;
        h_object_no.at(5) ->Fill(q_jet.size() ,factor) ;
        // h_object_no.at(6) ->Fill(puppib_jet.size() ,factor) ;
        // h_object_no.at(7) ->Fill(puppin_forwjet.size() ,factor) ;

       // h_object_pt.at(0) ->Fill( pfMET ,factor); 
      }

      /*
       if ( id == 1){
            h_object_pt.at(idx+id)    ->Fill((*muPt)[en] ,muon_scale_factor); 
            // h_object_pt.at(idx+id)    ->Fill((*muIsoTrk)[en] ,factor); 
            h_object_eta.at(idx+id)   ->Fill((*muEta)[en] ,muon_scale_factor);
       }

       if( id == 2) {
          h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4bjet
          h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
       }

       if( id == 4){
          h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4qjet
          h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
       }

       if( id == 6){
          h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4forwjet
          h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
       }

       if( id == 8){
          h_object_pt.at(idx+id)    ->Fill((*jetPt)[en] ,factor);       // AK4forwjet
          h_object_eta.at(idx+id)   ->Fill((*jetEta)[en] ,factor);
       }

           // if( id == 7){
              // h_object_pt.at(idx+id)    ->Fill((*puppijetPt)[en] ,factor);       // puppibjet
              // h_object_eta.at(idx+id)   ->Fill((*puppijetEta)[en] ,factor);
           // }
        
           // if( id == 9){
              // h_object_pt.at(idx+id)    ->Fill((*puppijetPt)[en] ,factor);       // puppiqjet
              // h_object_eta.at(idx+id)   ->Fill((*puppijetEta)[en] ,factor);
           // }
         
           // if( id == 11){
              // h_object_pt.at(idx+id)    ->Fill((*puppijetPt)[en] ,factor);       // puppibjet
              // h_object_eta.at(idx+id)   ->Fill((*puppijetEta)[en] ,factor);
           // }

       if (id == 12 ) {
             
             // for AK8jet       
             h_object_pt.at(idx+id) ->Fill((*AK8JetPt)[en] ,factor); 
             h_object_eta.at(idx+id) ->Fill((*AK8JetEta)[en] ,factor);

             h_AK8_Jetmass.at(idx) -> Fill((*AK8JetCHSMass)[en] ,factor) ;
             h_AK8_PUPPImass.at(idx) -> Fill((*AK8JetMass)[en] ,factor);

             h_AK8_PUPPISDmass.at(idx) -> Fill((*AK8puppiSDMass)[en] ,factor);
             h_AK8_CHSmass.at(idx) -> Fill((*AK8JetCHSMass)[en] ,factor) ;     

             //h_AK8_PUPPIvsmass.at(idx) -> Fill(puppi_mass,(*AK8_puppiMass)[en]) ;
             //h_AK8_CHSvsmass.at(idx) -> Fill(CHS_mass,(*AK8_JetMass)[en]) ;

             ptau1 = ((*AK8puppiTau2)[en]/(*AK8puppiTau1)[en]) ;
             h_AK8_PUPPItau21.at(idx) -> Fill(ptau1 ,factor);
             ptau1 = ((*AK8puppiTau3)[en]/(*AK8puppiTau2)[en]) ;
             h_AK8_PUPPItau32.at(idx) -> Fill(ptau1 ,factor);
             ptau1 = ((*AK8puppiTau3)[en]/(*AK8puppiTau1)[en]) ;
             h_AK8_PUPPItau31.at(idx) -> Fill(ptau1 ,factor);

             ptau1 = ((*AK8puppiTau4)[en]/(*AK8puppiTau1)[en]) ;
             h_AK8_PUPPItau41.at(idx) -> Fill(ptau1 ,factor);
             ptau1 = ((*AK8puppiTau4)[en]/(*AK8puppiTau2)[en]) ;
             h_AK8_PUPPItau42.at(idx) -> Fill(ptau1 ,factor);
             ptau1 = ((*AK8puppiTau4)[en]/(*AK8puppiTau3)[en]) ;
             h_AK8_PUPPItau43.at(idx) -> Fill(ptau1 ,factor);

             ptau1 = ((*AK8Jet_tau2)[en]/(*AK8Jet_tau1)[en]) ;
             h_AK8_tau21.at(idx) -> Fill(ptau1 ,factor);
             ptau1 = ((*AK8Jet_tau3)[en]/(*AK8Jet_tau2)[en]) ;
             h_AK8_tau32.at(idx) -> Fill(ptau1 ,factor);
             ptau1 = ((*AK8Jet_tau4)[en]/(*AK8Jet_tau2)[en]) ;
             h_AK8_CHStau42.at(idx) -> Fill(ptau1 ,factor);
      
        
        } */  

}


void RecoPlots_dRHisto()
{
   float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, dpt;
   int b1 = -1, b2 =-1 ;
    //   id for defining particle type,  mu= 0, AK4bjet = 1, AK4qjet = 3, AK4forwjet = 5, puppibjet = 6, puppiqjet = 8, puppiforwjet = 10
    //   AK8jet= 11(W) , 
      int Msize   = ( n_Mu.size() >= 1) ? 1 : n_Mu.size() ;             
      int Asize   = ( n_AK8Jet.size() >= 2) ? 2 : n_AK8Jet.size() ;    // focussing only on first 2 ak8Jet
      int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
      int Fsize   = ( n_forwjet.size() >= 2) ? 2 : n_forwjet.size() ;  
      int Qsize   = ( q_jet.size() >= 2 ) ?  2 : q_jet.size() ;
      int Nsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;


      // int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
      // int P_qsize = ( puppin_jet.size() >= 2 ) ?  2 : puppin_jet.size() ;
      // int P_fsize = ( puppin_forwjet.size() >= 1 ) ?  1 : puppin_forwjet.size() ;           

    TVector3 vec_lep, vec_jet;
      int id ; 
      
       /* 
       // for muon w.r.t other jets dR plots
       for ( int h = 0 ; h < Msize ; h ++ ) {

          b1    = n_Mu[h];   
          eta1  = (*muEta)[b1];
          phi1  = (*muPhi)[b1];
          vec_lep.SetPtEtaPhi( (*muPt)[b1], (*muEta)[b1] , (*muPhi)[b1] ) ;

          // cout <<"\n check1";

          id = 1 ; // for AK4bjet
          for( int g = 0 ; g < Bsize ; g ++ ) {

             b2   = b_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;
          // cout <<"\n check2";
             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.  at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);


          }

          id = 3; // for ak4jet
               for( int g = 0 ; g < Nsize ; g ++ ) {

             b2   = n_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;
          // cout <<"\n check3";
             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);

          }

          id = 5; // for forw jet      
          for( int g = 0 ; g < Fsize ; g ++ ) {
             
             b2 = n_forwjet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;
          // cout <<"\n check4";
             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);

          }


          id = 7; // for qjet collection
          for( int g = 0 ; g < Qsize ; g ++ ) {
             
             b2 = q_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);
             // cout <<"\n checkqjet";

          }

          id = 11 ; // for AK8jet
          for( int g = 0 ; g < Asize ; g ++ ) {
             
             b2 = n_AK8Jet[g];         
             eta2 = (*AK8JetEta)[b2] ;
             phi2 = (*AK8JetPhi)[b2] ;
             vec_jet.SetPtEtaPhi( (*AK8JetPt)[b2], (*AK8JetEta)[b2], (*AK8JetPhi)[b2] ) ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco.at(h).at(g+id)->
             Fill(dR);
             h_dEta_Reco.at(h).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi);
             dpt = dPt_Calculator(vec_lep, vec_jet) ;
             h_dPt_Reco.at(g+id)->Fill(dpt);
             // cout <<"\n checkAk8jet";

          }  
       }

       // for ak4 bjet w.r.t other ak4jets and AK8jets

       // id = 1 ; // for AK4bjet
       for( int h = 0 ; h < Bsize ; h ++ ) {

              b1    = b_jet[h];
              eta1  = (*jetEta)[b1] ;
              phi1  = (*jetPhi)[b1] ;
              // cout <<"\n checkbjet  == " << b1;
              // cout <<"\nBsize = " << Bsize << endl ;
            if(h == 0 && Bsize == 2  ){
             b2   = b_jet[h+1];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco  .at(h+1).at(h+2)->Fill(dR);
             h_dEta_Reco.at(h+1).at(h+2)->Fill(dEta);


            }

          id = 3; // for ak4jet
          for( int g = 0 ; g < Nsize ; g ++ ) {

             b2   = n_jet[g];
             eta2 = (*jetEta)[b2] ;
             phi2 = (*jetPhi)[b2] ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco  .at(h+1)  .at(g+id)->Fill(dR);
             h_dEta_Reco.at(h+1)  .at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h+1)  .at(g+id)->Fill(dPhi);

             // cout <<"\n checkbjetnjet";

            }

          id = 11 ; // for AK8jet
          for( int g = 0 ; g < Asize ; g ++ ) {
             
             b2 = n_AK8Jet[g];
             eta2 = (*AK8JetEta)[b2] ;
             phi2 = (*AK8JetPhi)[b2] ;

             dR_Calculator(eta1, phi1, eta2, phi2) ;
             h_dR_Reco  .at(h+1).at(g+id)->Fill(dR);
             h_dEta_Reco.at(h+1).at(g+id)->Fill(dEta);
             h_dPhi_Reco.at(h+1).at(g+id)->Fill(dPhi);

             // cout <<"\n checkbjetak8jet";

          }


       }


      // for ak4  w.r.t  AK8jets
          
          id = 11 ; // for AK8jet
          for( int h = 0 ; h < Nsize ; h ++ ) {

              b1    = n_jet[h];
              eta1  = (*jetEta)[b1] ;
              phi1  = (*jetPhi)[b1] ;

              for( int g = 0 ; g < Asize ; g ++ ) {
               
               b2   = n_AK8Jet[g];
               eta2 = (*AK8JetEta)[b2] ;
               phi2 = (*AK8JetPhi)[b2] ;


               dR_Calculator(eta1, phi1, eta2, phi2) ;
               h_dR_Reco  .at(h+3).at(g+id)->Fill(dR , factor);
               h_dEta_Reco.at(h+3).at(g+id)->Fill(dEta , factor);
               h_dPhi_Reco.at(h+3).at(g+id)->Fill(dPhi , factor);
               // cout <<"\n checkak4jetak8jet";

              }
              
          }

          // for qjet  w.r.t  AK8jets
          
          id = 11 ; // for AK8jet
          for( int h = 0 ; h < Qsize ; h ++ ) {

              b1    = q_jet[h];
              eta1  = (*jetEta)[b1] ;
              phi1  = (*jetPhi)[b1] ;

              for( int g = 0 ; g < Asize ; g ++ ) {
               
               b2   = n_AK8Jet[g];
               eta2 = (*AK8JetEta)[b2] ;
               phi2 = (*AK8JetPhi)[b2] ;

               dR_Calculator(eta1, phi1, eta2, phi2) ;
               h_dR_Reco  .at(h+7).at(g+id)->Fill(dR , factor);
               h_dEta_Reco.at(h+7).at(g+id)->Fill(dEta , factor);
               h_dPhi_Reco.at(h+7).at(g+id)->Fill(dPhi , factor);
               // cout <<"\n checkqjetak8jet";

              }
              
          } */

}




void RecoPlots_dRHisto_v2(int mu)
{
      float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0, dpt;
      int b1 = -1, b2 =-1 ;
      //   id for defining particle type,  mu= 0, AK4bjet = 1, AK4qjet = 3, AK4forwjet = 5, puppibjet = 6, puppiqjet = 8, puppiforwjet = 10
      //   AK8jet= 11(W) , 
      int Msize   = ( n_Mu.size() >= 1) ? 1 : n_Mu.size() ;             
      int Asize   = ( n_AK8Jet.size() >= 2) ? 2 : n_AK8Jet.size() ;    // focussing only on first 2 ak8Jet
      int Bsize   = ( b_jet.size() >= 2) ? 2 : b_jet.size() ;                
      int Fsize   = ( n_forwjet.size() >= 2) ? 2 : n_forwjet.size() ;  
      int Qsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;

      // int P_bsize = ( puppib_jet.size() >= 2) ? 2 : puppib_jet.size() ;    
      // int P_qsize = ( puppin_jet.size() >= 2 ) ?  2 : puppin_jet.size() ;
      // int P_fsize = ( puppin_forwjet.size() >= 1 ) ?  1 : puppin_forwjet.size() ;           

      TVector3 vec_lep, vec_jet;
      int id ; 
      // cout << "\n Check 1 ";
      // for muon w.r.t other jets dR plots

      /*

      b1    = mu;   
      eta1  = (*muEta)[b1];
      phi1  = (*muPhi)[b1];
      vec_lep.SetPtEtaPhi( (*muPt)[b1], (*muEta)[b1] , (*muPhi)[b1] ) ;
      int h = 0 ;
      id = 1 ; // for AK4bjet
      for( int g = 0 ; g < Bsize ; g ++ ) {

         b2   = b_jet[g];
         eta2 = (*jetEta)[b2] ;
         phi2 = (*jetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor );


      } // end loop for bjets

      id = 3; // for ak4qjet
      for( int g = 0 ; g < Qsize ; g ++ ) {

         b2   = n_jet[g];
         eta2 = (*jetEta)[b2] ;
         phi2 = (*jetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor);

      } // end loop for qjets

      id = 5; // for forw jet      
      for( int g = 0 ; g < Fsize ; g ++ ) {
         
         b2 = n_forwjet[g];
         eta2 = (*jetEta)[b2] ;
         phi2 = (*jetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*jetPt)[b2], (*jetEta)[b2], (*jetPhi)[b2] ) ;

         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor);

      } //end loop for forwjets


      id = 11 ; // for AK8jet
      for( int g = 0 ; g < Asize ; g ++ ) {
         
         b2 = n_AK8Jet[g];         
         eta2 = (*AK8JetEta)[b2] ;
         phi2 = (*AK8JetPhi)[b2] ;
         vec_jet.SetPtEtaPhi( (*AK8JetPt)[b2], (*AK8JetEta)[b2], (*AK8JetPhi)[b2] ) ;


         dR_Calculator(eta1, phi1, eta2, phi2) ;
         h_dR_Reco.at(h).at(g+id)->Fill(dR , factor);
         h_dEta_Reco.at(h).at(g+id)->Fill(dEta , factor);
         h_dPhi_Reco.at(h).at(g+id)->Fill(dPhi , factor);
         dpt = dPt_Calculator(vec_lep, vec_jet) ;
         h_dPt_Reco.at(g+id)->Fill(dpt , factor);

      }  // end loop for AK8jets

      // for ak4 bjet w.r.t other ak4jets and AK8jets
      
      id = 1 ; // for AK4bjet
      for( h = 0 ; h < Bsize ; h ++ ) {

          b1    = b_jet[h];
          eta1  = (*jetEta)[b1] ;
          phi1  = (*jetPhi)[b1] ;

          if(h == 0 && Bsize == 2){
           b2   = b_jet[h+1];
           eta2 = (*jetEta)[b2] ;
           phi2 = (*jetPhi)[b2] ;

           dR_Calculator(eta1, phi1, eta2, phi2) ;
           h_dR_Reco.at(h+id).at(h+id+1)  ->Fill(dR , factor);
           h_dEta_Reco.at(h+id).at(h+id+1)->Fill(dEta , factor);
           h_dPhi_Reco.at(h+id).at(h+id+1)->Fill(dPhi , factor);
          }

          
          id = 3; // for ak4qjet
          for( int g = 0 ; g < Qsize ; g ++ ) {

           b2   = n_jet[g];
           eta2 = (*jetEta)[b2] ;
           phi2 = (*jetPhi)[b2] ;

           dR_Calculator(eta1, phi1, eta2, phi2) ;
           h_dR_Reco  .at(h+1) .at(g+id)->Fill(dR , factor);
           h_dEta_Reco.at(h+1)  .at(g+id)->Fill(dEta , factor);
           h_dPhi_Reco.at(h+1)  .at(g+id)->Fill(dPhi , factor);

          }

          id = 11 ; // for AK8jet
          for( int g = 0 ; g < Asize ; g ++ ) {
           
           b2 = n_AK8Jet[g];
           eta2 = (*AK8JetEta)[b2] ;
           phi2 = (*AK8JetPhi)[b2] ;

           dR_Calculator(eta1, phi1, eta2, phi2) ;
           h_dR_Reco  .at(h+1).at(g+id)->Fill(dR , factor);
           h_dEta_Reco.at(h+1).at(g+id)->Fill(dEta , factor);
           h_dPhi_Reco.at(h+1).at(g+id)->Fill(dPhi , factor);

          }
          

      } */
      


}


// float dRPlots_ak4_ak8Jet( int b1, int b2, int idx)  ==============
  // Temporary function to plot dR b/w ak8jet(b2) and ak4Jet(b1) and in histo of index idx 


// void dRPlots_ak4_ak8Jet_v2( int b2 , int idx)  ===============
  // Temporary function to plot dR b/w ak8jet(b2) and ak4Jet(b1) and in histo of index idx 

 

// void ak4jet_Higgs_dR_check(int Higgs, int var) ===================
  
  // After this step only those ak4jet are remained for those, dR(ak4jet, Higgjet) >1.2 and stored into q_jet collection
  // Then bjets are selected from them into b_jet collection



// void bjet_Higgs_dR_check(int Higgs) ===============================
  
  // After this step only those ak4jet are remained for those, dR(ak4jet, Higgjet) >1.2 and stored into q_jet collection
  // Then bjets are selected from them into b_jet collection


//////////////////////////////////////////////////////////////////////////////////////////
// filling of histograms for tagged jets =================================================
///////////////////////////////////////////////////////////////////////////////////////////

 /// void  Higgsjet_Plots( ) 




// Generalised function to sort Higgs jet collection  void Jet_Sorting( TString jet)



// DeltaR calculation and plotting for muon & bjet w.r.t to heavy jets void dR_TagJets_objects( ) 


/// to check deltaR explicitly for Higgs & muon void dR_TagJets_objects_v2(int muon) 


//////////////////////////////////////////////////////////////////////////////////////////////
// filling for histograms for selected category===============================================
//////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// function definitions for histogram detailing ==========================================
//Defaults Histograms for root =================================

// function definitions for histogram detailing 

// Histograms for muon studying ===================================

void Histo_Muon_ID_Study() {

    //   New defination of histogram
    char   pT_name[100] , pT_title[100] ; 
    string reco_object = {"Gen_Matched_muon_reco"};
    string variable[5] = {"pT300", "pT1000", "eta","phi", "N(Primary Vertex)"} ;
    string ar;
    //cout << "\nFunc 4" ;
    int s = -1;
    const int nBin = 29;
    const double Bin_value[nBin+1] =  {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 220.0, 240.0, 260.0, 280.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.0 } ;
   
    // for object pT histograms
    for(Int_t k = 0 ; k <  5; k++) {
     
 
        sprintf( pT_name , "%s_%s_" , variable[k].c_str(), reco_object.c_str() ) ;
        sprintf( pT_title , "%s(%s) Distribution" , variable[k].c_str(), reco_object.c_str() ) ;     
   
        if ( k == 0) {
          Match_Muon_Pt300  = new TH1D(pT_name,pT_title, nBin, Bin_value);
          Match_Muon_Pt300 ->GetYaxis()->SetTitle("Events");
        }

        if ( k == 1) {
          Match_Muon_Pt1000 = new TH1D(pT_name,pT_title, nBin, Bin_value);
          Match_Muon_Pt1000 ->GetYaxis()->SetTitle("Events");
          //cout<< " h_object_eta["<<k<<"].name() : "<< h_object_eta.at(k) ->GetName()<<endl;   
        }

        if( k == 2) {
          
          Match_Muon_Eta =  new TH1D(pT_name,pT_title, 200, -5.0,  5.0);
          Match_Muon_Eta -> GetYaxis()->SetTitle("Events");
        }

        if( k == 3) {
          
          Match_Muon_Phi =  new TH1D(pT_name,pT_title, 200, -5.0,  5.0);
          Match_Muon_Phi -> GetYaxis()->SetTitle("Events");
          
        }
   
        if( k == 4) {
          
          Match_Primary_Vertex =  new TH1D(pT_name,pT_title, 60, 0, 60) ;
          Match_Primary_Vertex -> GetYaxis()->SetTitle("Events");
          
        }  
   
    } // End loop of K

          Muon_Pt_ratio =  new TH1D("Muon_Pt_ratio","Muon_Pt_ratio Distribution", 20000.0, 0.0, 1000.0) ;
          Muon_Pt_ratio -> GetYaxis()->SetTitle("Events");

}

   
    
void Define_Mt_Histo()
 {
      //   New defination of histogram
      char  dr_MTname[100] , dr_MTtitle[100] ;
    
      int s = -1;
      int rk = -1 ;
      string MT_comp[9] = {"Mt_muMeT", "Mt_WmuMeT", "Mt_Tprime", "Mt_topjet", "Mt_Wjet", "Mt_Wmc", "MT_HiggsMC", "MT_topmc", "MT_Tmc"} ;
      //cout<<"\nFunc 1" ;
      // for Transverse mass plots, we have 6 combinations for objects
      for( int Sk = 0 ; Sk < 9 ; Sk ++ )
      {
        sprintf( dr_MTname, "%s",  MT_comp[Sk].c_str() ) ;
        sprintf( dr_MTtitle, "%s Distribution",  MT_comp[Sk].c_str() ) ;    
        h_object_MT.at(Sk) = new TH1D(dr_MTname,dr_MTtitle,  600, 0.0 , 3000.0 );
        h_object_MT.at(Sk)->GetYaxis()->SetTitle("Events");
        //cout<< " , h_object_Mt["<<Sk<<"].name() : "<< h_object_MT.at(Sk) ->GetName()<<endl; 
      }      
    }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------mc level objects ----------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  DefineMC_NPtEta_Histo()
{
  //   New defination of histogram
  //        TString   mc_pT , mc_pT_title, gh_name, gh_title;
  char mc_pT[100], mc_pT_title[100], gh_name[100], gh_title[100] ;

  std::string mc_objectI[7] = {"topb", "topWl","higgWq1", "higgWq2", "higgWl", "assob", "forwq" };
  //std::string mc_objectI[3] = {"topb", "topWl","higgWq1"};
  // for object pT histograms
  //cout << "\nFunc 2" ;
  for(Int_t k = 0 ; k < 7; ++k) {
    sprintf (mc_pT, "Pt(%s)", mc_objectI[k].c_str() )  ;
    sprintf (mc_pT_title, "Pt(%s) Distribution", mc_objectI[k].c_str() )  ;               
    h_mcobject_pt.at(k) = new TH1D(mc_pT,mc_pT_title, 24, 0, 1200.0);
    h_mcobject_pt.at(k) ->GetYaxis()->SetTitle("Events");        
    //  cout<< " , h_mcobject_pt["<<k<<"].name() : "<< h_mcobject_pt.at(k) ->GetName()<<endl;   
  }


  for(Int_t h = 0 ; h < 7; ++h) {
    sprintf (gh_name, "Eta(%s)", mc_objectI[h].c_str() )  ;
    sprintf (gh_title, "Eta(%s) Distribution", mc_objectI[h].c_str() )  ;                            
    h_mcobject_eta.at(h) = new  TH1D(gh_name,gh_title, 100, -5.0, 5.0);
    h_mcobject_eta.at(h) ->GetYaxis()->SetTitle("Events");
    //cout<<" , h_mcobject_eta["<<h<<"].name() : "<< h_mcobject_eta.at(h) ->GetName()<<endl; 
  }

  for(Int_t h = 0 ; h < 7; ++h) {
    sprintf (gh_name, "Mass(%s)", mc_objectI[h].c_str() )  ;
    sprintf (gh_title, "Mass(%s) Distribution", mc_objectI[h].c_str() )  ;                            
    h_mcobject_mass.at(h) = new  TH1D(gh_name,gh_title, 300, 0.0, 3000.0);
    h_mcobject_mass.at(h) ->GetYaxis()->SetTitle("Events");
    // cout<<" , h_mcobject_eta["<<h<<"].name() : "<< h_mcobject_eta.at(h) ->GetName()<<endl; 
  }
}



void  dRHisto_MCObject()
{
  // New defination of histogram
  char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ;
  string mc_object[7] = {"topb", "topWl","higgWq1", "higgWq2", "higgWl", "assob", "forwq" };
  // Here, i = 0-1 top decayed, i = 2-4 Higgs decayed, i = 5 assob, i = 6 forwq
  Int_t s = -1;
  //cout << "\nFunc 3" ;  
  for (Int_t i = 0; i < 7; i++) {     
    for (Int_t k = i+1; k < 7; k++) {
      // for mc  objects dR histograms
      sprintf(dR_name, "DeltaR_%s_%s_", mc_object[i].c_str(), mc_object[k].c_str()) ;
      sprintf(dR_title, "DeltaR(%s_%s) Distribution", mc_object[i].c_str(), mc_object[k].c_str()) ;
      h_dR_MC.at(i).at(k) = new TH1D(dR_name,dR_title, 50, 0, 5.0);
      h_dR_MC.at(i).at(k) ->GetYaxis()->SetTitle("Events");     
      //cout<<" , h_dR_MC["<<i<<"]["<<k<<"].name() : "<< h_dR_MC.at(i).at(k) ->GetName()<<endl; 
      // for mc Object dPt histograms     
      sprintf(dPt_name, "DeltaPt_%s_%s_", mc_object[i].c_str(), mc_object[k].c_str()) ;
      sprintf(dPt_title, "DeltaPt(%s_%s) Distribution", mc_object[i].c_str(), mc_object[k].c_str()) ;
      h_dPt_MC.at(i).at(k) = new TH1D(dPt_name,dPt_title, 100, 0, 500.0);
      h_dPt_MC.at(i).at(k) ->GetYaxis()->SetTitle("Events");      
      //cout<<" h_dPt_MC["<<i<<"]["<<k<<"].name() : "<< h_dPt_MC.at(i).at(k) ->GetName()<<endl;     
    }
  }
}     


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------reco level objects - Preselection--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   void  Define_2DMass_Histo()
   {
    //   New defination of histogram
    char   mass[100] , massT[100] ; 
    string object_no[4] = {"Higgs", "WHiggs","Top","WTop"};
    string reco_object[3] = {"AK8jet1", "AK8jet2","AK8jet3"};
   
    for(Int_t k = 0 ; k <  3; k++) {
      for(Int_t j = 0; j < 4; j++) {
   
        sprintf( mass , "%svs%s_Mass" , reco_object[k].c_str(),  object_no[j].c_str()  ) ;
        sprintf( massT , "%svs%s_Mass Distribution" , reco_object[k].c_str(),  object_no[j].c_str()) ;      
   
        if ( k == 0) {
          h_AK81vsGenObj.at(j) = new TH2F(mass,massT, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
          h_AK81vsGenObj.at(j) ->GetYaxis()->SetTitle("Events");
          
        }
   
        if ( k == 1) {
          h_AK82vsGenObj.at(j) = new TH2F(mass,massT, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
          h_AK82vsGenObj.at(j) ->GetYaxis()->SetTitle("Events");
        }
   
        if ( k == 2) {
          h_AK83vsGenObj.at(j) = new TH2F(mass,massT, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
          h_AK83vsGenObj.at(j) ->GetYaxis()->SetTitle("Events");
        }
   
      }
    }
   }
   





   void  Define_NPtEta_Histo()
   {
    //   New defination of histogram
      char   pT_name[100] , pT_title[100] ; 
      string object_no[8] = {"mu", "bjet", "AK8jet","jet","forwjet","qjet","puppi_bjet","puppi_forwjet"};
      string reco_object[15] = {"MET", "mu1", "bjet1", "bjet2","jet1","jet2","fjet1", "fjet2","qjet1","qjet2","puppiqjet2","puppifjet1", "AK8jet1", "AK8jet2","AK8jet3"};
      string variable[18] = {"pt", "eta", "puppimass", "chsprunedmass", "puppitau21", "puppitau32","tau21", "tau32", "chstau42","puppisdvsmass", "chsprunedvsmass","jetmass","puppisdmass","puppitau42","puppitau41", "puppitau43","puppitau31", "phi"} ;
      string ar;
      //cout << "\nFunc 4" ;
      int s = -1;
   
      // for object pT histograms
      for(Int_t k = 0 ; k <  15; k++) {
        for(Int_t j = 0; j < 18; j++) {
   
          sprintf( pT_name , "%s_%s_" , variable[j].c_str(), reco_object[k].c_str() ) ;
          sprintf( pT_title , "%s(%s) Distribution" , variable[j].c_str(), reco_object[k].c_str() ) ;     
          
          if( k < 12 && k > 9) continue ;
          if ( j == 0) {
            h_object_pt.at(k) = new TH1D(pT_name,pT_title,120, 0, 1200.0);
            h_object_pt.at(k) ->GetYaxis()->SetTitle("Events");
            // cout<< " h_object_pt["<<k<<"].name() : "<< h_object_pt.at(k) ->GetName()<<endl;   

          }
          if ( j == 1) {
            h_object_eta.at(k) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
            h_object_eta.at(k) ->GetYaxis()->SetTitle("Events");
          }
          if ( j == 17) {
            h_object_phi.at(k) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
            h_object_phi.at(k) ->GetYaxis()->SetTitle("Events");
          }

          if(!( k > 11) ) continue ;
          if( j == 2) {
            s = k +j - 14 ;
            h_AK8_PUPPImass.at(s) =  new TH1D(pT_name,pT_title, 100, 0.0,  1000.0);
            h_AK8_PUPPImass.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPImass["<<s<<"].name() : "<< h_AK8_PUPPImass.at(s)->GetName()<<endl;  
          }
          if( j == 3) {
            s = k +j - 15 ;
            h_AK8_CHSmass.at(s) =  new TH1D(pT_name,pT_title, 50, 0.0, 500.0);
            h_AK8_CHSmass.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_CHSmass["<<s<<"].name() : "<< h_AK8_CHSmass.at(s)->GetName()<<endl;  
          }
   
          if( j == 4) {
            s = k +j - 16;
            h_AK8_PUPPItau21.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_PUPPItau21.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPItau21["<<s<<"].name() : "<< h_AK8_PUPPItau21.at(s)->GetName()<<endl;          
          }
          if( j == 5) {
            s = k +j - 17 ;
            h_AK8_PUPPItau32.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_PUPPItau32.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPItau32["<<s<<"].name() : "<< h_AK8_PUPPItau32.at(s)->GetName()<<endl;                  
          }
          if( j == 6) {
            s = k +j - 18 ;
            h_AK8_tau21.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_tau21.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_tau21["<<s<<"].name() : "<< h_AK8_tau21.at(s)->GetName()<<endl;          
          }
          if( j == 7) {
            s = k +j - 19 ;
            h_AK8_tau32.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_tau32.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_tau32["<<s<<"].name() : "<< h_AK8_tau32.at(s)->GetName()<<endl;                  
          }
   
          if( j == 8) {
            s = k +j - 20 ;
            h_AK8_CHStau42.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_CHStau42.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_CHStau42["<<s<<"].name() : "<< h_AK8_CHStau42.at(s)->GetName()<<endl;                  
          }
          if( j == 9) {
            s = k +j - 21 ;
            h_AK8_PUPPIvsmass.at(s) =  new TH2F(pT_name,pT_title, 160, 0.0, 1600.0, 320, 0.0, 1600.0) ;
            h_AK8_PUPPIvsmass.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_Puppivsmass["<<s<<"].name() : "<< h_AK8_PUPPIvsmass.at(s)->GetName()<<endl;                  
          }
          if( j == 10) {
            s = k +j - 22 ;
            h_AK8_CHSvsmass.at(s) =  new TH2F(pT_name,pT_title, 202, -10.0, 1000.0, 202, -10.0, 1000.0) ;
            h_AK8_CHSvsmass.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_CHSvsmass["<<s<<"].name() : "<< h_AK8_CHSvsmass.at(s)->GetName()<<endl;                  
          }
   
          if( j == 11) {
            s = k +j - 23 ;
            h_AK8_Jetmass.at(s) =  new TH1D(pT_name,pT_title, 100, 0.0, 1000.0);
            h_AK8_Jetmass.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPImass["<<s<<"].name() : "<< h_AK8_Jetmass.at(s)->GetName()<<endl;  
          }
   
          if( j == 12) {
            s = k +j - 24 ;
            h_AK8_PUPPISDmass.at(s) =  new TH1D(pT_name,pT_title, 50,  0.0, 500.0) ;
            h_AK8_PUPPISDmass.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPImass["<<s<<"].name() : "<< h_AK8_PUPPImass.at(s)->GetName()<<endl;  
          }
          if( j == 13) {
            s = k +j - 25 ;
            h_AK8_PUPPItau42.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_PUPPItau42.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
          }
          if( j == 14) {
            s = k +j - 26;
            h_AK8_PUPPItau41.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_PUPPItau41.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
          }
          if( j == 15) {
            s = k +j - 27;
            h_AK8_PUPPItau43.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_PUPPItau43.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
          }
          if( j == 16) {
            s = k +j - 28;
            h_AK8_PUPPItau31.at(s) =  new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
            h_AK8_PUPPItau31.at(s) -> GetYaxis()->SetTitle("Events");
            //cout<<"h_AK8_PUPPItau42["<<s<<"].name() : "<< h_AK8_PUPPItau42.at(s)->GetName()<<endl;          
          }
   
        }  //end loop for J
      }  // end loop for K
   
      // TString   pT_name1  = "Hist" ;
      // TString   pT_title1 = "Distribution" ; 

      // // for No. object  histograms
      // for(Int_t j = 0; j < 8; j++) {  
      //   pT_name1   =  Histogram_Object_List[j+1] ;
      //   pT_title1  =  Histogram_Object_List[j+1]  + " Distribution" ;
      //   h_object_no.at(j) = new TH1D( pT_name1, pT_title1, 10, 0, 10);  
      //   h_object_no.at(j) ->GetYaxis()->SetTitle("Events");
      //   // cout<<"h_object_no["<<j<<"].name() : "<< h_object_no.at(j)->GetName()<<endl;      
      // }



   
   }
   
   
   void  dRHisto_RecoObject() 
   {
        // New defination of histogram for reco level at Preselection 
        char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ,dEta_title[100], dEta_name[100], dPhi_name[100], dPhi_title[100];
        string reco_object[14] = {"mu1", "bjet1", "bjet2","jet1","jet2","fjet1", "fjet2","qjet1","qjet2","puppiqjet2","puppifjet1", "AK8jet1", "AK8jet2","AK8jet3"};
        
        // Here i -> 0 muon, i -> 1-2 bjet & i -> 3-4 forwjet, i -> 5-6 AK8jet
        //cout<<"\nFunc 5" ;  
        int j = -1;
        for (Int_t i = 0; i < 14; i++) {      
    
          // if (( i >= 9 && i <= 10) ) continue ;  
          for (Int_t k = i+1; k < 14; k++) {      
      
            // if (( k >= 9 && k <= 10 ) )continue ;    
    
            // for reco preselected objects dR histograms
            sprintf( dR_name , "DeltaR_%s_%s_" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dR_title ,"DeltaR_%s_%s_ Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dR_Reco.at(i).at(k) = new TH1D(dR_name,dR_title, 1000, 0, 10.0);
            h_dR_Reco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dR_Reco[" <<i<<"]["<<k<<"].name() : "<< h_dR_Reco.at(i).at(k)->GetName()<<endl;                  
      
            // for reco preselected objects dEta histograms
            sprintf( dEta_name , "DeltaEta(%s_%s)" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dEta_title ,"DeltaEta(%s_%s) Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dEta_Reco.at(i).at(k) = new TH1D(dEta_name,dEta_title, 100, 0, 10.0);
            h_dEta_Reco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dEta_Reco" <<i<<"]["<<k<<"].name() : "<< h_dEta_Reco.at(i).at(k)->GetName()<<endl;                  
      
      
            // for reco preselected objects dPhi histograms
            sprintf( dPhi_name , "DeltaPhi(%s_%s)" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPhi_title ,"DeltaPhi(%s_%s) Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dPhi_Reco.at(i).at(k) = new TH1D(dPhi_name,dPhi_title, 100, 0, 10.0);
            h_dPhi_Reco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dPhi_Reco[" <<i<<"]["<<k<<"].name() : "<< h_dPhi_Reco.at(i).at(k)->GetName()<<endl;                  
      
      
            // for lep-bjet dPt histograms  
            if(i == 0){
            sprintf( dPt_name , "DeltaPt_%s_%s_" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPt_title ,"DeltaPt(%s_%s) Distribution",reco_object[i].c_str(),reco_object[k].c_str());
            h_dPt_Reco.at(k) = new TH1D(dPt_name,dPt_title, 500, 0, 500.0);
            h_dPt_Reco.at(k) ->GetYaxis()->SetTitle("Events");
            // cout<<"h_dPt_Reco[" <<i<<"]["<<k<<"].name() : "<< h_dPt_Reco.at(k)->GetName()<<endl;                   
            } // if loop 

            if ( (reco_object[i] == "mu1") && ( reco_object[k] == "bjet1" || reco_object[k] == "qjet1" )) {

            if ( reco_object[k] == "bjet1" ) j = 0 ;
            if ( reco_object[k] == "qjet1" ) j = 1 ;

            // cout << "\ni = " << i <<" and j = " << reco_object[k] ;
            sprintf( dR_name , "DeltaR_%s_%s__lt04" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dR_title ,"DeltaR(%s_%s)_lt04 Distribution",reco_object[i].c_str(),reco_object[k].c_str()) ;
            h_dR_Reco_lt04.at(i).at(j) = new TH1D(dR_name,dR_title, 100, 0.0, 0.50);
            h_dR_Reco_lt04.at(i).at(j) ->GetYaxis()->SetTitle("Events");

            sprintf( dPt_name , "DeltaPt_%s_%s__lt10" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPt_title ,"DeltaPt_%s_%s__lt10 Distribution",reco_object[i].c_str(),reco_object[k].c_str());
            h_dPt_Reco_lt10.at(i).at(j) = new TH1D(dPt_name,dPt_title,20, 0, 20.0);
            h_dPt_Reco_lt10.at(i).at(j) ->GetYaxis()->SetTitle("Events");

            sprintf( dPt_name , "DeltaPt_%s_%s__lt15" , reco_object[i].c_str(), reco_object[k].c_str() ) ;
            sprintf( dPt_title ,"DeltaPt_%s_%s__lt15 Distribution",reco_object[i].c_str(),reco_object[k].c_str());
            h_dPt_Reco_lt15.at(i).at(j) = new TH1D(dPt_name,dPt_title,20, 0, 20.0);
            h_dPt_Reco_lt15.at(i).at(j) ->GetYaxis()->SetTitle("Events");

            }
          }
        }
   }     

/////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------mc-Reco dR Histogram--------------------------------------


void  dRHisto_MCRecoObject()
{
  // New defination of histogram
  char dR_name[100], dR_title[100];
  string mc_object[4] = {"Higgs","W_Higgs", "Top", "W_Top"};
  string reco_object[3] = {"AK8jet1", "AK8jet2","AK8jet3"};
  //cout<<"\nFunc 6" ;
  for (Int_t i = 0; i < 3; i++) {          
    for (Int_t k = 0; k < 4; k++) {
      // for mc  objects dR histograms
      sprintf( dR_name, "DeltaR_%s_%s_" ,reco_object[i].c_str(), mc_object[k].c_str()) ;
      sprintf( dR_title,"DeltaR(%s_%s) Distribution" , reco_object[i].c_str(), mc_object[k].c_str()) ;
      h_dR_MCReco.at(i).at(k) = new TH1D(dR_name,dR_title, 500, 0, 5.0);
      h_dR_MCReco.at(i).at(k) ->GetYaxis()->SetTitle("Events");
      //cout<<"h_dR_MCReco[" <<i<<"]["<<k<<"].name() : "<< h_dR_MCReco.at(i).at(k)->GetName()<<endl;      
    }
  }     
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------Tagged jets Histogram ---------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////

void   Define_Tag_Jet_Histo()
   {
      char tag_name[100] , tag_title[100] ;
      int x1 = -1 ;
      int rk = -1 ;
    
      string jet_tag[4] = { "Wjet", "topjet", "Higgsjet", "fatjet" } ; 
      string  Wjet_var[12]  = { "Pt", "Eta", "Mass", "PuppiSDMass","CHSPrunedMass", "tau21","tau32","Puppitau21", "PUPPItau32", "CHStau42","PUPPIMass", "PUPPItau42"} ;
      string   top_var[12]  = { "Pt", "Eta", "Mass", "PuppiSDMass","CHSPrunedMass", "tau21","tau32","Puppitau21", "PUPPItau32", "CHStau42","PUPPIMass", "PUPPItau42"} ;
      string Higgs_var[12]  = {"Pt", "Eta", "Mass", "PuppiSDMass","CHSPrunedMass", "tau21","tau32","Puppitau21", "PUPPItau32", "CHStau42","PUPPIMass", "PUPPItau42"} ;
      //cout<<"\nFunc 7" ;
      for( int h =0 ; h < 3 ; h ++) {       
        // neglecting fatjet objetcs
        sprintf( tag_name, "N(%s)" , jet_tag[h].c_str() ) ;
        sprintf( tag_title, "N(%s) Distribution" , jet_tag[h].c_str() ) ;
        h_tag_N.at(h)  =  new TH1D(tag_name,tag_title, 10, 0, 10);
        h_tag_N.at(h)  -> GetYaxis()->SetTitle("Events");
        //cout<<"h_tag_N[" <<h<<"].name() : "<< h_tag_N.at(h)->GetName()<<endl;     
      }
    
      // Here i = 0-1 Wjets, i -> 2 topjet, i = 3 Higgsjet, i = 4-5  fatjet,Use this index cycle for filling plots  
      for(     int Sj = 0 ; Sj <  4; Sj ++) {


        for( int Tk = 0 ; Tk < 12; Tk ++ ) {
    

          if ( Sj < 2  ) {
            x1 = Sj + 1 ;                // for Wjets index   0-1     
            sprintf( tag_name, "%s(%s%d)",  Wjet_var[Tk].c_str(), jet_tag[0].c_str(), x1 ) ;  
            sprintf( tag_title,"%s(%s%d) Distribution", Wjet_var[Tk].c_str(), jet_tag[0].c_str(), x1);        
          }
          if ( Sj == 2 ) {
            x1 = Sj - 1 ;           // for topjet index  2
            sprintf( tag_name, "%s(%s%d)",  top_var[Tk].c_str(), jet_tag[1].c_str(), x1 ) ;  
            sprintf( tag_title,"%s(%s%d) Distribution", top_var[Tk].c_str(), jet_tag[1].c_str(), x1); 
          }
          if ( Sj == 3 ) {
            x1 = Sj - 2 ;           // for Higgsjet index   3 
            sprintf( tag_name, "%s(%s%d)",  Higgs_var[Tk].c_str(), jet_tag[2].c_str(), x1 ) ;       
            sprintf( tag_title,"%s(%s%d) Distribution", Higgs_var[Tk].c_str(), jet_tag[2].c_str(), x1);   
          }          
          if ( Sj > 3)      {
            x1 = Sj - 3 ;            // for fatjet index 4-5
            sprintf( tag_name, "%s(%s%d)",  Wjet_var[Tk].c_str(), jet_tag[3].c_str(), x1 ) ;      
            sprintf( tag_title,"%s(%s%d) Distribution", Wjet_var[Tk].c_str(), jet_tag[3].c_str(), x1);  
          }         
    
          if(Tk == 0 ) {
            h_tag_Pt.at(Sj)             = new TH1D(tag_name,tag_title, 40, 0, 1600.0);
            h_tag_Pt.at(Sj)             ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_Pt[" <<Sj<<"].name() : "<< h_tag_Pt.at(Sj)->GetName()<<endl;             
          }      
          if(Tk == 1 )  {
            h_tag_Eta.at(Sj)           = new TH1D(tag_name,tag_title, 200, -5.0, 5.0);                   
            h_tag_Eta.at(Sj)            ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_Eta[" <<Sj<<"].name() : "<< h_tag_Eta.at(Sj)->GetName()<<endl;       
          }      
          if(Tk == 2 ) {
            h_tag_Mass.at(Sj)         = new TH1D(tag_name,tag_title, 100, 0, 1000.0);         
            h_tag_Mass.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_Mass[" <<Sj<<"].name() : "<< h_tag_Mass.at(Sj)->GetName()<<endl;             
          }                                
          if(Tk == 3  )  {
            h_tag_SD.at(Sj)           = new TH1D(tag_name,tag_title, 50, 0.0, 500.0);       
            h_tag_SD.at(Sj)       ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_SD[" <<Sj<<"].name() : "<< h_tag_SD.at(Sj)->GetName()<<endl;       
          }            
          if( Tk == 4 )  {
            h_tag_Pruned.at(Sj)        = new TH1D(tag_name,tag_title, 50, 0.0, 500.0);        
            h_tag_Pruned.at(Sj)       ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_SD[" <<Sj<<"].name() : "<< h_tag_SD.at(Sj)->GetName()<<endl;       
          }            
    
          if(Tk == 5 )  {
            h_tag_tau21.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_tau21.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_tau21.at(Sj)->GetName()<<endl;       
          }                        
          if(Tk == 6 )  {
            h_tag_tau32.at(Sj)         = new TH1D(tag_name,tag_title,200, -1.0, 1.0);               
            h_tag_tau32.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_tau32.at(Sj)->GetName()<<endl;       
          }   
          if(Tk == 7 )  {
            h_tag_Puppitau21.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_Puppitau21.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_Puppitau21.at(Sj)->GetName()<<endl;        
          }   
          if(Tk == 8 )  {
            h_tag_Puppitau32.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_Puppitau32.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_Puppitau32.at(Sj)->GetName()<<endl;        
          }   
          if(Tk == 9 )  {
            h_tag_CHStau42.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_CHStau42.at(Sj)         ->GetYaxis()->SetTitle("Events");
          } 
          if(Tk == 10){ 
            h_tag_PUPPImass.at(Sj)         = new TH1D(tag_name,tag_title, 100, 0, 1000.0);       
            h_tag_PUPPImass.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_PUPPImass[" <<Sj<<"].name() : "<< h_tag_PUPPImass.at(Sj)->GetName()<<endl;       
          } 
          if(Tk == 11 )  {
            h_tag_Puppitau42.at(Sj)         = new TH1D(tag_name,tag_title, 200, -1.0, 1.0);               
            h_tag_Puppitau42.at(Sj)         ->GetYaxis()->SetTitle("Events");
            //cout<<"h_tag_tau[" <<Sj<<"].name() : "<< h_tag_Puppitau32.at(Sj)->GetName()<<endl;        
          }   
    
    
        }      
      }
 }
       
       
void  dR_tagjetHisto() {
  
  // New defination of histogram
  char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ;
  string tag_jet[6] = {"Wjet1", "Wjet2", "topjet1",  "Higgsjet1", "fatjet1", "fatjet2"} ;                   
  //for tag jet   dR histograms
  // Here i = 0-1 Wjets, i -> 2 topjet, i = 3 Higgsjet, i = 4-5 fatjet, Use this index cycle for illing plots
  //cout<<"\nFunc 8" ;
  for (int i = 0; i < 4; i++) {
    for(int j = i+1; j < 4; j++) {
      // neglecting fatjets objects

      sprintf(dR_name,"DeltaR_%s_%s_" , tag_jet[i].c_str(), tag_jet[j].c_str() ) ;
      sprintf(dR_title,"DeltaR(%s_%s) Distribution", tag_jet[i].c_str(), tag_jet[j].c_str() ) ; 
      h_dR_tagjet.at(i).at(j)   =    new TH1D(dR_name,dR_title, 50, 0, 5.0);
      h_dR_tagjet.at(i).at(j)   ->   GetYaxis()->SetTitle("Events");         
      //cout<<"h_dR_tagjet["<<i<<"]["<<j<<"].name() : "<< h_dR_tagjet.at(i).at(j)->GetName()<<endl;     
    }
  }

}
       
       
void  Define_Reco_tagjetHisto()  {
  // New defination of histogram
  char dR_name[100], dR_title[100], dPt_name[100], dPt_title[100] ,dEta_title[100], dEta_name[100], dPhi_name[100], dPhi_title[100];
  string reco_object[3]  =  {"muon","bjet1", "bjet2"} ;
  string tag_jet[6] = {"Wjet1", "Wjet2", "topjet1", "Higgsjet1", "fatjet1", "fatjet2" } ;  

  //for tag jet - muon  dR histograms
  // Here i = 0-1 Wjets, i -> 2 topjet, i = 3 Higgsjet, i = 4-5 fatjet, Use this index cycle for illing plots
  //cout<<"\nFunc 9" ;  
  int s = -1 ;
  for (Int_t i = 0; i < 3; i++) {
    for(Int_t j = 0; j < 4; j++) {
      // neglecting fatjets objects
      //cout << "\n value i = " << i << " && value j << " << j ;        
      if (tag_jet[j] != "Higgsjet1") continue ;   
      if( i == 0){      
        sprintf( dR_name,"DeltaR_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dR_title,"DeltaR_%s_%s_ Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dR_Recomu_tagjet.at(j)= new TH1D(dR_name,dR_title, 50, 0, 5.0);
        h_dR_Recomu_tagjet.at(j)->GetYaxis()->SetTitle("Events");
        //cout<<"h_dR_Recomu_tagjet]"<<j<<"].name() : "<< h_dR_Recomu_tagjet.at(j)->GetName()<<endl;          

        sprintf( dEta_name, "DeltaEta(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dEta_title,"DeltaEta(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dEta_Recomu_tagjet.at(j)= new TH1D(dEta_name,dEta_title, 50, 0, 5.0);
        h_dEta_Recomu_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPhi_name, "DeltaPhi(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPhi_title,"DeltaPhi(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dPhi_Recomu_tagjet.at(j)= new TH1D(dPhi_name,dPhi_title, 50, 0, 5.0);
        h_dPhi_Recomu_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPt_name,"DeltaPt_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPt_title,"DeltaPt(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str());
        h_dPt_lep_tagjet.at(j)= new TH1D(dPt_name,dPt_title, 100, 0, 500.0);
        h_dPt_lep_tagjet.at(j)->GetYaxis()->SetTitle("Events");       
        //cout<<"h_dPt_lep_tagjet]"<<j<<"].name() : "<< h_dPt_lep_tagjet.at(j)->GetName()<<endl;            
      }

      if( i == 1){
        sprintf( dR_name,"DeltaR_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dR_title,"DeltaR(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str());  
        h_dR_Recob1_tagjet.at(j)= new TH1D(dR_name,dR_title, 50, 0, 5.0);
        h_dR_Recob1_tagjet.at(j)->GetYaxis()->SetTitle("Events");      
        //cout<<"h_dR_Recob1_tagjet]"<<j<<"].name() : "<< h_dR_Recob1_tagjet.at(j)->GetName()<<endl;                    

        sprintf( dEta_name, "DeltaEta(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dEta_title,"DeltaEta(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dEta_Recob1_tagjet.at(j)= new TH1D(dEta_name,dEta_title, 50, 0, 5.0);
        h_dEta_Recob1_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPhi_name, "DeltaPhi(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPhi_title,"DeltaPhi(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dPhi_Recob1_tagjet.at(j)= new TH1D(dPhi_name,dPhi_title, 50, 0, 5.0);
        h_dPhi_Recob1_tagjet.at(j)->GetYaxis()->SetTitle("Events");
      }

      if( i == 2){
        sprintf( dR_name,"DeltaR_%s_%s_",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dR_title,"DeltaR_%s_%s_ Distribution", reco_object[i].c_str(), tag_jet[j].c_str() );
        h_dR_Recob2_tagjet.at(j)= new TH1D(dR_name,dR_title, 50, 0, 5.0);
        h_dR_Recob2_tagjet.at(j)->GetYaxis()->SetTitle("Events");
        //cout<<"h_dR_Recob2_tagjet]"<<j<<"].name() : "<< h_dR_Recob2_tagjet.at(j)->GetName()<<endl;  

        sprintf( dEta_name, "DeltaEta(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dEta_title,"DeltaEta(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dEta_Recob2_tagjet.at(j)= new TH1D(dEta_name,dEta_title, 50, 0, 5.0);
        h_dEta_Recob2_tagjet.at(j)->GetYaxis()->SetTitle("Events");

        sprintf( dPhi_name, "DeltaPhi(%s_%s)",  reco_object[i].c_str(), tag_jet[j].c_str() ) ;
        sprintf( dPhi_title,"DeltaPhi(%s_%s) Distribution", reco_object[i].c_str(), tag_jet[j].c_str()) ;
        h_dPhi_Recob2_tagjet.at(j)= new TH1D(dPhi_name,dPhi_title, 50, 0, 5.0);
        h_dPhi_Recob2_tagjet.at(j)->GetYaxis()->SetTitle("Events");     

      }
    }//END OF J
  }// END OF I

} // END OF FUNC


// ============================================================================================================


//// // //  //       //       ////           //////////   ////////            //////////   
//      //  //       //      //   //         //           //                         // 
//      //  //       //     //     //        //           //                        //
// //////   //// //////    // // // //       //////////   //////     =======    /////
//          //       //   //         //              //   //                       \\\
//          //       //  //           //             //   //                        \\\
//          //       // //             //    //////////   ////////            ///////\\\


///////////////////////////////////////////////////////////////////////////////////////////////////////
//PHASE_III Functions AND HISTOGRAMS..........REMEBER TO CHECK AND EDIT FROM HERE
////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////=========THIS SECTION FOR DEFINING MAPS & KEYS=============//////////////////////////////////////////////////////////////////////////
   std::map<int, TString > Histogram_Object_List = {
                                                   { 0   , "Hist_nMET"}, 
                                                   { 1   , "Hist_nElectron"}, 
                                                   { 2   , "Hist_nMuon"}, 
                                                   { 3   , "Hist_nJet"}, 
                                                   { 4   , "Hist_nFatJet"}, 
                                                   { 5   , "Hist_nForwJet"}, 
                                                   { 6   , "Hist_nCleanJet"}, 
                                                   { 7   , "Hist_nbjet"}, 
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ; 



   std::map<int, TString > Histogram_Pt_List = {
                                                   { 0   , "Hist_MET_pt"}, 
                                                   { 1   , "Hist_MET_sumEt"}, 
                                                   { 2   , "Hist_Electron1_pt"}, 
                                                   { 3   , "Hist_Electron2_pt"}, 
                                                   { 4   , "Hist_Muon1_pt"}, 
                                                   { 5   , "Hist_Muon2_pt"}, 
                                                   { 6   , "Hist_Jet1_pt"}, 
                                                   { 7   , "Hist_Jet2_pt"}, 
                                                   { 8   , "Hist_FatJet1_pt"}, 
                                                   { 9   , "Hist_FatJet2_pt"},  
                                                   { 10  , "Hist_ForwJet1_pt"}, 
                                                   { 11  , "Hist_ForwJet2_pt"}, 
                                                   { 12  , "Hist_CleanJet1_pt"}, 
                                                   { 13  , "Hist_CleanJet2_pt"}, 
                                                   { 14  , "Hist_bJet1_pt"}, 
                                                   { 15  , "Hist_bJet2_pt"}, 
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ;

   std::map<int, TString > Histogram_Eta_List = {
                                                   { 0   , "Hist_MET_eta1"}, 
                                                   { 1   , "Hist_MET_eta2"}, 
                                                   { 2   , "Hist_Electron1_eta"}, 
                                                   { 3   , "Hist_Electron2_eta"}, 
                                                   { 4   , "Hist_Muon1_eta"}, 
                                                   { 5   , "Hist_Muon2_eta"}, 
                                                   { 6   , "Hist_Jet1_eta"}, 
                                                   { 7   , "Hist_Jet2_eta"}, 
                                                   { 8   , "Hist_FatJet1_eta"}, 
                                                   { 9   , "Hist_FatJet2_eta"},  
                                                   { 10  , "Hist_ForwJet1_eta"}, 
                                                   { 11  , "Hist_ForwJet2_eta"}, 
                                                   { 12  , "Hist_CleanJet1_eta"}, 
                                                   { 13  , "Hist_CleanJet2_eta"}, 
                                                   { 14  , "Hist_bJet1_eta"}, 
                                                   { 15  , "Hist_bJet2_eta"}, 
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ;       

   std::map<int, TString > Histogram_Phi_List = {
                                                   { 0   , "Hist_MET_phi1"}, 
                                                   { 1   , "Hist_MET_phi2"}, 
                                                   { 2   , "Hist_Electron1_phi"}, 
                                                   { 3   , "Hist_Electron2_phi"}, 
                                                   { 4   , "Hist_Muon1_phi"}, 
                                                   { 5   , "Hist_Muon2_phi"}, 
                                                   { 6   , "Hist_Jet1_phi"}, 
                                                   { 7   , "Hist_Jet2_phi"}, 
                                                   { 8   , "Hist_FatJet1_phi"}, 
                                                   { 9   , "Hist_FatJet2_phi"},  
                                                   { 10  , "Hist_ForwJet1_phi"}, 
                                                   { 11  , "Hist_ForwJet2_phi"}, 
                                                   { 12  , "Hist_CleanJet1_phi"}, 
                                                   { 13  , "Hist_CleanJet2_phi"}, 
                                                   { 14  , "Hist_bJet1_phi"}, 
                                                   { 15  , "Hist_bJet2_phi"}, 
                                                   // { 17  , "Hist_"}, 
                                                   // { 18  , "Hist_"}, 
                                                   // { 19  , "Hist_"}, 
                                                   // { 20  , "Hist_"},  
                                                } ;  

   std::map<int, TString > Histogram_FatJet_List = {

                                                { 0    , "Hist_FatJet1_deepTagMD_H4qvsQCD"},
                                                { 1    , "Hist_FatJet1_deepTagMD_TvsQCD   "},
                                                { 2    , "Hist_FatJet1_deepTagMD_WvsQCD"},
                                                { 3    , "Hist_FatJet1_deepTag_H"},
                                                { 4    , "Hist_FatJet1_deepTag_TvsQCD"},
                                                { 5    , "Hist_FatJet1_deepTag_WvsQCD"},
                                                { 6    , "Hist_FatJet1_tau1"},
                                                { 7    , "Hist_FatJet1_tau2"},
                                                { 8    , "Hist_FatJet1_tau3"},
                                                { 9    , "Hist_FatJet1_tau4"},
                                                { 10   , "Hist_FatJet1_ratio_tau21"}, 
                                                { 11   , "Hist_FatJet1_ratio_tau31"},
                                                { 12   , "Hist_FatJet1_ratio_tau32"}, 
                                                { 13   , "Hist_FatJet1_ratio_tau41"}, 
                                                { 14   , "Hist_FatJet1_ratio_tau42"}, 
                                                { 15   , "Hist_FatJet1_ratio_tau43"}, 
                                                { 16   , "Hist_FatJet1_mass"},
                                                { 17   , "Hist_FatJet1_msoftdrop"},
                                                { 18   , "Hist_FatJet1_msoftdrop_corr"}
                                               
                                                // { 19   , "Hist_FatJet1_eta_clean"},                                                
                                                // { 20   , "Hist_FatJet1_phi_clean"},
                                                // { 21   , "Hist_FatJet1_msoftdrop_corr"}                                                                                                                                                    
                                                };

   std::map<int, TString > Histogram_FatJet2_List = {                                                                                               
                                                { 0    , "Hist_FatJet2_deepTagMD_H4qvsQCD"},
                                                { 1    , "Hist_FatJet2_deepTagMD_TvsQCD   "},
                                                { 2    , "Hist_FatJet2_deepTagMD_WvsQCD"},
                                                { 3    , "Hist_FatJet2_deepTag_H"},
                                                { 4    , "Hist_FatJet2_deepTag_TvsQCD"},
                                                { 5    , "Hist_FatJet2_deepTag_WvsQCD"},
                                                { 6    , "Hist_FatJet2_tau1"},
                                                { 7    , "Hist_FatJet2_tau2"},                                     
                                                { 8    , "Hist_FatJet2_tau3"},                                                
                                                { 9    , "Hist_FatJet2_tau4"},
                                                { 10   , "Hist_FatJet2_ratio_tau21"}, 
                                                { 11   , "Hist_FatJet2_ratio_tau31"},
                                                { 12   , "Hist_FatJet2_ratio_tau32"}, 
                                                { 13   , "Hist_FatJet2_ratio_tau41"}, 
                                                { 14   , "Hist_FatJet2_ratio_tau42"},                                                
                                                { 15   , "Hist_FatJet2_ratio_tau43"},                                                
                                                { 16   , "Hist_FatJet2_mass"},
                                                { 17   , "Hist_FatJet2_msoftdrop"},
                                                { 18   , "Hist_FatJet2_msoftdrop_corr"}

                                                // { 19   , "Hist_FatJet2_eta_clean"},                                                
                                                // { 20   , "Hist_FatJet2_phi_clean"},  
                                                // { 21   , "Hist_FatJet2_msoftdrop_corr"}    
                                                };


   std::map<int, TString > Histogram_DeltaR_FatJet_List = {                                                                                               
                                                    { 0    , "DeltaR_Hist_FatJet1_wrt_jet1"},
                                                    { 1    , "DeltaR_Hist_FatJet1_wrt_jet2"},
                                                    { 2    , "DeltaR_Hist_FatJet1_wrt_jet3"},
                                                    { 3    , "DeltaR_Hist_FatJet2_wrt_jet1"},
                                                    { 4    , "DeltaR_Hist_FatJet2_wrt_jet2"},
                                                    { 5    , "DeltaR_Hist_FatJet2_wrt_jet3"},
                                                    { 6    , "DeltaR_Hist_FatJet3_wrt_jet1"},
                                                    { 7    , "DeltaR_Hist_FatJet3_wrt_jet2"},
                                                    { 8    , "DeltaR_Hist_FatJet3_wrt_jet3"},

                                                    } ;



   std::map<int, TString > Histogram_DeltaR_Muon_List = {                                                                                               
                                                    { 0    , "DeltaR_Hist_Muon_wrt_jet1"},
                                                    { 1    , "DeltaR_Hist_Muon_wrt_jet2"},
                                                    { 2    , "DeltaR_Hist_Muon_wrt_jet3"},
                                                    { 3    , "DeltaR_Hist_Muon_wrt_cleanjet1"},
                                                    { 4    , "DeltaR_Hist_Muon_wrt_cleanjet2"},
                                                    { 5    , "DeltaR_Hist_Muon_wrt_cleanjet3"},
                                                    { 6    , "DeltaR_Hist_Muon_wrt_bjet1"},
                                                    { 7    , "DeltaR_Hist_Muon_wrt_bjet2"},
                                                    { 8    , "DeltaR_Hist_Muon_wrt_bjet3"},
                                                    } ;


   std::map<int, TString > Histogram_Higgs_List = {

                                                { 0    , "Hist_HiggsJet_deepTagMD_H4qvsQCD"},
                                                { 1    , "Hist_HiggsJet_deepTagMD_TvsQCD   "},
                                                { 2    , "Hist_HiggsJet_deepTagMD_WvsQCD"},
                                                { 3    , "Hist_HiggsJet_deepTag_H"},
                                                { 4    , "Hist_HiggsJet_deepTag_TvsQCD"},
                                                { 5    , "Hist_HiggsJet_deepTag_WvsQCD"},
                                                { 6    , "Hist_HiggsJet_ratio_tau21"}, 
                                                { 7    , "Hist_HiggsJet_ratio_tau31"},
                                                { 8    , "Hist_HiggsJet_ratio_tau32"}, 
                                                { 9    , "Hist_HiggsJet_ratio_tau41"}, 
                                                { 10   , "Hist_HiggsJet_ratio_tau43"},                                                 
                                                { 11   , "Hist_HiggsJet_ratio_tau42"}, 
                                                { 12   , "Hist_HiggsJet_msoftdrop"},                                                
                                                { 13   , "Hist_HiggsJet_mass"},
                                                { 14   , "Hist_HiggsJet_pt"},
                                                { 15   , "Hist_HiggsJet_eta"},                                                
                                                { 16   , "Hist_N_HiggsJet"},
                                                { 17   , "Hist_DeltaR_HiggsJet_wrt_lep"} ,
                                                { 18   , "Hist_DeltaR_HiggsJet_wrt_jet1"} , 
                                                { 19   , "Hist_DeltaR_HiggsJet_wrt_jet2"} ,
                                                { 20   , "Hist_DeltaR_HiggsJet_wrt_jet3"}  ,                                                                                                                                                                                              
                                                { 21   , "Hist_HiggsJet_msoftdrop_corr"}                                                

                                             };


   std::map<int, TString > Histogram_LepCleanJet_List = {
                                                            { 0   , "Hist_Cleanjet1_pt"}, 
                                                            { 1   , "Hist_Cleanjet2_pt"}, 
                                                            { 2   , "Hist_UnCleanJet1_pt"}, 
                                                            { 3   , "Hist_UnCleanJet2_pt"}, 
                                                            { 4   , "Hist_Cleanjet1_eta"}, 
                                                            { 5   , "Hist_Cleanjet2_eta"}, 
                                                            { 6   , "Hist_UnCleanJet1_eta"}, 
                                                            { 7   , "Hist_UnCleanJet2_eta"}, 
                                                            { 8   , "Hist_Cleanjet1_phi"}, 
                                                            { 9   , "Hist_Cleanjet2_phi"}, 
                                                            { 10  , "Hist_UnCleanJet1_phi"}, 
                                                            { 11  , "Hist_UnCleanJet2_phi"}, 
                                                            { 12  , "DeltaR_Hist_Muon_wrt_Cleanjet1"}, 
                                                            { 13  , "DeltaR_Hist_Muon_wrt_Cleanjet2"}, 
                                                            { 14  , "DeltaR_Hist_Muon_wrt_UnCleanjet1"}, 
                                                            { 15  , "DeltaR_Hist_Muon_wrt_UnCleanjet2"}, 
                                                            { 16  , "DeltaPt_Hist_Muon_wrt_Cleanjet1"}, 
                                                            { 17  , "DeltaPt_Hist_Muon_wrt_Cleanjet2"}, 
                                                            { 18  , "DeltaPt_Hist_Muon_wrt_UnCleanjet1"}, 
                                                            { 19  , "DeltaPt_Hist_Muon_wrt_UnCleanjet2"},  
                                                       } ;


   std::map<int, TString > Histogram_LepCleanFatJet_List = {
                                                                  { 0   , "Hist_CleanFatJet1_pt"}, 
                                                                  { 1   , "Hist_CleanFatJet2_pt"}, 
                                                                  { 2   , "Hist_UnCleanFatJet1_pt"}, 
                                                                  { 3   , "Hist_UnCleanFatJet2_pt"}, 
                                                                  { 4   , "Hist_CleanFatJet1_eta"}, 
                                                                  { 5   , "Hist_CleanFatJet2_eta"}, 
                                                                  { 6   , "Hist_UnCleanFatJet1_eta"}, 
                                                                  { 7   , "Hist_UnCleanFatJet2_eta"}, 
                                                                  { 8   , "Hist_CleanFatJet1_phi"}, 
                                                                  { 9   , "Hist_CleanFatJet2_phi"}, 
                                                                  { 10  , "Hist_UnCleanFatJet1_phi"}, 
                                                                  { 11  , "Hist_UnCleanFatJet2_phi"}, 
                                                                  { 12  , "DeltaR_Hist_Muon_wrt_Cleanfatjet1"}, 
                                                                  { 13  , "DeltaR_Hist_Muon_wrt_Cleanfatjet2"}, 
                                                                  { 14  , "DeltaR_Hist_Muon_wrt_UnCleanfatjet1"}, 
                                                                  { 15  , "DeltaR_Hist_Muon_wrt_UnCleanfatjet2"}, 
                                                                  // { 17  , "Hist_"}, 
                                                                  // { 18  , "Hist_"}, 
                                                                  // { 19  , "Hist_"}, 
                                                                  // { 20  , "Hist_"},  
                                                            } ;

   std::map<int, TString > Histogram_Delta_wrt_Pt_LepCleanJet_List = {
                                                            { 0   , "DeltaR_wrt_Pt_Hist_for_Cleanjet1"},  
                                                            { 1   , "DeltaR_wrt_Pt_Hist_for_Cleanjet2"},  
                                                            { 2   , "DeltaR_wrt_Pt_Hist_for_UnCleanjet1"}, 
                                                            { 3   , "DeltaR_wrt_Pt_Hist_for_UnCleanjet2"}, 
                                                            { 4   , "DeltaR_wrt_Pt_Hist_for_Cleanfatjet1"},  
                                                            { 5   , "DeltaR_wrt_Pt_Hist_for_Cleanfatjet2"},  
                                                            { 6   , "DeltaR_wrt_Pt_Hist_for_UnCleanfatjet1"}, 
                                                            { 7   , "DeltaR_wrt_Pt_Hist_for_UnCleanfatjet2"}, 
                                                            { 8   , "DeltaPt_wrt_Pt_Hist_for_Cleanjet1"},  
                                                            { 9   , "DeltaPt_wrt_Pt_Hist_for_Cleanjet2"},  
                                                            { 10  , "DeltaPt_wrt_Pt_Hist_for_UnCleanjet1"}, 
                                                            { 11  , "DeltaPt_wrt_Pt_Hist_for_UnCleanjet2"}, 
                                                            // { 12  , "DeltaR_Hist_Muon_wrt_Cleanjet1"}, 
                                                            // { 13  , "DeltaR_Hist_Muon_wrt_Cleanjet2"}, 
                                                            // { 14  , "DeltaR_Hist_Muon_wrt_UnCleanjet1"}, 
                                                            // { 15  , "DeltaR_Hist_Muon_wrt_UnCleanjet2"}, 
                                                            // { 17  , "Hist_"}, 
                                                            // { 18  , "Hist_"}, 
                                                            // { 19  , "Hist_"}, 
                                                            // { 20  , "Hist_"},  
                                                       } ;      


    //==============Luminosity Normalization for each samples========================================================
         std::map< int, TString> Sample_List = {  // Xsections are in units fb-1 just remember
                                                               {  0   , "temp"              ,                           }, 
                                                               {  1   , "Tprime_M1000_UL17",                            }, 
                                                               {  2   , "Tprime_M1500_UL17",                            }, 
                                                               {  3   , "Tprime_M1800_UL17",                            }, 
                                                               {  4   , "TTbar_UL17",                                   }, 
                                                               {  5   , "QCD_Pt-80_MuEnr_UL17",                         }, 
                                                               {  6   , "QCD_Pt-120_MuEnr_UL17",                        }, 
                                                               {  7   , "QCD_Pt-170_MuEnr_UL17",                        }, 
                                                               {  8   , "QCD_Pt-300_MuEnr_UL17",                        }, 
                                                               {  9   , "QCD_Pt-470_MuEnr_UL17",                        }, 
                                                               {  10  , "QCD_Pt-600_MuEnr_UL17",                        }, 
                                                               {  11  , "QCD_Pt-800_MuEnr_UL17",                        }, 
                                                               {  12  , "QCD_Pt-1000_MuEnr_UL17",                       }, 
                                                               {  13  , "WJets_LNu_UL17",                               }, 
                                                               {  14  , "DYJetsToLL_UL17",                              }, 
                                                               {  15  , "ST_s-channel_4f_leptonDecays_v3_",             }, 
                                                               {  16  , "ST_t-channel_antitop_4f_inclusiveDecays_v3_"   }, 
                                                               {  17  , "ST_t-channel_top_4f_inclusiveDecays_v3_",      }, 
                                                               {  18  , "ST_tW_antitop_5f_inclusiveDecays_v3_",         }, 
                                                               {  19  , "ST_tW_top_5f_inclusiveDecays_v3_",             } 
                                                                 } ;
    
      std::map<TString,double> Sample_X_Section = {  // Xsections are in units fb-1 just remember
                                                               { "temp"              ,                        1.064e+01   },
                                                               { "Tprime_M1000_UL17",                         3.136e+01   },  
                                                               { "Tprime_M1500_UL17",                         1.064e+01  },  
                                                               { "Tprime_M1800_UL17",                         5.970e+00   },  
                                                               { "TTbar_UL17",                                7.641e+05  },    
                                                               { "QCD_Pt-80_MuEnr_UL17",                      8.903e+07    },    
                                                               { "QCD_Pt-120_MuEnr_UL17",                     2.074e+07   },
                                                               { "QCD_Pt-170_MuEnr_UL17",                     6.903e+06   },   
                                                               { "QCD_Pt-300_MuEnr_UL17",                     6.194e+05  },    
                                                               { "QCD_Pt-470_MuEnr_UL17",                     5.893e+04  },   
                                                               { "QCD_Pt-600_MuEnr_UL17",                     1.846e+04  },
                                                               { "QCD_Pt-800_MuEnr_UL17",                     3.294e+03  },  
                                                               { "QCD_Pt-1000_MuEnr_UL17",                    1.094e+03  } ,
                                                               { "WJets_LNu_UL17",                            5.373e+07  } ,
                                                               { "DYJetsToLL_UL17",                           5.413e+06   } ,                                                               
                                                               { "ST_s-channel_4f_leptonDecays_v3_",               3.365e+03   },
                                                               { "ST_t-channel_antitop_4f_inclusiveDecays_v3_",    7.441e+04   },
                                                               { "ST_t-channel_top_4f_inclusiveDecays_v3_",        1.233e+05   },
                                                               { "ST_tW_antitop_5f_inclusiveDecays_v3_",           3.809e+04   },
                                                               { "ST_tW_top_5f_inclusiveDecays_v3_",               3.806e+04   }
                                                                 } ;
    
    
      std::map<TString,double> Sample_Total_Events = {  // total events from Ntuplized samples just remember
                                                               { "temp"              ,                        400000   },
                                                               { "Tprime_M1000_UL17",                              400000   },  
                                                               { "Tprime_M1500_UL17",                              400000   },  
                                                               { "Tprime_M1800_UL17",                              400000   },  
                                                               { "TTbar_UL17",                                     148768378   },  

                                                               { "QCD_Pt-80_MuEnr_UL17",                           613257   }, 

                                                               { "QCD_Pt-120_MuEnr_UL17",                          648944   },

                                                               { "QCD_Pt-170_MuEnr_UL17",                          36918785   },   

                                                               { "QCD_Pt-300_MuEnr_UL17",                          494796  },    

                                                               { "QCD_Pt-470_MuEnr_UL17",                          517382   },   


                                                               { "QCD_Pt-600_MuEnr_UL17",                          17354151   },

                                                             
                                                               { "QCD_Pt-800_MuEnr_UL17",                          16995944  },  

                                                               { "QCD_Pt-1000_MuEnr_UL17",                         14751368  } ,
                                                       
                                                               { "WJets_LNu_UL17",                                 87614760  } ,


                                                               { "DYJetsToLL_UL17",                                101079197   } ,                                                               
                                                               { "ST_s-channel_4f_leptonDecays_v3_",               3.365e+03   },
                                                               { "ST_t-channel_antitop_4f_inclusiveDecays_v3_",    7.441e+04   },
                                                               { "ST_t-channel_top_4f_inclusiveDecays_v3_",        1.233e+05   },
                                                               { "ST_tW_antitop_5f_inclusiveDecays_v3_",           3.809e+04   },
                                                               { "ST_tW_top_5f_inclusiveDecays_v3_",               3.806e+04   }                                                                                                                                
                                                                 } ;       
    
    

      void Luminosity_Normalization(TString sample) {

            TString temp_sample = "NONE";
            TString Dataset     = "NONE";

            for (int i = 0; i < 20; ++i)
            {
                  temp_sample = Sample_List[i];
                  if (!( sample.Contains(temp_sample))) continue ;
                  Dataset     = temp_sample ; 
                  cout <<"\n For Sample = " << Dataset;
            }
    
            double Xsections    = Sample_X_Section[Dataset];
            double Total_Events = Sample_Total_Events[Dataset] ;
                  cout <<"   Xsections = " << Xsections <<" && Events = " << Total_Events <<endl;

            // double Luminosity   = 35.917150 ;  // in units of fb-1 for 2016
            // double Luminosity   = 59.74 ;  // in units of fb-1 for 2018
            double Luminosity   = 41.53 ;  // in units of fb-1 for 2017   
            factor = ( Xsections / Total_Events ) * Luminosity ;
    
            // return Luminosity ;
      }         
/////////////////=========THIS SECTION FOR DEFINING NEW SETS OF HOSTOGRAMS=============///////////////////////////////////////////////////////////////////

    // Histograms for Cut flow 
    void Define_Histo_For_Global_Var() 
    {
    
    
           Good_PV_Histo    = new TH1D("Good_PV_Histo", "Good Primary Vertex Distribution", 100, 0.0, 100);
    
           Good_PV_Pr_Histo = new TH1D("Good_PV_Pr_Histo", "Good Primary Vertex (after Pre-Sel) Distribution", 100, 0.0, 100);
    
    
     
           const int    nBin = 16;
           const double Bin_value[nBin+1] =  {0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 700.0, 800.0, 900.0, 1000.0, 1200.0, 1400.0, 1600.0 } ;
    
           Int_t i;
           const Int_t nx = 14;
           const char *cut_pass[nx] = {  "Total Events",            //0                                      
                                         "Primary_Vertex",          //1
                                         "HLT_Mu50 Trigger",        //2
                                         "Forward Jet Tag"    ,     //3   
                                         "MET Cut" ,                //4                                         
                                         "Muon Cut",                //5
                                         "AK8 Jet Tag" ,            //6
                                         "Clean Jet Tag",           //7           
                                         "Higgs Tag",               //8                                                                                                      
                                         "Higgs_Pt Cut",            //9   
                                         "St Cut"  ,                //10                                       
                                         "bjet tag",                //11                      
                                         "dR check",                //12                    
                                         "Lep Iso",                 //13                                                                                                                             
                                         // "bjet Tag" ,                                                       
                                         // "HiggspT > 300",                                    // "dR(Higgs, bjet) Cut" ,    //9
                                         // "dR(mu, bjet) Cut" ,       //10
                                         // "Pt Bjet Cut" ,            // 11                       
                                        };
    
    
           Cut_Efficiency_Flow = new TH1D("Cut_Efficiency_Flow","Cut Efficiency Flow",nx,0,nx);
           Cut_Efficiency_Flow->SetFillColor(38);
    
           for (i=1;i<=nx;i++) {
               Cut_Efficiency_Flow->GetXaxis()->SetBinLabel(i,cut_pass[i-1]);
           }
    
    
    
           const Int_t sx = 6 ;
           const char *cut_St[sx] = {"St > 000GeV", 
                                     "St > 400GeV", 
                                     "St > 500GeV", 
                                     "St > 600GeV", 
                                     "St > 700GeV",
                                     "St > 800GeV",
    
                                    };
        
           Cut_ST_Cut_Flow = new TH1D("Cut_ST_Cut_Flow", "ST Cut_Flow", sx, 0, sx);
           Cut_ST_Cut_Flow->SetFillColor(30) ;
           for (int i = 1; i <= sx; i++)
           {
             Cut_ST_Cut_Flow->GetXaxis()->SetBinLabel(i,cut_St[i-1]);
           }
    
    
           const Int_t Mx = 4 ;
           const char *cut_MT[Mx] = {"MET > 00GeV", 
                                     "MET > 50GeV", 
                                     "MET > 100GeV", 
                                     "MET > 150GeV"
                                    };
        
           Cut_MET_Cut_Flow = new TH1D("Cut_MET_Cut_Flow", "MET Cut Flow", Mx, 0, Mx);
           Cut_MET_Cut_Flow->SetFillColor(20) ;
           for (int i = 1; i <= Mx; i++)
           {
             Cut_MET_Cut_Flow->GetXaxis()->SetBinLabel(i,cut_MT[i-1]);
           }
    
    
           const Int_t taux = 21 ;
           const char *cut_tau[taux] = {"No cut on tau42", 
                                        "tau42 < 1.00",
                                        "tau42 < 0.95",
                                        "tau42 < 0.90",                                                                      
                                        "tau42 < 0.85",
                                        "tau42 < 0.80",                                   
                                        "tau42 < 0.75", 
                                        "tau42 < 0.70",                                   
                                        "tau42 < 0.65",
                                        "tau42 < 0.60",
                                        "tau42 < 0.55",   
                                        "tau42 < 0.50",                                                                                                        
                                        "tau42 < 0.45", 
                                        "tau42 < 0.40",                                   
                                        "tau42 < 0.35",
                                        "tau42 < 0.30",                                   
                                        "tau42 < 0.25",                                   
                                        "tau42 < 0.20",                                   
                                        "tau42 < 0.15",                                   
                                        "tau42 < 0.10", 
                                        "tau42 < 0.05",                                   
                                       };
        
           Cut_Tau42_Flow = new TH1D("Cut_Tau42_Flow", "Cut Tau42 Flow", taux, 0, taux);
           Cut_Tau42_Flow->SetFillColor(35) ;
           for (int i = 1; i <= taux; i++)
           {
             Cut_Tau42_Flow->GetXaxis()->SetBinLabel(i,cut_tau[i-1]);
           }
    
    
    
    
           const Int_t Higgsx = 5;
           const char *cut_Higgs[Higgsx] = { 
                                        "Total Events",
                                        "Events with Parent",                //0                                      
                                        "Events with matched AK8Jet",           //1
                                        "SDmass passed",           //2
                                        "Tau42 passed" ,            //3                   
                                       };
           Cut_Higgs_Tagging_Flow = new TH1D("Cut_Higgs_Tagging_Flow","Higgs Tagging Flow",Higgsx,0,Higgsx);
           Cut_Higgs_Tagging_Flow->SetFillColor(38);
    
    
           for (i=1;i<=Higgsx;i++) {
            Cut_Higgs_Tagging_Flow->GetXaxis()->SetBinLabel(i,cut_Higgs[i-1]);
           }
    
    
    
           const Int_t pTx = 7 ;
           const char *cut_pTH[pTx] = { "pT > 200GeV", 
                                        "pT > 250GeV", 
                                        "pT > 300GeV", 
                                        "pT > 350GeV",  
                                        "pT > 400GeV",  
                                        "pT > 450GeV",  
                                        "pT > 500GeV", 
                                       };
         
           Cut_pTHiggs_Flow = new TH1D("Cut_pTHiggs_Flow", "Cut pTHiggs Flow", pTx, 0, pTx);
           Cut_pTHiggs_Flow->SetFillColor(35) ;
           for ( i = 1; i <= pTx; i++)
           {
            Cut_pTHiggs_Flow->GetXaxis()->SetBinLabel(i,cut_pTH[i-1]);
           }
    
    
           const Int_t SDx = 8 ;
           const char *cut_SD[SDx] =   {"SD = [ 50,150]GeV", 
                                        "SD = [ 70,150]GeV", 
                                        "SD = [ 75,150]GeV", 
                                        "SD = [ 80,150]GeV",  
                                        "SD = [ 85,150]GeV",  
                                        "SD = [ 90,150]GeV",  
                                        "SD = [ 95,150]GeV", 
                                        "SD = [100,150]GeV", 
                                       };
    
        
           Cut_SDMass_Flow = new TH1D("Cut_SDMass_Flow", "Cut SDMass Flow", SDx, 0, SDx);
           Cut_SDMass_Flow->SetFillColor(35) ;
           for ( i = 1; i <= SDx; i++)
           {
             Cut_SDMass_Flow->GetXaxis()->SetBinLabel(i,cut_SD[i-1]);
           }
    
    
    
           ST_Sum_Presel = new TH1D("ST_Sum_Presel", "ST Sum Distribution(Preselection)", 100, 0.0, 5000.0 );
           ST_Sum_Presel ->GetYaxis()->SetTitle("Events") ;
    
           ST_Sum_Evesel = new TH1D( "ST_Sum_Evesel", "ST Sum Distribution(Event selection)", 100, 0.0, 5000.0 );
           ST_Sum_Evesel ->GetYaxis()->SetTitle("Events") ;
    
           ST_Sum_LeadObj = new TH1D( "ST_Sum_LeadObj", "ST Sum Distribution(Leading objects)", 100, 0.0, 5000.0 );
           ST_Sum_LeadObj ->GetYaxis()->SetTitle("Events") ;
    
          
    
    
    } 
   ///////////////////======================= Function Defining Kinematic Histogram ===================================================///////////////////                                             
   void  Define_Kinematic_Histo_for_RecoObject()
   {
    //   New defination of histogram
      TString   pT_name  = "Hist" ;
      TString   pT_title = "Distribution" ; 

      int index = 0 ;

   
      ///// for object histograms//////////////////////
      for(Int_t k = 0 ; k <  16; ++k) {

            index = k ;
            ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
            pT_name   =  Histogram_Pt_List[index] ;            
            pT_title  =  Histogram_Pt_List[index]  + " Distribution" ;   
           
            Hist_object_pt.at(index) = new TH1D(pT_name,pT_title,140, 0, 1400.0);
            Hist_object_pt.at(index) ->GetYaxis()->SetTitle("Events");

            ////////HISTROGRAM FOR ETA OF MAJOR OBJECTS //////////////////////////////
            pT_name   =  Histogram_Eta_List[index] ;            
            pT_title  =  Histogram_Eta_List[index]  + " Distribution" ;   

            Hist_object_eta.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
            Hist_object_eta.at(index) ->GetYaxis()->SetTitle("Events");

            ////////HISTROGRAM FOR PHI OF MAJOR OBJECTS //////////////////////////////
            pT_name   =  Histogram_Phi_List[index] ;            
            pT_title  =  Histogram_Phi_List[index]  + " Distribution" ;   

            Hist_object_phi.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);
            Hist_object_phi.at(index) ->GetYaxis()->SetTitle("Events");

      }


      ////FOR LEADING FATJET HISTOGRAMS//////////////
      for (int i = 0; i < 19; ++i)
      {

            if ( i < 16 ) {

                            ////FOR LEADING FATJET HISTOGRAMS//////////////              

                            pT_name   =  Histogram_FatJet_List[i] ;            
                            pT_title  =  Histogram_FatJet_List[i]  + " Distribution" ;   

                            Hist_for_Leading_FatJet.at(i) = new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
                            Hist_for_Leading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");  

                            ////FOR SUB-LEADING FATJET HISTOGRAMS//////////////
                            pT_name   =  Histogram_FatJet2_List[i] ;            
                            pT_title  =  Histogram_FatJet2_List[i]  + " Distribution" ;   

                            Hist_for_Subleading_FatJet.at(i) = new TH1D(pT_name,pT_title, 200, -1.0, 1.0) ;
                            Hist_for_Subleading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");      
                          }
                            
            if ( i >= 16 ) { 

                            ////FOR LEADING FATJET HISTOGRAMS//////////////              

                            pT_name   =  Histogram_FatJet_List[i] ;            
                            pT_title  =  Histogram_FatJet_List[i]  + " Distribution" ;   

                            Hist_for_Leading_FatJet.at(i) = new TH1D(pT_name,pT_title, 100, 0.0,  1000.0);
                            Hist_for_Leading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");     
   
                            ////FOR SUB-LEADING FATJET HISTOGRAMS//////////////
                            pT_name   =  Histogram_FatJet2_List[i] ;            
                            pT_title  =  Histogram_FatJet2_List[i]  + " Distribution" ;   


                            Hist_for_Subleading_FatJet.at(i) = new TH1D(pT_name,pT_title, 100, 0.0,  1000.0);
                            Hist_for_Subleading_FatJet.at(i) ->GetYaxis()->SetTitle("Events");                            
                          }  


      }
      





      // for No. object  histograms
      for(Int_t j = 0; j < 8; j++) 
      {  
            pT_name   =  Histogram_Object_List[j] ;
            pT_title  =  Histogram_Object_List[j]  + " Distribution" ;
            h_object_no.at(j) = new TH1D( pT_name, pT_title, 10, 0, 10);  
            h_object_no.at(j) ->GetYaxis()->SetTitle("Events");
        // cout<<"h_object_no["<<j<<"].name() : "<< h_object_no.at(j)->GetName()<<endl;      
      }



   
   }


   void  Define_Kinematic_Histo_for_HiggsJet()
   {

      TString   pT_name  = "Hist" ;
      TString   pT_title = "Distribution" ; 

      int index = 0 ;

   
      ////FOR HiggsJet HISTOGRAMS//////////////
      for(Int_t k = 0 ; k <  22; ++k) {

            index = k ;
            pT_name   =  Histogram_Higgs_List[index] ;            
            pT_title  =  Histogram_Higgs_List[index]  + " Distribution" ;  

            if ( index < 12 ) {

                            ////FOR Discriminators of HiggsJet HISTOGRAMS//////////////               

                            Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 220, -1.1, 1.1) ;
 
                          } 

            if ( (index > 11 && index < 15 ) || (index == 21 ) ){              
                         
                            ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
             
                         Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 280, 0.0, 1400.0);

                        }


                         /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index == 15 ) Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

                         /////++++ POPULATION HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index == 16 ) Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 8, 0, 8);
            
            if ( index >  16 && index < 21 ) Hist_for_Leading_HiggsJet.at(index) = new TH1D(pT_name,pT_title, 500, 0, 5.0);              


            Hist_for_Leading_HiggsJet.at(index) ->GetYaxis()->SetTitle("Events");  

   
      } // END OF THE LOOP!!!!

   }   // END OF THE FUNCTION !!!!!!!!   

   //////////////////=================Function Defining DeltaR and Delta Pt Histograms==============================///////////////////////////////////

   /////////////------Function For Calling Other Functions To Declare Delta R Histo---------------------------------///////////////////////////////////
   void  Define_DelatR_Histo_for_RecoObject() 
   {

         Define_DelatR_Histo_for_Fatjet_wrt_Jet()      ;
         Define_DelatR_Histo_for_Muon_wrt_Jet()        ;

   }


   ////-----------------------Function to define Histogram  of DeltaR  btw Fatjet and Jet--------------------------/////////////////////////////////
   void Define_DelatR_Histo_for_Fatjet_wrt_Jet() 
   {

        TString dR_name  = "Hist";
        TString dR_title = "Distribution";
        
        // Here i = 0 to 2 for leading fatjet
        // Here i = 3 to 5  for sub leading fatjet
        // Here i = 6 to 8  for 3rd leading fatjet,
        // if want to extend histograms, increase i to 9

        for (Int_t i = 0; i < 6; i++) {      
    
          dR_name    =  Histogram_DeltaR_FatJet_List[i] ;
          dR_title   =  Histogram_DeltaR_FatJet_List[i] + "Distribution" ;
                
          DeltaR_Hist_FatJet_wrt_jet.at(i) = new TH1D(dR_name,dR_title, 500, 0, 5.0);
          DeltaR_Hist_FatJet_wrt_jet.at(i) ->GetYaxis()->SetTitle("Events");
               
        } // End of LOOP !!!!      

   }  // END OF FUNCTION !!!!!!!!!!!!!!!

   ////-----------------------Function to define Histogram  of DeltaR  btw Muon and Jet--------------------------/////////////////////////////////
   void Define_DelatR_Histo_for_Muon_wrt_Jet() 
   {

        TString dR_name  = "Hist";
        TString dR_title = "Distribution";
        
        // Here i = 0 to 2 for normal jet
        // Here i = 3 to 5  for clean jet
        // Here i = 6 to 8  for b jet,
        // if want to extend histograms, increase i to 9 depending on your choice

        for (Int_t i = 0; i < 6; i++) {      
    
          dR_name    =  Histogram_DeltaR_Muon_List[i] ;
          dR_title   =  Histogram_DeltaR_Muon_List[i] + "Distribution" ;
                
          DeltaR_Hist_Muon_wrt_jet.at(i) = new TH1D(dR_name,dR_title, 500, 0, 5.0);
          DeltaR_Hist_Muon_wrt_jet.at(i) ->GetYaxis()->SetTitle("Events");
               
        } // End of LOOP !!!!      

   }  // END OF FUNCTION !!!!!!!!!!!!!!!



   ///-------==================-========= Function Definitions for Hitograms of JetLepton Cleaning ---------========================///////////////////

   void  Define_Histograms_For_LeptonJet_Cleaning_Effect()
   {
      Define_Kinematic_Histo_for_LepCleanJet() ;
      Define_Kinematic_Histo_for_LepCleanFatJet();
      Define_Histo_of_Pt_wrt_Delta_For_CleanJet() ;
   }                                                            

   //-----cLEAN jET hISTOGRAMS dEFINED HERE
   void  Define_Kinematic_Histo_for_LepCleanJet()
   {

        TString   pT_name  = "Hist" ;
        TString   pT_title = "Distribution" ; 

        int index = 0 ;

   
        ////FOR CleanJet HISTOGRAMS//////////////
        for(Int_t k = 0 ; k <  20; ++k) {

              index = k ;
              pT_name   =  Histogram_LepCleanJet_List[index] ;            
              pT_title  =  Histogram_LepCleanJet_List[index]  + " Distribution" ;  


              ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
              if ( index < 4 ) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 280, 0.0, 1400.0);


              /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
              if ( index > 3 && index < 8 ) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

              /////++++ Phi HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
              if ( index > 7 && index < 12 ) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

              /////++++ Delta R HISTOGRAM OF HIGGSJET ++++++++////////////////////////////         
              if ( index > 11 && index < 16) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 500, 0, 5.0);              

              /////++++ Delta R HISTOGRAM OF HIGGSJET ++++++++////////////////////////////         
              if ( index > 15) Hist_for_LeptonCleaned_Jet.at(index) = new TH1D(pT_name,pT_title, 100, 0, 500.0);     
              Hist_for_LeptonCleaned_Jet.at(index) ->GetYaxis()->SetTitle("Events");  

   
        } // END OF THE LOOP!!!!

              dPt_dR_mu_cleanjet1   = new TH2F("dPt_dR_Hist_mu_cleanjet1", "dPt & dR for mu n cleanjet1 Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);
              dPt_dR_mu_cleanjet2   = new TH2F("dPt_dR_Hist_mu_cleanjet2", "dPt & dR for mu n cleanjet2 Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);

              // dPt_dR_muqjet   = new TH2F("dPt_dR_muqjet", "dPt & dR for mu,qjet Distribution", 100, -1.0, 1.0, 500, 0.0, 1000.0);  // for tau42 study
              dPt_dR_mu_jet1   = new TH2F("dPt_dR_Hist_mu_jet1", "dPt & dR for mu n jet1 Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);
              dPt_dR_mu_jet2   = new TH2F("dPt_dR_Hist_mu_jet2", "dPt & dR for mu n jet2 Distribution", 100, 0.0, 5.0, 200, 0.0, 1000.0);


   }   // END OF THE FUNCTION !!!!!!!!   


   //-----cLEAN fATjET hISTOGRAMS dEFINED HERE
   void  Define_Kinematic_Histo_for_LepCleanFatJet()
   {

      TString   pT_name  = "Hist" ;
      TString   pT_title = "Distribution" ; 

      int index = 0 ;

   
      ////FOR CleanJet HISTOGRAMS//////////////
      for(Int_t k = 0 ; k <  16; ++k) {

            index = k ;
            pT_name   =  Histogram_LepCleanFatJet_List[index] ;            
            pT_title  =  Histogram_LepCleanFatJet_List[index]  + " Distribution" ;  


            ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
            if ( index < 4 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 280, 0.0, 1400.0);


            /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index > 3 && index < 8 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

            /////++++ Phi HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
            if ( index > 7 && index < 12 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 200, -5.0, 5.0);

            /////++++ Delta R HISTOGRAM OF HIGGSJET ++++++++////////////////////////////         
            if ( index > 11 ) Hist_for_LeptonCleaned_FatJet.at(index) = new TH1D(pT_name,pT_title, 500, 0, 5.0);              


            Hist_for_LeptonCleaned_FatJet.at(index) ->GetYaxis()->SetTitle("Events");  

   
      } // END OF THE LOOP!!!!

   }   // END OF THE FUNCTION !!!!!!!!      


void  Define_Histo_of_Pt_wrt_Delta_For_CleanJet() 
{
        TString   pT_name  = "Hist" ;
        TString   pT_title = "Distribution" ; 

        int index = 0 ;

   
        ////FOR CleanJet 2D HISTOGRAMS//////////////
        for(Int_t k = 0 ; k <  12; ++k) {

              index = k ;
              pT_name   =  Histogram_Delta_wrt_Pt_LepCleanJet_List[index] ;            
              pT_title  =  Histogram_Delta_wrt_Pt_LepCleanJet_List[index]  + " Distribution" ;  


              ////////HISTROGRAM FOR PT OF MAJOR OBJECTS //////////////////////////////
              if ( index < 8 ) {
                    Hist_DeltaR_wrt_Pt_LepCleanJet.at(index)  = new TH2D(pT_name, pT_title, 200, 0.0, 1000.0 , 100, 0.0, 5.0);
                    Hist_DeltaR_wrt_Pt_LepCleanJet.at(index) ->GetXaxis()->SetTitle("P_{T}(leading jet)(GeV)");  
              }      

              /////++++ ETA HISTOGRAM OF HIGGSJET ++++++++////////////////////////////
              if ( index > 7 ) {
                    Hist_DeltaPt_wrt_Pt_LepCleanJet.at(index - 8)  = new TH2D(pT_name, pT_title, 200, 0.0, 1000.0, 200, 0.0, 1000.0);
                    Hist_DeltaPt_wrt_Pt_LepCleanJet.at(index - 8) ->GetXaxis()->SetTitle("P_{T}(leading jet)(GeV)");  
              }      
   
        } // END OF THE LOOP!!!!

             


}   // END OF THE FUNCTION !!!!!!!!                                                         


/////////////////=========THIS SECTION FOR DEFINING NEW SETS OF FILLING HOSTOGRAMS FUNCTIONS=============///////////////////////////////////////////////


// For Leptons at preselection level, 
//you could also define the channel, 
//if you want to fill according to it
////////////////////////////////////////////////////
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

////////////------  Filling Leptons at Preselction Level------------------- ///////////////////////////////////////////////////////
void   Fill_Lepton_Hist_Preselction_LvL( TString lepton, int lep_index , int lep_count)
{
  int Prog_ID = 0 ;

  //// Filling MET for the event
  if (lepton.Contains("YesMET"))
  {
    Prog_ID = 0 ;
    Hist_object_pt.at (Prog_ID)  ->Fill(MET_pt, factor);
    Hist_object_phi.at (Prog_ID)  ->Fill(MET_phi, factor);
    Hist_object_pt.at (Prog_ID + 1)  ->Fill(MET_sumEt, factor);  // SUM MET filing

  }

  //// Filling Electron for the event
  if ( lepton == "Electron")
  {
    Prog_ID = 2 ;
    Hist_object_pt.at  (Prog_ID + lep_count)  ->Fill(Electron_pt[lep_index], factor); 
    Hist_object_eta.at (Prog_ID + lep_count)  ->Fill(Electron_eta[lep_index], factor);
    Hist_object_phi.at (Prog_ID + lep_count)  ->Fill(Electron_phi[lep_index], factor);  
  }


  //// Filling Muon for the event
  if ( lepton == "Muon")
  {
    Prog_ID = 4 ;
    Hist_object_pt.at  (Prog_ID + lep_count)  ->Fill(Muon_pt[lep_index], factor); 
    Hist_object_eta.at (Prog_ID + lep_count)  ->Fill(Muon_eta[lep_index], factor);
    Hist_object_phi.at (Prog_ID + lep_count)  ->Fill(Muon_phi[lep_index], factor);  
  }


} // END of the function !!!!!!!!!!!


////////////------  Filling Jets at Preselction Level------------------- ///////////////////////////////////////////////////////

void   Fill_Jet_Hist_Preselction_LvL( TString jet, int jet_index , int jet_count)
{
  int Prog_ID = 0 ;

  //// Filling ALLJET for the event
  if (jet.Contains("ALLJET"))
  {
    Prog_ID = 6 ;
    if ( jet.Contains("Cleaned")){
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);
    }

    else{
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi[jet_index], factor);
    }

  }

  //// Filling Forward jet for the event
  if (jet == "ForwJet")
  {
    Prog_ID = 10 ;
    Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
    Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
    Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);

  }


  //// Filling Clean Jet for the event
  if (jet.Contains("CleanJet"))
  {
    Prog_ID = 12 ;

    if ( jet.Contains("Lepton")){
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);
    }

    else{
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi[jet_index], factor);
    }


  }

  //// Filling bjet for the event
  if (jet.Contains("bJet"))
  {
    Prog_ID = 14 ;

    if ( jet.Contains("LeptonCleaned")){
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt_clean[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta_clean[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi_clean[jet_index], factor);
    }

    else{
        Hist_object_pt.at   (Prog_ID + jet_count)     ->Fill(Jet_pt[jet_index], factor); 
        Hist_object_eta.at  (Prog_ID + jet_count)     ->Fill(Jet_eta[jet_index], factor);
        Hist_object_phi.at  (Prog_ID + jet_count)     ->Fill(Jet_phi[jet_index], factor);
    }

  }


} // END of the function !!!!!!!!!!!


////////////------  Filling FATJets at Preselction Level------------------- ///////////////////////////////////////////////////////

void   Fill_FatJet_Hist_Preselction_LvL( TString fatjet, int fatjet_index , int fatjet_count)
{
  int Prog_ID = 0 ;

  double  msoftdrop_corr = FatJet_msoftdrop_raw[fatjet_index] * FatJet_msoftdrop_corr_PUPPI[fatjet_index] ;

  //// Filling ALLJET for the event
  if (fatjet.Contains("LeadingJet"))
  {
    Prog_ID = 8 ;


    if( fatjet.Contains("Cleaned")){
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt_clean[ fatjet_index], factor); 
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta_clean[fatjet_index], factor);
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi_clean[fatjet_index], factor);
    }

    else{
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt[ fatjet_index], factor);  
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta[fatjet_index], factor); 
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi[fatjet_index], factor); 
    }

    Hist_for_Leading_FatJet.at(0 )   ->Fill(FatJet_deepTagMD_H4qvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(1 )   ->Fill(FatJet_deepTagMD_TvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(2 )   ->Fill(FatJet_deepTagMD_WvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(3 )   ->Fill(FatJet_deepTag_H[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(4 )   ->Fill(FatJet_deepTag_TvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(5 )   ->Fill(FatJet_deepTag_WvsQCD[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(6 )   ->Fill(FatJet_tau1[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(7 )   ->Fill(FatJet_tau2[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(8 )   ->Fill(FatJet_tau3[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(9 )   ->Fill(FatJet_tau4[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(16)   ->Fill(FatJet_mass_clean[fatjet_index], factor); 
    Hist_for_Leading_FatJet.at(17)   ->Fill(FatJet_msoftdrop[fatjet_index], factor); 

    // if ( (!( msoftdrop_corr < 70.0 || msoftdrop_corr > 150.0)) ) 
      Hist_for_Leading_FatJet.at(18)   ->Fill(msoftdrop_corr, factor); 
      Hist_for_Leading_FatJet.at(10)   ->Fill( (FatJet_tau2[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(11)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(12)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(13)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(14)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
      Hist_for_Leading_FatJet.at(15)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau3[fatjet_index]), factor); 
    // }
  }

  //// Filling Forward jet for the event
  if (fatjet.Contains("SubleadingJet"))
  {
    Prog_ID = 9 ;

    if( fatjet.Contains("Cleaned")){
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt_clean[ fatjet_index], factor); 
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta_clean[fatjet_index], factor);
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi_clean[fatjet_index], factor);
    }

    else{
        Hist_object_pt.at  (Prog_ID  )     ->Fill(FatJet_pt[ fatjet_index], factor);  
        Hist_object_eta.at (Prog_ID  )     ->Fill(FatJet_eta[fatjet_index], factor); 
        Hist_object_phi.at (Prog_ID  )     ->Fill(FatJet_phi[fatjet_index], factor); 
    }

    Hist_for_Subleading_FatJet.at(0 )   ->Fill(FatJet_deepTagMD_H4qvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(1 )   ->Fill(FatJet_deepTagMD_TvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(2 )   ->Fill(FatJet_deepTagMD_WvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(3 )   ->Fill(FatJet_deepTag_H[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(4 )   ->Fill(FatJet_deepTag_TvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(5 )   ->Fill(FatJet_deepTag_WvsQCD[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(6 )   ->Fill(FatJet_tau1[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(7 )   ->Fill(FatJet_tau2[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(8 )   ->Fill(FatJet_tau3[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(9 )   ->Fill(FatJet_tau4[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(16)   ->Fill(FatJet_mass_clean[fatjet_index], factor); 
    Hist_for_Subleading_FatJet.at(17)   ->Fill(FatJet_msoftdrop[fatjet_index], factor); 

    // if ( (!( msoftdrop_corr < 70.0 || msoftdrop_corr > 150.0)) ) 
    Hist_for_Subleading_FatJet.at(18)   ->Fill(msoftdrop_corr, factor); 
    Hist_for_Subleading_FatJet.at(10)   ->Fill( (FatJet_tau2[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(11)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(12)   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(13)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(14)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]), factor); 
    Hist_for_Subleading_FatJet.at(15)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau3[fatjet_index]), factor); 
    // }
  }


} // END of the function !!!!!!!!!!!


////////////------  Filling HiggsJet ------------------- ///////////////////////////////////////////////////////

void   Fill_HiggsJet_Hist_Preselction_LvL( TString fatjet )
{
  int Prog_ID = 0 ;
  int fatjet_index = Higgsjets[0];

  double  msoftdrop_corr = FatJet_msoftdrop_raw[fatjet_index] * FatJet_msoftdrop_corr_PUPPI[fatjet_index] ;

  //// Filling ALLJET for the event
  if (fatjet.Contains("FillHiggsJet"))
  {

    Hist_for_Leading_HiggsJet.at(0 )   ->Fill(FatJet_deepTagMD_H4qvsQCD[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(1 )   ->Fill(FatJet_deepTagMD_TvsQCD   [fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(2 )   ->Fill(FatJet_deepTagMD_WvsQCD[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(3 )   ->Fill(FatJet_deepTag_H[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(4 )   ->Fill(FatJet_deepTag_TvsQCD[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(5 )   ->Fill(FatJet_deepTag_WvsQCD[fatjet_index], factor ) ;

    Hist_for_Leading_HiggsJet.at(6 )   ->Fill( (FatJet_tau2[fatjet_index] / FatJet_tau1[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(7 )   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau1[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(8 )   ->Fill( (FatJet_tau3[fatjet_index] / FatJet_tau2[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(9 )   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau1[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(10)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau3[fatjet_index]), factor ) ;

    Hist_for_Leading_HiggsJet.at(11)   ->Fill( (FatJet_tau4[fatjet_index] / FatJet_tau2[fatjet_index]), factor ) ;
    Hist_for_Leading_HiggsJet.at(12)   ->Fill(FatJet_msoftdrop[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(13)   ->Fill(FatJet_mass_clean[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(14)   ->Fill(FatJet_pt_clean[ fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(15)   ->Fill(FatJet_eta_clean[fatjet_index], factor ) ;
    Hist_for_Leading_HiggsJet.at(21)   ->Fill(msoftdrop_corr, factor ) ;
    
  }

  Fill_DeltaR_Hist_of_Higgs_wrt_Top_Prod( fatjet_index );

} // END of the function !!!!!!!!!!!


void  Fill_DeltaR_Hist_of_Higgs_wrt_Top_Prod( int Higgs_index )
{
      // Histogram index 17  for  "Hist_DeltaR_HiggsJet_wrt_lep (muon or ele)
      // Histogram index 18  for  "Hist_DeltaR_HiggsJet_wrt_jet1
      // Histogram index 19  for  "Hist_DeltaR_HiggsJet_wrt_jet2
      // Histogram index 20  for  "Hist_DeltaR_HiggsJet_wrt_jet3
      
      float Higgs_eta = FatJet_eta_clean[Higgs_index] ;
      float Higgs_phi = FatJet_phi_clean[Higgs_index] ;

      float top_prod_eta = 0.0 ; 
      float top_prod_phi = 0.0 ; 
      int   top_prod     = -1 ;

      int   hist_index   = -1 ;  // index for clean jet

      // DELTAr wrt Muon
      if ( n_Mu.size() > 0){

          top_prod       = n_Mu[0];
          top_prod_eta   = Muon_eta[top_prod] ;
          top_prod_phi   = Muon_phi[top_prod] ;

          dR_Calculator(Higgs_eta, Higgs_phi, top_prod_eta, top_prod_phi) ;
    
          Hist_for_Leading_HiggsJet.at(17)  ->Fill(dR, factor ) ;

      } // Muon Loop Ended !!!!!!!
      
      // Delta r wrt to clean jets

      int Ssize   = ( n_cleanjet.size() >= 3 ) ?  3 : n_cleanjet.size() ;

      for (int kji = 0; kji < Ssize; ++kji)
      {
        top_prod  = n_cleanjet[kji] ;
        top_prod_eta     = Jet_eta_clean[top_prod] ;
        top_prod_phi     = Jet_phi_clean[top_prod] ;       

        hist_index  = kji + 18 ;  // index for clean jet

        dR_Calculator(Higgs_eta, Higgs_phi, top_prod_eta, top_prod_phi) ;
    
        Hist_for_Leading_HiggsJet.at(hist_index)  ->Fill(dR, factor ) ;

      } // Clean Jet Loop Ended !!!!!!!


} // END of the function !!!!!!!!!!!


/////========== Fiilling the objects after selection criterias are clear =========== ///////////
void Fill_Object_Hist_After_Preselction_LvL(  TString Filling) 
 {
      int index  = -1 ;
      int count  =  -1 ;
      int JetSize = 0;
 
      Fill_Lepton_Hist_Preselction_LvL( Filling +"MET" , 0 , 0) ; // both entries 0 for MET 

      index = n_Mu[0];
      count =  0 ;

      Fill_Lepton_Hist_Preselction_LvL( "Muon" , index , count) ;        // Filling Muon

      // Fill_Lepton_Hist_Preselction_LvL( "Electron" , i , ele_count) ;  // Filling electron

      // Fill Forward jet
      JetSize   = ( n_forwjet.size() >= 2 ) ?  2 : n_forwjet.size() ;
      count     = 0 ;

      for (count = 0; count < JetSize; ++count )
        {
             index = n_forwjet[count] ;
             Fill_Jet_Hist_Preselction_LvL( "ForwJet",  index , count) ;                  
        }

      // Fill Clean jet
      JetSize   = ( n_cleanjet.size() >= 2 ) ?  2 : n_cleanjet.size() ;
      count     = 0 ;

      for (count = 0; count < JetSize; ++count )
        {
             index = n_cleanjet[count] ;            
             Fill_Jet_Hist_Preselction_LvL( "LeptonCleanJet",  index , count) ; 

        } 

      // Fill Fat jet
      JetSize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
      count     = 0 ;

      for (count = 0; count < JetSize; ++count )
        {
             index = n_AK8Jet[count] ;            
             Fill_Jet_Hist_Preselction_LvL( "LeptonCleanJet",  index , count) ; 
             if ( count == 0) Fill_FatJet_Hist_Preselction_LvL( "CleanedLeadingJet" ,    index , count) ;  
             if ( count == 1) Fill_FatJet_Hist_Preselction_LvL( "CleanedSubleadingJet",  index , count) ;               

        } 


      // Delta R distributions 
      Check_deltaR_For_Muon_wrt_LepCleanJets( Filling ) ;  
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////======================== FUNCTIONS FOR SELECTION OF OBJECTS===========================/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////============ Loop over electron for seletion===================//////////////////////////////////////////
void  Check_Electrons_For_Event_N_Fill(TString Filling)
{

    int   ele_count = -1 ;  
    float eleEta = 0.0 ; 

    //============ Loop over electron for seletion===================
      for (int i = 0; i < nElectron; ++i)
      {
    
        if (Electron_cutBased[i] < 2.0 )          continue ; // for loose, but move to medium
        eleEta = fabs (Electron_eta[i]) ;
        // cout << "\n before Eta = " << Eta;
        if ( eleEta > 1.44 && (eleEta < 1.56 || eleEta > 2.5) )    continue ;          
        if (Electron_pt[i] < 40.0 )             continue ;  

        n_ele.push_back(i);
        
        ele_count ++; 

        if ( ele_count >= 2) continue;

        if( Filling.Contains("Yes")) Fill_Lepton_Hist_Preselction_LvL( "Electron" , i , ele_count) ;  // Yes for Filling

      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!


////////////////////============ Loop over MUON for seletion===================//////////////////////////////////////////

void  Check_Muons_For_Event_N_Fill( TString Filling)
{

      int   mu_count = -1 ;
      int   Muon_ID  = -1; 

      for (int ki = 0; ki < nMuon; ++ki)
      {

        Muon_ID = Muon_highPtId[ki] ;
 
        // cout << "\n\n Before Selection, muon have pT = " << Muon_pt[ki] << "  n eta = " << Muon_eta[ki] << "  n HighpTID = " << Muon_ID ;
        // printf("Muon_highPtId = %d", Muon_highPtId[ki] )  ;

        if ( fabs(Muon_eta[ki]) > 2.1 )       continue ;
        if ( Muon_ID < 2  )                   continue ;
        if ( Muon_pt[ki] < 40.0 )             continue ;
    
        n_Mu.push_back(ki);

        mu_count ++; 

        if ( mu_count >= 2) continue;

        if( Filling.Contains("Yes"))  Fill_Lepton_Hist_Preselction_LvL( "Muon" , ki , mu_count) ;        


      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!      


////////////////////============ Loop over FatJet for seletion===================//////////////////////////////////////////

void  Check_FatJet_For_Event_N_Fill( TString Filling)
{
      int fatjet_count   = -1 ;

      for (int fi = 0; fi < nFatJet; ++fi)
      {
         if ( FatJet_corr_JEC[fi] < 0.0)  continue ;

         if ( FatJet_pt[fi] < 200.0 )        continue ;
         if ( fabs(FatJet_eta[fi]) > 2.4 )     continue ;
         if ( FatJet_jetId[fi] < 2 )         continue ;   // for 2016, < 1, 2017/18 < 2

         n_AK8Jet.push_back(fi);
         fatjet_count ++; 

         if ( Filling.Contains("Yes")) {

                if ( fatjet_count == 0) Fill_FatJet_Hist_Preselction_LvL( "LeadingJet" , fi , fatjet_count) ;
                if ( fatjet_count == 1) Fill_FatJet_Hist_Preselction_LvL( "SubleadingJet" , fi , fatjet_count) ;       

         }

      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!   

void  Check_CleanFatJet_For_Event_N_Fill( TString Sorting)
{
      int fatjet_count   = -1 ;

      for (int fi = 0; fi < nFatJet; ++fi)
      {


        if ( FatJet_corr_JEC[fi] < 0.0)  continue ;

        if ( FatJet_pt_clean[fi] < 200.0 )        continue ;
        if ( fabs(FatJet_eta_clean[fi]) > 2.4 )     continue ;
        if ( FatJet_jetId[fi] < 2 )         continue ;   // for 2016, < 1, 2017/18 < 2

        // if ( FatJet_pt[fi] < 200.0 )        continue ;
        // if ( fabs(FatJet_eta[fi]) > 2.4 )     continue ;
        // if ( FatJet_jetId[fi] < 2 )         continue ;   // for 2016, < 1, 2017/18 < 2

        n_AK8Jet.push_back(fi);

        fatjet_count ++; 

        // no fILLING HERE BUT AFTER SORTING THE  FATJETS, IF YOU WANT UNCOMMENT IT AND PASS "NO" TO SORTING ()
        // if ( fatjet_count >= 2) continue;
        // if ( fatjet_count == 0) Fill_FatJet_Hist_Preselction_LvL( "CleanedLeading_Jet" , fi , fatjet_count) ;
        // if ( fatjet_count == 1) Fill_FatJet_Hist_Preselction_LvL( "CleanedSubleading_Jet" , fi , fatjet_count) ;       
        // h_object_pt.at (count + id)   ->Fill(FatJet_pt[fi]);       // AK8jet
       //  h_object_eta.at(count + id)   ->Fill(FatJet_eta[fi]);
       //  h_object_phi.at(count + id)   ->Fill(FatJet_phi[fi]);


      }

      if ( Sorting.Contains("Sorting")){


        if ( n_AK8Jet.size() > 1 ) {

            fatjet_copy = n_AK8Jet ;
            fatjet_sort = n_AK8Jet ;
            FatJet_sorting_pT_based_After_Cleaning(Sorting);      // PASS "NO" FOR NO FILLING     

        }

        else             fatjet_sort = n_AK8Jet ; 
      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!! 


////////////////////============ Loop over Jet for seletion===================//////////////////////////////////////////

void  Check_Jet_For_Event_N_Fill( TString Filling )
{
      
      int jet_count = -1 ;      
      int jets      = -1 ;

      for (int ji = 0; ji < nJet; ++ji)
      {
        if ( Jet_corr_JEC[ji] < 0.0  )    continue ;  

        if ( Jet_pt[ji] < 30.0 )        continue ;
        if ( Jet_jetId[ji] < 1 )        continue ;
        
        if ( fabs(Jet_eta[ji]) > 2.4 )  n_forwjet.push_back(ji) ;
        else n_jet.push_back(ji);
        // else Check_Jet_Matched_Lepton_Index_N_Pass( ji ) ;

      }  


      int Qsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;
      
      if ( Filling.Contains("Yes") ) {
        
         Qsize   = ( n_jet.size() >= 2 ) ?  2 : n_jet.size() ;
         for (int jij = 0; jij < Qsize; ++jij )
             {
                  jets = n_jet[jij] ;
                  Fill_Jet_Hist_Preselction_LvL( "ALLJET",  jets , jij) ;                  
             } // end of loop

         Qsize   = ( n_forwjet.size() >= 2 ) ?  2 : n_forwjet.size() ;
         for (int kij = 0; kij < Qsize; ++kij )
             {
                  jets = n_forwjet[kij] ;
                  Fill_Jet_Hist_Preselction_LvL( "ForwJet",  jets , kij) ;                  
             }               
      }

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!   

void Check_Jet_Matched_Lepton_Index_N_Pass( int jet_index)
{
     

         if ( Jet_electronIdx1[jet_index] == -1 &&  Jet_electronIdx2[jet_index] == -1 
              && Jet_muonIdx1[jet_index] == -1 && Jet_muonIdx2[jet_index] == -1 )  n_jet.push_back(jet_index) ;

}

/////// sELECTION OF cLEAN jET AND fILL aLSO  uSING fILLING STRING
void  Check_CLeanedJet_For_Event_N_Fill( TString Filling )
{
      
      int jet_count = -1 ;      
      int jets      = -1 ;

      for (int ji = 0; ji < nJet; ++ji)
      {
        if ( Jet_corr_JEC[ji] < 0.0  )    continue ;  

        if ( Jet_pt_clean[ji] < 30.0 )    continue ;
        if ( Jet_jetId[ji] < 2 )          continue ;  // for 2016, < 1, 2017/18 < 2
        
        if ( fabs(Jet_eta_clean[ji]) > 2.4 )  n_forwjet.push_back(ji) ;
        else n_jet.push_back(ji);
        // else Check_Jet_Matched_Lepton_Index_N_Pass( ji ) ;

      }  


      int Qsize   = ( n_forwjet.size() >= 2 ) ?  2 : n_forwjet.size() ;
      
      if ( Filling == "Yes") {        
         
         for (int kij = 0; kij < Qsize; ++kij )
             {
                  jets = n_forwjet[kij] ;
                  Fill_Jet_Hist_Preselction_LvL( "ForwJet",  jets , kij) ;                  
             }               
      } // end of filling       

}  // END OF THE SELECTION FUNCTION !!!!!!!!!!!!!!!!!  


///////////////////////////////////////////////////////////////////////////////////////////
///////------====== GENERAL FUNCTIONS ARE DEFINED BELOW  -----------===================
//////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////======================= FUNCTIONS FOR DELTA R N DELTA PT CALCULATION =============================//////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//------------ for  General Functions of dR & dPt ---------------------------

  float dPt_Calculator(const TVector3 & lep , const TVector3 & jet ) {
    // type for jet type, type = 0 is AK4jet, type = 1 is puppijet, type = 2 is 
    float  vec_mag = 0.0 ;
    TVector3 vec_Xprod ; 
  
    vec_Xprod = lep.Cross(jet);
    vec_mag   = jet.Mag();
  
    float dPt =  (vec_Xprod.Mag() ) / vec_mag ;
  
    // cout << "\n dPt calculated = " << dPt ;
    return dPt ;

  }  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   


  float dR_Calculator( float eta1, float phi1, float eta2, float phi2)  {
  
     const float PI    =  2.0*acos(0.0);
     const float TWOPI =  2.0*PI;
     float PHI         =  fabs( phi1 - phi2 ) ;
     dPhi              = (PHI<=PI)? PHI : TWOPI-PHI;
     dEta              =  fabs( eta1 - eta2 );       
     dR                =  Sqrt(dPhi*dPhi + dEta*dEta) ;
  
     return dR ;
  
  }  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   

  float delta_phi(float phi1,float phi2) {
     const float PI=2.0*acos(0.0);
     const float TWOPI=2.0*PI;
     float PHI=fabs( phi1 - phi2 ) ;
     return (PHI<=PI)? PHI : TWOPI-PHI;
  
  }  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   

//------------ for  General Functions of dR & dPt ---------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//CLEANING OF JET FROM FATJETS =====================================
//------ First Delta R   (jet, fatjet) check
//---- Then Cleaning is done ----------------  
void Check_deltaR_N_Cleaning_Jet_from_FatJet( TString Check_OR_Clean)
{

  int   hist_index = -1 ; // Use for indexing histogram in later loop
  // Here index = 0 to 2 for leading fatjet
  // Here index = 3 to 5  for sub leading fatjet
  // Here index = 6 to 8  for 3rd leading fatjet, 

  int   fatjet = -1 ;
  int   slimjet    = -1 ;
  float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ; 

  int Fsize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
  int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;

  if ( Check_OR_Clean.Contains("CHECK")){

    for (int fi = 0; fi < Fsize; ++fi)
    {
      fatjet = n_AK8Jet[fi] ;
      eta1   = FatJet_eta[fatjet] ;
      phi1   = FatJet_phi[fatjet] ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        // slimjet  = n_jet[ji] ;
        slimjet  = n_cleanjet[ji] ;
        
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
 
        hist_index = 3*fi + ji ;
        // cout << "\n index = " << hist_index;

        DeltaR_Hist_FatJet_wrt_jet.at(hist_index)  ->Fill(dR , factor );
      }

    }

  }
    
    ////////======== HERE WE CHECKED AK4JET OVERLAPPING WITH LEADING AK8JET AND DISCARD THOSE AK4JET WHICH ARE IN Dr < 1.2 RANGE =======//////////////
  if ( Check_OR_Clean.Contains("CLEAN")){

    Ssize   =  n_jet.size() ;
    fatjet  = n_AK8Jet[0] ;
    eta1   = FatJet_eta[fatjet] ;
    phi1   = FatJet_phi[fatjet] ;
    hist_index  = -1 ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
        
        if ( dR > 1.2){
             hist_index ++ ;
             n_cleanjet.push_back(slimjet) ;
             if( hist_index < 2) Fill_Jet_Hist_Preselction_LvL( "LeptonCleanJet",  slimjet , hist_index) ; // Filling Clean Jet at this level============                 
        }     
      } /// END OF JET LOOP !!!!!!!
  }  // END OF CLEANING !!!!!!!!
  

}  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   





/////////////////--------Check DeltaR Distribution Between Muon & Jet---------------////////////////////////////////////////////
void Check_deltaR_For_Muon_wrt_Jet( TString Check)
{

      int   hist_index = -1 ; // Use for indexing histogram in later loop
      // Here index = 0 to 2  for normal jet
      // Here index = 3 to 5  for clean jet
      // Here index = 6 to 8  for b jet,


      int lead_muon = n_Mu[0];
      int slimjet    = -1 ;
      float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ;      

      eta1   = Muon_eta[lead_muon] ;
      phi1   = Muon_phi[lead_muon] ;

      int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        hist_index  = ji ;  // index for normal jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR) ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Dirty Jets") ;

      }  

      Ssize   = ( n_cleanjet.size() >= 3 ) ?  3 : n_cleanjet.size() ;

      for (int kji = 0; kji < Ssize; ++kji)
      {
        slimjet  = n_jet[kji] ;
        eta2     = Jet_eta[slimjet] ;
        phi2     = Jet_phi[slimjet] ;       

        hist_index  = kji + 3 ;  // index for clean jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        // cout <<"\n For leading Muon = " << lead_muon <<"     the DeltaR = " << dR ;

        DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR) ;
        // Check_deltaR_For_Jet_wrt_MatchedMuon( slimjet, eta2, phi2 ) ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Clean Jets") ;        

      }

}




void Check_deltaR_For_Jet_wrt_MatchedMuon( int jet_index, float jet_eta, float jet_phi)
{
     int Jet_MatchedMuon = Jet_muonIdx1[jet_index] ;

     float muon_eta  = Muon_eta[Jet_MatchedMuon] ; 
     float muon_phi  = Muon_phi[Jet_MatchedMuon] ;

     dR_Calculator(jet_eta, jet_phi, muon_eta, muon_phi) ;

     cout <<"\n For Jetmatched Muon = " << Jet_MatchedMuon <<"     the DeltaR = " << dR <<endl;


}



void Check_Jet_Matched_Lepton_Index( int jet_index, TString Jet_Type)
{
     if( Jet_Type == "Dirty Jets"){

         cout <<" \n //////   ========== for Dirty Jets [ " << jet_index << " ] matched leptons are ===========    ////////////" <<endl;
         cout << "   ---------------------Lead Electron  [ " << Jet_electronIdx1[jet_index] << " ]  and Sublead Electron  [ "  << Jet_electronIdx2[jet_index] << " ] ------";
         cout << "\n   ---------------------Lead Muon      [ " << Jet_muonIdx1[jet_index] << " ]  and Sublead Muon  [ "  << Jet_muonIdx2[jet_index] << " ] ------";


     }

     // int Jet_MatchedMuon = Jet_muonIdx1[jet_index] ;

     if( Jet_Type == "Clean Jets"){

         cout <<" \n //////////========== for Clean Jets [ " << jet_index << " ] matched leptons are ==============////////////" <<endl;
         cout << "   ---------------------Lead Electron  [ " << Jet_electronIdx1[jet_index] << " ]  and Sublead Electron  [ "  << Jet_electronIdx2[jet_index] << " ] ------";
         cout << "\n   ---------------------Lead Muon      [ " << Jet_muonIdx1[jet_index] << " ]  and Sublead Muon  [ "  << Jet_muonIdx2[jet_index] << " ] ------";


     }


}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////================= DEFINITION OF JET TAGGING FUNCTIONS====================///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////========== For HiggsJet Selections Using PUPPI Variables===================================

  void  HiggsJet_Selection_Using_PUPPI_Variables(int var, float ST_cut) 
  {
     
 
     int index = -1 ;
     
   // if you want to check only leading fatjet  
     // int Wsize  = ( n_AK8Jet.size() >= 2) ? 2 :  n_AK8Jet.size() ;  

   // if you want to check whole fatjet collection
     // n_AK8Jet   = fatjet_sort ;
     int Wsize  =  n_AK8Jet.size()  ;

     const  Int_t cut = 7 ;
     double Tau42_Cut_loc[cut] = { 0.0, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75} ;
     double tau              =  0.0 ;
     double msoftdrop_corr   =  0.0 ;

     // Loop over fatjet collection
     for (int g = 0 ; g < Wsize ; g ++ ){
  
        index = n_AK8Jet[g] ;
  
        // These selections are from last VHF Talk on 17 Feb 2020
        // link: https://indico.cern.ch/event/889576/contributions/3752894/attachments/1988684/3315032/Tprime_Update_VHF_MEETING_17Feb2020.pdf 

        msoftdrop_corr = FatJet_msoftdrop_raw[index] * FatJet_msoftdrop_corr_PUPPI[index] ;
        // cout <<" \n Delta PUPPI mass = "  << tau ;   //!

        
        tau               =  (FatJet_tau4[index]/FatJet_tau2[index]) ;
        // if( tau > Tau42_Cut_loc[var - 1]  ) continue ;
        if( tau > 0.75  ) continue ;        
        if( msoftdrop_corr > 150.00 || msoftdrop_corr < ST_cut ) continue ;
        if( FatJet_pt_clean[index]  < 400.0 ) continue;     
        Higgsjets.push_back(index);
    
     } /// END of Loop !!!!

  }  // END of FUNCTION !!!!      

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ========================================= Lepton Jet Cleaning effects ---------------- =========================
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --------- ========= Delta R of Muon wrt Lep Clean jets ---------=======

void Check_deltaR_For_Muon_wrt_LepCleanJets( TString Check)
{

      int   hist_index = -1 ; // Use for indexing histogram in later loop
      // Here index = 0 to 2  for slim jet
      // Here index = 3 to 5  for fatjet
      // Here index = 6 to 8  for b jet,


      int lead_muon = n_Mu[0];
      int slimjet    = -1 ;
      float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ;      

      eta1   = Muon_eta[lead_muon] ;
      phi1   = Muon_phi[lead_muon] ;

      // int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;
      int Ssize   = ( n_cleanjet.size() >= 3 ) ?  3 : n_cleanjet.size() ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        // slimjet  = n_jet[ji] ;
        slimjet  = n_cleanjet[ji] ;
        eta2     = Jet_eta_clean[slimjet] ;
        phi2     = Jet_phi_clean[slimjet] ;       

        hist_index  = ji ;  // index for normal jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        if( Check.Contains("Yes")) DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR, factor );
        // cout<<" \n Pt for clean jet [" << slimjet << " ] = " << Jet_pt_clean[slimjet] ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Dirty Jets") ;

      }  

      Ssize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;

      for (int kji = 0; kji < Ssize; ++kji)
      {
        slimjet  = n_AK8Jet[kji] ;
        eta2     = FatJet_eta_clean[slimjet] ;
        phi2     = FatJet_phi_clean[slimjet] ;       

        hist_index  = kji + 3 ;  // index for clean jet
        dR_Calculator(eta1, phi1, eta2, phi2) ;

        // cout <<"\n For leading Muon = " << lead_muon <<"     the DeltaR = " << dR ;

        if( Check.Contains("Yes"))  DeltaR_Hist_Muon_wrt_jet.at(hist_index) ->Fill(dR, factor );
        // Check_deltaR_For_Jet_wrt_MatchedMuon( slimjet, eta2, phi2 ) ;
        // Check_Jet_Matched_Lepton_Index( slimjet, "Clean Jets") ;        

      }

} // END of FUNCTION !!!!

//CLEANING OF Lepton-Jet Clean Jets FROM Lepton-Jet Clean FATJETS =====================================
//------ First Delta R   (jet, fatjet) check
//---- Then Cleaning is done ---------------- ===

void Check_deltaR_For_LeptonClean_Jet_from_FatJet( TString Check_OR_Clean)
{

  int   hist_index = -1 ; // Use for indexing histogram in later loop
  // Here index = 0 to 2 for leading fatjet
  // Here index = 3 to 5  for sub leading fatjet
  // Here index = 6 to 8  for 3rd leading fatjet, 

  int   fatjet = -1 ;
  int   slimjet    = -1 ;
  float eta1 = 0.0 , eta2 = 0.0, phi1 = 0.0, phi2 = 0.0 ; 

  // n_jet = jet_sort ;  // COMMENT IT IF YOU DON'T WANT SORTED JETS !!!!!!

  int Fsize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
  int Ssize   = ( n_jet.size() >= 3 ) ?  3 : n_jet.size() ;

  if ( Check_OR_Clean.Contains("CHECK")){
    // Ssize   = ( n_cleanjet.size() >= 3 ) ?  3 : n_cleanjet.size() ;

    for (int fi = 0; fi < Fsize; ++fi)
    {
      fatjet = n_AK8Jet[fi] ;
      eta1   = FatJet_eta_clean[fatjet] ;
      phi1   = FatJet_phi_clean[fatjet] ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        // slimjet  = n_cleanjet[ji] ;
        
        eta2     = Jet_eta_clean[slimjet] ;
        phi2     = Jet_phi_clean[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
 
        hist_index = 3*fi + ji ;
        // cout << "\n index = " << hist_index;

        DeltaR_Hist_FatJet_wrt_jet.at(hist_index)  ->Fill(dR, factor );
      }

    }

  }

  if ( Check_OR_Clean.Contains("CLEAN")){

    Ssize   =  n_jet.size() ;
    fatjet  = n_AK8Jet[0] ;
    eta1   = FatJet_eta_clean[fatjet] ;
    phi1   = FatJet_phi_clean[fatjet] ;
    hist_index  = -1 ;

      for (int ji = 0; ji < Ssize; ++ji)
      {
        slimjet  = n_jet[ji] ;
        eta2     = Jet_eta_clean[slimjet] ;
        phi2     = Jet_phi_clean[slimjet] ;       

        dR_Calculator(eta1, phi1, eta2, phi2) ;
        
        if ( dR > 1.2){
             hist_index ++ ;
             n_cleanjet.push_back(slimjet) ;
             if( hist_index < 2 && Check_OR_Clean.Contains("Yes")) Fill_Jet_Hist_Preselction_LvL( "LeptonCleanJet",  slimjet , hist_index) ; // Filling Clean Jet at this level============                 
        } 
      }      
      
  } /// END OF JET LOOP !!!!!!!
  
  

}  // END OF THE FUNCTION !!!!!!!!!!!!!!!!!   



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////======================== Pt based sorting of Jets==========================================.///////////////////////////////

// ===================================

void FatJet_sorting_pT_based_After_Cleaning( TString Filling) {

      int jmax = -1 ;
      int jt   = -1 ; 
      float max_pT = 0.0;



      for( int i = 0 ; i < fatjet_sort.size(); i++){

        if( fatjet_copy.size() == 0) continue ;

        jmax   = 0;
        max_pT = FatJet_pt_clean[fatjet_copy[0]];  

        for (int k = 0; k < fatjet_copy.size(); k++)
        {
          jt   = fatjet_copy[k];

          if( FatJet_pt_clean[jt] > max_pT ) {
            jmax   = k ;
            max_pT = FatJet_pt_clean[jt];

          }  
        }
       
        fatjet_sort[i] = fatjet_copy[jmax];
        fatjet_copy.erase(fatjet_copy.begin() + jmax);

      }



      // // check loop...delete it after successful check.
      if ( Filling.Contains("Yes")){

          jmax  = ( fatjet_sort.size() >= 2) ? 2 :  fatjet_sort.size() ;  

          for (int i = 0; i < jmax; ++i)
          {
               // jmax = n_AK8Jet[i];
               jt   = fatjet_sort[i] ;

               if ( i == 0) Fill_FatJet_Hist_Preselction_LvL( "CleanedLeadingJet" ,  jt , i ) ;  
               if ( i == 1) Fill_FatJet_Hist_Preselction_LvL( "CleanedSubleadingJet",  jt , i ) ;  
          }
      } // END of FIlling Loop !!!!!

      // cout << "\n Size of copy = " << fatjet_copy.size() ;
}  // END of FUNCTION !!!!  


//-=-=-=-==-=-==-=-==-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=---------================------============--------=

void Jet_sorting_pT_based_After_Cleaning(TString Filling) {

      int jmax = -1 ;
      int jt   = -1 ; 

      float max_pT = 0.0;

      if ( n_jet.size() == 1 ) jet_sort = n_jet ;
    

      if ( n_jet.size() > 1 ){
          
            jet_sort = n_jet ; 
            jet_copy = n_jet ; 

            for( int i = 0 ; i < jet_sort.size(); i++){

              if( jet_copy.size() == 0) continue ;

              jmax   = 0;
              max_pT = Jet_pt_clean[jet_copy[0]];  

              for (int k = 0; k < jet_copy.size(); k++)
              {
                jt   = jet_copy[k];

                if( Jet_pt_clean[jt] > max_pT ) {
                  jmax   = k ;
                  max_pT = Jet_pt_clean[jt];

                }  
              }
             
              jet_sort[i] =  jet_copy[jmax];
              jet_copy.erase(jet_copy.begin() + jmax);

            }
      }
      
      //      jet_copy = n_jet ; 

      if ( Filling.Contains("Yes")){

          jmax  = ( jet_sort.size() >= 2) ? 2 :  jet_sort.size() ;  

          for (int i = 0; i < jmax; ++i)
          {
               // jmax = n_AK8Jet[i];
               jt   = jet_sort[i] ;
               Fill_Jet_Hist_Preselction_LvL( "CleanedALLJET",  jt , i) ;   
          }
      } // END of FIlling Loop !!!!!

}  // END of FUNCTION !!!!  


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // General Functions for Calling and Checking clean Jets functions =========
   void Study_JetLepton_Cleaning_Effect()
   {


      Check_FatJet_For_Event_N_Fill( "No") ;  // Put Yes if you want to plots Jet Histo without pT based sorting

      Check_Jet_For_Event_N_Fill( "No" ) ;  // Put Yes if you want to plots Jet Histo without pT based sorting

      // if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_For_LeptonClean_Jet_from_FatJet("CHECK") ;  

      if ( n_AK8Jet.size() > 0 && n_jet.size() > 0 ) Check_deltaR_N_Cleaning_Jet_from_FatJet("CLEAN") ;  

      int Fsize   = ( n_AK8Jet.size() >= 2 ) ?  2 : n_AK8Jet.size() ;
      int Ssize   = ( n_cleanjet.size() >= 2 ) ?  2 : n_cleanjet.size() ;

      int jet_idx = -1 ;

      for (int i = 0; i < Fsize; ++i)
      {
            jet_idx = n_AK8Jet[i] ;
            if ( i == 0 )     Fill_CleanedFatJet_Hist( "LeadingJet", jet_idx , i) ;
            if ( i == 1 )     Fill_CleanedFatJet_Hist( "SubleadingJet", jet_idx , i) ;
     
      }
// Fill_CleanedJet_Hist

      for (int i = 0; i < Ssize; ++i)
      {
            jet_idx = n_cleanjet[i] ;
            if ( i == 0 )     Fill_CleanedJet_Hist( "LeadingJet", jet_idx , i) ;
            if ( i == 1 )     Fill_CleanedJet_Hist( "SubleadingJet", jet_idx , i) ;
     
      }

  }




//----==========--- For Cleaned Fatjet Histograms ------------==========================

void   Fill_CleanedFatJet_Hist( TString fatjet, int fatjet_index , int fatjet_count)
{


  int mu_idx = -1 ;

  if ( n_Mu.size() > 0){
        mu_idx = n_Mu[0] ;

  }

  // Filling ALLJET for the event
  if (fatjet.Contains("LeadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_FatJet.at(0  + fatjet_count )   ->Fill(FatJet_pt_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(2  + fatjet_count )   ->Fill(FatJet_pt[fatjet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_FatJet.at(4  + fatjet_count )   ->Fill(FatJet_eta_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(6  + fatjet_count )   ->Fill(FatJet_eta[fatjet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_FatJet.at(8  + fatjet_count )   ->Fill(FatJet_phi_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(10 + fatjet_count )   ->Fill(FatJet_phi[fatjet_index]) ;
   
    // for Delta R histo
    if( mu_idx != -1 ){

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta_clean[fatjet_index], FatJet_phi_clean[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(12 + fatjet_count )   ->Fill(dR) ;

            Hist_DeltaR_wrt_Pt_LepCleanJet.at(4  + fatjet_count) ->Fill(   Jet_pt_clean[fatjet_index] , dR  );

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta[fatjet_index], FatJet_phi[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(14 + fatjet_count )   ->Fill(dR) ;

            Hist_DeltaR_wrt_Pt_LepCleanJet.at(6  + fatjet_count) ->Fill(   Jet_pt[fatjet_index] , dR  );

    }        

  }

  // Filling Forward jet for the event
  if (fatjet.Contains("SubleadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_FatJet.at(0  + fatjet_count )   ->Fill(FatJet_pt_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(2  + fatjet_count )   ->Fill(FatJet_pt[fatjet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_FatJet.at(4  + fatjet_count )   ->Fill(FatJet_eta_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(6  + fatjet_count )   ->Fill(FatJet_eta[fatjet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_FatJet.at(8  + fatjet_count )   ->Fill(FatJet_phi_clean[fatjet_index]) ;
    Hist_for_LeptonCleaned_FatJet.at(10 + fatjet_count )   ->Fill(FatJet_phi[fatjet_index]) ;
   
    // for Delta R histo
    if( mu_idx != -1 ){

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta_clean[fatjet_index], FatJet_phi_clean[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(12 + fatjet_count )   ->Fill(dR) ;
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(4  + fatjet_count) ->Fill(   Jet_pt_clean[fatjet_index], dR  );

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], FatJet_eta[fatjet_index], FatJet_phi[fatjet_index]) ;      
            Hist_for_LeptonCleaned_FatJet.at(14 + fatjet_count )   ->Fill(dR) ;
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(6 + fatjet_count) ->Fill(   Jet_pt[fatjet_index], dR  );

    } 

  }  

} // END of the function !!!!!!!!!!!     

//=======---------------=================---------------=======================

void   Fill_CleanedJet_Hist( TString fatjet, int jet_index , int jet_count)
{


  int mu_idx = -1 ;

  if ( n_Mu.size() > 0){
        mu_idx = n_Mu[0] ;

  }
  
  TVector3 vec_lep, vec_jet;
  float dPt = 0.0 ;

  // Filling ALLJET for the event
  if (fatjet.Contains("LeadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_Jet.at(0  + jet_count )   ->Fill(Jet_pt_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(2  + jet_count )   ->Fill(Jet_pt[jet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_Jet.at(4  + jet_count )   ->Fill(Jet_eta_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(6  + jet_count )   ->Fill(Jet_eta[jet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_Jet.at(8  + jet_count )   ->Fill(Jet_phi_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(10 + jet_count )   ->Fill(Jet_phi[jet_index]) ;
   
    // for Delta R and Delta Pt histo
    if( mu_idx != -1 ){

            vec_lep.SetPtEtaPhi( Muon_pt[mu_idx],Muon_eta[mu_idx], Muon_phi[mu_idx] ) ;

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index]) ;      
            Hist_for_LeptonCleaned_Jet.at(12 + jet_count )   ->Fill(dR) ;

            vec_jet.SetPtEtaPhi( Jet_pt_clean[jet_index], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index] ) ;
            dPt  = dPt_Calculator(vec_lep, vec_jet) ;      
            Hist_for_LeptonCleaned_Jet.at(16 + jet_count )   ->Fill(dPt) ;      

            dPt_dR_mu_cleanjet1 ->Fill( dR, dPt);
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(0  + jet_count) ->Fill(  Jet_pt_clean[jet_index] , dR  );
            Hist_DeltaPt_wrt_Pt_LepCleanJet.at(0 + jet_count) ->Fill(  Jet_pt_clean[jet_index] , dPt );


            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta[jet_index], Jet_phi[jet_index]) ;      
            Hist_for_LeptonCleaned_Jet.at(14 + jet_count )   ->Fill(dR) ;

            vec_jet.SetPtEtaPhi( Jet_pt[jet_index], Jet_eta[jet_index], Jet_phi[jet_index] ) ;
            dPt  = dPt_Calculator(vec_lep, vec_jet) ;      
            Hist_for_LeptonCleaned_Jet.at(18 + jet_count )   ->Fill(dPt) ;  

            dPt_dR_mu_jet1  ->Fill( dR, dPt);
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(2   + jet_count) ->Fill(  Jet_pt[jet_index], dR   );
            Hist_DeltaPt_wrt_Pt_LepCleanJet.at(2 + jet_count)  ->Fill(  Jet_pt[jet_index], dPt  );         


    }        

  }

  // Filling Forward jet for the event
  if (fatjet.Contains("SubleadingJet"))
  {
    // for jet Pt histo    
    Hist_for_LeptonCleaned_Jet.at(0  + jet_count )   ->Fill(Jet_pt_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(2  + jet_count )   ->Fill(Jet_pt[jet_index]) ;

    // for jet Eta histo
    Hist_for_LeptonCleaned_Jet.at(4  + jet_count )   ->Fill(Jet_eta_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(6  + jet_count )   ->Fill(Jet_eta[jet_index]) ;

    // for jet Phi histo
    Hist_for_LeptonCleaned_Jet.at(8  + jet_count )   ->Fill(Jet_phi_clean[jet_index]) ;
    Hist_for_LeptonCleaned_Jet.at(10 + jet_count )   ->Fill(Jet_phi[jet_index]) ;
   
    // for Delta R and Delta Pt histo
    if( mu_idx != -1 ){

            vec_lep.SetPtEtaPhi( Muon_pt[mu_idx],Muon_eta[mu_idx], Muon_phi[mu_idx] ) ;

            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index]) ;      
            Hist_for_LeptonCleaned_Jet.at(12 + jet_count )   ->Fill(dR) ;

            vec_jet.SetPtEtaPhi( Jet_pt_clean[jet_index], Jet_eta_clean[jet_index], Jet_phi_clean[jet_index] ) ;
            dPt  = dPt_Calculator(vec_lep, vec_jet) ;      
            Hist_for_LeptonCleaned_Jet.at(16 + jet_count )   ->Fill(dPt) ;      

            dPt_dR_mu_cleanjet1 ->Fill( dR, dPt);
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(0  + jet_count) ->Fill(   Jet_pt_clean[jet_index], dR  );
            Hist_DeltaPt_wrt_Pt_LepCleanJet.at(0 + jet_count) ->Fill(   Jet_pt_clean[jet_index], dPt );


            dR_Calculator(Muon_eta[mu_idx], Muon_phi[mu_idx], Jet_eta[jet_index], Jet_phi[jet_index]) ;      
            Hist_for_LeptonCleaned_Jet.at(14 + jet_count )   ->Fill(dR) ;

            vec_jet.SetPtEtaPhi( Jet_pt[jet_index], Jet_eta[jet_index], Jet_phi[jet_index] ) ;
            dPt  = dPt_Calculator(vec_lep, vec_jet) ;      
            Hist_for_LeptonCleaned_Jet.at(18 + jet_count )   ->Fill(dPt) ;  

            dPt_dR_mu_jet1  ->Fill( dR, dPt);
            Hist_DeltaR_wrt_Pt_LepCleanJet.at(2   + jet_count) ->Fill(  Jet_pt[jet_index] , dR  );
            Hist_DeltaPt_wrt_Pt_LepCleanJet.at(2 + jet_count)  ->Fill(  Jet_pt[jet_index] , dPt );  

    }        

  }  // END of SUbleading Jet Loop

} // END of the function !!!!!!!!!!!   


/////////=====================================================///////////////////////////////////////////////////////////////////
/////////=====================================================///////////////////////////////////////////////////////////////////
/////////=====================================================///////////////////////////////////////////////////////////////////
/////////=====================================================///////////////////////////////////////////////////////////////////
////////////////////////SELECTIONS APPLIED AND TEST ARE RUN HERE =========//////////////////////////////////////////////////////



void Scalar_Sum_pT_Function()
{
  
  Scalar_Sum_pT =  MET_pt ;

  int    b2 = n_Mu[0];

  Scalar_Sum_pT += Muon_pt[b2]  ;

  // for (int j = 0 ; j < n_jet.size() ; j ++) {
  //   b2 =  n_jet[j];
  //   Scalar_Sum_pT += (*jetPt)[b2] ;

  // }

  for ( int k = 0 ; k < n_AK8Jet.size() ; k ++) {
    b2 =  n_AK8Jet[k];
    Scalar_Sum_pT += FatJet_pt_clean[b2];
  }

  ST_Sum_Presel -> Fill(Scalar_Sum_pT, factor) ;

  

}