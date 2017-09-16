#!/bin/bash
#source clean.sh
CENTPbPbMIN=${1:-0}
CENTPbPbMAX=${2:-100}
#

LUMIPP=27.4
LUMIPPMB=0.0381639 # from brilcalc
LUMIPbPbGJ=15.5020   # from brilcalc
LUMIPbPbTO=4.63386   # from brilcalc
LUMIPbPbMB=1.6419125
FILEEND=""
if [ $CENTPbPbMAX -eq 10 ]
then
    LUMIPbPbGJ=6.50280
    LUMIPbPbTO=1.94635
    LUMIPbPbMB=0.6891959
    FILEEND="Cent10"
fi

#Central point of the analysis

DOANALYSISPP_FONLL=0
DOANALYSISPP_TRGCOMBINATION=0
DOANALYSISPP_FIT=0
DOANALYSISPP_DRAWFIT=0
DOANALYSISPP_MCSTUDY=0
DOANALYSISPP_CROSS=0

DOANALYSISPbPb_FONLL=0
DOANALYSISPbPb_TRGCOMBINATION=0
DOANALYSISPbPb_FIT=0
DOANALYSISPbPb_DRAWFIT=0
DOANALYSISPbPb_MCSTUDY=0
DOANALYSISPbPb_CROSS=0
DOANALYSISPbPb_COMBGJTO=0

DOANALYSISPPMB_FONLL=0
DOANALYSISPPMB_FIT=0
DOANALYSISPPMB_DRAWFIT=0
DOANALYSISPPMB_MCSTUDY=0
DOANALYSISPPMB_CROSS=0

DOANALYSISPbPbMB_FONLL=0
DOANALYSISPbPbMB_FIT=0
DOANALYSISPbPbMB_DRAWFIT=0
DOANALYSISPbPbMB_MCSTUDY=0
DOANALYSISPbPbMB_CROSS=0

DOANALYSISPP_MCSTUDYCombine=0
DOANALYSISPbPb_MCSTUDYCombine=0

DORAA=0
DORAAMB=0

DOCombineCrossSectionPP=0
DOCombineCrossSectionPbPb=0
DOCombineRAA=1

#
DOCombineCrossSectionPPnPbPb=0

#

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLDATINPUTBtoD="pp_Btod0meson_5TeV_y1"
FONLLDATINPUTB="pp_Bmeson_5TeV_y1"

#

## PP MONTE CARLO
NTUPLAPYTHIA="/data/HeavyFlavourRun2/BtoDPythia/treefile_ptall_11january2016.root"
INPUTMCPP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"  
INPUTMCNPPP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

## PP DATA 
INPUTDATAPPSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson_skim_myskim.root"
INPUTDATAPPUNSKIMMED="/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson.root"
INPUTDATAPPMBUNSKIMMED="/data/jisun/ppMB2015fullstats/skim_Dntuple_crab_pp_MinimumBias1to20_AOD_D0Dsy1p1_tkpt0p5eta2p0_04122016.root"
INPUTDATAPPMBSKIMMED="/data/jisun/ppMB2015fullstats/skim_Dntuple_crab_pp_MinimumBias1to20_AOD_D0Dsy1p1_tkpt0p5eta2p0_04122016.root"

## PbPb MONTE CARLO
INPUTMCPbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCNPPbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

## PbPb DATA 
INPUTDATAPbPbGJSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_skimmed.root"
INPUTDATAPbPbGJUNSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON.root"
INPUTDATAPbPbTOSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/Dntuple_crab_PbPb_HIHardProbes_tkpt6p0eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
INPUTDATAPbPbTOUNSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/Dntuple_crab_PbPb_HIHardProbes_tkpt6p0eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
INPUTDATAPbPbMBUNSKIMMED="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"
INPUTDATAPbPbMBSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/ntDntuple_PbPb_MinimumBias_GoldenjsonNTrackerOnlyjson_skimOPTcuts.root"

#

PLOTFOLDERS=("plotCrossSection" "plotEff" "plotFONLL" "plotFits" "plotFitsYield" "plotFitsPaper" "plotOthers" "plotRAA" "ROOTfiles${FILEEND}" "plotPaper")
for ifolder in ${PLOTFOLDERS[@]}
do
    if [ ! -d $ifolder ]
    then
        mkdir $ifolder
    fi
done

#

## ANALYSIS PP TRIGGERED

FONLLOUTPUTFILE="ROOTfiles${FILEEND}/output_pp_d0meson_5TeV_y1.root"
FONLLOUTPUTFILEBtoD="ROOTfiles${FILEEND}/output_pp_Btod0meson_5TeV_y1.root"
FONLLOUTPUTFILEInclusiveD="ROOTfiles${FILEEND}/output_inclusiveDd0meson_5TeV_y1.root"
FONLLOUTPUTFILEB="ROOTfiles${FILEEND}/output_pp_Bmeson_5TeV_y1.root"
OUTPUTFILEPP="ROOTfiles${FILEEND}/hPtSpectrumDzeroPP.root"
OUTPUTFILEFITMASSPP="ROOTfiles${FILEEND}/hMassFitPP"
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

cp config/parametersHighpt.h parameters.h

if [ $DOANALYSISPP_FONLL -eq 1 ]; then
    g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe  || return 1
    ./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPP"
    ./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoD" "$LABELPP"
    rm Dzerodsigmadpt.exe
fi 

if [ $DOANALYSISPP_TRGCOMBINATION -eq 1 ]; then      
    g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe || return 1
    ./triggercombination.exe 0 "$INPUTDATAPPUNSKIMMED" "$CUTFORTRIGGERPRESCALEPP" "$OUTPUTPrescalePP" 0
    rm triggercombination.exe
fi 

if [ $DOANALYSISPP_FIT -eq 1 ]; then      
    g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe || return 1
    ./fitD.exe 0 "$INPUTDATAPPSKIMMED"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP" "$OUTPUTFILEFITMASSPP"
    rm fitD.exe
fi 

if [ $DOANALYSISPP_DRAWFIT -eq 1 ]; then      
    g++ fitDdraw.C $(root-config --cflags --libs) -g -o fitDdraw.exe || return 1
    ./fitDdraw.exe 0 "$OUTPUTFILEFITMASSPP" "$LABELPP"
    rm fitDdraw.exe
fi 

if [ $DOANALYSISPP_MCSTUDY -eq 1 ]; then      
    g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe || return 1
    ./MCefficiency.exe  0 "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
    ./MCefficiency.exe  0 "$INPUTMCNPPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELNPPP" "$OUTPUTFILEMCSTUDYNPPP" "$ISDOWEIGHTPP" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm MCefficiency.exe
    g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe || return 1
    ./plotPnNP.exe "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEMCSTUDYNPPP"
    rm plotPnNP.exe
fi


if [ $DOANALYSISPP_CROSS -eq 1 ]; then      
    g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe || return 1
    ./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPP"  "$OUTPUTFILEMCSTUDYPP" "$OUTPUTPrescalePP" "$USEPRESCALEPP" "$OUTPUTFILEPlotPP" 0 "$LABELPP" "$LUMIPP" 
    rm CrossSectionRatio.exe
fi

rm parameters.h

## ANALYSIS PbPb TRIGGERED

cp config/parametersHighpt.h parameters.h

OUTPUTPrescalePbPbGJ="ROOTfiles${FILEEND}/prescalePbPbGJ.root"
OUTPUTPrescalePbPbTO="ROOTfiles${FILEEND}/prescalePbPbTO.root"
OUTPUTFILEMCSTUDYPbPb="ROOTfiles${FILEEND}/MCstudiesPbPb.root"
OUTPUTFILEMCSTUDYNPPbPb="ROOTfiles${FILEEND}/MCstudiesNPPbPb.root"
OUTPUTFILEPbPbGJ="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbGJ.root"
OUTPUTFILEFITMASSPbPbGJ="ROOTfiles${FILEEND}/hMassFitPbPbGJ"
OUTPUTFILEPbPbTO="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbTO.root"
OUTPUTFILEFITMASSPbPbTO="ROOTfiles${FILEEND}/hMassFitPbPbTO"
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


if [ $DOANALYSISPbPb_FONLL -eq 1 ]; then
    g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe || return 1
    ./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPbPb"
    rm Dzerodsigmadpt.exe
fi

if [ $DOANALYSISPbPb_TRGCOMBINATION -eq 1 ]; then      
    g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe || return 1
    ./triggercombination.exe 1 "$INPUTDATAPbPbGJUNSKIMMED" "$CUTFORTRIGGERPRESCALEPbPb" "$OUTPUTPrescalePbPbGJ" 1
    ./triggercombination.exe 1 "$INPUTDATAPbPbTOUNSKIMMED" "$CUTFORTRIGGERPRESCALEPbPb" "$OUTPUTPrescalePbPbTO" 0
    rm triggercombination.exe
fi

if [ $DOANALYSISPbPb_FIT -eq 1 ]; then      
    g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe || return 1
    ./fitD.exe 1 "$INPUTDATAPbPbTOSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbTO" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"  "$LABELPbPb"  "$OUTPUTFILEPbPbTO" "$OUTPUTFILEFITMASSPbPbTO" "$CENTPbPbMIN" "$CENTPbPbMAX" 0
    ./fitD.exe 1 "$INPUTDATAPbPbGJSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbGJ" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"  "$LABELPbPb"  "$OUTPUTFILEPbPbGJ" "$OUTPUTFILEFITMASSPbPbGJ" "$CENTPbPbMIN" "$CENTPbPbMAX" 1
    rm fitD.exe
    g++ combineGJTOfitD.C $(root-config --cflags --libs) -g -o combineGJTOfitD.exe || return 1
    ./combineGJTOfitD.exe 1 "$OUTPUTFILEFITMASSPbPbGJ" "$OUTPUTFILEFITMASSPbPbTO" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm combineGJTOfitD.exe
fi

if [ $DOANALYSISPbPb_DRAWFIT -eq 1 ]; then      
    g++ fitDdraw.C $(root-config --cflags --libs) -g -o fitDdraw.exe || return 1
    ./fitDdraw.exe 1 "$OUTPUTFILEFITMASSPbPbTO" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX" 0
    ./fitDdraw.exe 1 "$OUTPUTFILEFITMASSPbPbGJ" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX" 1
    rm fitDdraw.exe
    g++ combineGJTOfitD.C $(root-config --cflags --libs) -g -o combineGJTOfitD.exe || return 1
    ./combineGJTOfitD.exe 1 "$OUTPUTFILEFITMASSPbPbGJ" "$OUTPUTFILEFITMASSPbPbTO" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm combineGJTOfitD.exe
fi 


if [ $DOANALYSISPbPb_MCSTUDY -eq 1 ]; then      
    g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe || return 1
    ./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    ./MCefficiency.exe 1 "$INPUTMCNPPbPb"  "$SELGENPbPb" "$SELGENACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELNPPbPb" "$OUTPUTFILEMCSTUDYNPPbPb" "$ISDOWEIGHTPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm MCefficiency.exe
    g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe || return 1
    ./plotPnNP.exe "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTFILEMCSTUDYNPPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm plotPnNP.exe
fi

if [ $DOANALYSISPbPb_CROSS -eq 1 ]; then      
    g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe || return 1
    ./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPbPbGJ" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTPrescalePbPbGJ" "$USEPRESCALEPbPb" "$OUTPUTFILEPlotPbPbGJ" 1 "$LABELPbPb" "$LUMIPbPbGJ" "$CENTPbPbMIN" "$CENTPbPbMAX"
    ./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPbPbTO" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTPrescalePbPbTO" "$USEPRESCALEPbPb" "$OUTPUTFILEPlotPbPbTO" 1 "$LABELPbPb" "$LUMIPbPbTO" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPbPb_COMBGJTO -eq 1 ]; then
    g++ combineGJTO.C $(root-config --cflags --libs) -g -o combineGJTO.exe || return 1
    ./combineGJTO.exe "$OUTPUTFILEPlotPbPbGJ" "$OUTPUTFILEPlotPbPbTO" "$OUTPUTFILEPlotPbPb" "$LUMIPbPbGJ" "$LUMIPbPbTO"
    rm combineGJTO.exe
fi

if [ $DORAA -eq 1 ]; then      
    g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe || return 1 
    ./NuclearModificationFactor.exe "$OUTPUTFILEPlotPP" "$OUTPUTFILEPlotPbPb"  "$LABELPbPb" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm NuclearModificationFactor.exe
fi

rm parameters.h

## ANALYSIS PP MB

cp config/parametersLowpt.h parameters.h

FONLLOUTPUTFILEMB="ROOTfiles${FILEEND}/output_pp_d0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBtoDMB="ROOTfiles${FILEEND}/output_pp_Btod0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEInclusiveDMB="ROOTfiles${FILEEND}/output_inclusiveDd0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBMB="ROOTfiles${FILEEND}/output_pp_Bmeson_5TeV_y1MB.root"
OUTPUTFILEPPMB="ROOTfiles${FILEEND}/hPtSpectrumDzeroPPMB.root"
OUTPUTFILEFITMASSPPMB="ROOTfiles${FILEEND}/hMassFitPPMB"
OUTPUTFILEPlotPPMB="ROOTfiles${FILEEND}/CrossSectionFONLLPPMB.root"
OUTPUTFILEMCSTUDYPPMB="ROOTfiles${FILEEND}/MCstudiesPPMB.root"
OUTPUTFILEMCSTUDYNPPPMB="ROOTfiles${FILEEND}/MCstudiesNPPPMB.root"

ISMCPPMB=0
ISDOWEIGHTPPMB=1
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5"
CUTPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"
LABELNPPPMB="NPPPMB"
USEPRESCALEPPMB=0


if [ $DOANALYSISPPMB_FONLL -eq 1 ]; then
    g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe || return 1 
    ./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEMB" "$LABELPPMB"
    ./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoDMB" "$LABELPPMB"
    rm Dzerodsigmadpt.exe
fi

if [ $DOANALYSISPPMB_FIT -eq 1 ]; then      
    g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe || return 1 
    ./fitD.exe 0 "$INPUTDATAPPMBSKIMMED"  "$INPUTMCPP"  "$TRGPPMB" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMB"   1   "$ISDOWEIGHTPPMB"   "$LABELPPMB"  "$OUTPUTFILEPPMB" "$OUTPUTFILEFITMASSPPMB"
    rm fitD.exe
fi

if [ $DOANALYSISPPMB_DRAWFIT -eq 1 ]; then      
    g++ fitDdraw.C $(root-config --cflags --libs) -g -o fitDdraw.exe || return 1 
    ./fitDdraw.exe 0 "$OUTPUTFILEFITMASSPPMB" "$LABELPPMB"
    rm fitDdraw.exe
fi 

if [ $DOANALYSISPPMB_MCSTUDY -eq 1 ]; then      
    g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe || return 1 
    ./MCefficiency.exe 0 "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$ISDOWEIGHTPPMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    ./MCefficiency.exe 0 "$INPUTMCNPPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELNPPPMB" "$OUTPUTFILEMCSTUDYNPPPMB" "$ISDOWEIGHTPPMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm MCefficiency.exe
    g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe || return 1 
    ./plotPnNP.exe "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$OUTPUTFILEMCSTUDYNPPPMB"
    rm plotPnNP.exe
fi

if [ $DOANALYSISPPMB_CROSS -eq 1 ]; then      
    g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe || return 1 
    ./CrossSectionRatio.exe "$FONLLOUTPUTFILEMB"  "$OUTPUTFILEPPMB"  "$OUTPUTFILEMCSTUDYPPMB" "$OUTPUTPrescalePP" "$USEPRESCALEPPMB" "$OUTPUTFILEPlotPPMB" 0 "$LABELPPMB" "$LUMIPPMB"
    rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPP_MCSTUDYCombine -eq 1 ]; then
    g++ CombineplotPnNP.C $(root-config --cflags --libs) -g -o CombineplotPnNP.exe || return 1 
    ./CombineplotPnNP.exe "pp" "$OUTPUTFILEMCSTUDYPPMB" "$OUTPUTFILEMCSTUDYPP" "$OUTPUTFILEMCSTUDYNPPPMB" "$OUTPUTFILEMCSTUDYNPPP"
    rm CombineplotPnNP.exe
fi

rm parameters.h

## ANALYSIS PbPb MB

cp config/parametersLowpt.h parameters.h

OUTPUTFILEPbPbMB="ROOTfiles${FILEEND}/hPtSpectrumDzeroPbPbMB.root"
OUTPUTFILEFITMASSPbPbMB="ROOTfiles${FILEEND}/hMassFitPbPbMB"
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
TRGPbPbMB="1"
LABELPbPbMB="PbPbMB"
LABELNPPbPbMB="NPPbPbMB"
USEPRESCALEPbPbMB=0

if [ $DOANALYSISPbPbMB_FONLL -eq 1 ]; then      
    g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe || return 1 
    ./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEMB" "$LABELPbPbMB"
    rm Dzerodsigmadpt.exe
fi

if [ $DOANALYSISPbPbMB_FIT -eq 1 ]; then      
    g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe || return 1 
    ./fitD.exe 1 "$INPUTDATAPbPbMBSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbMB" "$CUTPbPbMB"   "$SELGENPbPbMB"   "$ISMCPbPbMB"   1   "$ISDOWEIGHTPbPbMB"   "$LABELPbPbMB"  "$OUTPUTFILEPbPbMB" "$OUTPUTFILEFITMASSPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitD.exe
fi

if [ $DOANALYSISPbPbMB_DRAWFIT -eq 1 ]; then      
    g++ fitDdraw.C $(root-config --cflags --libs) -g -o fitDdraw.exe || return 1 
    ./fitDdraw.exe 1 "$OUTPUTFILEFITMASSPbPbMB" "$LABELPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDdraw.exe
fi 

if [ $DOANALYSISPbPbMB_MCSTUDY -eq 1 ]; then      
    g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe || return 1 
    ./MCefficiency.exe 1 "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$ISDOWEIGHTPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    ./MCefficiency.exe 1 "$INPUTMCNPPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELNPPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$ISDOWEIGHTPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm MCefficiency.exe
    g++ plotPnNP.C $(root-config --cflags --libs) -g -o plotPnNP.exe || return 1 
    ./plotPnNP.exe "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm plotPnNP.exe
fi

if [ $DOANALYSISPbPbMB_CROSS -eq 1 ]; then      
    g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe || return 1 
    ./CrossSectionRatio.exe "$FONLLOUTPUTFILEMB"  "$OUTPUTFILEPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$OUTPUTPrescalePbPb" "$USEPRESCALEPbPbMB" "$OUTPUTFILEPlotPbPbMB" 1 "$LABELPbPbMB" "$LUMIPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm CrossSectionRatio.exe
fi

if [ $DOANALYSISPbPb_MCSTUDYCombine -eq 1 ]; then
    g++ CombineplotPnNP.C $(root-config --cflags --libs) -g -o CombineplotPnNP.exe || return 1 
    ./CombineplotPnNP.exe "PbPb" "$OUTPUTFILEMCSTUDYPbPbMB" "$OUTPUTFILEMCSTUDYPbPb" "$OUTPUTFILEMCSTUDYNPPbPbMB" "$OUTPUTFILEMCSTUDYNPPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm CombineplotPnNP.exe
fi

if [ $DORAAMB -eq 1 ]; then      
    g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe || return 1 
    ./NuclearModificationFactor.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB" "$OUTPUTFILERAAMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm NuclearModificationFactor.exe
fi

rm parameters.h

## COMBINE RESULTS

if [ $DOCombineCrossSectionPP -eq 1 ]; then      
    g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe || return 1 
    ./CombineCrossSections.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPP" "0"
    rm CombineCrossSections.exe
fi

if [ $DOCombineCrossSectionPbPb -eq 1 ]; then      
    g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe || return 1 
    ./CombineCrossSections.exe "$OUTPUTFILEPlotPbPbMB" "$OUTPUTFILEPlotPbPb" "1" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm CombineCrossSections.exe
fi

if [ $DOCombineRAA -eq 1 ]; then      
    g++ CombineRAA.C $(root-config --cflags --libs) -g -o CombineRAA.exe || return 1 
    ./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 0 0 0
    if [ $CENTPbPbMAX -eq 100 ]; then
        ./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 1 0 0 0 
        ./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 1 1 0 0 
        ./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 1 2 0 0 
    fi
    if [ $CENTPbPbMAX -eq 10 ];then
        ./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 1 0 0 0 0
        ./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 0 0 1
    fi
    ./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CENTPbPbMIN" "$CENTPbPbMAX" 0 0 0 1 0

    rm CombineRAA.exe
fi

if [ $DOCombineCrossSectionPPnPbPb -eq 1 ]; then      
    g++ CombineCrossSectionsPPnPbPb.C $(root-config --cflags --libs) -g -o CombineCrossSectionsPPnPbPb.exe || return 1 
    ./CombineCrossSectionsPPnPbPb.exe "ROOTfiles/CrossSectionFONLLPPMB.root" "ROOTfiles/CrossSectionFONLLPP.root" "ROOTfiles/CrossSectionFONLLPbPbMB.root" "ROOTfiles/CrossSectionFONLLPbPb.root" "ROOTfilesCent10/CrossSectionFONLLPbPbMB.root" "ROOTfilesCent10/CrossSectionFONLLPbPb.root"
    rm CombineCrossSectionsPPnPbPb.exe
fi

#

PAPERFILES=("plotFitsPaper/DMassPPMB_4.pdf" "plotFitsPaper/DMassPbPbMB_0_100_4.pdf" "plotFitsPaper/DMassPP_2.pdf" "plotFitsPaper/DMassPbPb_0_100_2_.pdf" "plotCrossSection/CrossSectionComparison_Calculation_BothRatio_PP.pdf" "plotCrossSection/CrossSection_ComparisonPPnPbPb_noRatio_Long.pdf" "plotRAA/canvasRAA_charged_cent_0_10.pdf" "plotRAA/canvasRAA_charged_BnNjpsi_cent_0_100.pdf" "plotRAA/canvasRAA_theoryAll_cent_0_10.pdf" "plotRAA/canvasRAA_theoryAll_cent_0_100.pdf")

for i in ${PAPERFILES[@]}
{
    if [ -f $i ]
    then
        cp $i plotPaper/
    fi
}
