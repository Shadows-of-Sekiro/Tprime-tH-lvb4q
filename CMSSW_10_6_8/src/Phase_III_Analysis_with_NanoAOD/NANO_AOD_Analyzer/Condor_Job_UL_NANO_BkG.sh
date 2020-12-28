#!/bin/bash

echo "Starting job on " `date`
echo "Running on: `uname -a`"
echo "System software: `cat /etc/redhat-release`"
source /cvmfs/cms.cern.ch/cmsset_default.sh

echo "PWD: "$PWD
export SCRAM_ARCH=slc7_amd64_gcc700


xrdcp -f  root://eosuser.cern.ch//eos/user/a/achhetri/CMSSW_10_68.tgz .
tar -xf CMSSW_10_68.tgz
rm CMSSW_10_68.tgz
cd CMSSW_10_6_8/src/Phase_III_Analysis_with_NanoAOD/NANO_AOD_Analyzer
scramv1 b ProjectRename
eval `scram runtime -sh`


ls
echo "============================================"
./PUPPI.exe $*

echo "PWD: "$PWD
echo "====> List output files : " 

#ls TEST/*.root 

#xrdcp -f *.root  root://eosuser.cern.ch//eos/user/a/achhetri/TTbar_UL16_test.root
xrdcp -f ../Analyzed_Files_Nano_AOD/UL_TTbar/root_text_files_list/TTbar*.root  root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_TTbar_Files/
xrdcp -f ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/QCD*.root        root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/
xrdcp -f ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/WJets_LNu*.root        root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/
xrdcp -f ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/DYJetsToLL_*.root        root://eosuser.cern.ch//eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/

cd ${_CONDOR_SCRATCH_DIR}
rm -rf CMSSW_10_6_8

date

# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL_TTbar/root_text_files_list/TTbar_UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/QCD_*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/WJets_*UL17_*.txt
# Queue filename matching files ../Analyzed_Files_Nano_AOD/UL17_Bkg/root_file_list/DYJets*UL17_*.txt

















# //////////////////////////////////////////////////////////////////////////////////////////////////////
# echo "Starting job on " `date`
# echo "Running on: `uname -a`"
# echo "System software: `cat /etc/redhat-release`"
# source /cvmfs/cms.cern.ch/cmsset_default.sh
# export SCRAM_ARCH=slc6_amd64_gcc530
# ### copy the input root files if they are needed only if you require local reading
# xrdcp -s root://cmseos.fnal.gov//store/user/achhetri/CMSSW_94_13.tgz .
# tar -xf CMSSW_94_13.tgz
# rm CMSSW_94_13.tgz
# cd CMSSW_9_4_13/src/Main_Ntuples_Analyzer/Background_2016_v3_Sample
# scramv1 b ProjectRename
# eval `scram runtime -sh`
# ls
# echo "============================================"
# ./PUPPI.exe $* 
# echo "====> List output files : " 
# ls *.root


# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-80to*.root 		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-80to120_MuEnr_v3/ 
# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-120*.root 		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-120to170_MuEnr_v3/
# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-170*.root 		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-170to300_MuEnr_v3/
# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-300*.root 		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-300to470_MuEnr_v3/
# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-470*.root 		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-470to600_MuEnr_v3/
# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-600*.root 		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-600to800_MuEnr_v3/
# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-800*.root 		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-800to1000_MuEnr_v3/
# xrdcp list_of_Bkgfiles/Bkg_QCD_Pt-1000*.root   		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_QCD_Pt-1000toInf_MuEnr_v3/

# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-70*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-70To100_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-100*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-100To200_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-200*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-200To400_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-400*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-400To600_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-600*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-600To800_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-800*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-800To1200_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-1200*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-1200To2500_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_LNu_HT-2500*.root 	            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_LNu_HT-2500ToInf_v3/
# xrdcp list_of_Bkgfiles/Bkg_WJets_QQ*.root      		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_WJets_QQ_HT-600ToInf_v3/

# xrdcp list_of_Bkgfiles/Bkg_TTbar*.root         		            		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_TTbar_v3/

# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-70*.root 	    			   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-70To100_v3/
# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-100*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-100To200_v3/
# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-200*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-200To400_v3/
# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-400*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-400To600_v3/
# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-600To800_v3/
# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-800*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-800To1200_v3/
# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-1200*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-1200To2500_v3/
# xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-2500*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/Bkg_DYJetsToLL_M-50_HT-2500ToInf_v3/

# xrdcp list_of_Bkgfiles/ST_s-channel_4f_leptonDecays*.root       		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_s-channel_4f_leptonDecays_v3/
# xrdcp list_of_Bkgfiles/ST_t-channel_antitop_4f_inclusiveDecays*.root       root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_t-channel_antitop_4f_inclusiveDecays_v3/
# xrdcp list_of_Bkgfiles/ST_t-channel_top_4f_inclusiveDecays*.root       	   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_t-channel_top_4f_inclusiveDecays_v3/
# xrdcp list_of_Bkgfiles/ST_tW_antitop_5f_inclusiveDecays*.root       	   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_tW_antitop_5f_inclusiveDecays_v3/
# xrdcp list_of_Bkgfiles/ST_tW_top_5f_inclusiveDecays_*.root       		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_tW_top_5f_inclusiveDecays_v3/ 

# # xrdcp list_of_Bkgfiles/Bkg_DYJetsToLL_M-50_HT-600*.root 	    		   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/JobsCheckFile_v3/
# # xrdcp list_of_Bkgfiles/ST_t-channel_antitop_4f_inclusiveDecays*.root       	   root://cmseos.fnal.gov//store/user/achhetri/PhaseII_MainTree/JobsCheckFile_v3/



# rm list_of_Bkgfiles/*.root
# cd ${_CONDOR_SCRATCH_DIR}
# rm -rf CMSSW_9_4_13








