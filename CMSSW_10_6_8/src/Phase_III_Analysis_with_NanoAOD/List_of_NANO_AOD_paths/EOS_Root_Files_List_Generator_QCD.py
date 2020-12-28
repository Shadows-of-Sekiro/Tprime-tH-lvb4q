#!/usr/bin/python

import sys
#import datetime
import os

source	 = "/eos/user/a/achhetri/Tprime_v5_NANo_AOD_106X/"

SingleTop_Samples = {
'QCD_Pt-80to120_MuEnr_UL17'      :'QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
'QCD_Pt-120to170_MuEnr_UL17'     :'QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
'QCD_Pt-170to300_MuEnr_UL17'     :'QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
'QCD_Pt-300to470_MuEnr_UL17'     :'QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
'QCD_Pt-470to600_MuEnr_UL17'     :'QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
'QCD_Pt-600to800_MuEnr_UL17'     :'QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
'QCD_Pt-800to1000_MuEnr_UL17'    :'QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
'QCD_Pt-1000toInf_MuEnr_UL17'    :'QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/',
}


listofSamples = [
'QCD_Pt-80to120_MuEnr_UL17'   ,
'QCD_Pt-120to170_MuEnr_UL17'  ,
'QCD_Pt-170to300_MuEnr_UL17'  ,
'QCD_Pt-300to470_MuEnr_UL17'  ,
'QCD_Pt-470to600_MuEnr_UL17'  ,
'QCD_Pt-600to800_MuEnr_UL17'  ,
'QCD_Pt-800to1000_MuEnr_UL17' ,
'QCD_Pt-1000toInf_MuEnr_UL17' ,
]

#listofSamples.reverse()
os.system ("rm QCD_*.txt")

for sample in listofSamples:
	
    source_ST  = "/eos/user/a/achhetri/Tprime_v5_NANo_AOD_106X/" + SingleTop_Samples[sample]
    textfileNumber = 0
    for root, dirs, filenames in os.walk(source_ST):
    	#print "a: ",root,"\t",dirs,"\t",filenames
    	
    		rootFileList = []
    		for f in filenames:
    			#os.sys("root://cmseos.fnal.gov ls root+ os.sep + f")
    			#print f
    			#print  textfileNumber
    			rootFileList.append(f)
           		fr=open(SingleTop_Samples[sample].replace("/","_UL17.txt"), "a") 
           		for rootFile in rootFileList :
           		         	 fr.write(root.replace("/eos/uscms","")+"/"+rootFile+"\n")
           		del rootFileList[:]









