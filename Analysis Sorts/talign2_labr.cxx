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
};

class AidaHit : public TObject
{
public:
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

  int64_t Time;
  int64_t TimeFront;
  int64_t TimeBack;
  int64_t FastTime;
  int64_t FastTimeFront;
  int64_t FastTimeBack;

  AidaHit() { Zero(); }
  void Zero() {}
  virtual ~AidaHit() {}

  ClassDef(AidaHit, 1)
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
    
    TH1F *det0dt = new TH1F("det0dt","det0dt",40000,-20000,20000);
    TH1F *det1dt = new TH1F("det1dt","det1dt",40000,-20000,20000);
    TH1F *det2dt = new TH1F("det2dt","det2dt",40000,-20000,20000);
    TH1F *det3dt = new TH1F("det3dt","det3dt",40000,-20000,20000);
    TH1F *det4dt = new TH1F("det4dt","det4dt",40000,-20000,20000);
    TH1F *det5dt = new TH1F("det5dt","det5dt",40000,-20000,20000);
    TH1F *det6dt = new TH1F("det6dt","det6dt",40000,-20000,20000);
    TH1F *det7dt = new TH1F("det7dt","det7dt",40000,-20000,20000);
    TH1F *det8dt = new TH1F("det8dt","det8dt",40000,-20000,20000);
    TH1F *det9dt = new TH1F("det9dt","det9dt",40000,-20000,20000);
    TH1F *det10dt = new TH1F("det10dt","det10dt",40000,-20000,20000);
    TH1F *det11dt = new TH1F("det11dt","det11dt",40000,-20000,20000);
    TH1F *det12dt = new TH1F("det12dt","det12dt",40000,-20000,20000);
    TH1F *det13dt = new TH1F("det13dt","det13dt",40000,-20000,20000);
    TH1F *det14dt = new TH1F("det14dt","det14dt",40000,-20000,20000);
    TH1F *det15dt = new TH1F("det15dt","det15dt",40000,-20000,20000);
    TH1F *det16dt = new TH1F("det16dt","det16dt",40000,-20000,20000);
    TH1F *det17dt = new TH1F("det17dt","det17dt",40000,-20000,20000);
    TH1F *det18dt = new TH1F("det18dt","det18dt",40000,-20000,20000);
    TH1F *det19dt = new TH1F("det19dt","det19dt",40000,-20000,20000);
    TH1F *det20dt = new TH1F("det20dt","det20dt",40000,-20000,20000);
    TH1F *det21dt = new TH1F("det21dt","det21dt",40000,-20000,20000);
    TH1F *det22dt = new TH1F("det22dt","det22dt",40000,-20000,20000);
    TH1F *det23dt = new TH1F("det23dt","det23dt",40000,-20000,20000);
    TH1F *det24dt = new TH1F("det24dt","det24dt",40000,-20000,20000);
    TH1F *det25dt = new TH1F("det25dt","det25dt",40000,-20000,20000);
    TH1F *det26dt = new TH1F("det26dt","det26dt",40000,-20000,20000);
    TH1F *det27dt = new TH1F("det27dt","det27dt",40000,-20000,20000);
    TH1F *det29dt = new TH1F("det29dt","det29dt",40000,-20000,20000);
    TH1F *det30dt = new TH1F("det30dt","det30dt",40000,-20000,20000);
    TH1F *det31dt = new TH1F("det31dt","det31dt",40000,-20000,20000);
    TH1F *det28dt = new TH1F("det28dt","det28dt",40000,-20000,20000);
    TH1F *det32dt = new TH1F("det32dt","det32dt",40000,-20000,20000);
    TH1F *det33dt = new TH1F("det33dt","det33dt",40000,-20000,20000);
    TH1F *det34dt = new TH1F("det34dt","det34dt",40000,-20000,20000);
    TH1F *det35dt = new TH1F("det35dt","det35dt",40000,-20000,20000);


    TH1F *det0dta = new TH1F("det0dta","det0dta",400,-200,200);
    TH1F *det1dta = new TH1F("det1dta","det1dta",400,-200,200);
    TH1F *det2dta = new TH1F("det2dta","det2dta",400,-200,200);
    TH1F *det3dta = new TH1F("det3dta","det3dta",400,-200,200);
    TH1F *det4dta = new TH1F("det4dta","det4dta",400,-200,200);
    TH1F *det5dta = new TH1F("det5dta","det5dta",400,-200,200);
    TH1F *det6dta = new TH1F("det6dta","det6dta",400,-200,200);
    TH1F *det7dta = new TH1F("det7dta","det7dta",400,-200,200);
    TH1F *det8dta = new TH1F("det8dta","det8dta",400,-200,200);
    TH1F *det9dta = new TH1F("det9dta","det9dta",400,-200,200);
    TH1F *det10dta = new TH1F("det10dta","det10dta",400,-200,200);
    TH1F *det11dta = new TH1F("det11dta","det11dta",400,-200,200);
    TH1F *det12dta = new TH1F("det12dta","det12dta",400,-200,200);
    TH1F *det13dta = new TH1F("det13dta","det13dta",400,-200,200);
    TH1F *det14dta = new TH1F("det14dta","det14dta",400,-200,200);
    TH1F *det15dta = new TH1F("det15dta","det15dta",400,-200,200);
    TH1F *det16dta = new TH1F("det16dta","det16dta",400,-200,200);
    TH1F *det17dta = new TH1F("det17dta","det17dta",400,-200,200);
    TH1F *det18dta = new TH1F("det18dta","det18dta",400,-200,200);
    TH1F *det19dta = new TH1F("det19dta","det19dta",400,-200,200);
    TH1F *det20dta = new TH1F("det20dta","det20dta",400,-200,200);
    TH1F *det21dta = new TH1F("det21dta","det21dta",400,-200,200);
    TH1F *det22dta = new TH1F("det22dta","det22dta",400,-200,200);
    TH1F *det23dta = new TH1F("det23dta","det23dta",400,-200,200);
    TH1F *det24dta = new TH1F("det24dta","det24dta",400,-200,200);
    TH1F *det25dta = new TH1F("det25dta","det25dta",400,-200,200);
    TH1F *det26dta = new TH1F("det26dta","det26dta",400,-200,200);
    TH1F *det27dta = new TH1F("det27dta","det27dta",400,-200,200);
    TH1F *det29dta = new TH1F("det29dta","det29dta",400,-200,200);
    TH1F *det30dta = new TH1F("det30dta","det30dta",400,-200,200);
    TH1F *det31dta = new TH1F("det31dta","det31dta",400,-200,200);
    TH1F *det28dta = new TH1F("det28dta","det28dta",400,-200,200);
    TH1F *det32dta = new TH1F("det32dta","det32dta",400,-200,200);
    TH1F *det33dta = new TH1F("det33dta","det33dta",400,-200,200);
    TH1F *det34dta = new TH1F("det34dta","det34dta",400,-200,200);
    TH1F *det35dta = new TH1F("det35dta","det35dta",400,-200,200);

    TH2F *TvsID = new TH2F("TvsID","tvsID",40000,-2000,2000,36,0,36);
    TH2F *TvsIDa = new TH2F("TvsIDa","tvsIDa",80000,-2000,6000,36,0,36);
    TH2F *TvsIDapd94 = new TH2F("TvsIDapd94","tvsIDapd94",4000,-200,200,36,0,36);
    TH2F *TvsIDapd96 = new TH2F("TvsIDapd96","tvsIDapd96",4000,-200,200,36,0,36);

        TH2F *EvsIDa = new TH2F("EvsIDa","EvsIDa",6000,-2000,4000,36,0,36);

    TH1F *sc41_r = new TH1F("sc41_r","sc41_r",100000,-50000,50000);
    TH1F *sc41_l = new TH1F("sc41_l","sc41_l",100000,-50000,50000);


    TH2F *TvsIDadet15 = new TH2F("TvsIDadet15","TvsIDadet15",3000,-1000,2000,36,0,36);
    TH2F *TvsIDadet32 = new TH2F("TvsIDadet32","TvsIDadet32",3000,-1000,2000,36,0,36);

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
    outpath = "~/gsi/tree_sorting/hists/LaBrTCorr_Sept_";
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
   TTreeReaderArray<double> LaBr_E(myReader,"AnlEvent.pFat_QDC_E[50]");
   TTreeReaderArray<Long64_t> FatTDC_T(myReader,"AnlEvent.pFat_TDC_T[50]");  
   TTreeReaderValue<float> FRS_z(myReader,"AnlEvent.pFRS_z");
   TTreeReaderValue<float> FRS_AoQ(myReader,"AnlEvent.pFRS_AoQ");
   TTreeReaderArray<int> QDCID(myReader,"AnlEvent.pFat_QDC_ID[50]");
   TTreeReaderArray<int> TDCID(myReader,"AnlEvent.pFat_TDC_ID[50]");
   TTreeReaderArray<int> QDCID_singles(myReader,"AnlEvent.pFat_QDC_Singles_ID[50]");
   TTreeReaderArray<int> TDCID_singles(myReader,"AnlEvent.pFat_TDC_Singles_ID[50]");
   TTreeReaderArray<Long64_t> SC40_T(myReader,"AnlEvent.pSC40[10]"); 
   TTreeReaderArray<Long64_t> SC41_T(myReader,"AnlEvent.pSC41[10]"); 
   TTreeReaderValue<int> Fatmult(myReader,"AnlEvent.pFatmult");
   TTreeReaderArray<float> SC_E(myReader,"AnlEvent.pFRS_sci_e[12]"  );


   //*******************************************************************
   // DEFINE FRS GATES HERE
   TCutG *pd94 = new TCutG("pd94",7);
   pd94->SetVarX("FRS_AoQ");
   pd94->SetVarY("FRS_z");
   pd94->SetPoint(0,2.05607,49.8055);
   pd94->SetPoint(1,2.05777,49.4359);
   pd94->SetPoint(2,2.06314,49.3802);
   pd94->SetPoint(3,2.06785,49.1777);
   pd94->SetPoint(4,2.08703,49.1827);
   pd94->SetPoint(5,2.08654,49.2688);
   pd94->SetPoint(6,2.06842,49.9371);
   
   TCutG *pd96 = new TCutG("pd96",4);
   pd96->SetVarX("FRS_AoQ");
   pd96->SetVarY("FRS_z");
   pd96->SetPoint(0,2.095,50.1397);
   pd96->SetPoint(1,2.1102,49.2739);
   pd96->SetPoint(2,2.1297,49.3488);
   pd96->SetPoint(3,2.12987,50.3371);

   TCutG *ag96 = new TCutG("ag96",5);
   ag96->SetVarX("FRS_AoQ");
   ag96->SetVarY("FRS_z");
   ag96->SetPoint(0, 2.10063, 50.9089);
   ag96->SetPoint(1, 2.10689, 50.3888);
   ag96->SetPoint(2, 2.12315, 50.4755);
   ag96->SetPoint(3, 2.11852, 51.1343);   
   ag96->SetPoint(4, 2.10239, 51.1343);   


   TCutG *ru94 = new TCutG("ru94",4);
   ru94->SetVarX("FRS_AoQ");
   ru94->SetVarY("FRS_z");
   ru94->SetPoint(0, 2.07982, 47.8587);
   ru94->SetPoint(1, 2.07972, 47.372);
   ru94->SetPoint(2, 2.1032, 47.3347);
   ru94->SetPoint(3, 2.1032, 47.9291);
   //*******************************************************************

   Int_t ParticlesInsideGate = 0;
   Int_t testcounter = 0;
   Int_t EvNum = 0;
   //Old time corr
   //double timecorrection[36] = {0, -19.175,-30.375,-39.8,-15.425,-17.775,82.3,-32.925,-69.25,-18.55,-152.6,-25.975,-34.15,80.325,-26.25,-46.8,-3.5,-32.525,-29.7,-12.025,-11.05,-30.85,109.575,115.275,-43.95,-13.9,-15.8,-26.725,0.,6.85,44.375,19.15,155.925,140.65,97.1,93.75};   
   //My time corr
   double timecorrection[36] = {-410.548, -371.8132,  -358.3364,  -343.3788,  -387.012, -383.9516,  -502.104, -357.868, -302.4824,  -374.2976,  -541.06,  -353.4456,  -337.8608,  -489.78,  -356.9296,  -322.0832,  -373.1748,  -345.6328,  -350.8328,  -375.1572,  -414.784, -344.1724,  -490.584, -549.336, -322.1784,  -365.8164,  -368.944, -342.3236,  -102.4084,  -407.632, -469.652, -424.06,  -615.712, -582.46,  -515.456, -488.432};
   double FatTDC_Talign[50];

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


       //***********************************************
   	    //cout << "new event" << endl;


  for(int i = 0; i < *Fatmult; i++){

    FatTDC_Talign[i] = (FatTDC_T[i] - timecorrection[TDCID[i]]);

  }

if(SC41_T[0] != 0.){

  for(int i = 0; i < *Fatmult; i++){


    if(FatTDC_T[i] > 0.){

    if(TDCID[i] == 0)det0dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 1)det1dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 2)det2dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 3)det3dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 4)det4dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 5)det5dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 6)det6dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 7)det7dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 8)det8dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 9)det9dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 10)det10dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 11)det11dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 12)det12dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 13)det13dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 14)det14dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 15)det15dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 16)det16dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 17)det17dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 18)det18dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 19)det19dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 20)det20dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 21)det21dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 22)det22dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 23)det23dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 24)det24dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 25)det25dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 26)det26dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 27)det27dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 28)det28dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 29)det29dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 30)det30dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 31)det31dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 32)det32dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 33)det33dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 34)det34dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 35)det35dt->Fill((FatTDC_T[i] - SC41_T[0])*0.025);

    if(TDCID[i] == 0)det0dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 1)det1dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 2)det2dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 3)det3dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 4)det4dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 5)det5dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 6)det6dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 7)det7dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 8)det8dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 9)det9dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 10)det10dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 11)det11dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 12)det12dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 13)det13dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 14)det14dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 15)det15dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 16)det16dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 17)det17dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 18)det18dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 19)det19dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 20)det20dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 21)det21dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 22)det22dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 23)det23dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 24)det24dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 25)det25dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 26)det26dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 27)det27dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 28)det28dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 29)det29dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 30)det30dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 31)det31dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 32)det32dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 33)det33dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 34)det34dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
    if(TDCID[i] == 35)det35dta->Fill((FatTDC_Talign[i] - SC41_T[0])*0.025);
  
    if(SC_E[6] > 0.){
      TvsID->Fill(((FatTDC_T[i] - SC41_T[0])*0.025), TDCID[i]);
      TvsIDa->Fill((FatTDC_Talign[i])*0.025, TDCID[i]);
      EvsIDa->Fill(LaBr_E[i], TDCID[i]);
      sc41_r->Fill(SC41_T[0]*0.025);
      sc41_l->Fill(SC40_T[0]*0.025);

      if(TDCID[i] == 15){
        for (int j = 0; j < *Fatmult; j++)
        {
            if(TDCID[j] != 15) TvsIDadet15->Fill((FatTDC_Talign[i] - FatTDC_Talign[j])*0.025, TDCID[j] );
        }
        
      }


      if(TDCID[i] == 33){
        for (int j = 0; j < *Fatmult; j++)
        {
            if(TDCID[j] != 33) TvsIDadet32->Fill((FatTDC_Talign[i] - FatTDC_Talign[j])*0.025, TDCID[j] );
        }
        
      }

    }
    }
  }
}

    if(pd94->IsInside(*FRS_AoQ,*FRS_z)){
      if(Gal_T[25] != 0. && Gal_T[i] > 0. && LaBr_E[i] > 0. && LaBr_E[i] < 100.){

        for(int i = 0; i < *Fatmult; i++){
          TvsIDapd94->Fill(((FatTDC_Talign[i] - SC41_T[0])*0.025), TDCID[i]);
        }
      
      }
    }

    if(pd96->IsInside(*FRS_AoQ,*FRS_z)){
      if(Gal_T[25] != 0. && Gal_T[i] > 0. && LaBr_E[i] > 0. && LaBr_E[i] < 100.){

        for(int i = 0; i < *Fatmult; i++){
          TvsIDapd94->Fill(((FatTDC_Talign[i] - SC41_T[0])*0.025), TDCID[i]);
        }

      }
    }

   iterator++;
   
}
   

   //**************************************************
   // WRITING HISTOGRAMS TO FILE
   // Choose histograms to write to file

  det0dt->Write();
  det1dt->Write();
  det2dt->Write();
  det3dt->Write();
  det4dt->Write();
  det5dt->Write();
  det6dt->Write();
  det7dt->Write();
  det8dt->Write();
  det9dt->Write();
  det10dt->Write();
  det11dt->Write();
  det12dt->Write();
  det13dt->Write();
  det14dt->Write();
  det15dt->Write();
  det16dt->Write();
  det17dt->Write();
  det18dt->Write();
  det19dt->Write();
  det20dt->Write();
  det21dt->Write();
  det22dt->Write();
  det23dt->Write();
  det24dt->Write();
  det25dt->Write();
  det26dt->Write();
  det27dt->Write();
  det28dt->Write();
  det29dt->Write();
  det30dt->Write();
  det31dt->Write();
  det32dt->Write();
  det33dt->Write();
  det34dt->Write();
  det35dt->Write();

  det0dta->Write();
  det1dta->Write();
  det2dta->Write();
  det3dta->Write();
  det4dta->Write();
  det5dta->Write();
  det6dta->Write();
  det7dta->Write();
  det8dta->Write();
  det9dta->Write();
  det10dta->Write();
  det11dta->Write();
  det12dta->Write();
  det13dta->Write();
  det14dta->Write();
  det15dta->Write();
  det16dta->Write();
  det17dta->Write();
  det18dta->Write();
  det19dta->Write();
  det20dta->Write();
  det21dta->Write();
  det22dta->Write();
  det23dta->Write();
  det24dta->Write();
  det25dta->Write();
  det26dta->Write();
  det27dta->Write();
  det28dta->Write();
  det29dta->Write();
  det30dta->Write();
  det31dta->Write();
  det32dta->Write();
  det33dta->Write();
  det34dta->Write();
  det35dta->Write();


EvsIDa->Write();
TvsID->Write();
TvsIDa->Write();
TvsIDapd96->Write();
TvsIDapd94->Write();
      sc41_r->Write();
      sc41_l->Write();
TvsIDadet15->Write();
TvsIDadet32->Write();
     out->Close(); 

delete gROOT->FindObject("det0dt");
delete gROOT->FindObject("det1dt");
delete gROOT->FindObject("det2dt");
delete gROOT->FindObject("det3dt");
delete gROOT->FindObject("det4dt");
delete gROOT->FindObject("det5dt");
delete gROOT->FindObject("det6dt");
delete gROOT->FindObject("det7dt");
delete gROOT->FindObject("det8dt");
delete gROOT->FindObject("det9dt");
delete gROOT->FindObject("det10dt");
delete gROOT->FindObject("det11dt");
delete gROOT->FindObject("det12dt");
delete gROOT->FindObject("det13dt");
delete gROOT->FindObject("det14dt");
delete gROOT->FindObject("det15dt");
delete gROOT->FindObject("det16dt");
delete gROOT->FindObject("det17dt");
delete gROOT->FindObject("det18dt");
delete gROOT->FindObject("det19dt");
delete gROOT->FindObject("det20dt");
delete gROOT->FindObject("det21dt");
delete gROOT->FindObject("det22dt");
delete gROOT->FindObject("det23dt");
delete gROOT->FindObject("det24dt");
delete gROOT->FindObject("det25dt");
delete gROOT->FindObject("det26dt");
delete gROOT->FindObject("det27dt");
delete gROOT->FindObject("det28dt");
delete gROOT->FindObject("det29dt");
delete gROOT->FindObject("det30dt");
delete gROOT->FindObject("det31dt");
delete gROOT->FindObject("det32dt");
delete gROOT->FindObject("det33dt");
delete gROOT->FindObject("det34dt");
delete gROOT->FindObject("det35dt");

delete gROOT->FindObject("det0dta");
delete gROOT->FindObject("det1dta");
delete gROOT->FindObject("det2dta");
delete gROOT->FindObject("det3dta");
delete gROOT->FindObject("det4dta");
delete gROOT->FindObject("det5dta");
delete gROOT->FindObject("det6dta");
delete gROOT->FindObject("det7dta");
delete gROOT->FindObject("det8dta");
delete gROOT->FindObject("det9dta");
delete gROOT->FindObject("det10dta");
delete gROOT->FindObject("det11dta");
delete gROOT->FindObject("det12dta");
delete gROOT->FindObject("det13dta");
delete gROOT->FindObject("det14dta");
delete gROOT->FindObject("det15dta");
delete gROOT->FindObject("det16dta");
delete gROOT->FindObject("det17dta");
delete gROOT->FindObject("det18dta");
delete gROOT->FindObject("det19dta");
delete gROOT->FindObject("det20dta");
delete gROOT->FindObject("det21dta");
delete gROOT->FindObject("det22dta");
delete gROOT->FindObject("det23dta");
delete gROOT->FindObject("det24dta");
delete gROOT->FindObject("det25dta");
delete gROOT->FindObject("det26dta");
delete gROOT->FindObject("det27dta");
delete gROOT->FindObject("det28dta");
delete gROOT->FindObject("det29dta");
delete gROOT->FindObject("det30dta");
delete gROOT->FindObject("det31dta");
delete gROOT->FindObject("det32dta");
delete gROOT->FindObject("det33dta");
delete gROOT->FindObject("det34dta");
delete gROOT->FindObject("det35dta");

delete gROOT->FindObject("TvsID");
delete gROOT->FindObject("TvsIDa");
delete gROOT->FindObject("TvsIDapd96");
delete gROOT->FindObject("TvsIDapd94");
   //**************************************************


}

void BatchAnalysis(){
  

    //char *path = "/media/sj00239/sjdrive/DESPEC/";
    //char *file = "f44_anal.root";
        

    //Mar 10 18:19 - 19:28
  
AnalyzeTree("./data/","S480f014noaidadec_50_1.root");

   
    //Current total 1:09 + 0:02 + 00:31 + 00:50 + 00:11 + 00:29 + 03:02= 6:13 


}
