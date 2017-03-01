void prescaleBrilCalc(){

/*

brilcalc lumi -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/5TeV/Cert_262081-262328_5TeV_PromptReco_Collisions15_25ns_JSON.txt  --hltpath  
brilcalc lumi -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt    --hltpath  **


| HLT_DmesonPPTrackingGlobal_Dpt15_v1                       | 6     | 24   | 6196 | 1035781.853       | 1006475.256      |
| HLT_DmesonPPTrackingGlobal_Dpt20_v1                       | 6     | 24   | 6196 | 3239126.844       | 3146348.607      |
| HLT_DmesonPPTrackingGlobal_Dpt30_v1                       | 6     | 24   | 6196 | 6520191.277       | 6329008.193      |
| HLT_DmesonPPTrackingGlobal_Dpt40_v1                       | 6     | 24   | 6196 | 6520191.277       | 6329008.193      |
| HLT_DmesonPPTrackingGlobal_Dpt50_v1                       | 6     | 24   | 6196 | 26564901.822      | 25775344.462     |
| HLT_DmesonPPTrackingGlobal_Dpt60_v1                       | 6     | 24   | 6196 | 26564901.822      | 25775344.462     |
| HLT_DmesonPPTrackingGlobal_Dpt8_v1                        | 6     | 24   | 6196 | 266640.179        | 259286.311       |


| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v1   | 2     | 3    | 637   | 1.057             | 1.022            |
| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent0_10_v2   | 24    | 61   | 21493 | 218.568           | 208.473          |
| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v1 | 2     | 3    | 637   | 0.488             | 0.473            |
| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v2 | 9     | 36   | 9061  | 13.924            | 12.664           |
| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent30_100_v3 | 15    | 25   | 12432 | 58.682            | 57.914           |
| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v1 | 2     | 3    | 637   | 0.488             | 0.473            |
| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v2 | 9     | 36   | 9061  | 10.651            | 9.724            |
| HLT_HIDmesonHITrackingGlobal_Dpt20_Cent50_100_v3 | 15    | 25   | 12432 | 26.331            | 25.967           |
| HLT_HIDmesonHITrackingGlobal_Dpt20_v1            | 11    | 39   | 9698  | 50.657            | 45.995           |
| HLT_HIDmesonHITrackingGlobal_Dpt20_v2            | 15    | 25   | 12432 | 27.381            | 27.018           |
| HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v1   | 2     | 3    | 637   | 1.057             | 1.022            |
| HLT_HIDmesonHITrackingGlobal_Dpt30_Cent0_10_v2   | 24    | 61   | 21493 | 218.568           | 208.473          |
| HLT_HIDmesonHITrackingGlobal_Dpt30_Cent30_100_v1 | 26    | 64   | 22130 | 128.452           | 122.376          |
| HLT_HIDmesonHITrackingGlobal_Dpt30_Cent50_100_v1 | 26    | 64   | 22130 | 234.910           | 224.137          |
| HLT_HIDmesonHITrackingGlobal_Dpt30_v1            | 11    | 17   | 8300  | 31.172            | 29.741           |
| HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v1   | 2     | 3    | 637   | 1.057             | 1.022            |
| HLT_HIDmesonHITrackingGlobal_Dpt40_Cent0_10_v2   | 24    | 61   | 21493 | 218.568           | 208.473          |
| HLT_HIDmesonHITrackingGlobal_Dpt40_Cent30_100_v1 | 26    | 64   | 22130 | 421.926           | 403.442          |
| HLT_HIDmesonHITrackingGlobal_Dpt40_Cent50_100_v1 | 26    | 64   | 22130 | 421.926           | 403.442          |
| HLT_HIDmesonHITrackingGlobal_Dpt40_v1            | 26    | 64   | 22130 | 268.841           | 255.189          |
| HLT_HIDmesonHITrackingGlobal_Dpt60_Cent30_100_v1 | 26    | 64   | 22130 | 421.926           | 403.442          |
| HLT_HIDmesonHITrackingGlobal_Dpt60_Cent50_100_v1 | 26    | 64   | 22130 | 421.926           | 403.442          |
| HLT_HIDmesonHITrackingGlobal_Dpt60_v1            | 26    | 64   | 22130 | 421.926           | 403.442          |
*/

double prescaleHLTtree8=0.0100176;
double prescaleHLTtree15=0.0386102;
double prescaleHLTtree30=0.245349;
double prescaleHLTtree50=1;
double prescaleHLTtreeMB=0.00109638;

double unprescale=25775344.462;
double unprescaleMB=1898.856*19;
double D8pp=259286.311;
double D15pp=1006475.256;
double D30pp=6329008.193;
double D50pp=25775344.462;


double prescaleHLTtreePbPbD20=0.108224;
double prescaleHLTtreePbPbD40=0.616808;
double prescaleHLTtreePbPbD60=1;
double prescaleHLTtreePbPbMB=0.0578064;


double unprescalePbPb=403.442;
double unprescaleMBPbPb=7.211*3;
double D20PbPb=45.995;
double D40PbPb=255.189;
double D60PbPb=403.442;

double prescaleMB=unprescaleMB/unprescale;
double prescale8=D8pp/unprescale;
double prescale15=D15pp/unprescale;
double prescale30=D30pp/unprescale;
double prescale50=D50pp/unprescale;

double prescalePbPbMB=unprescaleMBPbPb/unprescalePbPb;
double prescalePbPb20=D20PbPb/unprescalePbPb;
double prescalePbPb40=D40PbPb/unprescalePbPb;
double prescalePbPb60=D60PbPb/unprescalePbPb;

cout<<"******************* prescales for pp from the brilcalc *******************"<<endl;

cout<<"prescaleMB="<<prescaleMB<<endl;
cout<<"prescale8="<<prescale8<<endl;
cout<<"prescale15="<<prescale15<<endl;
cout<<"prescale30="<<prescale30<<endl;
cout<<"prescale50="<<prescale50<<endl;

cout<<"******************* prescales for pp from the HLT overlaps and  *******************"<<endl;

cout<<"prescaleHLTtree8="<<prescaleHLTtree8<<endl;
cout<<"prescaleHLTtree15="<<prescaleHLTtree15<<endl;
cout<<"prescaleHLTtree30="<<prescaleHLTtree30<<endl;
cout<<"prescaleHLTtree50="<<prescaleHLTtree50<<endl;
cout<<"prescaleHLTtreeMB="<<prescaleHLTtreeMB<<endl;

cout<<"******************* LUMI PP  *******************"<<endl;

cout<<"lumipp brilcalc="<<prescaleMB*25.8<<endl;
cout<<"lumipp tree="<<prescaleHLTtreeMB*25.8<<endl;
cout<<"lumipp Data driven="<<0.034747<<endl;

cout<<"******************* prescales for PbPb from the brilcalc *******************"<<endl;


cout<<"prescalePbPbMB="<<prescalePbPbMB<<endl;
cout<<"prescalePbPb20="<<prescalePbPb20<<endl;
cout<<"prescalePbPb40="<<prescalePbPb40<<endl;
cout<<"prescalePbPb60="<<prescalePbPb60<<endl;

cout<<"******************* prescales for PbPb from the HLT overlaps and  *******************"<<endl;

cout<<"prescaleHLTtreePbPbMB="<<prescaleHLTtreePbPbMB<<endl;
cout<<"prescalePbPb20="<<prescalePbPb20<<endl;
cout<<"prescalePbPb40="<<prescalePbPb40<<endl;
cout<<"prescalePbPb60="<<prescalePbPb60<<endl;


TFile*f=new TFile("/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root");
TTree *ntDkpi = (TTree*)f->Get("ntDkpi");
TTree *ntHlt = (TTree*)f->Get("ntHlt");
TTree *ntSkim = (TTree*)f->Get("ntSkim");
TTree *ntHi = (TTree*)f->Get("ntHi");
ntDkpi->AddFriend(ntSkim);
ntDkpi->AddFriend(ntHlt);
ntDkpi->AddFriend(ntHi);
TH1F*hcountsMB=new TH1F("hcountsMB","hcountsMB",100,-2,2);

ntDkpi->Draw("1>>hcountsMB","pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)&&hiBin<180");

double ncountsMBPbPb=hcountsMB->GetEntries()*10/9;
std::cout<<"number of MB events="<<ncountsMBPbPb<<std::endl;
double TAA=392.4/(70.*1e9);
double lumiMB=TAA*ncountsMBPbPb;
double lumiHighpt=lumiMB/prescalePbPbMB;      


cout<<"******************* LUMI PbPb 0-100 *******************"<<endl;

std::cout<<"Luminosity brilcalc low pt="<<lumiMB<<std::endl;
std::cout<<"Luminosity brilcalc high pt="<<lumiHighpt<<std::endl;
//std::cout<<"Luminosity data driven high pt="<<16.1<<std::endl;
//std::cout<<"Luminosity data overlaps high pt="<<lumiMB/prescaleHLTtreePbPbMB<<std::endl;

cout<<"******************* LUMI PbPb 0-10 *******************"<<endl;

//double ncountsMBPbPb010=1.50947e+07;
ntDkpi->Draw("1>>hcountsMB","pclusterCompatibilityFilter&&pprimaryVertexFilter&&phfCoincFilter3&&(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)&&hiBin<20");
double ncountsMBPbPb010=hcountsMB->GetEntries();
std::cout<<"number of MB events 0-10="<<ncountsMBPbPb010<<std::endl;

double TAA010=(23.2/1e9);
double lumiMB010=TAA010*ncountsMBPbPb010;
double lumiHighpt010=lumiMB010/prescalePbPbMB;      

std::cout<<"Luminosity brilcalc low pt 010="<<lumiMB010<<std::endl;
std::cout<<"Luminosity brilcalc high pt 010="<<lumiHighpt010<<std::endl;


/*

lumi_bril=21.633
Nevents=1.48357e+08/0.72
*/

}