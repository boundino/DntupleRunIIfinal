#!/bin/bash

#source clean.sh
CENTPbPbMIN=${1:-0}
CENTPbPbMAX=${2:-100}
#
NSMEAR=1000
NGEN=1000


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

#
DOANALYSISPP_SAVEHISTPICKEVT=0
DOANALYSISPP_TOYMCPICKEVT=0
DOANALYSISPP_DRAWTOYMCPICKEVT=1

DOANALYSISPbPb_SAVEHISTPICKEVT=0
DOANALYSISPbPb_TOYMCPICKEVT=0
DOANALYSISPbPb_DRAWTOYMCPICKEVT=1

DOANALYSISPPMB_SAVEHISTPICKEVT=0
DOANALYSISPPMB_TOYMCPICKEVT=0
DOANALYSISPPMB_DRAWTOYMCPICKEVT=1

DOANALYSISPbPbMB_SAVEHISTPICKEVT=0
DOANALYSISPbPbMB_TOYMCPICKEVT=0
DOANALYSISPbPbMB_DRAWTOYMCPICKEVT=1

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

PLOTFOLDERS=("ROOTfiles${FILEEND}" "plotToyMCpickevt")
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

PTMIN=(20 25 30 40 60)
PTMAX=(25 30 40 60 100)
nPTBINS=${#PTMIN[@]}
#

OUTPUTFILEEFFPP="ROOTfiles${FILEEND}/hEffPP"
OUTPUTFILETOYMCPICKEVTPP="ROOTfiles${FILEEND}/hToyMCpickevtPP"

CUTPP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUTGENPP="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
LABELPP="PP"

if [ $DOANALYSISPP_SAVEHISTPICKEVT -eq 1 ]
then
    g++ fitDsavehistpickevt.C $(root-config --cflags --libs) -g -o fitDsavehistpickevt.exe 
    ./fitDsavehistpickevt.exe "$INPUTMCPP" "$CUTPP" "$CUTGENPP" "$LABELPP" "$OUTPUTFILEEFFPP"
    rm fitDsavehistpickevt.exe
fi 

i=0
while ((i<$nPTBINS))
do
    if [ $DOANALYSISPP_TOYMCPICKEVT -eq 1 ]
    then
        g++ fitDtoyMCpickevt.C $(root-config --cflags --libs) -g -o fitDtoyMCpickevt.exe 
        ./fitDtoyMCpickevt.exe "$INPUTMCPP" "$OUTPUTFILEEFFPP" "${OUTPUTFILETOYMCPICKEVTPP}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPP" "${PTMIN[i]}" "${PTMAX[i]}" "$NSMEAR" "$NGEN"
        rm fitDtoyMCpickevt.exe
    fi 

    if [ $DOANALYSISPP_DRAWTOYMCPICKEVT -eq 1 ]
    then
        g++ drawtoyMCpickevt.C $(root-config --cflags --libs) -g -o drawtoyMCpickevt.exe 
        if [ -f "${OUTPUTFILETOYMCPICKEVTPP}_pt_${PTMIN[i]}_${PTMAX[i]}.root" ]
        then
            ./drawtoyMCpickevt.exe "${OUTPUTFILETOYMCPICKEVTPP}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPP" "${PTMIN[i]}" "${PTMAX[i]}"
        else
            echo -e "\033[1;31merror:\033[0m ${OUTPUTFILETOYMCPICKEVTPP}_pt_${PTMIN[i]}_${PTMAX[i]}.root does not exist."
        fi
        rm drawtoyMCpickevt.exe
    fi 
    i=$((i+1))
done

rm parameters.h

## ANALYSIS PP MB

cp config/parametersLowpt.h parameters.h

PTMIN=(2 3 4 5 6 8 10 12.5 15)
PTMAX=(3 4 5 6 8 10 12.5 15 20)
nPTBINS=${#PTMIN[@]}
#
OUTPUTFILEEFFPPMB="ROOTfiles${FILEEND}/hEffPPMB"
OUTPUTFILETOYMCPICKEVTPPMB="ROOTfiles${FILEEND}/hToyMCpickevtPPMB"

CUTPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTGENPPMB="abs(PVz)<15&&pBeamScrapingFilter&&pPAprimaryVertexFilter&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"

if [ $DOANALYSISPPMB_SAVEHISTPICKEVT -eq 1 ]
then
    g++ fitDsavehistpickevt.C $(root-config --cflags --libs) -g -o fitDsavehistpickevt.exe 
    ./fitDsavehistpickevt.exe "$INPUTMCPP" "$CUTPPMB" "$CUTGENPPMB" "$LABELPPMB" "$OUTPUTFILEEFFPPMB"
    rm fitDsavehistpickevt.exe
fi 

i=0
while ((i<$nPTBINS))
do
    if [ $DOANALYSISPPMB_TOYMCPICKEVT -eq 1 ]
    then
        g++ fitDtoyMCpickevt.C $(root-config --cflags --libs) -g -o fitDtoyMCpickevt.exe 
        ./fitDtoyMCpickevt.exe "$INPUTMCPP" "$OUTPUTFILEEFFPPMB" "${OUTPUTFILETOYMCPICKEVTPPMB}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPPMB" "${PTMIN[i]}" "${PTMAX[i]}" "$NSMEAR" "$NGEN" 
        rm fitDtoyMCpickevt.exe
    fi 
    
    if [ $DOANALYSISPPMB_DRAWTOYMCPICKEVT -eq 1 ]
    then
        g++ drawtoyMCpickevt.C $(root-config --cflags --libs) -g -o drawtoyMCpickevt.exe 
        if [ -f "${OUTPUTFILETOYMCPICKEVTPPMB}_pt_${PTMIN[i]}_${PTMAX[i]}.root" ]
        then
            ./drawtoyMCpickevt.exe "${OUTPUTFILETOYMCPICKEVTPPMB}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPPMB" "${PTMIN[i]}" "${PTMAX[i]}"
        else
            echo -e "\033[1;31merror:\033[0m ${OUTPUTFILETOYMCPICKEVTPPMB}_pt_${PTMIN[i]}_${PTMAX[i]}.root does not exist."
        fi
        rm drawtoyMCpickevt.exe
    fi 
    i=$((i+1))
done

rm parameters.h

## ANALYSIS PbPb TRIGGERED

cp config/parametersHighpt.h parameters.h

PTMIN=(20 25 30 40 60)
PTMAX=(25 30 40 60 100)
nPTBINS=${#PTMIN[@]}
#
OUTPUTFILEEFFPbPb="ROOTfiles${FILEEND}/hEffPbPb"
OUTPUTFILETOYMCPICKEVTPbPb="ROOTfiles${FILEEND}/hToyMCpickevtPbPb"

CUTPbPb="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTGENPbPb="abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
LABELPbPb="PbPb"

if [ $DOANALYSISPbPb_SAVEHISTPICKEVT -eq 1 ]
then
    g++ fitDsavehistpickevt.C $(root-config --cflags --libs) -g -o fitDsavehistpickevt.exe 
    ./fitDsavehistpickevt.exe "$INPUTMCPbPb" "$CUTPbPb" "$CUTGENPbPb" "$LABELPbPb" "$OUTPUTFILEEFFPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDsavehistpickevt.exe
fi 

i=0
while ((i<$nPTBINS))
do
    if [ $DOANALYSISPbPb_TOYMCPICKEVT -eq 1 ]
    then
        g++ fitDtoyMCpickevt.C $(root-config --cflags --libs) -g -o fitDtoyMCpickevt.exe 
        ./fitDtoyMCpickevt.exe "$INPUTMCPbPb" "$OUTPUTFILEEFFPbPb" "${OUTPUTFILETOYMCPICKEVTPbPb}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPbPb" "${PTMIN[i]}" "${PTMAX[i]}" "$NSMEAR" "$NGEN" "$CENTPbPbMIN" "$CENTPbPbMAX"
        rm fitDtoyMCpickevt.exe
    fi 
    
    if [ $DOANALYSISPbPb_DRAWTOYMCPICKEVT -eq 1 ]
    then
        g++ drawtoyMCpickevt.C $(root-config --cflags --libs) -g -o drawtoyMCpickevt.exe 
        if [ -f "${OUTPUTFILETOYMCPICKEVTPbPb}_pt_${PTMIN[i]}_${PTMAX[i]}.root" ]
        then
            ./drawtoyMCpickevt.exe "${OUTPUTFILETOYMCPICKEVTPbPb}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPbPb" "${PTMIN[i]}" "${PTMAX[i]}" "$CENTPbPbMIN" "$CENTPbPbMAX"
        else
            echo -e "\033[1;31merror:\033[0m ${OUTPUTFILETOYMCPICKEVTPbPb}_pt_${PTMIN[i]}_${PTMAX[i]}.root does not exist."
        fi
        rm drawtoyMCpickevt.exe
    fi 
    i=$((i+1))
done

rm parameters.h

## ANALYSIS PbPb MB

cp config/parametersLowpt.h parameters.h

PTMIN=(2 3 4 5 6 8 10 12.5 15)
PTMAX=(3 4 5 6 8 10 12.5 15 20)
nPTBINS=${#PTMIN[@]}
#
OUTPUTFILEEFFPbPbMB="ROOTfiles${FILEEND}/hEffPbPbMB"
OUTPUTFILETOYMCPICKEVTPbPbMB="ROOTfiles${FILEEND}/hToyMCpickevtPbPbMB"

CUTPbPbMB="pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&abs(PVz)<15&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>2.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<3&&(DsvpvDistance/DsvpvDisErr)>4.62&&Dchi2cl>0.161)||(Dpt>3&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>4.80&&Dchi2cl>0.197)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>4.63&&Dchi2cl>0.141)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.53&&Dchi2cl>0.172)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.09&&Dchi2cl>0.120)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.02&&Dchi2cl>0.098)||(Dpt>10&&Dpt<12.5&&(DsvpvDistance/DsvpvDisErr)>3.66&&Dchi2cl>0.099)||(Dpt>12.5&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>3.70&&Dchi2cl>0.084)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.53&&Dchi2cl>0.047)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
CUTGENPbPbMB="abs(PVz)<15&&pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&(GisSignal==1||GisSignal==2)&&Gy>-1&&Gy<1"
LABELPbPbMB="PbPbMB"

if [ $DOANALYSISPbPbMB_SAVEHISTPICKEVT -eq 1 ]
then
    g++ fitDsavehistpickevt.C $(root-config --cflags --libs) -g -o fitDsavehistpickevt.exe 
    ./fitDsavehistpickevt.exe "$INPUTMCPbPb" "$CUTPbPbMB" "$CUTGENPbPbMB" "$LABELPbPbMB" "$OUTPUTFILEEFFPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
    rm fitDsavehistpickevt.exe
fi 

i=0
while ((i<$nPTBINS))
do
    if [ $DOANALYSISPbPbMB_TOYMCPICKEVT -eq 1 ]
    then
        g++ fitDtoyMCpickevt.C $(root-config --cflags --libs) -g -o fitDtoyMCpickevt.exe 
        ./fitDtoyMCpickevt.exe "$INPUTMCPbPb" "$OUTPUTFILEEFFPbPbMB" "${OUTPUTFILETOYMCPICKEVTPbPbMB}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPbPbMB" "${PTMIN[i]}" "${PTMAX[i]}" "$NSMEAR" "$NGEN" "$CENTPbPbMIN" "$CENTPbPbMAX"
        rm fitDtoyMCpickevt.exe
    fi 
    
    if [ $DOANALYSISPbPbMB_DRAWTOYMCPICKEVT -eq 1 ]
    then
        g++ drawtoyMCpickevt.C $(root-config --cflags --libs) -g -o drawtoyMCpickevt.exe 
        if [ -f "${OUTPUTFILETOYMCPICKEVTPbPbMB}_pt_${PTMIN[i]}_${PTMAX[i]}.root" ]
        then
            ./drawtoyMCpickevt.exe "${OUTPUTFILETOYMCPICKEVTPbPbMB}_pt_${PTMIN[i]}_${PTMAX[i]}" "$LABELPbPbMB" "${PTMIN[i]}" "${PTMAX[i]}" "$CENTPbPbMIN" "$CENTPbPbMAX"
        else
            echo -e "\033[1;31merror:\033[0m ${OUTPUTFILETOYMCPICKEVTPbPbMB}_pt_${PTMIN[i]}_${PTMAX[i]}.root does not exist."
        fi
        rm drawtoyMCpickevt.exe
    fi 
    i=$((i+1))
done

rm parameters.h

## COMBINE

