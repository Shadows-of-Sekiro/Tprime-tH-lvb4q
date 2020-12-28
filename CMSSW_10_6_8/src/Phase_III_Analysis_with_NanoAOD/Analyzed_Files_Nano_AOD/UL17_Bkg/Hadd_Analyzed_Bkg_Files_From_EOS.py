import os


#Tb_tH_LH_M1000_merged.sh
#Tb_tH_LH_M1000_merged.jdl

#TTbar_mcbkg_test_python.txt

QCD_dataset = {
   'QCD_Pt80to120'                : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt*UL17'  ,
   # 'QCD_Pt120to170'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt120to170' ,
   # 'QCD_Pt170to300'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt170to300' ,
   # 'QCD_Pt300to470'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt300to470' ,
   # 'QCD_Pt470to600'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt470to600' ,
   # 'QCD_Pt600to800'               : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt600to800' ,
   # 'QCD_Pt800to1000'              : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt800to1000',
   # 'QCD_Pt1000toInf'              : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_QCD_MuEnr_Files/QCD_Pt1000toInf',
   }


WJetsToLNu_dataset = {   
   'WJetsToLNu'                   : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_Wjets_To_LNu_Files/WJets_LNu_UL17', 

  }

DYJetsToLL_dataset = {   
   'DYJetsToLL'                   : '/eos/user/a/achhetri/Tprime_PhaseIII/Analyzed_NANO_file_via_Condor/Background_Samples_UL17/UL17_DYjetsTo_LL_Files/',
   }

SingleTop_dataset = {   
   's-channel'                    : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_s-channel_4f_leptonDecays_v3/ST_s-channel_4f_leptonDecays'  ,
   't-channel_antitop'            : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_t-channel_antitop_4f_inclusiveDecays_v3/ST_t-channel_antitop_4f_inclusiveDecays'  ,
   't-channel_top'                : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_t-channel_top_4f_inclusiveDecays_v3/ST_t-channel_top_4f_inclusiveDecays'  ,
   'tW_antitop'                   : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_tW_antitop_5f_inclusiveDecays_v3/ST_tW_antitop_5f_inclusiveDecays'  ,
   'tW_top'                       : '/eos/uscms/store/user/achhetri/PhaseII_MainTree/Background_v3_Samples/ST_tW_top_5f_inclusiveDecays_v3/ST_tW_top_5f_inclusiveDecays' ,   
   }



QCDSamples = [
   'QCD_Pt80to120',        
   # 'QCD_Pt120to170',        
   # 'QCD_Pt170to300',        
   # 'QCD_Pt300to470',        
   # 'QCD_Pt470to600', 
   # 'QCD_Pt600to800',
   # 'QCD_Pt800to1000',      
   # 'QCD_Pt1000toInf',
    ]
WjetsToLNuSamples = [
   'WJetsToLNu'  
   ]
   
DYJetsToLLSamples = [
   'DYJetsToLL'  
   ]

SingleTopSamples = [
   's-channel' ,
   't-channel_antitop' ,
   't-channel_top' ,
   'tW_antitop' ,
   'tW_top' ,        
   ]


dataset = {
            '1' : '*Full_Selection_26-12-20.root',
            # '1' : '*LeptonCleaned_Jets_24-12-20.root',
            # '2' : '*_LeptonCleaned_18-12-20.root',
            # '3' : '*_LeptonCleaned_18-12-20.root',

   }



#nevents = -1 
eventsPerJob = {
            '1' : 'Full_Selection_26-12-20.root',
            # '1' : 'LeptonCleaned_Jets_24-12-20.root',
            # '2' : 'LeptonCleaned_18-12-20.root',
            # '3' : 'LeptonCleaned_18-12-20.root',

      }

listOfSamples = [
  '1'  ,
  # '2'  ,
  # '3'  ,
  # '4'  ,
  # '5'  ,
  # '6'  ,
  # '7'  ,
  # '8'  ,
  # '9'  ,
  # '10' ,
  # '11' ,
  # '12' ,
  # '13' ,
  # '14' ,
  # '15' ,
  # '16' ,
  # '17' ,
  # '18' ,
  # '19' ,
  # '20' ,  
   ]


listOfSamples.reverse()
os.system ("rm *Hadd.sh")

     # InputTextFile = open (dataset[samples])S
     # lines = InputTextFile.readlines()
     
     # count=0
     # textfileNumber = 0


rootFileList = []    
fr=open("QCDmultijetFiles_Hadd.sh", "a") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd -f QCD_MUEnr_UL17/QCD_MuEnr_UL17_" + eventsPerJob[samples] + "   ")
                         for QCD in QCDSamples :
                             fr.write( QCD_dataset[QCD]  + dataset[samples] + "    " )
            del rootFileList[:]                                            


rootFileList = []    
fr=open("WjetsToLNuFiles_Hadd.sh", "a") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd -f Wjets_LNu_UL17/Wjets_LNu_UL17_" + eventsPerJob[samples] + "   ")
                         for Wjets in WjetsToLNuSamples :
                             fr.write( WJetsToLNu_dataset[Wjets]  + dataset[samples] + "    " )
            del rootFileList[:]   



rootFileList = []    
fr=open("DYJetsToLLFiles_Hadd.sh", "a") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd -f DYjets_LL_UL17/DYJetsToLL_UL17_" + eventsPerJob[samples] + "   ")
                         for DYJets in DYJetsToLLSamples :
                             fr.write( DYJetsToLL_dataset[DYJets]  + dataset[samples] + "    " )
            del rootFileList[:]   


 
rootFileList = []    
fr=open("SingleTopFiles_Hadd.sh", "a") 
fr.write("#!/bin/bash" + "\n\n")
for samples in listOfSamples :      
            rootFileList.append(samples)
            for rootFile in rootFileList :
                         fr.write("\n\n" + "hadd SingleTop_" + eventsPerJob[samples] + "   ")
                         for STop in SingleTopSamples :
                             fr.write( SingleTop_dataset[STop]  + dataset[samples] + "    " )
            del rootFileList[:]                                         
