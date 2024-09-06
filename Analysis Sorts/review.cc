// To run: root -l ROOTFILE.root
// .x bgs.cc

#include <iostream>
#include <string>
#include "TH1D.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH2D.h"
#include "TH2I.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TRandom3.h"
#include "TVirtualFitter.h"
#include "TList.h"
#include "TFormula.h"
#include "setup.cc"

using namespace std;



void review() {

	TFile f("./hists/cubes_combo7.root");

	 TH2F *pid = (TH2F*)f.Get("zvsaoq");
	 TH2F *pid94 = (TH2F*)f.Get("zvsaoqpd94cut");
	 TH2F *pid96 = (TH2F*)f.Get("zvsaoqpd96cut");


	 TH2D *Edt = (TH2D*)f.Get("Edt");

	 TH2D *Edt96 = (TH2D*)f.Get("Edt96");
	 TH2D *Edt96_Plastic = (TH2D*)f.Get("Edt96_Plastic");
	 TH2D *Edt96_SC41 = (TH2D*)f.Get("Edt96_SC41");
	 TH2D *Edt96_AIDA = (TH2D*)f.Get("Edt96_AIDA");
	 TH2D *Edt96_SC41_Plastic = (TH2D*)f.Get("Edt96_SC41_Plastic");
	 TH2D *Edt96_Plastic_AIDA = (TH2D*)f.Get("Edt96_Plastic_AIDA");
	 TH2D *Edt96_SC41_AIDA = (TH2D*)f.Get("Edt96_SC41_AIDA");
	 TH2D *Edt96_SC41_Plastic_AIDA = (TH2D*)f.Get("Edt96_SC41_Plastic_AIDA");

	 TH2D *Edt94 = (TH2D*)f.Get("Edt94");
	 TH2D *Edt94_Plastic = (TH2D*)f.Get("Edt94_Plastic");
	 TH2D *Edt94_SC41 = (TH2D*)f.Get("Edt94_SC41");
	 TH2D *Edt94_AIDA = (TH2D*)f.Get("Edt94_AIDA");
	 TH2D *Edt94_SC41_Plastic = (TH2D*)f.Get("Edt94_SC41_Plastic");
	 TH2D *Edt94_Plastic_AIDA = (TH2D*)f.Get("Edt94_Plastic_AIDA");
	 TH2D *Edt94_SC41_AIDA = (TH2D*)f.Get("Edt94_SC41_AIDA");
	 TH2D *Edt94_SC41_Plastic_AIDA = (TH2D*)f.Get("Edt94_SC41_Plastic_AIDA");
	 
	 pid->SetDirectory(0);
	 pid94->SetDirectory(0);
	 pid96->SetDirectory(0);

	 Edt->SetDirectory(0);

	 Edt96->SetDirectory(0);
	 Edt96_Plastic->SetDirectory(0);
	 Edt96_SC41->SetDirectory(0);
	 Edt96_AIDA->SetDirectory(0);
	 Edt96_SC41_Plastic->SetDirectory(0);
	 Edt96_Plastic_AIDA->SetDirectory(0);
	 Edt96_SC41_AIDA->SetDirectory(0);
	 Edt96_SC41_Plastic_AIDA->SetDirectory(0);
	 
	 Edt94->SetDirectory(0);
	 Edt94_Plastic->SetDirectory(0);
	 Edt94_SC41->SetDirectory(0);
	 Edt94_AIDA->SetDirectory(0);
	 Edt94_SC41_Plastic->SetDirectory(0);
	 Edt94_Plastic_AIDA->SetDirectory(0);
	 Edt94_SC41_AIDA->SetDirectory(0);
	 Edt94_SC41_Plastic_AIDA->SetDirectory(0);

	 f.Close();

	

	TFile *lts = new TFile("review_combo7.root","RECREATE");


	TH1D* Edt_Projection = Edt->ProjectionY("edtproj",0,30000);
 	Edt_Projection->SetTitle("Ungated Singles E_{#gamma}");
	gamma(Edt_Projection);

	TH1D* Edt96_Projection = Edt96->ProjectionY("edt96proj",0,30000);
 	Edt96_Projection->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection);

	TH1D* Edt94_Projection = Edt94->ProjectionY("edt94proj",0,30000);
 	Edt94_Projection->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection);

//Pd 96 edt projections
	TH1D* Edt96_Projection_np = Edt96->ProjectionY("edt96proj_np",10800,18400);
 	Edt96_Projection_np->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np);

	TH1D* Edt96_Projection_np_Plastic = Edt96_Plastic->ProjectionY("edt96proj_np_Plastic",10800,18400);
 	Edt96_Projection_np_Plastic->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np_Plastic);

	TH1D* Edt96_Projection_np_SC41 = Edt96_SC41->ProjectionY("edt96proj_np_SC41",10800,18400);
 	Edt96_Projection_np_SC41->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np_SC41);

	TH1D* Edt96_Projection_np_AIDA = Edt96_AIDA->ProjectionY("edt96proj_np_AIDA",10800,18400);
 	Edt96_Projection_np_AIDA->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np_AIDA);

	TH1D* Edt96_Projection_np_SC41_Plastic = Edt96_SC41_Plastic->ProjectionY("edt96proj_np_SC41_Plastic",10800,18400);
 	Edt96_Projection_np_SC41_Plastic->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np_SC41_Plastic);

	TH1D* Edt96_Projection_np_Plastic_AIDA = Edt96_Plastic_AIDA->ProjectionY("edt96proj_np_Plastic_AIDA",10800,18400);
 	Edt96_Projection_np_Plastic_AIDA->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np_Plastic_AIDA);

	TH1D* Edt96_Projection_np_SC41_AIDA = Edt96_SC41_AIDA->ProjectionY("edt96proj_np_SC41_AIDA",10800,18400);
 	Edt96_Projection_np_SC41_AIDA->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np_SC41_AIDA);

	TH1D* Edt96_Projection_np_SC41_Plastic_AIDA = Edt96_SC41_Plastic_AIDA->ProjectionY("edt96proj_np_SC41_Plastic_AIDA",10800,18400);
 	Edt96_Projection_np_SC41_Plastic_AIDA->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt96_Projection_np_SC41_Plastic_AIDA);

	TCanvas pd96canvas;
	Edt96_Projection_np->SetLineColor(1);
	Edt96_Projection_np->Draw();
	Edt96_Projection_np_Plastic->SetLineColor(2);
	Edt96_Projection_np_Plastic->Draw("same");
	Edt96_Projection_np_SC41->SetLineColor(3);
	Edt96_Projection_np_SC41->Draw("same");
	Edt96_Projection_np_AIDA->SetLineColor(4);
	Edt96_Projection_np_AIDA->Draw("same");
	Edt96_Projection_np_SC41_Plastic->SetLineColor(5);
	Edt96_Projection_np_SC41_Plastic->Draw("same");
	Edt96_Projection_np_Plastic_AIDA->SetLineColor(6);
	Edt96_Projection_np_Plastic_AIDA->Draw("same");
	Edt96_Projection_np_SC41_AIDA->SetLineColor(7);
	Edt96_Projection_np_SC41_AIDA->Draw("same");
	Edt96_Projection_np_SC41_Plastic_AIDA->SetLineColor(8);
	Edt96_Projection_np_SC41_Plastic_AIDA->Draw("same");

    auto legend96 = new TLegend(0.1,0.7,0.48,0.9);
    legend96->SetHeader("Gamma Ray Gating Conditions","C"); // option "C" allows to center the header
    legend96->AddEntry(Edt96_Projection_np,"PID","l");
    legend96->AddEntry(Edt96_Projection_np_Plastic,"PID + Plastic Energy","l");
    legend96->AddEntry(Edt96_Projection_np_SC41,"PID + SC41/SC42 Energy","l");
    legend96->AddEntry(Edt96_Projection_np_AIDA,"PID + Stopped in AIDA","l");
    legend96->AddEntry(Edt96_Projection_np_SC41_Plastic,"PID + SC41/SC42 Energy + Plastic Energy","l");
    legend96->AddEntry(Edt96_Projection_np_Plastic_AIDA,"PID + Plastic Energy + Stopped in AIDA","l");
    legend96->AddEntry(Edt96_Projection_np_SC41_AIDA,"PID + SC41/42 Energy + Stopped in AIDA","l");
    legend96->AddEntry(Edt96_Projection_np_SC41_Plastic_AIDA,"PID + SC41/42 Energy + Stopped in AIDA + Plastic Energy","l");
    legend96->Draw("same");
	pd96canvas.SetTitle("^{96}Pd E_{#gamma} Projection");
	pd96canvas.Write();




	TH1D* Edt94_Projection_np = Edt94->ProjectionY("edt94proj_np",10800,18400);
 	Edt94_Projection_np->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection_np);

	TH1D* Edt94_Projection_np_Plastic = Edt94_Plastic->ProjectionY("edt94proj_np_Plastic",10800,18400);
 	Edt94_Projection_np_Plastic->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection_np_Plastic);

	TH1D* Edt94_Projection_np_SC41 = Edt94_SC41->ProjectionY("edt94proj_np_SC41",10800,18400);
 	Edt94_Projection_np_SC41->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection_np_SC41);

	TH1D* Edt94_Projection_np_AIDA = Edt94_AIDA->ProjectionY("edt94proj_np_AIDA",10800,18400);
 	Edt94_Projection_np_AIDA->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection_np_AIDA);

	TH1D* Edt94_Projection_np_SC41_Plastic = Edt94_SC41_Plastic->ProjectionY("edt94proj_np_SC41_Plastic",10800,18400);
 	Edt94_Projection_np_SC41_Plastic->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection_np_SC41_Plastic);

	TH1D* Edt94_Projection_np_Plastic_AIDA = Edt94_Plastic_AIDA->ProjectionY("edt94proj_np_Plastic_AIDA",10800,18400);
 	Edt94_Projection_np_Plastic_AIDA->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection_np_Plastic_AIDA);

	TH1D* Edt94_Projection_np_SC41_AIDA = Edt94_SC41_AIDA->ProjectionY("edt94proj_np_SC41_AIDA",10800,18400);
 	Edt94_Projection_np_SC41_AIDA->SetTitle("^{94}Pd E_{#gamma}");
	gamma(Edt94_Projection_np_SC41_AIDA);

	TH1D* Edt94_Projection_np_SC41_Plastic_AIDA = Edt94_SC41_Plastic_AIDA->ProjectionY("edt94proj_np_SC41_Plastic_AIDA",10800,18400);
 	Edt94_Projection_np_SC41_Plastic_AIDA->SetTitle("^{96}Pd E_{#gamma}");
	gamma(Edt94_Projection_np_SC41_Plastic_AIDA);


	TCanvas pd94canvas;
	Edt94_Projection_np->SetLineColor(1);
	Edt94_Projection_np->Draw();
	Edt94_Projection_np_Plastic->SetLineColor(2);
	Edt94_Projection_np_Plastic->Draw("same");
	Edt94_Projection_np_SC41->SetLineColor(3);
	Edt94_Projection_np_SC41->Draw("same");
	Edt94_Projection_np_AIDA->SetLineColor(4);
	Edt94_Projection_np_AIDA->Draw("same");
	Edt94_Projection_np_SC41_Plastic->SetLineColor(5);
	Edt94_Projection_np_SC41_Plastic->Draw("same");
	Edt94_Projection_np_Plastic_AIDA->SetLineColor(6);
	Edt94_Projection_np_Plastic_AIDA->Draw("same");
	Edt94_Projection_np_SC41_AIDA->SetLineColor(7);
	Edt94_Projection_np_SC41_AIDA->Draw("same");
	Edt94_Projection_np_SC41_Plastic_AIDA->SetLineColor(8);
	Edt94_Projection_np_SC41_Plastic_AIDA->Draw("same");

    auto legend94 = new TLegend(0.1,0.7,0.48,0.9);
    legend94->SetHeader("Gamma Ray Gating Conditions","C"); // option "C" allows to center the header
    legend94->AddEntry(Edt94_Projection_np,"PID","l");
    legend94->AddEntry(Edt94_Projection_np_Plastic,"PID + Plastic Energy","l");
    legend94->AddEntry(Edt94_Projection_np_SC41,"PID + SC41/SC42 Energy","l");
    legend94->AddEntry(Edt94_Projection_np_AIDA,"PID + Stopped in AIDA","l");
    legend94->AddEntry(Edt94_Projection_np_SC41_Plastic,"PID + SC41/SC42 Energy + Plastic Energy","l");
    legend94->AddEntry(Edt94_Projection_np_Plastic_AIDA,"PID + Plastic Energy + Stopped in AIDA","l");
    legend94->AddEntry(Edt94_Projection_np_SC41_AIDA,"PID + SC41/42 Energy + Stopped in AIDA","l");
    legend94->AddEntry(Edt94_Projection_np_SC41_Plastic_AIDA,"PID + SC41/42 Energy + Stopped in AIDA + Plastic Energy","l");
    legend94->Draw("same");
	pd94canvas.SetTitle("^{94}Pd E_{#gamma} Projection");
	pd94canvas.Write();


	pid->SetTitle("S480 FRS PID");
	pids(pid);
	pids(pid96);
	pids(pid94);

	Edt->SetTitle("E_{#gamma} vs dt");
	Edts(Edt);	 
	Edt96->SetTitle("^{96}Pd E_{#gamma} vs dt");
	Edts(Edt96);	 
	Edt94->SetTitle("^{94}Pd E_{#gamma} vs dt");
	Edts(Edt94);


	Edt94->Print("Edt94.png");




	lts->Close();

}
