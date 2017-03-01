#!/bin/bash
#source clean.sh
CENTPbPbMIN=0
CENTPbPbMAX=100

DOTriggered=1
DOMB=1

DONORM=1

UNITY=1
NULL=0

## PbPb 

## PbPb MONTE CARLO

INPUTMCPbPb="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
INPUTMCPbPbMB="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160330_Dfinder_20160329_PbPb_Pythia8_prompt_D0_dPt1tkPt0p5_pthatweight.root"

## PbPb DATA 

INPUTDATAPbPbSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_skimmed.root"
INPUTDATAPbPbUNSKIMMED="/data/wangj/Data2015/Dntuple/PbPb/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON.root"
INPUTDATAPbPbMBUNSKIMMED="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"
INPUTDATAPbPbMBSKIMMED="/data/jisun/PbPb2015/HF2and_tk1p0_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"


if [ $DOTriggered -eq 1 ]; then      

for VARIABLE in 20 40 60 999
do

cp config/parametersHighHLT20.h parameters.h

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLOUTPUTFILEPbPb="ROOTfiles/output_pp_d0meson_5TeV_y1_$VARIABLE.root"
OUTPUTPrescalePbPb="ROOTfiles/prescalePbPb_$VARIABLE.root"
OUTPUTFILEMCSTUDYPbPb="ROOTfiles/MCstudiesPbPb_$VARIABLE.root"
OUTPUTFILEMCSTUDYNPPbPb="ROOTfiles/MCstudiesNPPbPb_$VARIABLE.root"
OUTPUTFILEPbPb="ROOTfiles/hPtSpectrumDzeroPbPb_$VARIABLE.root"
OUTPUTFILEPlotPbPb="ROOTfiles/CrossSectionFONLLPbPb_$VARIABLE.root"
OUTPUTFILERAA="ROOTfiles/outputRAA_$VARIABLE.root"

LUMIPbPb=17.1001
#LUMIPbPb=1
ISMCPbPb=0
ISDOWEIGHTPbPb=0
SELGENPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPbPb="pprimaryVertexFilter&&phfCoincFilter3&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUTPbPb="pprimaryVertexFilter&&phfCoincFilter3&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
LABELPbPb="PbPb_$VARIABLE"
LABELNPPbPb="NPPbPb"
USEPRESCALEPbPb=1
CUTFORTRIGGERPRESCALEPbPb=0

if [ $VARIABLE -eq 20 ]; then      
cp config/parametersHighHLT20.h parameters.h
TRGPbPb="HLT_HIDmesonHITrackingGlobal_Dpt20_v1"
fi 

if [ $VARIABLE -eq 40 ]; then     
cp config/parametersHighHLT40.h parameters.h
TRGPbPb="HLT_HIDmesonHITrackingGlobal_Dpt40_v1"
fi 

if [ $VARIABLE -eq 60 ]; then     
cp config/parametersHighHLT60.h parameters.h
TRGPbPb="HLT_HIDmesonHITrackingGlobal_Dpt60_v1"
fi 

if [ $VARIABLE -eq 999 ]; then     
cp config/parametersHighpt.h parameters.h
TRGPbPb="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<40)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>40&&Dpt<60)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>60))"
fi 


if [ $DONORM -eq 1 ]; then     
LUMIPbPb=1
fi 

 
 g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEPbPb" "$LABELPbPb"
 
g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe 1  "$INPUTDATAPbPbUNSKIMMED" "$INPUTDATAPbPbMBUNSKIMMED" "$CUTFORTRIGGERPRESCALEPbPb" "$OUTPUTPrescalePbPb"
rm triggercombination.exe

g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 1 "$INPUTDATAPbPbSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   1   "$ISDOWEIGHTPbPb"  "$LABELPbPb"  "$OUTPUTFILEPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitD.exe

g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEPbPb"  "$OUTPUTFILEPbPb" "$OUTPUTPrescalePbPb" "$USEPRESCALEPbPb" "$OUTPUTFILEPlotPbPb" 1 "$LABELPbPb" "$LUMIPbPb" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatio.exe

done

fi

if [ $DOMB -eq 1 ]; then      

cp config/parametersLowptPbPb_extended.h parameters.h

## ANALYSIS PbPb MB
FONLLDATINPUT="pp_d0meson_5TeV_y1"
OUTPUTFILEPbPbMB="ROOTfiles/hPtSpectrumDzeroPbPbMB_extended.root"
OUTPUTFILEPlotPbPbMB="ROOTfiles/CrossSectionFONLLPbPbMB_extended.root"
FONLLOUTPUTFILEPbPbMB="ROOTfiles/output_pp_d0meson_5TeV_y1_extended.root"
OUTPUTFILERAAMB="ROOTfiles/outputRAAMB_extended.root"

LUMIPbPbMB=0.831646 
#LUMIPbPbMB=1 
ISMCPbPbMB=0
ISDOWEIGHTPbPbMB=0
SELGENPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPbPbMB="pprimaryVertexFilter&&phfCoincFilter3&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3"
CUTPbPbMB="pprimaryVertexFilter&&phfCoincFilter3&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
LABELPbPbMB="PbPbMB_extended"
LABELNPPbPbMB="NPPbPbMB"
USEPRESCALEPbPbMB=0


if [ $DONORM -eq 1 ]; then     
LUMIPbPbMB=1
fi 

g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEPbPbMB" "$LABELPbPbMB"


g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 1 "$INPUTDATAPbPbMBSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbMB" "$CUTPbPbMB"   "$SELGENPbPbMB"   "$ISMCPbPbMB"   1   "$ISDOWEIGHTPbPbMB"   "$LABELPbPbMB"  "$OUTPUTFILEPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm fitD.exe

g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEPbPbMB"  "$OUTPUTFILEPbPbMB" "$OUTPUTPrescalePbPb" "$USEPRESCALEPbPbMB" "$OUTPUTFILEPlotPbPbMB" 1 "$LABELPbPbMB" "$LUMIPbPbMB" "$CENTPbPbMIN" "$CENTPbPbMAX"
rm CrossSectionRatio.exe

fi









