#!/bin/bash

#source clean.sh
CENTPbPbMIN=${1:-0}
CENTPbPbMAX=${2:-100}
#
if [ $CENTPbPbMIN -eq 0 ] && [ $CENTPbPbMAX -eq 100 ]
then
    FILEEND=""
elif [ $CENTPbPbMIN -eq 0 ] && [ $CENTPbPbMAX -eq 10 ]
then
    FILEEND="Cent10"
else
    echo -e "error: invalid centrality range"
    exit 1
fi

#Central point of the analysis

DOANALYSISPP_SAVEHIST=0
DOANALYSISPP_DRAWFIT=0
DOANALYSISPP_TOYMC=0
DOANALYSISPP_CLOSURE=1

DOANALYSISPbPb_SAVEHIST=0
DOANALYSISPbPb_DRAWFIT=0
DOANALYSISPbPb_TOYMC=0
DOANALYSISPbPb_CLOSURE=1

DOANALYSISPPMB_SAVEHIST=0
DOANALYSISPPMB_DRAWFIT=0
DOANALYSISPPMB_TOYMC=0
DOANALYSISPPMB_CLOSURE=1

DOANALYSISPbPbMB_SAVEHIST=0
DOANALYSISPbPbMB_DRAWFIT=0
DOANALYSISPbPbMB_TOYMC=0
DOANALYSISPbPbMB_CLOSURE=1

#

## PP MONTE CARLO
INPUTMCPP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"  
INPUTMCNPPP="/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

## PP DATA 
INPUTDATAPPSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson_skim_myskim.root"
INPUTDATAPPMBSKIMMED="/data/jisun/ppMB2015fullstats/skim_Dntuple_crab_pp_MinimumBias1to20_AOD_D0Dsy1p1_tkpt0p5eta2p0_04122016.root"

## PbPb MONTE CARLO
INPUTMCPbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"
INPUTMCNPPbPb="/data/HeavyFlavourRun2/MC2015/Dntuple/PbPb/ntD_EvtBase_20160513_DfinderMC_PbPb_20160502_dPt1tkPt0p5_D0_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root"

## PbPb DATA 
INPUTDATAPbPbGJSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_skimmed.root"
INPUTDATAPbPbTOSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/Dntuple_crab_PbPb_HIHardProbes_tkpt6p0eta1p5_Dy1p1_EvtPlaneCalibration_v2v3etagap_05142016_TrackerOnly_JSON.root"
INPUTDATAPbPbMBSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/ntDntuple_PbPb_MinimumBias_GoldenjsonNTrackerOnlyjson_skimOPTcuts.root"

#

PLOTFOLDERS=("plotFits" "plotFitsMC" "plotFitsMCSignal" "ROOTfiles${FILEEND}" "plotToyMC" "plotClosure")
for ifolder in ${PLOTFOLDERS[@]}
do
    if [ ! -d $ifolder ]
    then
        mkdir $ifolder
    fi
done

#

## ANALYSIS PP TRIGGERED

cp config/parametersHighpt.h parameters.h

OUTPUTFILEFITMASSPP="ROOTfiles${FILEEND}/hMassFitPP"
OUTPUTFILESTATPP="ROOTfiles${FILEEND}/hFitParPP"
OUTPUTFILETOYMCPP="ROOTfiles${FILEEND}/hToyMCPP"

CUTPP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUTGENPP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt8_v1&&Dpt>10&&Dpt<20)||(HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
LABELPP="PP"

if [ $DOANALYSISPP_SAVEHIST -eq 1 ]
then
    g++ fitDsavehist.C $(root-config --cflags --libs) -g -o fitDsavehist.exe 
    ./fitDsavehist.exe "$INPUTDATAPPSKIMMED" "$INPUTMCPP" "$TRGPP" "$CUTPP" "$LABELPP" "$OUTPUTFILEFITMASSPP"
    rm fitDsavehist.exe
fi 

if [ $DOANALYSISPP_DRAWFIT -eq 1 ]
then
    g++ fitDfithist.C $(root-config --cflags --libs) -g -o fitDfithist.exe 
    ./fitDfithist.exe "$OUTPUTFILEFITMASSPP" "$OUTPUTFILESTATPP" "$LABELPP"
    rm fitDfithist.exe
fi 

if [ $DOANALYSISPP_TOYMC -eq 1 ]
then
    g++ fitDtoyMC.C $(root-config --cflags --libs) -g -o fitDtoyMC.exe 
    ./fitDtoyMC.exe "$OUTPUTFILEFITMASSPP" "$OUTPUTFILETOYMCPP" "$LABELPP"
    rm fitDtoyMC.exe
fi 

if [ $DOANALYSISPP_CLOSURE -eq 1 ]
then
    g++ fitDclosure.C $(root-config --cflags --libs) -g -o fitDclosure.exe 
    ./fitDclosure.exe "$OUTPUTFILESTATPP" "$LABELPP"
    rm fitDclosure.exe
fi 

rm parameters.h

## ANALYSIS PbPb TRIGGERED

cp config/parametersHighpt.h parameters.h

OUTPUTFILEFITMASSPbPbGJ="ROOTfiles${FILEEND}/hMassFitPbPbGJ"
OUTPUTFILEFITMASSPbPbTO="ROOTfiles${FILEEND}/hMassFitPbPbTO"
OUTPUTFILEFITMASSPbPb="ROOTfiles${FILEEND}/hMassFitPbPb"
OUTPUTFILESTATPbPbGJ="ROOTfiles${FILEEND}/hFitParPbPbGJ"
OUTPUTFILESTATPbPbTO="ROOTfiles${FILEEND}/hFitParPbPbTO"
OUTPUTFILESTATPbPb="ROOTfiles${FILEEND}/hFitParPbPb"
OUTPUTFILETOYMCPbPb="ROOTfiles${FILEEND}/hToyMCPbPb"

CUTPbPb="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTGENPbPb="abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
TRGPbPbGJ="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
TRGPbPbTO="((HLT_HIDmesonHITrackingGlobal_Dpt20_v2&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
LABELPbPb="PbPb"

if [ $DOANALYSISPbPb_SAVEHIST -eq 1 ]
then
    g++ fitDsavehist.C $(root-config --cflags --libs) -g -o fitDsavehist.exe 
    ./fitDsavehist.exe "$INPUTDATAPbPbTOSKIMMED" "$INPUTMCPbPb" "$TRGPbPbTO" "$CUTPbPb" "$LABELPbPb" "$OUTPUTFILEFITMASSPbPbTO" "$CENTPbPbMIN" "$CENTPbPbMAX"
    ./fitDsavehist.exe "$INPUTDATAPbPbGJSKIMMED" "$INPUTMCPbPb" "$TRGPbPbGJ" "$CUTPbPb" "$LABELPbPb" "$OUTPUTFILEFITMASSPbPbGJ" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDsavehist.exe

    g++ combineGJTOfitD.C $(root-config --cflags --libs) -g -o combineGJTOfitD.exe 
    ./combineGJTOfitD.exe "$OUTPUTFILEFITMASSPbPbGJ" "$OUTPUTFILEFITMASSPbPbTO" "$OUTPUTFILEFITMASSPbPb"
    rm combineGJTOfitD.exe
fi

if [ $DOANALYSISPbPb_DRAWFIT -eq 1 ]
then
    g++ fitDfithist.C $(root-config --cflags --libs) -g -o fitDfithist.exe 
    #./fitDfithist.exe "$OUTPUTFILEFITMASSPbPbGJ" "$OUTPUTFILESTATPbPbGJ" "${LABELPbPb}GJ" "$CENTPbPbMIN" "$CENTPbPbMAX"
    #./fitDfithist.exe "$OUTPUTFILEFITMASSPbPbTO" "$OUTPUTFILESTATPbPbTO" "${LABELPbPb}TO" "$CENTPbPbMIN" "$CENTPbPbMAX"
    ./fitDfithist.exe "$OUTPUTFILEFITMASSPbPb" "$OUTPUTFILESTATPbPb" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDfithist.exe
fi 

if [ $DOANALYSISPbPb_TOYMC -eq 1 ]
then
    g++ fitDtoyMC.C $(root-config --cflags --libs) -g -o fitDtoyMC.exe 
    ./fitDtoyMC.exe "$OUTPUTFILEFITMASSPbPb" "$OUTPUTFILETOYMCPbPb" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDtoyMC.exe
fi 

if [ $DOANALYSISPbPb_CLOSURE -eq 1 ]
then
    g++ fitDclosure.C $(root-config --cflags --libs) -g -o fitDclosure.exe 
    ./fitDclosure.exe "$OUTPUTFILESTATPbPb" "$LABELPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDclosure.exe
fi 

rm parameters.h

## ANALYSIS PP MB

cp config/parametersLowpt.h parameters.h

OUTPUTFILEFITMASSPPMB="ROOTfiles${FILEEND}/hMassFitPPMB"
OUTPUTFILESTATPPMB="ROOTfiles${FILEEND}/hFitParPPMB"
OUTPUTFILETOYMCPPMB="ROOTfiles${FILEEND}/hToyMCPPMB"

CUTPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTGENPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"

if [ $DOANALYSISPPMB_SAVEHIST -eq 1 ]
then
    g++ fitDsavehist.C $(root-config --cflags --libs) -g -o fitDsavehist.exe 
    ./fitDsavehist.exe "$INPUTDATAPPMBSKIMMED" "$INPUTMCPP" "$TRGPPMB" "$CUTPPMB" "$LABELPPMB" "$OUTPUTFILEFITMASSPPMB"
    rm fitDsavehist.exe
fi

if [ $DOANALYSISPPMB_DRAWFIT -eq 1 ]
then
    g++ fitDfithist.C $(root-config --cflags --libs) -g -o fitDfithist.exe 
    ./fitDfithist.exe "$OUTPUTFILEFITMASSPPMB" "$OUTPUTFILESTATPPMB" "$LABELPPMB"
    rm fitDfithist.exe
fi 

if [ $DOANALYSISPPMB_TOYMC -eq 1 ]
then
    g++ fitDtoyMC.C $(root-config --cflags --libs) -g -o fitDtoyMC.exe
    ./fitDtoyMC.exe "$OUTPUTFILEFITMASSPPMB" "$OUTPUTFILETOYMCPPMB" "$LABELPPMB"
    rm fitDtoyMC.exe
fi

if [ $DOANALYSISPPMB_CLOSURE -eq 1 ]
then
    g++ fitDclosure.C $(root-config --cflags --libs) -g -o fitDclosure.exe 
    ./fitDclosure.exe "$OUTPUTFILESTATPPMB" "$LABELPPMB"
    rm fitDclosure.exe
fi 

rm parameters.h

## ANALYSIS PbPb MB

cp config/parametersLowpt.h parameters.h

OUTPUTFILEFITMASSPbPbMB="ROOTfiles${FILEEND}/hMassFitPbPbMB"
OUTPUTFILESTATPbPbMB="ROOTfiles${FILEEND}/hFitParPbPbMB"
OUTPUTFILETOYMCPbPbMB="ROOTfiles${FILEEND}/hToyMCPbPbMB"

CUTPbPbMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTGENPbPbMB="abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
TRGPbPbMB="1"
LABELPbPbMB="PbPbMB"

if [ $DOANALYSISPbPbMB_SAVEHIST -eq 1 ]
then
    g++ fitDsavehist.C $(root-config --cflags --libs) -g -o fitDsavehist.exe 
    ./fitDsavehist.exe "$INPUTDATAPbPbMBSKIMMED" "$INPUTMCPbPb" "$TRGPbPbMB" "$CUTPbPbMB" "$LABELPbPbMB" "$OUTPUTFILEFITMASSPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDsavehist.exe
fi

if [ $DOANALYSISPbPbMB_DRAWFIT -eq 1 ]
then
    g++ fitDfithist.C $(root-config --cflags --libs) -g -o fitDfithist.exe 
    ./fitDfithist.exe "$OUTPUTFILEFITMASSPbPbMB" "$OUTPUTFILESTATPbPbMB" "$LABELPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDfithist.exe
fi 

if [ $DOANALYSISPbPbMB_TOYMC -eq 1 ]
then
    g++ fitDtoyMC.C $(root-config --cflags --libs) -g -o fitDtoyMC.exe
    ./fitDtoyMC.exe "$OUTPUTFILEFITMASSPbPbMB" "$OUTPUTFILETOYMCPbPbMB" "$LABELPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDtoyMC.exe
fi

if [ $DOANALYSISPbPbMB_CLOSURE -eq 1 ]
then
    g++ fitDclosure.C $(root-config --cflags --libs) -g -o fitDclosure.exe 
    ./fitDclosure.exe "$OUTPUTFILESTATPbPbMB" "$LABELPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDclosure.exe
fi 

rm parameters.h

## COMBINE

