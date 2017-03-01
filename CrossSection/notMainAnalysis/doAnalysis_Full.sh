#!/bin/bash
#source clean.sh
CENTPbPbMIN=0
CENTPbPbMAX=10
#
LUMIPP=27.4
#LUMIPP=25.8
LUMIPPMB=0.0381639 # from brilcalc
#LUMIPPMB=0.0361128 # from brilcalc
LUMIPbPbGJ=15.5020   # from brilcalc
LUMIPbPbTO=4.63386   # from brilcalc
#LUMIPbPb=15.5665   # from brilcalc
LUMIPbPbMB=1.6419125
#LUMIPbPbMB=0.834692 
FILEEND=""
PREDICTIONS=""
if [ $CENTPbPbMAX -eq 10 ];then
    LUMIPbPbGJ=6.50280
    LUMIPbPbTO=1.94635
    LUMIPbPbMB=0.6891959
    FILEEND="Cent10"
    PREDICTIONS="../TheoryPredictions/PredictionsCUJET3_pt_0_10.root"
fi

#Central point of the analysis

DOANALYSISPP_FONLL=0
DOANALYSISPP_TRGCOMBINATION=0
DOANALYSISPP_FIT=0
DOANALYSISPP_CROSS=1
DOANALYSISPP_MCSTUDY=0

DOANALYSISPbPb_FONLL=0
DOANALYSISPbPb_TRGCOMBINATION=0
DOANALYSISPbPb_FIT=0
DOANALYSISPbPb_CROSS=1
DOANALYSISPbPb_MCSTUDY=0
DOANALYSISPbPb_COMBGJTO=1

DOANALYSISPPMB_FONLL=0
DOANALYSISPPMB_FIT=0
DOANALYSISPPMB_CROSS=1
DOANALYSISPPMB_MCSTUDY=0

DOANALYSISPbPbMB_FONLL=0
DOANALYSISPbPbMB_FIT=0
DOANALYSISPbPbMB_CROSS=1
DOANALYSISPbPbMB_MCSTUDY=0

DOANALYSISPP_MCSTUDYCombine=0
DOANALYSISPbPb_MCSTUDYCombine=0

DONORMPP=0
DONORMPPMB=0
DONORMPbPb=0
DONORMPbPbMB=0

DORAA=1
DORAAMB=1

DOCombineCrossSectionPP=0
DOCombineCrossSectionPbPb=0
DOCombineRAA=1

#systematic section

DOFITSPPMCClosure=0
DOFITSPbPbMCClosure=0
DOFITSPPMBMCClosure=0
DOFITSPbPbMBMCClosure=0

DOsystematicPthatstudyPP=0
DOsystematicPthatstudyPbPb=0

DOsystematicTrackingPP=0
DOsystematicTrackingPPMB=0
DOsystematicTrackingPbPb=0
DOsystematicTrackingPbPbMB=0

DOANALYSIS_MCSTUDYDETAIL=0
DOANALYSISPbPb_MCSTUDYDETAIL=0

UNITY=1
NULL=0

MINIMUMFIT=2
MAXIMUMFIT=100

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLDATINPUTBtoD="pp_Btod0meson_5TeV_y1"
FONLLDATINPUTB="pp_Bmeson_5TeV_y1"

## PP MONTE CARLO

NTUPLAPYTHIA="/data/HeavyFlavourRun2/BtoDPythia/treefile_ptall_11january2016.root"
INPUTMCPP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"  
INPUTMCNPPP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

## PP DATA 

INPUTDATAPPSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson_skim_myskim.root"
INPUTDATAPPUNSKIMMED="/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson.root"
INPUTDATAPPMBUNSKIMMED="/data/jisun/ppMB2015fullstats/skim_Dntuple_crab_pp_MinimumBias1to20_AOD_D0Dsy1p1_tkpt0p5eta2p0_04122016.root"
INPUTDATAPPMBSKIMMED="/data/jisun/ppMB2015fullstats/skim_Dntuple_crab_pp_MinimumBias1to20_AOD_D0Dsy1p1_tkpt0p5eta2p0_04122016.root"
#INPUTDATAPPMBSKIMMED="/data/dmeson2015/DataDntupleApproval/skim_Dntuple_crab_pp_MinimumBias1to20_AOD_D0Dsy1p1_tkpt0p5eta2p0_04122016_skimmed_15May2016_Dpt2_y1p1_Decay3p5_Alpha0p12.root"

## PbPb MONTE CARLO

INPUTMCPbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCNPPbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

## PbPb DATA 

INPUTDATAPbPbGJSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_skimmed.root"
INPUTDATAPbPbGJUNSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON.root"
INPUTDATAPbPbTOSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/Dntuple_crab_PbPb_HIHardProbes_tkpt6p0eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
INPUTDATAPbPbTOUNSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/Dntuple_crab_PbPb_HIHardProbes_tkpt6p0eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
INPUTDATAPbPbMBUNSKIMMED="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"
#INPUTDATAPbPbMBSKIMMED="/data/jisun/PbPb2015/HF2and_ncand_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_D0y1p1_tkpt0p7eta1p5_goldenjson_EvtPlaneCali_03182015.root"
INPUTDATAPbPbMBSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/ntDntuple_PbPb_MinimumBias_GoldenjsonNTrackerOnlyjson_skimOPTcuts.root"

## CHARGED RAA
CHARGEDHADRON="/afs/cern.ch/work/g/ginnocen/public/PlotRAA.root" 

## ANALYSIS PP TRIGGERED

FONLLOUTPUTFILE="ROOTfiles${FILEEND}/output_pp_d0meson_5TeV_y1.root"
FONLLOUTPUTFILEBtoD="ROOTfiles${FILEEND}/output_pp_Btod0meson_5TeV_y1.root"
FONLLOUTPUTFILEInclusiveD="ROOTfiles${FILEEND}/output_inclusiveDd0meson_5TeV_y1.root"
FONLLOUTPUTFILEB="ROOTfiles${FILEEND}/output_pp_Bmeson_5TeV_y1.root"
OUTPUTFILEPP="ROOTfiles${FILEEND}/hPtSpectrumDzeroPP.root"
OUTPUTFILEPlotPP="ROOTfiles${FILEEND}/CrossSectionFONLLPP.root"
OUTPUTFILEMCSTUDYPP="ROOTfiles${FILEEND}/MCstudiesPP.root"
OUTPUTFILEMCSTUDYNPPP="ROOTfiles${FILEEND}/MCstudiesNPPP.root"
OUTPUTPrescalePP="ROOTfiles${FILEEND}/prescalePP.root"

ISMCPP=0
ISDOWEIGHTPP=1
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUTPP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt8_v1&&Dpt>10&&Dpt<20)||(HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
LABELPP="PP"
LABELNPPP="NPPP"
USEPRESCALEPP=1
CUTFORTRIGGERPRESCALEPP=0

ISHADDUPL=1                                  

cp config/parametersHighpt.h parameters.h

if [ $DONORMPP -eq 1 ]; then      
cp config/parametersHighptPPNorm.h parameters.h
OUTPUTFILEPlotPP="ROOTfiles${FILEEND}/CrossSectionFONLLPPNorm.root"
OUTPUTPrescalePP="ROOTfiles${FILEEND}/prescalePPNorm.root"
OUTPUTFILEPP="ROOTfiles${FILEEND}/hPtSpectrumDzeroPPNorm.root"
LUMIPP=1
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt8_v1))"
fi

if [ $DOANALYSISPP_FONLL -eq 1 ]; then      
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPP"
./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoD" "$LABELPP"
rm Dzerodsigmadpt.exe

g++ BplusAlldsigmadpt.cc $(root-config --cflags --libs) -g -o BplusAlldsigmadpt.exe 
./BplusAlldsigmadpt.exe "$FONLLDATINPUTB"  "$FONLLOUTPUTFILEB" "$LABELPP"
rm BplusAlldsigmadpt.exe

g++ RatioFeedDown.cc $(root-config --cflags --libs) -g -o RatioFeedDown.exe 
./RatioFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEBtoD" "$FONLLOUTPUTFILEInclusiveD" "$LABELPP"
rm RatioFeedDown.exe

g++ plotFeedDown.C $(root-config --cflags --libs) -g -o plotFeedDown.exe 
./plotFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEB" "$NTUPLAPYTHIA" 1 0 100 
rm plotFeedDown.exe
fi 

if [ $DOANALYSISPP_TRGCOMBINATION -eq 1 ]; then      
g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe 0 "$INPUTDATAPPUNSKIMMED" "$CUTFORTRIGGERPRESCALEPP" "$OUTPUTPrescalePP" 0
rm triggercombination.exe
fi 

if [ $DOANALYSISPP_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 0 "$INPUTDATAPPSKIMMED"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP"
rm fitD.exe
fi 

if [ $DOANALYSISPP_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe  0 "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe  0 "$INPUTMCNPPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELNPPP" "$OUTPUTFILEMCSTUDYNPPP" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEMCSTUDYNPPP"
rm plotPnNP.exe
fi


if [ $DOANALYSISPP_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPP"  "$OUTPUTFILEMCSTUDYPP" "$OUTPUTPrescalePP" "$USEPRESCALEPP" "$OUTPUTFILEPlotPP" 0 "$LABELPP" "$LUMIPP" 
rm CrossSectionRatio.exe
fi

## ANALYSIS PbPb TRIGGERED

cp config/parametersHighpt.h parameters.h

OUTPUTPrescalePbPbGJ="ROOTfiles${FILEEND}/prescalePbPbGJ.root"
OUTPUTPrescalePbPbTO="ROOTfiles${FILEEND}/prescalePbPbTO.root"
OUTPUTFILEMCSTUDYPbPb="ROOTfiles${FILEEND}/MCstudiesPbPb.root"
OUTPUTFILEMCSTUDYNPPbPb="ROOTfiles${FILEEND}/MCstudiesNPPbPb.root"
OUTPUTFILEPbPbGJ="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbGJ.root"
OUTPUTFILEPbPbTO="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbTO.root"
OUTPUTFILEPlotPbPbGJ="ROOTfiles${FILEEND}/CrossSectionFONLLPbPbGJ.root"
OUTPUTFILEPlotPbPbTO="ROOTfiles${FILEEND}/CrossSectionFONLLPbPbTO.root"
OUTPUTFILEPlotPbPb="ROOTfiles${FILEEND}/CrossSectionFONLLPbPb.root"
OUTPUTFILERAA="ROOTfiles${FILEEND}/outputRAA.root"

ISMCPbPb=0
ISDOWEIGHTPbPb=2
SELGENPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPbPb="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUTPbPb="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPbGJ="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
TRGPbPbTO="((HLT_HIDmesonHITrackingGlobal_Dpt20_v2&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
LABELPbPb="PbPb"
LABELNPPbPb="NPPbPb"
USEPRESCALEPbPb=1
CUTFORTRIGGERPRESCALEPbPb=0

if [ $DONORMPbPb -eq 1 ]; then      
cp config/parametersHighptPbPbNorm.h parameters.h
OUTPUTFILEPlotPbPb="ROOTfiles${FILEEND}/CrossSectionFONLLPbPbNorm.root"
OUTPUTPrescalePbPb="ROOTfiles${FILEEND}/prescalePbPbNorm.root"
OUTPUTFILEPbPb="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbNorm.root"
LUMIPbPb=1
fi

if [ $DOANALYSISPbPb_FONLL -eq 1 ]; then
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPbPb"
rm Dzerodsigmadpt.exe
fi

if [ $DOANALYSISPbPb_TRGCOMBINATION -eq 1 ]; then      
g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe 1 "$INPUTDATAPbPbGJUNSKIMMED" "$CUTFORTRIGGERPRESCALEPbPb" "$OUTPUTPrescalePbPbGJ" 1
./triggercombination.exe 1 "$INPUTDATAPbPbTOUNSKIMMED" "$CUTFORTRIGGERPRESCALEPbPb" "$OUTPUTPrescalePbPbTO" 0
rm triggercombination.exe
fi

if [ $DOANALYSISPbPb_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 1 "$INPUTDATAPbPbGJSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbGJ" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"  "$LABELPbPb"  "$OUTPUTFILEPbPbGJ" "$CENTPbPbMIN" "$CENTPbPbMAX"
./fitD.exe 1 "$INPUTDATAPbPbTOSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbTO" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"  "$LABELPbPb"  "$OUTPUTFILEPbPbTO" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitD.exe
fi

if [ $DOANALYSISPbPb_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe 1 "$INPUTMCNPPbPb"  "$SELGENPbPb" "$SELGENACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELNPPbPb" "$OUTPUTFILEMCSTUDYNPPbPb" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTFILEMCSTUDYNPPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm plotPnNP.exe
fi

if [ $DOANALYSISPbPb_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPbPbGJ" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTPrescalePbPbGJ" "$USEPRESCALEPbPb" "$OUTPUTFILEPlotPbPbGJ" 1 "$LABELPbPb" "$LUMIPbPbGJ" "$CENTPbPbMIN" "$CENTPbPbMAX"
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPbPbTO" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTPrescalePbPbTO" "$USEPRESCALEPbPb" "$OUTPUTFILEPlotPbPbTO" 1 "$LABELPbPb" "$LUMIPbPbTO" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPbPb_COMBGJTO -eq 1 ]; then
g++ combineGJTO.C $(root-config --cflags --libs) -g -o combineGJTO.exe
./combineGJTO.exe "$OUTPUTFILEPlotPbPbGJ" "$OUTPUTFILEPlotPbPbTO" "$OUTPUTFILEPlotPbPb" "$LUMIPbPbGJ" "$LUMIPbPbTO"
rm combineGJTO.exe
fi

if [ $DORAA -eq 1 ]; then      
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe 
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPP" "$OUTPUTFILEPlotPbPb"  "$LABELPbPb" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactor.exe
fi


## ANALYSIS PP MB

FONLLOUTPUTFILEMB="ROOTfiles${FILEEND}/output_pp_d0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBtoDMB="ROOTfiles${FILEEND}/output_pp_Btod0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEInclusiveDMB="ROOTfiles${FILEEND}/output_inclusiveDd0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBMB="ROOTfiles${FILEEND}/output_pp_Bmeson_5TeV_y1MB.root"
OUTPUTFILEPPMB="ROOTfiles${FILEEND}/hPtSpectrumDzeroPPMB.root"
OUTPUTFILEPlotPPMB="ROOTfiles${FILEEND}/CrossSectionFONLLPPMB.root"
OUTPUTFILEMCSTUDYPPMB="ROOTfiles${FILEEND}/MCstudiesPPMB.root"
OUTPUTFILEMCSTUDYNPPPMB="ROOTfiles${FILEEND}/MCstudiesNPPPMB.root"

ISMCPPMB=0
ISDOWEIGHTPPMB=1
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5"
CUTPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
#CUTPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"
LABELNPPPMB="NPPPMB"
USEPRESCALEPPMB=0


cp config/parametersLowpt.h parameters.h


if [ $DONORMPPMB -eq 1 ]; then      
LUMIPPMB=1
cp config/parametersMBPPNorm.h parameters.h
OUTPUTFILEPlotPPMB="ROOTfiles${FILEEND}/CrossSectionFONLLPPMBNorm.root"
ISDOWEIGHTPPMB=0
OUTPUTFILEPPMB="ROOTfiles${FILEEND}/hPtSpectrumDzeroPPMBNorm.root"

fi 

if [ $DOANALYSISPPMB_FONLL -eq 1 ]; then
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEMB" "$LABELPPMB"
./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoDMB" "$LABELPPMB"
rm Dzerodsigmadpt.exe

g++ BplusAlldsigmadpt.cc $(root-config --cflags --libs) -g -o BplusAlldsigmadpt.exe 
./BplusAlldsigmadpt.exe "$FONLLDATINPUTB"  "$FONLLOUTPUTFILEBMB" "$LABELPPMB"
rm BplusAlldsigmadpt.exe

g++ RatioFeedDown.cc $(root-config --cflags --libs) -g -o RatioFeedDown.exe 
./RatioFeedDown.exe "$FONLLOUTPUTFILEMB"  "$FONLLOUTPUTFILEBtoDMB" "$FONLLOUTPUTFILEInclusiveDMB" "$LABELPPMB"
rm RatioFeedDown.exe

g++ plotFeedDown.C $(root-config --cflags --libs) -g -o plotFeedDown.exe 
./plotFeedDown.exe "$FONLLOUTPUTFILEMB"  "$FONLLOUTPUTFILEBMB" "$NTUPLAPYTHIA" 1 0 100 
rm plotFeedDown.exe
fi

if [ $DOANALYSISPPMB_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 0 "$INPUTDATAPPMBSKIMMED"  "$INPUTMCPP"  "$TRGPPMB" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMB"   1   "$ISDOWEIGHTPPMB"   "$LABELPPMB"  "$OUTPUTFILEPPMB"
rm fitD.exe
fi

if [ $DOANALYSISPPMB_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 0 "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$ISDOWEIGHTPPMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe 0 "$INPUTMCNPPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELNPPPMB" "$OUTPUTFILEMCSTUDYNPPPMB" "$ISDOWEIGHTPPMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$OUTPUTFILEMCSTUDYNPPPMB"
rm plotPnNP.exe
fi

if [ $DOANALYSISPPMB_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEMB"  "$OUTPUTFILEPPMB"  "$OUTPUTFILEMCSTUDYPPMB" "$OUTPUTPrescalePP" "$USEPRESCALEPPMB" "$OUTPUTFILEPlotPPMB" 0 "$LABELPPMB" "$LUMIPPMB"
rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPP_MCSTUDYCombine -eq 1 ]; then
g++ CombineplotPnNP.C $(root-config --cflags --libs) -g -o CombineplotPnNP.exe 
./CombineplotPnNP.exe "pp" "$OUTPUTFILEMCSTUDYPPMB" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEMCSTUDYNPPPMB" "$OUTPUTFILEMCSTUDYNPPP"
rm CombineplotPnNP.exe
fi

## ANALYSIS PbPb MB

OUTPUTFILEPbPbMB="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbMB.root"
OUTPUTFILEPlotPbPbMB="ROOTfiles${FILEEND}/CrossSectionFONLLPbPbMB.root"
OUTPUTFILEMCSTUDYPbPbMB="ROOTfiles${FILEEND}/MCstudiesPbPbMB.root"
OUTPUTFILEMCSTUDYNPPbPbMB="ROOTfiles${FILEEND}/MCstudiesNPPbPbMB.root"
OUTPUTFILERAAMB="ROOTfiles${FILEEND}/outputRAAMB.root"

ISMCPbPbMB=0
ISDOWEIGHTPbPbMB=3
SELGENPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPbPbMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5"
CUTPbPbMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
#CUTPbPbMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPbMB="1"
#TRGPbPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
LABELPbPbMB="PbPbMB"
LABELNPPbPbMB="NPPbPbMB"
USEPRESCALEPbPbMB=0

if [ $DONORMPbPbMB -eq 1 ]; then      
LUMIPbPbMB=1
cp config/parametersMBPbPbNorm.h parameters.h
OUTPUTFILEPlotPbPbMB="ROOTfiles${FILEEND}/CrossSectionFONLLPbPbMBNorm.root"
OUTPUTFILEPbPbMB="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbMBNorm.root"

fi

if [ $DOANALYSISPbPbMB_FONLL -eq 1 ]; then      
g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEMB" "$LABELPbPbMB"
rm Dzerodsigmadpt.exe
fi

if [ $DOANALYSISPbPbMB_FIT -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 1 "$INPUTDATAPbPbMBSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbMB" "$CUTPbPbMB"   "$SELGENPbPbMB"   "$ISMCPbPbMB"   1   "$ISDOWEIGHTPbPbMB"   "$LABELPbPbMB"  "$OUTPUTFILEPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitD.exe
fi

if [ $DOANALYSISPbPbMB_MCSTUDY -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$ISDOWEIGHTPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe 1 "$INPUTMCNPPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELNPPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$ISDOWEIGHTPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe 
./plotPnNP.exe "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm plotPnNP.exe
fi

if [ $DOANALYSISPbPbMB_CROSS -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEMB"  "$OUTPUTFILEPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$OUTPUTPrescalePbPb" "$USEPRESCALEPbPbMB" "$OUTPUTFILEPlotPbPbMB" 1 "$LABELPbPbMB" "$LUMIPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPbPb_MCSTUDYCombine -eq 1 ]; then
g++ CombineplotPnNP.C $(root-config --cflags --libs) -g -o CombineplotPnNP.exe 
./CombineplotPnNP.exe "PbPb" "$OUTPUTFILEMCSTUDYPbPbMB" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CombineplotPnNP.exe
fi


if [ $DORAAMB -eq 1 ]; then      
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe 
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB" "$OUTPUTFILERAAMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm NuclearModificationFactor.exe
fi

## COMBINE RESULTS

if [ $DOCombineCrossSectionPP -eq 1 ]; then      
g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe 
./CombineCrossSections.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPP" "0"
rm CombineCrossSections.exe
fi

if [ $DOCombineCrossSectionPbPb -eq 1 ]; then      
g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe 
./CombineCrossSections.exe "$OUTPUTFILEPlotPbPbMB" "$OUTPUTFILEPlotPbPb" "1" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CombineCrossSections.exe
fi

if [ $DOCombineRAA -eq 1 ]; then      
g++ CombineRAA.C $(root-config --cflags --libs) -g -o CombineRAA.exe 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON"  "$PREDICTIONS" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON"  "$PREDICTIONS" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 0 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON"  "$PREDICTIONS" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 1
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON"  "$PREDICTIONS" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 1
if [ $CENTPbPbMAX -eq 10 ];then
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON"  "$PREDICTIONS" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 2
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON"  "$PREDICTIONS" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 3
fi
rm CombineRAA.exe
fi

## SYSTEMATIC RESULTS

cp config/parametersAllpt.h parameters.h

if [ $DOsystematicPthatstudyPP -eq 1 ]; then   

 LABELPTHATALL="pthatallPP"
 FILEOUTPTHATALL="ROOTfiles${FILEEND}/pthatallPP.root" 
 LABELPTHATALLPTHATREWEIGHT="pthatallPPpthatreweighted"
 FILEOUTPTHATALLPTHATREWEIGHT="ROOTfiles${FILEEND}/pthatallPPpthatreweighted.root" 
 LABELPTHATALLPTWEIGHT="pthatallPPptreweighted"
 FILEOUTPTHATALLPTWEIGHT="ROOTfiles${FILEEND}/pthatallPPptreweighted.root" 

g++ FONLLweight.C $(root-config --cflags --libs) -g -o FONLLweight.exe 
#./FONLLweight.exe 0 "$INPUTMCPP" 2 100 "$LABELPTHATALL"
#./FONLLweight.exe 0 "$INPUTMCPPPthat10" 2 30 "$LABELPTHAT10"
#./FONLLweight.exe 0 "$INPUTMCPPPthat30" 2 70 "$LABELPTHAT30"
#./FONLLweight.exe 0 "$INPUTMCPPPthat50" 2 100 "$LABELPTHAT50"
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHATALL" "$FILEOUTPTHATALL" 0  "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHATALLPTHATREWEIGHT" "$FILEOUTPTHATALLPTHATREWEIGHT" 1 "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHATALLPTWEIGHT" "$FILEOUTPTHATALLPTWEIGHT" 2  "$CENTPbPbMIN" "$CENTPbPbMAX"

g++ PtShapeSystematic.C $(root-config --cflags --libs) -g -o PtShapeSystematic.exe 
./PtShapeSystematic.exe "$FILEOUTPTHATALL" "$FILEOUTPTHATALLPTWEIGHT" "ProtonProton" 0

fi

if [ $DOsystematicPthatstudyPbPb -eq 1 ]; then   
g++ FONLLweight.C $(root-config --cflags --libs) -g -o FONLLweight.exe 

 LABELPTHATALL="pthatallPbPb"
 FILEOUTPTHATALL="ROOTfiles${FILEEND}/pthatallPbPb.root" 
 LABELPTHATALLPTHATREWEIGHT="pthatallPbPbpthatreweighted"
 FILEOUTPTHATALLPTHATREWEIGHT="ROOTfiles${FILEEND}/pthatallPbPbpthatreweighted.root" 
 LABELPTHATALLPTWEIGHT="pthatallPbPbptreweighted"
 FILEOUTPTHATALLPTWEIGHT="ROOTfiles${FILEEND}/pthatallPbPbptreweighted.root" 
 LABELPTHATALLPTWEIGHTPPMC="pthatallPbPbptreweightedPPMC"
 FILEOUTPTHATALLPTWEIGHTPPMC="ROOTfiles${FILEEND}/pthatallPbPbptreweightedPPMC.root" 

#./FONLLweight.exe 0 "$INPUTMCPbPb" 2 100 "$LABELPTHATALL"
#./FONLLweight.exe 0 "$INPUTMCPbPbPthat10" 2 30 "$LABELPTHAT10"
#./FONLLweight.exe 0 "$INPUTMCPbPbPthat30" 2 70 "$LABELPTHAT30"
#./FONLLweight.exe 0 "$INPUTMCPbPbPthat50" 2 100 "$LABELPTHAT50"
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 

./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALL" "$FILEOUTPTHATALL" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALLPTHATREWEIGHT" "$FILEOUTPTHATALLPTHATREWEIGHT" 1  "$CENTPbPbMIN" "$CENTPbPbMAX"
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALLPTWEIGHT" "$FILEOUTPTHATALLPTWEIGHT" 3 "$CENTPbPbMIN" "$CENTPbPbMAX"
#./MCefficiency.exe "$INPUTMCPP"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB" "$LABELPTHATALLPTWEIGHTPPMC" "$FILEOUTPTHATALLPTWEIGHTPPMC" 0  2 100

g++ PtShapeSystematic.C $(root-config --cflags --libs) -g -o PtShapeSystematic.exe 
./PtShapeSystematic.exe "$FILEOUTPTHATALL" "$FILEOUTPTHATALLPTWEIGHT" "PbPbCent0100" 1

fi


cp config/parametersHighpt.h parameters.h

OUTPUTFILEPPMCClosure="ROOTfiles${FILEEND}/hPtSpectrumDzeroPPMCClosure.root"
OUTPUTFILEPbPbMCClosure="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbMCClosure.root"
LUMIPPMCClosure=1
ISMCPPMCClosure=1
ISDOWEIGHTPPMCClosure=0
TRGPPMCClosure="1"
LABELPPMCClosure="PPMCClosure"

LUMIPbPbMCClosure=1
ISMCPbPbMCClosure=1
ISDOWEIGHTPbPbMCClosure=0
TRGPbPbMCClosure="1"
LABELPbPbMCClosure="PbPbMCClosure"


if [ $DOFITSPPMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 0 "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMCClosure" "$CUTPP"   "$SELGENPP"   "$ISMCPPMCClosure"   "$LUMIPPMCClosure"   "$ISDOWEIGHTPPMCClosure"   "$LABELPPMCClosure"  "$OUTPUTFILEPPMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPPMCClosure" "$LABELPP"
fi

if [ $DOFITSPbPbMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 1 "$INPUTMCPbPb"  "$INPUTMCPbPb"  "$TRGPbPbMCClosure" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPbMCClosure"   "$LUMIPbPbMCClosure"   "$ISDOWEIGHTPbPbMCClosure"   "$LABELPbPbMCClosure"  "$OUTPUTFILEPbPbMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPbPbMCClosure" "$LABELPbPb"
fi

cp config/parametersLowpt.h parameters.h

OUTPUTFILEPPMBMCClosure="ROOTfiles${FILEEND}/hPtSpectrumDzeroPPMBMCClosure.root"
OUTPUTFILEPbPbMBMCClosure="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbMBMCClosure.root"
LUMIPPMBMCClosure=1
ISMCPPMBMCClosure=1
ISDOWEIGHTPPMBMCClosure=0
TRGPPMBMCClosure="1"
LABELPPMBMCClosure="PPMBMCClosure"

LUMIPbPbMBMCClosure=1
ISMCPbPbMBMCClosure=1
ISDOWEIGHTPbPbMBMCClosure=0
TRGPbPbMBMCClosure="1"
LABELPbPbMBMCClosure="PbPbMBMCClosure"

if [ $DOFITSPPMBMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 0 "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMBMCClosure" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMBMCClosure"   "$LUMIPPMBMCClosure"   "$ISDOWEIGHTPPMBMCClosure"   "$LABELPPMBMCClosure"  "$OUTPUTFILEPPMBMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPPMBMCClosure" "$LABELPPMB"
fi

if [ $DOFITSPbPbMBMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 1 "$INPUTMCPbPb"  "$INPUTMCPbPb"  "$TRGPbPbMBMCClosure" "$CUTPbPbMB"   "$SELGENPbPb"   "$ISMCPbPbMBMCClosure"   "$LUMIPbPbMBMCClosure"   "$ISDOWEIGHTPbPbMBMCClosure"   "$LABELPbPbMBMCClosure"  "$OUTPUTFILEPbPbMBMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPbPbMBMCClosure" "$LABELPbPbMB"
fi


if [ $DOsystematicTrackingPP -eq 1 ]; then      

cp config/parametersHighpt.h parameters.h

CUTPP[0]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPP[1]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
CUTPP[2]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPP[3]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"


InputType=(PPstdtrack PPnochi2 PPnohit PPlooseptresolution)
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe

for algo in 0 1 2 3
do
  
  LABEL="${InputType[algo]}"
  OUTPUTFILE="ROOTfiles${FILEEND}/hPtSpectrumDzero_${InputType[algo]}.root"
  echo $LABEL
  echo $OUTPUTFILE
  echo ${CUTPP[algo]}
  ./fitD.exe 0 "$INPUTDATAPPSKIMMED"  "$INPUTMCPP"  "$TRGPP" ${CUTPP[algo]}   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABEL"  "$OUTPUTFILE"
done
fi

if [ $DOsystematicTrackingPPMB -eq 1 ]; then      

cp config/parametersLowpt.h parameters.h

CUTPPMB[0]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12"
CUTPPMB[1]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPPMB[2]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11"
CUTPPMB[3]="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12"

InputType=(PPMBstdtrack PPMBwithchi2 PPMBwithhit PPMBtightptresolution )
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe

for algo in 0 1 2 3
do
  
  LABEL="${InputType[algo]}"
  OUTPUTFILE="ROOTfiles${FILEEND}/hPtSpectrumDzero_${InputType[algo]}.root"
  echo $LABEL
  echo $OUTPUTFILE
  echo ${CUTPPMB[algo]}
  ./fitD.exe 0 "$INPUTDATAPPMBSKIMMED"  "$INPUTMCPP"  "$TRGPPMB" ${CUTPPMB[algo]}   "$SELGENPPMB"   "$ISMCPPMB"   1   "$ISDOWEIGHTPPMB"   "$LABEL"  "$OUTPUTFILE"
done
fi

if [ $DOsystematicTrackingPbPb -eq 1 ]; then      

cp config/parametersHighpt.h parameters.h

CUTPbPb[0]="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTPbPb[1]="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTPbPb[2]="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTPbPb[3]="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&Dtrk1OriginalAlgo>3&&Dtrk1OriginalAlgo<8&&Dtrk2OriginalAlgo>3&&Dtrk2OriginalAlgo<8&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"


InputType=(PbPbstdtrack PbPbnohit  PbPbnochi2 PbPblooseptresolution)
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe

for algo in 0 1 2 3
do
  
  LABEL="${InputType[algo]}"
  OUTPUTFILE="ROOTfiles${FILEEND}/hPtSpectrumDzero_${InputType[algo]}.root"
  echo $LABEL
  echo $OUTPUTFILE
  echo ${CUTPbPb[algo]}
  ./fitD.exe 1 "$INPUTDATAPbPbSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPb" ${CUTPbPb[algo]}   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABEL"  "$OUTPUTFILE"
done
fi

if [ $DOANALYSIS_MCSTUDYDETAIL -eq 1 ]; then      

cp config/parametersHighpt.h parameters.h
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
OUTPUTFILEMCSTUDYPP="DetailEfficiency/PPnoweight.root"
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"

cp config/parametersLowpt.h parameters.h
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
OUTPUTFILEMCSTUDYPPMB="DetailEfficiency/PPMBnoweight.root"
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" 9 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
fi

if [ $DOANALYSISPbPb_MCSTUDYDETAIL -eq 1 ]; then      

cp config/parametersHighpt.h parameters.h
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
OUTPUTFILEMCSTUDYPbPb="DetailEfficiency/PbPbnoweight.root"
./MCefficiency.exe  1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
OUTPUTFILEMCSTUDYPbPb="DetailEfficiency/PbPbfinal.root"
./MCefficiency.exe  1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 2 "$CENTPbPbMIN" "$CENTPbPbMAX"
OUTPUTFILEMCSTUDYPbPb="DetailEfficiency/PbPbpthat.root"
./MCefficiency.exe  1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" 4 "$CENTPbPbMIN" "$CENTPbPbMAX"


cp config/parametersLowpt.h parameters.h
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
OUTPUTFILEMCSTUDYPbPbMB="DetailEfficiency/PbPbMBnoweight.root"
./MCefficiency.exe  1 "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" 0 "$CENTPbPbMIN" "$CENTPbPbMAX"
OUTPUTFILEMCSTUDYPbPbMB="DetailEfficiency/PbPbMBfinal.root"
./MCefficiency.exe  1 "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" 3 "$CENTPbPbMIN" "$CENTPbPbMAX"
OUTPUTFILEMCSTUDYPbPbMB="DetailEfficiency/PbPbMBpthat.root"
./MCefficiency.exe  1 "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" 4 "$CENTPbPbMIN" "$CENTPbPbMAX"
rm MCefficiency.exe
fi
