#include "TFile.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TString.h"
#include "TCutG.h"
#include <TH2.h>
#include <TStyle.h>
#include <stdio.h>
#include <TH1.h>
#include "TH1.h"


//#include "DESPEC_Online_Nov-vBEAM4/AIDA_Event.h"
//#include "DESPEC_Online_Nov-vBEAM4/AIDA_Decay_Event_Store.h"
//#include "TGo4EventElement.h"

#ifndef FRSGATES
#define FRSGATES 0
#endif

#ifndef NEIGHBOURS
#define NEIGHBOURS 1
#endif

#ifndef ALLHISTS
#define ALLHISTS 0
#endif

// Analysis strategy:
// 1. Selection of AIDA implants (i.e. first or highest energy hit)
//    Multiplicities for implants mostly 1... take the first one in all cases.
// 2. Correlating AIDA decays with preceding implants (nearest neighbour)
// 3. Gating on betas with bPlast - time with AIDA and energy
// 4. Look at Gammas in coincidence with bPlast
// 5. With and without FRS gates

class Pixel
{
public:
  int64_t pixtime;
  double Energy;  
  Int_t correlated;
  Int_t GatePass;
  Float_t FRS_Z;
  Float_t FRS_AoQ;
};


// AidaHit: Physical detector hits: front-back matched
class AidaHit : public TObject
{
  public:
    int Event;
    int DSSD;
    // Coordinate in Strip & Position
    double StripX;
    double StripY;
    double PosX;
    double PosY;
    double Energy;
    double EnergyFront;
    double EnergyBack;
    // Cluster Size for correlations
    int StripXMin;
    int StripXMax;
    int StripYMin;
    int StripYMax;
    int ClusterSizeX;
    int ClusterSizeY;
    int64_t Time;
    int64_t TimeFront;
    int64_t TimeBack;
    int64_t FastTime;
    int64_t FastTimeFront;
    int64_t FastTimeBack;
    bool Stopped;

    AidaHit() { Zero(); }
    void Zero() {};
    virtual ~AidaHit() {}
    ClassDef(AidaHit, 3)
};


// AidaHit: Physical detector hits: front-back matched
class AidaHitPID : public TObject
{
public:
  int Event;

  int DSSD;
  // Coordinate in Strip & Position
  double StripX;
  double StripY;
  double PosX;
  double PosY;
  

  double Energy;
  double EnergyFront;
  double EnergyBack;

  // Cluster Size for correlations
  int StripXMin;
  int StripXMax;
  int StripYMin;
  int StripYMax;
  int ClusterSizeX;
  int ClusterSizeY;

  int64_t Time;
  int64_t TimeFront;
  int64_t TimeBack;
  int64_t FastTime;
  int64_t FastTimeFront;
  int64_t FastTimeBack;
  
  // Add extra PID stuff for implants
  
  Int_t GatePass;
  Float_t FRS_Z;
  Float_t FRS_AoQ;

  // If the implant is believed to have stopped here (AIDA only veto)
  bool Stopped;

  AidaHitPID() { Zero(); }
  void Zero() {}
  virtual ~AidaHitPID() {}

  ClassDef(AidaHitPID, 3)
};

struct AidaAnlData {

  std::vector<AidaHit> Implants;

  std::vector<AidaHit> Decays;

};




void ReadPlasticGates(int channel, double* low, double* high){
    
    ifstream gatefile;
    gatefile.open("bPlast_betagates.dat");
    int ch = 0;
    double lo = .0;
    double hi = .0;
    
    
    while(gatefile.is_open() && !gatefile.eof()){
    gatefile >> ch >> lo >> hi;
    //hist->Fill(pi);
        if(ch == channel){
           //cout << "Channel: " << ch << ", low: " << lo << ", high: " << hi << endl;
           *low = lo;
           *high = hi;
        }
  }
    
    
    
}

double ToFCorr(int tdcid, double tdctime, double aidaposx, double aidaposy){
//void ToFCalc(){
    double correctedtime;
    double tof;
    double fat_aida_dpos;
    double c_air = 299792458/(1000000*1.0003); //Convert m/s to mm/ns

    double x[36] = {95.88638696,  70.19370701,  25.69267995,  -25.69267995, -70.19370701, -95.88638696, -95.88638696, -70.19370701, -25.69267995, 25.69267995,  70.19370701,  95.88638696,  137.2440216,  118.8568092,  68.62201078,  0,  -68.62201078, -118.8568092, -137.2440216, -118.8568092, -68.62201078, 0,  68.62201078,  118.8568092,  95.88638696,  70.19370701,  25.69267995,  -25.69267995, -70.19370701, -95.88638696, -95.88638696, -70.19370701, -25.69267995, 25.69267995,  70.19370701,  95.88638696};
    double y[36] = {25.69267995,  70.19370701,  95.88638696,  95.88638696,  70.19370701,  25.69267995,  -25.69267995, -70.19370701, -95.88638696, -95.88638696, -70.19370701, -25.69267995, 0,  68.62201078,  118.8568092,  137.2440216,  118.8568092,  68.62201078,  0,  -68.62201078, -118.8568092, -137.2440216, -118.8568092, -68.62201078, 25.69267995,  70.19370701,  95.88638696,  95.88638696,  70.19370701,  25.69267995,  -25.69267995, -70.19370701, -95.88638696, -95.88638696, -70.19370701, -25.69267995};
    double z[36] = {-95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -95.86285512, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, -14.42492793, 95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512,  95.86285512};

    fat_aida_dpos = pow( pow(aidaposx - x[tdcid], 2) + pow(aidaposy - y[tdcid],2) + pow(z[tdcid],2) ,0.5); 
    tof = fat_aida_dpos/c_air;
    correctedtime = tdctime - tof;

    //cout << "difference in position between fat and aida: " << fat_aida_dpos << " fat aida tof is " << tof << " old time is " << tdctime << " corrected time is " << correctedtime << endl;


    return correctedtime;
        
}

double ToFCorrDiff(int tdcidi, double tdctimei, int tdcidj, double tdctimej, double aidaposx, double aidaposy){

    double correctedtimediff;

    correctedtimediff = ToFCorr(tdcidi, tdctimei, aidaposx, aidaposy) - ToFCorr(tdcidj, tdctimej, aidaposx, aidaposy); 
    
    return correctedtimediff;
        
}


void AnalyzeTree(char* pathname,char* filename)
{

    //Histograms
    Int_t ToPrint = 0;
    Int_t ToPrint2 = 0;

    Int_t i;
    Int_t AidaImpHit = 0;
    Int_t AidaDecHit = 0;
    Int_t iterator = 0;
    Int_t AidaImpMult = 0;
    Int_t AidaDecMult = 0;
    char name[50];
    AidaHit firstImp;
    AidaHit firstDec;
    AidaHit HighEImp;
    AidaHit HighEDec;
    int64_t dT = 0;
    int64_t lastdT = 0;
    int64_t firstTimestamp = 0;
    Int_t strx = 0;
    Int_t stry = 0;
    Text_t hist[256];
    Text_t hist2[256];
    Text_t hist3[256];
    Text_t hist4[256];
    Text_t hist5[256];
    Text_t hist6[256];
    double lastImpE = .0;
    double lastDecE = .0;
    int64_t lastSC41WR = 0;
    int64_t lastSC41WR_gated = 0;
    
    Int_t bPlastMult = 0;
    Int_t bPlas_betaEv = 0;
    
    Pixel DSSD[3][130][130];
    
    int arg1 = 1;
    double arg2 = .0;
    double arg3 = .0;
    Int_t mm = 0;
    
    for(Int_t m = 0;m<3;m++){
    for(Int_t p = 0;p<130;p++){
      for(Int_t q = 0;q<130;q++){
  DSSD[m][p][q].pixtime = 0;
  DSSD[m][p][q].Energy = 0;
  DSSD[m][p][q].correlated = 0;
      }
    }
    }
    
    
    
    //*******************************************************************
    // Reading bPlast beta gates from file
    
    ifstream gatefile;
    gatefile.open("bPlast_betagates.dat");
    int ch = 0;
    double betalo[48];
    double betahi[48];
    
    for(mm=0;mm<48;mm++){
     betalo[mm] = 0.0;
     betahi[mm] = 0.0;
    }
    
    mm=0;
    while(gatefile.is_open() && !gatefile.eof()){
    gatefile >> ch >> betalo[mm] >> betahi[mm];
        mm++;
  }    
  
  for(mm=0;mm<48;mm++){
        //cout << "Channel " << mm << " has betalo " << betalo[mm] << ", betahi " << betahi[mm] << endl;
    }
	//*******************************************************************

    
    
    //*******************************************************************
    // HISTOGRAM DEFINITIONS HERE 

    //FRS Histos should be floats
    //Gates histos should be doubles

/*
    TH2D *gg = new TH2D("gg","gg",4000,0,4000,4000,0,4000);
    TH2D *gg94 = new TH2D("gg94","gg94",4000,0,4000,4000,0,4000);
    TH2D *gg96 = new TH2D("gg96","gg96",4000,0,4000,4000,0,4000);

    //96Pd gates
    TH2D *gated1415 = new TH2D("gated1415","gated1415",10000,-500,500,2000,0,2000);
    TH2D *gated680 = new TH2D("gated680","gated680",10000,-500,500,2000,0,2000); 
    TH2D *gated325 = new TH2D("gated325","gated325",10000,-500,500,2000,0,2000); 
    TH2D *gated105 = new TH2D("gated105","gated105",10000,-500,500,2000,0,2000);

    //94Pd gates
    TH2D *gated905 = new TH2D("gated905","gated905",10000,-500,500,2000,0,2000); 
    TH2D *gated814 = new TH2D("gated814","gated814",10000,-500,500,2000,0,2000);
    TH2D *gated324 = new TH2D("gated324","gated324",10000,-500,500,2000,0,2000); 
    TH2D *gated1092 = new TH2D("gated1092","gated1092",10000,-500,500,2000,0,2000); 
    TH2D *gated660 = new TH2D("gated660","gated660",10000,-500,500,2000,0,2000); 
    TH2D *gated96 = new TH2D("gated96","gated96",10000,-500,500,2000,0,2000); 
    TH2D *gated994 = new TH2D("gated994","gated994",20000,-500,500,2000,0,2000); 
*/
    TH2D *Edt94_41 = new TH2D("Edt94_41","Edt94_41",12000,-2000,10000,2000,0,2000); 
    TH2D *Edt96_41 = new TH2D("Edt96_41","Edt96_41",12000,-2000,10000,2000,0,2000);


    TH2D *gg96 = new TH2D("gg96","gg96",2000,0,2000,2000,0,2000);
    TH2D *gg94 = new TH2D("gg94","gg94",2000,0,2000,2000,0,2000); 
    
    TH2F *zvsaoq = new TH2F("zvsaoq","zvsaoq",1500,0,5, 1500,0,100);
    TH2F *zvsaoq96pd = new TH2F("zvsaoq96pd","zvsaoq96pd",1500,0,5, 1500,0,100);
    TH2F *zvsaoq94pd = new TH2F("zvsaoq94pd","zvsaoq94pd",1500,0,5, 1500,0,100);

    TH2D *EID = new TH2D("EID","EID",2000,0,2000,100,0,100);


    //*******************************************************************
   
    
    // INPUT FILE    
    TString totpath;
    totpath = pathname;
    totpath += filename;
    TFile *f = TFile::Open(totpath);
    if (f == 0) {
      printf("Error: cannot open tree\n");
      return;
    }
    // OUTPUT FILE
    TString outpath;
    //outpath = "/home/sj00239/gsi/tree_sorting/hists/testing_";
    outpath = "/lustre/gamma/jazrawi/hists/Isomeric_";

    outpath += filename;
    TFile *out = new TFile(outpath, "RECREATE");
    if (out == 0) {
       printf("Error: cannot open output root file\n");
       return;
    }
    
        
    ofstream readout;
    readout.open ("output.txt");
   
    // READING THE TREE.....
   
   TTreeReader myReader("AnalysisxTree",f); 
   TTreeReaderValue<int> EventNumber(myReader,"AnlEvent.pEvent_Number");
   //TTreeReaderArray<double> bPlasE(myReader,"AnlEvent.pbPlas_ToTCalib[32]"); //48 for Re data
   
   TTreeReaderArray<Double_t> plas_tot_calib(myReader,"AnlEvent.pbPlas_ToTCalib[3][16][10]"); //Plastic

   TTreeReaderArray<double> LaBr_E(myReader,"AnlEvent.pFat_QDC_E[50]");

   //TTreeReaderArray<double> Gal_E(myReader,"AnlEvent.pGal_EAddback[9][3]");
   //TTreeReaderArray<double> Gal_E(myReader,"AnlEvent.pGal_E_Raw[9][3]");
   TTreeReaderArray<double> Gal_E(myReader,"AnlEvent.pGal_E[9][3]");

   TTreeReaderArray<unsigned long long> Gal_T(myReader,"AnlEvent.pGal_T[9][3]");

   TTreeReaderArray<double> Tamex_lead(myReader,"AnlEvent.pFat_LeadT[50][10]");


   //TTreeReaderValue<double> GalEnergyAddback(myReader,"AnlEvent.pGalE_Addback");
   TTreeReaderValue<Long64_t> GalWR(myReader,"AnlEvent.pGAL_WR");
   //TTreeReaderValue<std::vector<AidaHit>> AidaImp(myReader,"AnlEvent.pAida.Implants");
   //TTreeReaderValue<std::vector<AidaHit>> AidaDec(myReader,"AnlEvent.pAida.Decays");
   TTreeReaderValue<float> FRS_z(myReader,"AnlEvent.pFRS_z");
   TTreeReaderValue<float> FRS_AoQ(myReader,"AnlEvent.pFRS_AoQ");
   TTreeReaderValue<Long64_t> FRSWR(myReader,"AnlEvent.pFRS_WR");
   TTreeReaderValue<Long64_t> bPlasWR(myReader,"AnlEvent.pbPLAS_WR");
   TTreeReaderValue<Long64_t> FatWR(myReader,"AnlEvent.pFAT_WR");
   //TTreeReaderValue<Long64_t> AIDAWR(myReader,"AnlEvent.pAIDA_WR");
   TTreeReaderArray<Long64_t> FatTDC_T(myReader,"AnlEvent.pFat_TDC_T[50]");  
   //TTreeReaderArray<double> SC41_t(myReader,"AnlEvent.pFat_SC41_t[50]"	);

   TTreeReaderArray<float> SC_E(myReader,"AnlEvent.pFRS_sci_e[12]"	);
   TTreeReaderArray<float> SC_T(myReader,"AnlEvent.pFRS_sci_tx[12]" );
   //SetBranchAddress

   //TTreeReaderArray<double> bPlasLeadT(myReader,"AnlEvent.pbPlas_LeadT[32][10]");// CHANGE ME to 48
   TTreeReaderValue<float> FRS_x4(myReader,"AnlEvent.pFRS_ID_x4");
   TTreeReaderValue<int> Fatmult(myReader,"AnlEvent.pFatmult");

   //SC41 multiplicities
   TTreeReaderValue<int> SC40mult(myReader,"AnlEvent.pSC40mult");
   TTreeReaderValue<int> SC41mult(myReader,"AnlEvent.pSC41mult");

   //Unmatched multiplcities
   TTreeReaderValue<UInt_t> singqdcmult(myReader,"AnlEvent.psqdcmult");
   TTreeReaderValue<UInt_t> singtdcmult(myReader,"AnlEvent.pstdcmult");

   //SC41 Times
   TTreeReaderArray<Long64_t> SC40_T(myReader,"AnlEvent.pSC40[10]"); 
   TTreeReaderArray<Long64_t> SC41_T(myReader,"AnlEvent.pSC41[10]"); 

	//IDs
   TTreeReaderArray<int> QDCID(myReader,"AnlEvent.pFat_QDC_ID[50]");
   TTreeReaderArray<int> TDCID(myReader,"AnlEvent.pFat_TDC_ID[50]");
   TTreeReaderArray<int> QDCID_singles(myReader,"AnlEvent.pFat_QDC_Singles_ID[50]");
   TTreeReaderArray<int> TDCID_singles(myReader,"AnlEvent.pFat_TDC_Singles_ID[50]");

   //Singles time and energy
   TTreeReaderArray<Long64_t> FatTDC_T_singles(myReader,"AnlEvent.pFat_TDC_Singles_t[50]");  
   TTreeReaderArray<double> LaBr_E_singles(myReader,"AnlEvent.pFat_QDC_Singles_E[50]");

   TTreeReaderArray<Double_t> FatQDC_t_fine(myReader,"AnlEvent.pFat_QDC_Singles_t_fine[50]");
   TTreeReaderArray<Long64_t> FatQDC_t_coarse(myReader,"AnlEvent.pFat_QDC_Singles_t_coarse[50]");  

   TTreeReaderArray<AidaAnlData> aida(myReader, "AnlEvent.pAida");



   //*******************************************************************
   // DEFINE FRS GATES HERE



   TCutG *pd96 = new TCutG("pd96",6);
   pd96->SetVarX("FRS_AoQ");
   pd96->SetVarY("FRS_z");
   pd96->SetPoint(0, 2.19479, 49.5361);
   pd96->SetPoint(1, 2.18678, 49.4650);
   pd96->SetPoint(2, 2.18678, 48.9968);
   pd96->SetPoint(3, 2.19497, 48.8676);
   pd96->SetPoint(4, 2.20187, 49.0642);
   pd96->SetPoint(5, 2.20165, 49.2983);

   TCutG *pd94 = new TCutG("pd94",5);
   pd94->SetVarX("FRS_AoQ");
   pd94->SetVarY("FRS_z");
   pd94->SetPoint(0,2.14433,48.6775);
   pd94->SetPoint(1,2.15012,48.8614);
   pd94->SetPoint(2,2.14806,49.2751);
   pd94->SetPoint(3,2.14133,49.2751);
   pd94->SetPoint(4,2.13822,49.1601);

   TCutG *sc41_42_pd96 = new TCutG("sc41_42_pd96",6);
   sc41_42_pd96->SetVarX("SC_E[6]");
   sc41_42_pd96->SetVarY("SC_E[5]");
   sc41_42_pd96->SetPoint(0, 1058, 856);
   sc41_42_pd96->SetPoint(1, 1461, 856);
   sc41_42_pd96->SetPoint(2, 1587, 951);
   sc41_42_pd96->SetPoint(3, 1526, 994);   
   sc41_42_pd96->SetPoint(4, 1091, 987);   
   sc41_42_pd96->SetPoint(5, 1010, 927);   

   TCutG *sc41_42_pd94 = new TCutG("sc41_42_pd94",5);
   sc41_42_pd94->SetVarX("SC_E[6]");
   sc41_42_pd94->SetVarY("SC_E[5]");
   sc41_42_pd94->SetPoint(0, 1021, 850);
   sc41_42_pd94->SetPoint(1, 1390, 850);
   sc41_42_pd94->SetPoint(2, 1460, 998);
   sc41_42_pd94->SetPoint(3, 1083, 987);   
   sc41_42_pd94->SetPoint(4, 998, 901);  



   TCutG *ru5 = new TCutG("ru5",4);
   ru5->SetVarX("FRS_AoQ");
   ru5->SetVarY("FRS_z");
   ru5->SetPoint(0,2.25,47.55);
   ru5->SetPoint(1,2.22771,47.55);
   ru5->SetPoint(2,2.22771,46.47);
   ru5->SetPoint(3,2.25,46.47);
/*
   TCutG *andy_pd96 = new TCutG("andy_pd96",8);
   andy_pd96->SetVarX("FRS_AoQ");
   andy_pd96->SetVarY("FRS_z");
   andy_pd96->SetPoint(0, 2.2017, 49.6497);
   andy_pd96->SetPoint(1, 2.20448, 49.053);
   andy_pd96->SetPoint(2, 2.19514, 48.8646);
   andy_pd96->SetPoint(3, 2.1824, 49.1891);
   andy_pd96->SetPoint(4, 2.18177, 49.4717);
   andy_pd96->SetPoint(5, 2.1853, 49.6811);
   andy_pd96->SetPoint(6, 2.19224, 49.7857);
   andy_pd96->SetPoint(7, 2.2017, 49.6497);
*/
   //*******************************************************************

   Int_t ParticlesInsideGate = 0;
   Int_t testcounter = 0;
   Int_t EvNum = 0;
   double timecorrection[36] = {-410.548, -371.8132,  -358.3364,  -343.3788,  -387.012, -383.9516,  -502.104, -357.868, -302.4824,  -374.2976,  -541.06,  -353.4456,  -337.8608,  -489.78,  -356.9296,  -322.0832,  -373.1748,  -345.6328,  -350.8328,  -375.1572,  -414.784, -344.1724,  -490.584, -549.336, -322.1784,  -365.8164,  -368.944, -342.3236,  -102.4084,  -407.632, -469.652, -424.06,  -615.712, -582.46,  -515.456, -488.432};
   double corr_eu[36] = {0, 7.14236, 3.011048, 4.2696, -1.759836, -1.838604, 40.0336, -1.611972, -2.899436, 6.54952, 0, 15.80204, 16.15804, 47.866, 9.30512, 13.38352, 30.96812, 11.12372, 11.89988, 17.62732, 12.30476, 17.3252, 95.144,	45.8544, 17.71824, 21.94832, 16.88864, 25.27368, 18.4072, 12.59856, 12.12048, 16.64344, 42.3556, 54, 50.278, 73.0552};



  std::vector<Long64_t> tag_fat_all;
  std::vector<Long64_t> ts_fat_all;
  Long64_t ts_fat, dT_frsfat_long, dT_FatT_long, Fat_FirstT_long, dT_frsfat_mult_long;


   while(myReader.Next()){	// && iterator<10000){
    

       AidaImpHit = 0;
       AidaDecHit = 0;
       AidaImpMult = 0;
       AidaDecMult = 0;
       //hEventNumber->Fill(*EventNumber);   
       testcounter = 0;
       EvNum = *EventNumber;
       bPlastMult = 0;
       bPlas_betaEv = 0;
       lastImpE = 0;
       lastDecE = 0;
       HighEImp.StripX = 0;
       HighEImp.StripY = 0;
       HighEImp.Energy = 0;
       HighEImp.Time = 0;

    int longisomermult=0;
    double FatE_Long[50];
    double FatT_Long[50];
       //***********************************************
   	    //cout << "new event" << endl;


if(pd96->IsInside(*FRS_AoQ,*FRS_z)){
          zvsaoq96pd->Fill(*FRS_AoQ,*FRS_z);



      for(int j = 0; j < 25; j++){


      if(Gal_E[j] > 0){
        Edt96_41->Fill(Gal_T[j] - Gal_T[25] , Gal_E[j]);
        EID->Fill(Gal_E[j],j);
      }
      if(Gal_E[j] != 0 && Gal_T[j] - Gal_T[25] > 300. && Gal_T[j] - Gal_T[25] < 6000.){

          for(int i = 0; i < 25; i++){
           
            if(Gal_E[i] != 0 && i != j && Gal_T[i] - Gal_T[25] > 300. && Gal_T[i] - Gal_T[25] < 6000. ){
              gg96->Fill(Gal_E[i],Gal_E[j]);     
            }
           
      }
    }
    
}//endsc41tag
}//end pd96


if(pd94->IsInside(*FRS_AoQ,*FRS_z)){
					zvsaoq94pd->Fill(*FRS_AoQ,*FRS_z);


      for(int j = 0; j < 25; j++){


	    if(Gal_E[j] > 0)Edt94_41->Fill(Gal_T[j] - Gal_T[25] , Gal_E[j]);

   		if(Gal_E[j] > 0 && Gal_T[j] - Gal_T[25] > 300. && Gal_T[j] - Gal_T[25] < 2500.){

      		for(int i = 0; i < 25; i++){
				   
				 if(i != j && Gal_T[i] - Gal_T[25] > 300. && Gal_T[i] - Gal_T[25] < 2500. ){
				 	 gg94->Fill(Gal_E[i],Gal_E[j]);			
				 }
				   
			}
		}
}

}//End if 94Pd

//96 Pd cut

 


   iterator++;

}

   //**************************************************
   // WRITING HISTOGRAMS TO FILE
   // Choose histograms to write to file


  gg94->Write();
  gg96->Write();

	Edt94_41->Write();
	Edt96_41->Write();

  EID->Write();

zvsaoq96pd->Write();
zvsaoq94pd->Write();
zvsaoq->Write();




out->Close(); 




delete gROOT->FindObject("Edt94_41");
delete gROOT->FindObject("Edt96_41");

delete gROOT->FindObject("EID");


delete gROOT->FindObject("gg96");
delete gROOT->FindObject("gg94");

delete gROOT->FindObject("zvsaoq96pd");
delete gROOT->FindObject("zvsaoq94pd");
delete gROOT->FindObject("zvsaoq");

//**************************************************


}

void BatchAnalysis(){

/*
AnalyzeTree("/home/sj00239/gsi/tree_sorting/data/","S480f030noaidadec_50.root");
AnalyzeTree("/home/sj00239/gsi/tree_sorting/data/","S480f014noaidadec_50_1.root");
AnalyzeTree("/home/sj00239/gsi/tree_sorting/data/","S480f023noaidadec_50_1.root");
AnalyzeTree("/home/sj00239/gsi/tree_sorting/data/","S480f028noaidadec_10.root");
AnalyzeTree("/home/sj00239/gsi/tree_sorting/data/","S480f031noaidadec_130_1.root");
AnalyzeTree("/home/sj00239/gsi/tree_sorting/data/","S480f022noaidadec_10_1.root");
*/


AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f004noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f004noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f005noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f005noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f006noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f006noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f006noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f006noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f007noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f008noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f009noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_10_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_20_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_30.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_30_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_40.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_40_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_50.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_50_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_60.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_60_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_70.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_70_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_70_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_80.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_80_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_80_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f010noaidadec_80_3.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f011noaidadec_0.root");   
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f011noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f012noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f012noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f012noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f012noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f013noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f013noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_10_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_20_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_20_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_30.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_30_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_30_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_40.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_40_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_40_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_50.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_50_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_50_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f014noaidadec_60.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f015noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f016noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f016noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f016noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f016noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f016noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f016noaidadec_10_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f016noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f017noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f017noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f018noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f019noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f019noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f019noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f020noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f021noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f022noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f022noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f022noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f022noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_0__2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_10_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_10__2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_20_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_20_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_20__2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_30.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_30_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_30_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_30__2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_40.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_40__2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_50.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_50_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_60.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_60_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_70.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_70_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_80.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_80_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_80_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_80__2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_90.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f023noaidadec_90_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f026noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f026noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f026noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f026noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f027noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_10_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_20_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_20_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_30.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_30_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_30_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_40.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f028noaidadec_40_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_20_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_30.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_30_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_40.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_40_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_50.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_50_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_60.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_60_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_70.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f029noaidadec_70_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_20_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_30.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_30_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_40.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_40_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_50.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_50_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_60.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_60_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_70_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_70__1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_70__2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_80.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_80_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_80_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_90.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_90_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_90_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_100.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_100_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_100_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_110.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_110_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_110_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_120.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_120_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_120_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_130.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_130_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_130_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_140.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_140_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_140_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_150.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_150_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_150_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_160.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_160_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_160_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_170.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_170_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_170_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_180.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_180_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_180_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_190.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_190_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_190_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_200.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_200_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_200_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_210.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_210_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_210_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_220.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_220_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_220_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_230.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_230_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_230_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_240.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_240_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_240_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_250.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_250_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_250_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_260.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_260_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_260_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_270.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_270_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_270_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_280.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_280_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_280_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_290.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_290_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_290_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_300.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_300_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_300_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_310.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_310_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_310_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_320.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_320_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_320_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_330.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_330_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_330_2.roo");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f030noaidadec_340.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_0.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_0_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_0_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_10.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_10_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_10_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_20.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_20_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_20_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_30.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_30_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_30_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_40.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_40_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_40_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_50.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_50_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_50_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_60.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_60_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_60_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_70.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_70_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_70_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_80.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_80_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_80_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_90.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_90_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_90_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_100.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_100_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_100_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_110.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_110_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_110_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_120.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_120_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_120_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_130.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_130_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_130_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_140.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_140_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_140_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_150.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_150_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_150_2.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_160.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f031noaidadec_160_1.root");
AnalyzeTree("/lustre/gamma/S480/trees/noaida_decays/","S480f032noaidadec_0.root");


}

