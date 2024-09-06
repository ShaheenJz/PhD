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
#include "thesis_setup.cc"

using namespace std;



void thesis_figures() {
/*
	TFile g("./gg_bgs_Nov_21.root");

	 TH1D *totalprojection96 = (TH1D*)g.Get("Projection96");
	 TH1D *totalprojection94 = (TH1D*)g.Get("Projection94");

	 totalprojection96->SetDirectory(0);
	 totalprojection94->SetDirectory(0);


	 // to decouple it from the open file directory

	 g.Close();

	 TFile f("./hists/ru94_combo3.root");

	 TH2D *ru3edt = (TH2D*)f.Get("ru3edt");
	 
	 ru3edt->SetDirectory(0);


	 // to decouple it from the open file directory

	 f.Close();


	 TFile h("./hists/eff_germ_21_04_14.root");

	 TH2D *Edt96_41 = (TH2D*)h.Get("Edt96_41");
	 TH2D *Edt94_41 = (TH2D*)h.Get("Edt94_41");
	 
	 Edt96_41->SetDirectory(0);
	 Edt94_41->SetDirectory(0);

	 // to decouple it from the open file directory

	 h.Close();

*/
TFile i("./hists/cubes_combo7.root"); //Lifetimes pd94 96

	THnSparseD *ggdt96 = (THnSparseD*)i.Get("ggdt_96_SC41");
	THnSparseD *ggdt94 = (THnSparseD*)i.Get("ggdt_94_SC41");

	ggdt96->GetAxis(0)->SetRange(1365,1455);
	TH2D* peak1415 = ggdt96->Projection(1,2);
	peak1415->SetDirectory(0);

	ggdt94->GetAxis(0)->SetRange(81,107);
	TH2D* peak96 = ggdt94->Projection(1,2);
	peak96->SetDirectory(0);

	ggdt94->GetAxis(2)->SetRange(-2,6);
	//TH2D* peak96rangelow = ggdt96->Projection(1);
	//peak96rangelow->SetDirectory(0);
	ggdt94->GetAxis(2)->SetRange(2,10);
	//TH2D* peak96rangelow = ggdt96->Projection(1);
	//peak96rangehigh->SetDirectory(0);


	ggdt94->GetAxis(0)->SetRange(308,341);
	TH2D* peak324 = ggdt94->Projection(1,2);
	peak324->SetDirectory(0);

	ggdt94->GetAxis(0)->SetRange(644,681);
	TH2D* peak659 = ggdt94->Projection(1,2);
	peak659->SetDirectory(0);

	ggdt94->GetAxis(0)->SetRange(787,847);
	TH2D* peak814 = ggdt94->Projection(1,2);
	peak814->SetDirectory(0);

	ggdt94->GetAxis(0)->SetRange(874,934);
	TH2D* peak905 = ggdt94->Projection(1,2);
	peak905->SetDirectory(0);

	ggdt94->GetAxis(0)->SetRange(965,1025);
	TH2D* peak994 = ggdt94->Projection(1,2);
	peak994->SetDirectory(0);

	ggdt94->GetAxis(0)->SetRange(1072,1130);
	TH2D* peak1092 = ggdt94->Projection(1,2);
	peak1092->SetDirectory(0);



	TH2D *pd96edt = (TH2D*)i.Get("Edt96_SC41_Plastic_AIDA");
	TH2D *pd94edt = (TH2D*)i.Get("Edt94_SC41");

	TH2F *zvsaoq = (TH2F*)i.Get("zvsaoq");

	pd96edt->SetDirectory(0);
	pd94edt->SetDirectory(0);
	zvsaoq->SetDirectory(0);

i.Close();
/*
TFile l("./review_combo7.root");


	TH1D *edt96proj_np = (TH1D*)l.Get("edt96proj_np");
	edt96proj_np->SetDirectory(0);
	TH1D *edt94proj_np = (TH1D*)l.Get("edt94proj_np");
	edt94proj_np->SetDirectory(0);

l.Close();
*/
TFile germs("./hists/cubes_germ.root"); //Germanium cubes


	TH2D *Edt96germ = (TH2D*)germs.Get("Edt96");
	Edt96germ->SetDirectory(0);
	TH2D *Edt94germ = (TH2D*)germs.Get("Edt94");
	Edt94germ->SetDirectory(0);

germs.Close();

TFile isrp("./isrpfigs.root"); // FIgures from ISRP paper


	TH2D *edtpd96labr = (TH2D*)isrp.Get("Edt96_SC41_Plastic_AIDA");
	edtpd96labr->SetDirectory(0);
	TH2D *edtpd94labr = (TH2D*)isrp.Get("Edt94_SC41");
	edtpd94labr->SetDirectory(0);
	TH2D *ru3edt_isrp = (TH2D*)isrp.Get("ru3edt");
	ru3edt_isrp->SetDirectory(0);
	TH1D *ru94lifetime = (TH1D*)isrp.Get("ru94ltsumbgs");
	ru94lifetime->SetDirectory(0);

	TH1D *ru3energy1 = (TH1D*)isrp.Get("ru3energy");
	ru3energy1->SetDirectory(0);
	TH1D *ru3energyfull1 = (TH1D*)isrp.Get("ru3energyfull");
	ru3energyfull1->SetDirectory(0);
	TH1D *ru3background1 = (TH1D*)isrp.Get("ru3background");
	ru3background1->SetDirectory(0);


isrp.Close();

TFile ru94("./hists/ru94_combo3.root");//Ru94 evs dt

	 TH2D *ru3edt = (TH2D*)ru94.Get("ru3edt");	 
	 ru3edt->SetDirectory(0);

ru94.Close();


TFile review("./review.root"); //Stacked energies different gating conditions

	 TH1D *edt96proj_np = (TH1D*)review.Get("edt96proj_np");	 
	 edt96proj_np->SetDirectory(0);
	 TH1D *edt96proj_np_Plastic = (TH1D*)review.Get("edt96proj_np_Plastic");	 
	 edt96proj_np_Plastic->SetDirectory(0);
	 TH1D *edt96proj_np_SC41 = (TH1D*)review.Get("edt96proj_np_SC41");	 
	 edt96proj_np_SC41->SetDirectory(0);
	 TH1D *edt96proj_np_AIDA = (TH1D*)review.Get("edt96proj_np_AIDA");	 
	 edt96proj_np_AIDA->SetDirectory(0);
	 TH1D *edt96proj_np_SC41_Plastic = (TH1D*)review.Get("edt96proj_np_SC41_Plastic");	 
	 edt96proj_np_SC41_Plastic->SetDirectory(0);
	 TH1D *edt96proj_np_Plastic_AIDA = (TH1D*)review.Get("edt96proj_np_Plastic_AIDA");	 
	 edt96proj_np_Plastic_AIDA->SetDirectory(0);
	 TH1D *edt96proj_np_SC41_AIDA = (TH1D*)review.Get("edt96proj_np_SC41_AIDA");	 
	 edt96proj_np_SC41_AIDA->SetDirectory(0);
	 TH1D *edt96proj_np_SC41_Plastic_AIDA = (TH1D*)review.Get("edt96proj_np_SC41_Plastic_AIDA");	 
	 edt96proj_np_SC41_Plastic_AIDA->SetDirectory(0);

	 TH1D *edt94proj_np = (TH1D*)review.Get("edt94proj_np");	 
	 edt94proj_np->SetDirectory(0);
	 TH1D *edt94proj_np_Plastic = (TH1D*)review.Get("edt94proj_np_Plastic");	 
	 edt94proj_np_Plastic->SetDirectory(0);
	 TH1D *edt94proj_np_SC41 = (TH1D*)review.Get("edt94proj_np_SC41");	 
	 edt94proj_np_SC41->SetDirectory(0);
	 TH1D *edt94proj_np_AIDA = (TH1D*)review.Get("edt94proj_np_AIDA");	 
	 edt94proj_np_AIDA->SetDirectory(0);
	 TH1D *edt94proj_np_SC41_Plastic = (TH1D*)review.Get("edt94proj_np_SC41_Plastic");	 
	 edt94proj_np_SC41_Plastic->SetDirectory(0);
	 TH1D *edt94proj_np_Plastic_AIDA = (TH1D*)review.Get("edt94proj_np_Plastic_AIDA");	 
	 edt94proj_np_Plastic_AIDA->SetDirectory(0);
	 TH1D *edt94proj_np_SC41_AIDA = (TH1D*)review.Get("edt94proj_np_SC41_AIDA");	 
	 edt94proj_np_SC41_AIDA->SetDirectory(0);
	 TH1D *edt94proj_np_SC41_Plastic_AIDA = (TH1D*)review.Get("edt94proj_np_SC41_Plastic_AIDA");	 
	 edt94proj_np_SC41_Plastic_AIDA->SetDirectory(0);


review.Close();

TFile reversepids("./aoq_subs.root"); //Background subtracted PIDs


	TH2F *reverse106 = (TH2F*)reversepids.Get("zvsaoqreversecut96pd106");
	reverse106->SetDirectory(0);
	TH2F *reverse106_bg = (TH2F*)reversepids.Get("zvsaoqreversecut96pd106_bg");
	reverse106_bg->SetDirectory(0);
	TH2F *reverse106_s = (TH2F*)reversepids.Get("reverse106_s");
	reverse106_s->SetDirectory(0);

	TH1D *reverse106_p = (TH1D*)reversepids.Get("reverse106_p");
	TH1D *reverse106_bg_p = (TH1D*)reversepids.Get("reverse106_bg_p");
	TH1D *reverse106_s_p = (TH1D*)reversepids.Get("reverse106_s_p");

	TH1D *reverse684_p = (TH1D*)reversepids.Get("reverse684_p");
	TH1D *reverse684_bg_p = (TH1D*)reversepids.Get("reverse684_bg_p");
	TH1D *reverse684_s_p = (TH1D*)reversepids.Get("reverse684_s_p");

	TH1D *reverse1415_p = (TH1D*)reversepids.Get("reverse1415_p");
	TH1D *reverse1415_bg_p = (TH1D*)reversepids.Get("reverse1415_bg_p");
	TH1D *reverse1415_s_p = (TH1D*)reversepids.Get("reverse1415_s_p");

	TH1D *reverse96_p = (TH1D*)reversepids.Get("reverse96_p");
	TH1D *reverse96_bg_p = (TH1D*)reversepids.Get("reverse96_bg_p");
	TH1D *reverse96_s_p = (TH1D*)reversepids.Get("reverse96_s_p");

	TH1D *reverse660_p = (TH1D*)reversepids.Get("reverse660_p");
	TH1D *reverse660_bg_p = (TH1D*)reversepids.Get("reverse660_bg_p");
	TH1D *reverse660_s_p = (TH1D*)reversepids.Get("reverse660_s_p");

	TH1D *reverse814_p = (TH1D*)reversepids.Get("reverse814_p");
	TH1D *reverse814_bg_p = (TH1D*)reversepids.Get("reverse814_bg_p");
	TH1D *reverse814_s_p = (TH1D*)reversepids.Get("reverse814_s_p");

	TH1D *reverse905_p = (TH1D*)reversepids.Get("reverse905_p");
	TH1D *reverse905_bg_p = (TH1D*)reversepids.Get("reverse905_bg_p");
	TH1D *reverse905_s_p = (TH1D*)reversepids.Get("reverse905_s_p");

	TH1D *reverse994_p = (TH1D*)reversepids.Get("reverse994_p");
	TH1D *reverse994_bg_p = (TH1D*)reversepids.Get("reverse994_bg_p");
	TH1D *reverse994_s_p = (TH1D*)reversepids.Get("reverse994_s_p");

	TH1D *reverse1092_p = (TH1D*)reversepids.Get("reverse1092_p");
	TH1D *reverse1092_bg_p = (TH1D*)reversepids.Get("reverse1092_bg_p");
	TH1D *reverse1092_s_p = (TH1D*)reversepids.Get("reverse1092_s_p");


	reverse106_p->SetDirectory(0);
	reverse106_bg_p->SetDirectory(0);
	reverse106_s_p->SetDirectory(0);

	reverse684_p->SetDirectory(0);
	reverse684_bg_p->SetDirectory(0);
	reverse684_s_p->SetDirectory(0);

	reverse1415_p->SetDirectory(0);
	reverse1415_bg_p->SetDirectory(0);
	reverse1415_s_p->SetDirectory(0);

	reverse96_p->SetDirectory(0);
	reverse96_bg_p->SetDirectory(0);
	reverse96_s_p->SetDirectory(0);

	reverse660_p->SetDirectory(0);
	reverse660_bg_p->SetDirectory(0);
	reverse660_s_p->SetDirectory(0);

	reverse814_p->SetDirectory(0);
	reverse814_bg_p->SetDirectory(0);
	reverse814_s_p->SetDirectory(0);

	reverse905_p->SetDirectory(0);
	reverse905_bg_p->SetDirectory(0);
	reverse905_s_p->SetDirectory(0);

	reverse994_p->SetDirectory(0);
	reverse994_bg_p->SetDirectory(0);
	reverse994_s_p->SetDirectory(0);

	reverse1092_p->SetDirectory(0);
	reverse1092_bg_p->SetDirectory(0);
	reverse1092_s_p->SetDirectory(0);
reversepids.Close();

/*
TFile j("./hists/pid_tre11.root");

	TH2F *zaoq = (TH2F*)j.Get("zaoq");

	zaoq->SetDirectory(0);


j.Close();
*/
/*
TFile k("./Lifetimes_bgs_Nov_2021.root");

	TH1D *pd962 = (TH1D*)k.Get("bgs_lifetime2");
	TH1D *pd964 = (TH1D*)k.Get("bgs_lifetime4");
	TH1D *pd966 = (TH1D*)k.Get("bgs_lifetime6");

	pd962->SetDirectory(0);
	pd964->SetDirectory(0);
	pd966->SetDirectory(0);

	TH1D *gate1415 = (TH1D*)k.Get("bgsgate1415");
	TH1D *gate684 = (TH1D*)k.Get("bgsgate684");
	TH1D *gate325 = (TH1D*)k.Get("bgsgate325");

	gate1415->SetDirectory(0);
	gate684->SetDirectory(0);
	gate325->SetDirectory(0);

k.Close();


TFile l("./Lifetimes_94ru.root");

	TH1D *ru942 = (TH1D*)l.Get("bgs_lifetime2");
	TH1D *ru944 = (TH1D*)l.Get("bgs_lifetime4");
	TH1D *ru946 = (TH1D*)l.Get("bgs_lifetime6");

	TH1D *bgs1431 = (TH1D*)l.Get("bgsgate1431");
	TH1D *bgs755 = (TH1D*)l.Get("bgsgate755");
	TH1D *bgs311 = (TH1D*)l.Get("bgsgate311");
	TH1D *bgs146 = (TH1D*)l.Get("bgsgate146");

	ru942->SetDirectory(0);
	ru944->SetDirectory(0);
	ru946->SetDirectory(0);

bgs1431->SetDirectory(0);
bgs755->SetDirectory(0);
bgs311->SetDirectory(0);
bgs146->SetDirectory(0);

l.Close();

TFile m("./Summed_lifetime_bgs.root");

	TH1D *pd942 = (TH1D*)m.Get("bgs_lifetime2");
	TH1D *pd944 = (TH1D*)m.Get("bgs_lifetime4");
	TH1D *pd946 = (TH1D*)m.Get("bgs_lifetime6");
	TH1D *pd948 = (TH1D*)m.Get("bgs_lifetime8");
	TH1D *pd9410 = (TH1D*)m.Get("bgs_lifetime10");
	TH1D *pd9412 = (TH1D*)m.Get("bgs_lifetime12");

	TH1D *summed8no96 = (TH1D*)m.Get("Summed8_no96");
	TH1D *sum_total = (TH1D*)m.Get("sum_total");

	pd942->SetDirectory(0);
	pd944->SetDirectory(0);
	pd946->SetDirectory(0);
	pd948->SetDirectory(0);
	pd9410->SetDirectory(0);
	pd9412->SetDirectory(0);

	summed8no96->SetDirectory(0);
	sum_total->SetDirectory(0);

m.Close();
*/


/* OUTFILE MIGHT NEED
	int gate_info [gate_num][6];
	ifstream outFile;
	outFile.open(gates);
	if (!outFile){
    		cerr << "Unable to open file your data file";
    		exit(1);   // call system to stop
		}
*/

/*

	TH1D* ru3energy = ru3edt->ProjectionY("ru3energy", 80, 350);
	TH1D* ru3background = ru3edt->ProjectionY("ru3background", 350, 620);

	TH1D* pd96proj = Edt96_41->ProjectionY("pd96proj", 2400, 9000);
	TH1D* pd94proj = Edt94_41->ProjectionY("pd94proj", 2400, 4500);


	TH1D* ru94_146_proj = ru3edt->ProjectionX("ru94_146_proj", 134, 161);
	TH1D* ru94_146_proj_bg = ru3edt->ProjectionX("ru94_146_proj_bg", 166, 193);
	TH1D* ru94_311_proj = ru3edt->ProjectionX("ru94_311_proj", 297, 332);
	TH1D* ru94_311_proj_bg = ru3edt->ProjectionX("ru94_311_proj_bg", 337, 372);
	TH1D* ru94_755_proj = ru3edt->ProjectionX("ru94_755_proj", 733, 780);
	TH1D* ru94_755_proj_bg = ru3edt->ProjectionX("ru94_755_proj_bg", 790, 837);
	TH1D* ru94_1431_proj = ru3edt->ProjectionX("ru94_1431_proj", 1398, 1488);
	TH1D* ru94_1431_proj_bg = ru3edt->ProjectionX("ru94_1431_proj_bg", 1488, 1578);


	ru94_146_proj->Add(ru94_146_proj_bg,-1);
	ru94_311_proj->Add(ru94_311_proj_bg,-1);
	ru94_755_proj->Add(ru94_755_proj_bg,-1);
	ru94_1431_proj->Add(ru94_1431_proj_bg,-1);

	ru94_146_proj->Write();
	ru94_311_proj->Write();
	ru94_755_proj->Write();
	ru94_1431_proj->Write();


    TH1D *ru94ltsumbgs = new TH1D("ru94ltsumbgs","ru94ltsumbgs",1000,0,1000); 

    ru94ltsumbgs->Add(ru94_146_proj);
    ru94ltsumbgs->Add(ru94_311_proj);
    //ru94ltsumbgs->Add(ru94_755_proj);
    //ru94ltsumbgs->Add(ru94_1431_proj);

    ru94ltsumbgs->Write();

	TCanvas *c5 = new TCanvas("c5","multipads8",900,700);
    ru94ltsumbgs->Draw("colz");
    c5->Write();

	ru3energy->Add(ru3background,-1);

	gg_bgs2(ru3energy);
	gg_bgs2(totalprojection94);

	bgs1431->Write();
	bgs755->Write();
	bgs311->Write();

	//ru3energy->SetLineColor(1);
	totalprojection96->SetLineColor(1);
	totalprojection94->SetLineColor(1);

	ru3energy->GetYaxis()->SetTitleOffset(0.5);
	totalprojection96->GetYaxis()->SetTitleOffset(0.5);
	totalprojection94->GetYaxis()->SetTitleOffset(0.5);
	totalprojection96->GetXaxis()->SetTitleSize(0.12);
	totalprojection96->GetYaxis()->SetTitleSize(0.12);
	totalprojection96->GetYaxis()->SetLabelSize(0.12);
	totalprojection96->GetYaxis()->SetLabelSize(0.12);



	TLine *l1 = new TLine(0,0,2000,0);
    TLatex latex;
    latex.SetTextSize(0.12);
    latex.SetTextAlign(13);  //align at top
    latex.SetTextFont(42);
    latex.SetTextAngle(90);
	TCanvas *c14 = new TCanvas("c14","multipads8",900,700);
    c14->Divide(1,3,0,0);
	c14->cd(1);

	totalprojection96->Draw("same");
	totalprojection96->GetYaxis()->SetRangeUser(-120,2700);
    latex.SetTextAngle(0);
    latex.DrawLatex(1000,200,"a) ^{96}Pd gamma singles gamma rays #delta t 40 ns - 400 ns");
    latex.SetTextAngle(90);   
    latex.DrawLatex(106,200,"106");
    latex.DrawLatex(325,200,"325");
    latex.DrawLatex(684,200,"684");
    latex.DrawLatex(1415,200,"1415");
    l1->Draw();

	c14->cd(2);
	totalprojection94->Draw();
	totalprojection94->GetYaxis()->SetRangeUser(-10,230);
	latex.SetTextAngle(0);
    latex.DrawLatex(1000,150,"b) ^{94}Pd gamma singles gamma rays #delta t 40 ns - 400 ns");
    latex.SetTextAngle(90);    
    latex.DrawLatex(96,150,"96");
    latex.DrawLatex(324,150,"324");
    latex.DrawLatex(659,150,"659");
    latex.DrawLatex(814,150,"814");
    latex.DrawLatex(905,150,"905");
    latex.DrawLatex(994,150,"994");
    latex.DrawLatex(1092,150,"1092");
    l1->Draw();

	c14->cd(3);
	ru3energy->Draw();
	ru3energy->GetYaxis()->SetRangeUser(-150,6700);
    latex.SetTextAngle(0);
    latex.DrawLatex(1000,6000,"c) ^{94}Ru gamma singles gamma rays #delta t 80 #mus - 350 #mus");
    latex.SetTextAngle(90);    
    latex.DrawLatex(146,4000,"146");
    latex.DrawLatex(311,4000,"311");
    latex.DrawLatex(756,4000,"756");
    latex.DrawLatex(1431,4000,"1431");
    l1->Draw();

	c14->Write();

	ru3energy->Write();

	Edt96_41->RebinY(2);
	Edt94_41->RebinY(5);

	Edtgerm(Edt96_41);
	Edtgerm(Edt94_41);

	Edt96_41->SetMinimum(3);
	Edt94_41->SetMinimum(2);

	TCanvas *c15 = new TCanvas("c15","multipads8",900,700);
    c15->Divide(1,2,0,0);
	c15->cd(1);
	Edt96_41->Draw("colz");
	c15->cd(2);
	Edt94_41->Draw("colz");
	c15->Write();

	TLatex latex2;
    latex2.SetTextSize(0.06);
    latex2.SetTextAlign(13);  //align at top
    latex2.SetTextFont(42);

    peak1415->Rebin2D(2,5);
    peak1415->SetTitle("1415 keV Coincidences;FATIMA - SC41 #Deltat (ns);Energy (keV)");
	peak1415->GetYaxis()->SetRangeUser(0,1501);
	peak1415->GetXaxis()->SetRangeUser(-10,40);
	peak1415->GetXaxis()->SetTitleOffset(1.1);
	peak1415->GetYaxis()->SetTitleOffset(1.1);
	peak1415->GetXaxis()->SetTitleSize(0.06);
	peak1415->GetYaxis()->SetTitleSize(0.06);
	peak1415->GetXaxis()->SetLabelSize(0.06);
	peak1415->GetYaxis()->SetLabelSize(0.06);
	peak1415->GetXaxis()->CenterTitle(true);
	peak1415->GetYaxis()->CenterTitle(true);

	TCanvas *c11 = new TCanvas("c11","multipads8",900,700);
	peak1415->Draw("colz");
    latex2.DrawLatex(30,684,"684 keV 4^{+} #rightarrow 2^{+}");
    latex2.DrawLatex(30,325,"325 keV 6^{+} #rightarrow 4^{+}");
    latex2.DrawLatex(30,106,"106 keV 8^{+} #rightarrow 6^{+}");
    c11->Write();

    peak96->SetTitle("96 keV Coincidences;FATIMA - FATIMA #Deltat (ns);Energy (keV)");
	edtmay2022(peak96);
    peak324->SetTitle("324 keV Coincidences;FATIMA - FATIMA #Deltat (ns);Energy (keV)");
	edtmay2022(peak324);
    peak659->SetTitle("659 keV Coincidences;FATIMA - FATIMA #Deltat (ns);Energy (keV)");	
	edtmay2022(peak659);
	peak814->SetTitle("814 keV Coincidences;FATIMA - FATIMA #Deltat (ns);Energy (keV)");
	edtmay2022(peak814);
	peak905->SetTitle("905 keV Coincidences;FATIMA - FATIMA #Deltat (ns);Energy (keV)");
	edtmay2022(peak905);
	peak994->SetTitle("994 keV Coincidences;FATIMA - FATIMA #Deltat (ns);Energy (keV)");
	edtmay2022(peak994);
	peak1092->SetTitle("1092 keV Coincidences;FATIMA - FATIMA #Deltat (ns);Energy (keV)");
	edtmay2022(peak1092);


	//TH1D* peak96rangelow = peak96->ProjectionY("peak96rangelow",);
//peak96->ProjectionY("")


    gamma_germ(pd96proj);
    gamma_germ(pd94proj);

	pd96proj->GetYaxis()->SetRangeUser(1,5800);
	pd94proj->GetYaxis()->SetRangeUser(0,150);

	TLatex latex3;
    latex3.SetTextSize(0.08);
    latex3.SetTextAlign(13);  //align at top
    latex3.SetTextFont(42);
    latex3.SetTextAngle(90);

	TCanvas *c16 = new TCanvas("c16","multipads8",900,700);
    c16->Divide(1,2,0,0);
	c16->cd(1);
	pd96proj->Draw("colz");
    latex3.DrawLatex(1415,500,"1415");
    latex3.DrawLatex(684,500,"684");
    latex3.DrawLatex(325,500,"325");
    latex3.DrawLatex(106,500,"106");
	c16->cd(2);
	pd94proj->Draw("colz");
    latex3.DrawLatex(1092,50,"1092");
    latex3.DrawLatex(994,50,"994");
    latex3.DrawLatex(905,50,"905");
    latex3.DrawLatex(814,50,"814");
    latex3.DrawLatex(659,50,"659");
    latex3.DrawLatex(324,50,"324");
    latex3.DrawLatex(96,50,"96");
	c16->Write();

	TLatex latex4;
    latex4.SetTextSize(0.12);
    latex4.SetTextAlign(13);  //align at top
    latex4.SetTextFont(42);

    pd962->SetLineColor(kRed);
    pd964->SetLineColor(kGreen);

	pdlifetimes(pd962);
	pdlifetimes(pd964);
	pdlifetimes(pd966);
	
	TCanvas *c17 = new TCanvas("c17","c17",900,700);
    c17->Divide(1,3,0,0);
	c17->cd(1);
	pd962->Draw();
    latex4.DrawLatex(3,40,"684 - 1415");
    c17->cd(2);
	pd964->Draw();
    latex4.DrawLatex(10,40,"T_{1/2} = 1.0(1) ns");
    latex4.DrawLatex(3,40,"325 - 684");
    c17->cd(3);
	pd966->Draw();
    latex4.DrawLatex(5,40,"T_{1/2} = 6.4(4) ns");
    latex4.DrawLatex(3,40,"106 - 325");
	c17->Write();


	TCanvas *c18 = new TCanvas("c18","c18",900,700);
	pd962->Draw();
    latex4.DrawLatex(3,40,"684 - 1415");
	pd964->Draw("same");
    latex4.DrawLatex(10,40,"T_{1/2} = 1.0(1) ns");
    latex4.DrawLatex(3,40,"325 - 684");
	pd966->Draw("same");
    latex4.DrawLatex(5,40,"T_{1/2} = 6.4(4) ns");
    latex4.DrawLatex(3,40,"106 - 325");
	c18->Write();


	rulifetimes(ru942);
	rulifetimes(ru944);
	rulifetimes(ru946);
	
	ru942->SetLineColor(kRed);
	ru944->SetLineColor(kGreen);

	TCanvas *c19 = new TCanvas("c19","c19",900,700);
    c19->Divide(1,3,0,0);
	c19->cd(1);
	ru942->Draw();
    latex4.DrawLatex(200,40,"{1431 keV, 755 keV}");
    c19->cd(2);
	ru944->Draw();
    latex4.DrawLatex(200,40,"{755 keV, 311 keV}");
    c19->cd(3);
	ru946->Draw();
    latex4.DrawLatex(5,40,"T_{1/2} = 63(4) ns");
    latex4.DrawLatex(200,40,"{311 keV, 146 keV}");
	c19->Write();

	ru942->Write();
	ru944->Write();
	ru946->Write();





	gg_bgs2(bgs1431);
	gg_bgs2(bgs755);
	gg_bgs2(bgs311);
	gg_bgs2(bgs146);

	TCanvas *c20 = new TCanvas("c20","multipads8",900,700);
    c20->Divide(1,3,0,0);
	c20->cd(1);

	bgs1431->Draw();
    latex.SetTextAngle(0);
    latex.DrawLatex(1000,100,"1431 keV gate");
    latex.DrawLatex(1000,20,"2^{+} #rightarrow 0^{+}");
    latex.SetTextAngle(90);   
    latex.DrawLatex(146,150,"146");
    latex.DrawLatex(311,150,"311");
    latex.DrawLatex(755,150,"755");
   	bgs1431->GetYaxis()->SetRangeUser(0,480);

    l1->Draw();

	c20->cd(2);
	bgs755->Draw();
	latex.SetTextAngle(0);
    latex.DrawLatex(1000,100,"755 keV gate");
    latex.DrawLatex(1000,20,"4^{+} #rightarrow 2^{+}");    
    latex.SetTextAngle(90);    
    latex.DrawLatex(146,100,"146");
    latex.DrawLatex(311,150,"311");
    latex.DrawLatex(1431,150,"1431");
   	bgs755->GetYaxis()->SetRangeUser(-10,240);

    l1->Draw();

	c20->cd(3);
	bgs311->Draw();
    latex.SetTextAngle(0);

    latex.DrawLatex(1000,100,"311 keV gate");
    latex.DrawLatex(1000,20,"6^{+} #rightarrow 4^{+}");
    latex.SetTextAngle(90);    
    latex.DrawLatex(146,150,"146");
    latex.DrawLatex(1431,150,"1431");
    latex.DrawLatex(755,150,"755");
   	bgs311->GetYaxis()->SetRangeUser(0,480);

    l1->Draw();

	c20->Write();



	TCanvas *c25 = new TCanvas("c25","multipads8",900,700);
    c25->Divide(1,5,0,0);
	c25->cd(1);
	ru3energy->Draw();
	ru3energy->GetYaxis()->SetRangeUser(-150,6700);
    latex.SetTextAngle(0);
    latex.DrawLatex(1000,6000,"^{94}Ru gamma singles gamma rays #Deltat 80 #mus - 350 #mus");
    latex.SetTextAngle(90);    
    latex.DrawLatex(146,4000,"146");
    latex.DrawLatex(311,4000,"311");
    latex.DrawLatex(756,4000,"755");
    latex.DrawLatex(1431,4000,"1431");
    l1->Draw();

	c25->cd(2);

	bgs1431->Draw();
    latex.SetTextAngle(0);
    latex.DrawLatex(1000,100,"1431 keV gate");
    latex.DrawLatex(1000,20,"2^{+} #rightarrow 0^{+}");
    latex.SetTextAngle(90);   
    latex.DrawLatex(146,150,"146");
    latex.DrawLatex(311,150,"311");
    latex.DrawLatex(755,150,"755");
   	bgs1431->GetYaxis()->SetRangeUser(0,480);

    l1->Draw();

	c25->cd(3);
	bgs755->Draw();
	latex.SetTextAngle(0);
    latex.DrawLatex(1000,100,"755 keV gate");
    latex.DrawLatex(1000,20,"4^{+} #rightarrow 2^{+}");    
    latex.SetTextAngle(90);    
    latex.DrawLatex(146,100,"146");
    latex.DrawLatex(311,150,"311");
    latex.DrawLatex(1431,150,"1431");
   	bgs755->GetYaxis()->SetRangeUser(-10,240);

    l1->Draw();

	c25->cd(4);
	bgs311->Draw();
    latex.SetTextAngle(0);

    latex.DrawLatex(1000,100,"311 keV gate");
    latex.DrawLatex(1000,20,"6^{+} #rightarrow 4^{+}");
    latex.SetTextAngle(90);    
    latex.DrawLatex(146,150,"146");
    latex.DrawLatex(1431,150,"1431");
    latex.DrawLatex(755,150,"755");
   	bgs311->GetYaxis()->SetRangeUser(0,480);

	c25->cd(5);
	bgs311->Draw();
    latex.SetTextAngle(0);

    latex.DrawLatex(1000,100,"146 keV gate");
    latex.DrawLatex(1000,20,"8{+} #rightarrow 2^{+}");
    latex.SetTextAngle(90);    
    latex.DrawLatex(146,150,"311");
    latex.DrawLatex(1431,150,"1431");
    latex.DrawLatex(755,150,"755");
   	bgs311->GetYaxis()->SetRangeUser(0,1000);

    l1->Draw();

	c25->Write();

	Edt_Nov_21(pd96edt);
	Edt94_Nov_21(pd94edt);

	TLatex latex5;
    latex5.SetTextSize(0.06);
    latex5.SetTextAlign(13);  //align at top
    latex5.SetTextFont(42);

	TCanvas *c2 = new TCanvas("c2","multipads8",900,700);
	pd96edt->Draw("colz");
    latex5.DrawLatex(500,1415,"1415 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(500,684,"684 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(500,325,"325 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(500,106,"106 keV 8^{+} #rightarrow 6^{+}");
	c2->Write();

	TCanvas *c94 = new TCanvas("c94","multipads8",900,700);
	pd94edt->Draw("colz");
    latex5.DrawLatex(500,1092,"1092 keV 10^{+} #rightarrow 8^{+}");
    latex5.DrawLatex(500,994,"994 keV 12^{+} #rightarrow 10^{+}");
    latex5.DrawLatex(500,905,"905 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(500,814,"814 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(500,659,"659 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(500,324,"324 keV 8^{+} #rightarrow 6^{+}");
    latex5.DrawLatex(500,96,"96 keV 14^{+} #rightarrow 12^{+}");

	c94->Write();



	Edt94_Nov_21(ru3edt);
	TCanvas *c3 = new TCanvas("c3","multipads8",900,700);
	ru3edt->Draw("colz");
    latex5.DrawLatex(500,1431,"1431 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(500,755,"755 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(500,311,"311 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(500,146,"146 keV 8^{+} #rightarrow 6^{+}");
	c3->Write();


	gg_bgs2(gate1415);
	gg_bgs2(gate684);
	gg_bgs2(gate325);

	TCanvas *c4 = new TCanvas("c4","multipads8",900,700);
    c4->Divide(1,3,0,0);
	c4->cd(1);

	gate1415->Draw();
    latex.SetTextAngle(0);
    latex.DrawLatex(1000,100,"1415 keV gate");
    latex.DrawLatex(1000,20,"2^{+} #rightarrow 0^{+}");
    latex.SetTextAngle(90);   
    latex.DrawLatex(106,150,"106");
    latex.DrawLatex(311,150,"325");
    latex.DrawLatex(755,150,"684");
   	bgs1431->GetYaxis()->SetRangeUser(0,480);

    l1->Draw();

	c4->cd(2);
	gate684->Draw();
	latex.SetTextAngle(0);
    latex.DrawLatex(1000,100,"684 keV gate");
    latex.DrawLatex(1000,20,"4^{+} #rightarrow 2^{+}");    
    latex.SetTextAngle(90);    
    latex.DrawLatex(106,150,"106");
    latex.DrawLatex(684,150,"684");
    latex.DrawLatex(1415,150,"1415");
   	bgs755->GetYaxis()->SetRangeUser(-10,240);

    l1->Draw();

	c4->cd(3);
	gate325->Draw();
    latex.SetTextAngle(0);

    latex.DrawLatex(1000,100,"325 keV gate");
    latex.DrawLatex(1000,20,"6^{+} #rightarrow 4^{+}");
    latex.SetTextAngle(90);    
    latex.DrawLatex(106,150,"106");
    latex.DrawLatex(684,150,"684");
    latex.DrawLatex(1415,150,"1415");
   	bgs311->GetYaxis()->SetRangeUser(0,480);

    l1->Draw();

	c4->Write();


	TCanvas *c6 = new TCanvas("c6","multipads6",900,700);
    c6->Divide(1,3,0,0);
	c6->cd(1);
	pd942->Draw();
	c6->cd(2);
	//pd944->Draw();
	c6->cd(3);
	pd946->Draw();
	c6->Write();

	TCanvas *c8 = new TCanvas("c8","multipads8",900,700);
    c8->Divide(1,3,0,0);
	c8->cd(1);
	pd948->Draw();
	c8->cd(2);
	pd9410->Draw();
	c8->cd(3);
	pd9412->Draw();
	c8->Write();

	TCanvas *c9 = new TCanvas("c9","multipads9",900,700);
    c9->Divide(1,2,0,0);
	c9->cd(1);
	summed8no96->Draw();
	c9->cd(2);
	sum_total->Draw();
	c9->Write();

*/
//Germanium Projections
	TH1D* Edt96germ_Projection_np = Edt96germ->ProjectionY("Edt96germ_Projection_np",2500,8000);
	TH1D* Edt94germ_Projection_np = Edt94germ->ProjectionY("Edt94germ_Projection_np",2500,8000);

//PID Projections
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
    TString outpath;
    outpath = "/home/sj00239/Thesis/template/Figures/final_root_figs/";

//gStyle->SetOptTitle(0);
//gStyle->SetOptStat(0);
TFile *lts = new TFile("thesis_figures_final.root","RECREATE");

   Double_t w = 1920;
   Double_t h = 1080;

//Ru94 background subtraction gammas

	TLatex latex20;
    latex20.SetTextSize(0.15);
    latex20.SetTextAlign(12);  //align at top
    latex20.SetTextFont(42);

    Stackedlabr3_energyru(ru3energyfull1);
    Stackedlabr3_energyru(ru3background1);
    Stackedlabr3_energyru(ru3energy1);


   	TCanvas *ru94comparison = new TCanvas("ru94comparison","ru94comparison",w,h);
    ru94comparison->Divide(1,3,0,0);
    ru94comparison->cd(1);
    ru3energyfull1->Draw();
    ru3energyfull1->GetYaxis()->SetRangeUser(-1500,22000);
    latex20.DrawLatex(1000,15000,"a) Singles FATIMA Decay Region #Deltat = 80 #mus - 350 #mus");
    latex20.DrawLatex(90,15000,"90");
    latex20.DrawLatex(146,15000,"146");
    latex20.DrawLatex(311,15000,"311");
    latex20.DrawLatex(511,15000,"511");
    latex20.DrawLatex(755,15000,"755");
    latex20.DrawLatex(1431,15000,"1431");
    latex20.DrawLatex(1460,15000,"1460");
    ru94comparison->cd(2);
    ru3background1->Draw();
    ru3background1->GetYaxis()->SetRangeUser(-1500,22000);
    latex20.DrawLatex(1000,15000,"b) Singles FATIMA Background Region #Deltat = 350 #mus - 620 #mus");
    latex20.DrawLatex(90,15000,"90");
    latex20.DrawLatex(511,15000,"511");
    latex20.DrawLatex(1431,15000,"1431");
    latex20.DrawLatex(1460,15000,"1460");
    ru94comparison->cd(3);
    ru3energy1->Draw();
    ru3energy1->GetYaxis()->SetRangeUser(-300,6500);
    latex20.DrawLatex(1000,4000,"c) Singles FATIMA Decay Region - Background Region");
    latex20.DrawLatex(146,4000,"146");
    latex20.DrawLatex(311,4000,"311");
    latex20.DrawLatex(755,4000,"755");
    latex20.DrawLatex(1431,4000,"1431");
	ru94comparison->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/ru94comparison.png","png");
	ru94comparison->Write();
    

    TLatex latex;
    latex.SetTextSize(0.06);
    latex.SetTextAlign(11);  //align at top
    latex.SetTextFont(42);
    latex.SetTextAngle(0);


/*
//Z vs AoQ Plot
	TCanvas *ZvsAoQ = new TCanvas("ZvsAoQ","ZvsAoQ",w,h);
	pids(zvsaoq);
	ZvsAoQ->SetLogz();
	zvsaoq->Draw("colz");
	ZvsAoQ->Write();
	ZvsAoQ->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/ZvsAoQ_new.png","png");

//Z vs AoQ Labelled
	TCutG *pd96cut = new TCutG("pd96cut",11);
	pd96cut->SetVarX("FRSMH_AoQ");
	pd96cut->SetVarY("FRSMH_Z1");
    pd96cut->SetPoint(0,2.18833,49.7299);
    pd96cut->SetPoint(1,2.19719,49.7036);
    pd96cut->SetPoint(2,2.20372,49.5191);
    pd96cut->SetPoint(3,2.20707,49.2028);
    pd96cut->SetPoint(4,2.20595,48.8426);
    pd96cut->SetPoint(5,2.19859,48.5791);
    pd96cut->SetPoint(6,2.19029,48.5966);
    pd96cut->SetPoint(7,2.1833,48.8251);
    pd96cut->SetPoint(8,2.18069,49.2116);
    pd96cut->SetPoint(9,2.18302,49.6333);
    pd96cut->SetPoint(10,2.18833,49.7299);
	pd96cut->SetLineColor(kBlue);
	pd96cut->SetLineWidth(4);
	pd96cut->Draw("same");
    
	TCutG *pd94cut = new TCutG("pd94cut",11);
	pd94cut->SetVarX("FRSMH_AoQ");
	pd94cut->SetVarY("FRSMH_Z1");
   	pd94cut->SetPoint(0,2.14405,49.563);
   	pd94cut->SetPoint(1,2.15169,49.3258);
   	pd94cut->SetPoint(2,2.15431,48.9129);
   	pd94cut->SetPoint(3,2.15225,48.6581);
   	pd94cut->SetPoint(4,2.14722,48.5351);
   	pd94cut->SetPoint(5,2.13846,48.5527);
   	pd94cut->SetPoint(6,2.13314,48.7108);
   	pd94cut->SetPoint(7,2.13156,49.1062);
   	pd94cut->SetPoint(8,2.13333,49.5279);
   	pd94cut->SetPoint(9,2.13976,49.6069);
   	pd94cut->SetPoint(10,2.14405,49.563);
	pd94cut->SetLineColor(kBlue);
	pd94cut->SetLineWidth(4);
	pd94cut->Draw("same");

    latex.DrawLatex(2.20372,49.5191,"^{96}Pd");
    latex.DrawLatex(2.14405,49.563,"^{94}Pd");

	ZvsAoQ->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/ZvsAoQ_Gates.png","png");

//Plastic Detector
	//TCanvas *Canvas_Plastic = new TCanvas("Canvas_Plastic","Canvas_Plastic",w,h);


	TLatex latex4;
    latex4.SetTextSize(0.05);
    latex4.SetTextAlign(22);  //align at center left
    latex4.SetTextFont(42);

//Ungated energy
	TCanvas *E96 = new TCanvas("E96","E96",w,h);
	gamma(edt96proj_np);
	edt96proj_np->Draw();
	edt96proj_np->GetYaxis()->SetRangeUser(0,7000);
    latex4.DrawLatex(106,6650,"106");
    latex4.DrawLatex(325,6100,"325");
    latex4.DrawLatex(684,2800,"684");
    latex4.DrawLatex(1415,1100,"1415");
	E96->Write();
	E96->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Labr3_pd96_ungated.png","png");

	TCanvas *E94 = new TCanvas("E94","E94",w,h);
	gamma(edt94proj_np);
	edt94proj_np->Draw();
	edt94proj_np->GetYaxis()->SetRangeUser(0,6000);
    latex4.DrawLatex(96,550,"96");
    latex4.DrawLatex(324,550,"324");
    latex4.DrawLatex(669,280,"669");
    latex4.DrawLatex(814,200,"814");
    latex4.DrawLatex(905,170,"905");
    latex4.DrawLatex(994,140,"994");
    latex4.DrawLatex(1092,110,"1092");
	E94->Write();
	E94->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Labr3_pd94_ungated.png","png");

	TCanvas *E96_germ = new TCanvas("E96_germ","E96_germ",w,h);
	gamma_germ(Edt96germ_Projection_np);
	Edt96germ_Projection_np->Draw();
	Edt96germ_Projection_np->GetYaxis()->SetRangeUser(0,5500);
    latex4.DrawLatex(106,4600,"106");
    latex4.DrawLatex(325,5300,"325");
    latex4.DrawLatex(684,3500,"684");
    latex4.DrawLatex(1415,2100,"1415");
	E96_germ->Write();
	E96_germ->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Germ_pd96_ungated.png","png");

	TCanvas *E94_germ = new TCanvas("E94_germ","E94_germ",w,h);
	gamma_germ(Edt94germ_Projection_np);
	Edt94germ_Projection_np->Draw();
	Edt94germ_Projection_np->GetYaxis()->SetRangeUser(0,150);
    latex4.DrawLatex(96,95,"96");
    latex4.DrawLatex(324,110,"324");
    latex4.DrawLatex(669,65,"669");
    latex4.DrawLatex(814,60,"814");
    latex4.DrawLatex(905,55,"905");
    latex4.DrawLatex(994,50,"994");
    latex4.DrawLatex(1092,55,"1092");
	E94_germ->Write();
	E94_germ->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Germ_pd94_ungated.png","png");


	//Ru94 Energy
	TCanvas *E94ru = new TCanvas("E94ru","E94ru",w,h);
	gammaru(ru3energy1);
	ru3energy1->Draw();
    latex4.DrawLatex(146,5350,"146");
    latex4.DrawLatex(311,3500,"311");
    latex4.DrawLatex(755,1360,"755");
    latex4.DrawLatex(1431,720,"1431");
	E94ru->Write();
	E94ru->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Labr3_ru94_bgs.png","png");

	//Ru94 Isomeric Lifetime
	TCanvas *lt94ru = new TCanvas("lt94ru","lt94ru",w,h);
	lt94ru->SetLogy();
	lifetimeru(ru94lifetime);
	ru94lifetime->Draw();
	lt94ru->Write();
	lt94ru->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/ru94_bgs_lifetime.png","png");

//PID Reverse Gating
	
	TCanvas *PID106_reverse = new TCanvas("PID106_reverse","PID106_reverse",w,h);
	pids3in1(reverse106);
	pids3in1(reverse106_bg);
	pids3in1(reverse106_s);
    gROOT->ForceStyle();    
    PID106_reverse->Divide(1,3,0,0);
    PID106_reverse->cd(1);
    reverse106->Draw("colz");
    PID106_reverse->cd(2);
    reverse106_bg->Draw("colz");
    PID106_reverse->cd(3);
    reverse106_s->Draw("colz");
	PID106_reverse->Write();
	PID106_reverse->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/PID106_reverse.png","png");

//PID Reverse Gating Subtractions

    auto legend94pd = new TLegend(0.1,0.7,0.48,0.9);
    legend94pd->AddEntry(reverse684_p,"Gamma Ray Energy Gated A/Q","l");
    legend94pd->AddEntry(reverse684_bg_p,"Background Gated A/Q","l");
    legend94pd->AddEntry(reverse684_s_p,"Background Subtracted A/Q","l");
    legend94pd->SetTextSize(0.15);

	TCanvas *PID96_reverse_projections = new TCanvas("PID96_reverse_projections","PID96_reverse_projections",w,h);
    PID96_reverse_projections->Divide(1,3,0,0);
    PID96_reverse_projections->cd(1);
    pidsproj_3in1(reverse106_p);
    pidsproj_3in1(reverse106_bg_p);
    pidsproj_3in1(reverse106_s_p);
    reverse106_p->GetYaxis()->SetRangeUser(-500,8500);
    reverse106_p->SetLineColor(kRed+1);
    reverse106_p->Draw();
    reverse106_bg_p->SetLineColor(kAzure-1);
    reverse106_bg_p->Draw("same");
    reverse106_s_p->SetLineColor(kTeal-7);
    reverse106_s_p->Draw("same");
    legend94pd->Draw("same");
    PID96_reverse_projections->cd(2);
    pidsproj_3in1(reverse684_p);
    pidsproj_3in1(reverse684_bg_p);
    pidsproj_3in1(reverse684_s_p);
    reverse684_p->SetLineColor(kRed+1);
    reverse684_p->GetYaxis()->SetRangeUser(-500,5500);
    reverse684_p->Draw();
    reverse684_bg_p->SetLineColor(kAzure-1);
    reverse684_bg_p->Draw("same");
    reverse684_s_p->SetLineColor(kTeal-7);
    reverse684_s_p->Draw("same");
    PID96_reverse_projections->cd(3);
    pidsproj_3in1(reverse1415_p);
    pidsproj_3in1(reverse1415_bg_p);
    pidsproj_3in1(reverse1415_s_p);
    reverse1415_p->SetLineColor(kRed+1);
    reverse1415_p->GetYaxis()->SetRangeUser(-200,2500);
    reverse1415_p->Draw();
    reverse1415_bg_p->SetLineColor(kAzure-1);
    reverse1415_bg_p->Draw("same");
    reverse1415_s_p->SetLineColor(kTeal-7);
    reverse1415_s_p->Draw("same");
	PID96_reverse_projections->Write();

    
	TCanvas *PID94_reverse_projections = new TCanvas("PID94_reverse_projections","PID94_reverse_projections",w,h);
    PID94_reverse_projections->Divide(1,3,0,0);
    PID94_reverse_projections->cd(1);
    pidsproj_3in1(reverse96_p);
    pidsproj_3in1(reverse96_bg_p);
    pidsproj_3in1(reverse96_s_p);
    //reverse96_p->GetYaxis()->SetRangeUser(-500,8500);
    
    reverse96_p->SetLineColor(kRed+1);
    reverse96_p->Draw();
    reverse96_bg_p->SetLineColor(kAzure-1);
    reverse96_bg_p->Draw("same");
    reverse96_s_p->SetLineColor(kTeal-7);
    reverse96_s_p->Draw("same");
    legend94pd->Draw("same");

    PID94_reverse_projections->cd(2);
    pidsproj_3in1(reverse660_p);
    pidsproj_3in1(reverse660_bg_p);
    pidsproj_3in1(reverse660_s_p);
    reverse660_p->SetLineColor(kRed+1);
    reverse660_p->GetYaxis()->SetRangeUser(-500,5500);
    reverse660_p->Draw();
    reverse660_bg_p->SetLineColor(kAzure-1);
    reverse660_bg_p->Draw("same");
    reverse660_s_p->SetLineColor(kTeal-7);
    reverse660_s_p->Draw("same");
    
    PID94_reverse_projections->cd(3);
    pidsproj_3in1(reverse814_p);
    pidsproj_3in1(reverse814_bg_p);
    pidsproj_3in1(reverse814_s_p);
    reverse814_p->SetLineColor(kRed+1);
    //reverse814_p->GetYaxis()->SetRangeUser(-200,2500);
    reverse814_p->Draw();
    reverse814_bg_p->SetLineColor(kAzure-1);
    reverse814_bg_p->Draw("same");
    reverse814_s_p->SetLineColor(kTeal-7);
    reverse814_s_p->Draw("same");
    
	PID94_reverse_projections->Write();


	TCanvas *PID94_reverse_projections_highE = new TCanvas("PID94_reverse_projections_highE","PID94_reverse_projections_highE",w,h);
    PID94_reverse_projections_highE->Divide(1,3,0,0);
    PID94_reverse_projections_highE->cd(1);
    pidsproj_3in1(reverse905_p);
    pidsproj_3in1(reverse905_bg_p);
    pidsproj_3in1(reverse905_s_p);
    //reverse905_p->GetYaxis()->SetRangeUser(-500,8500);
    reverse905_p->SetLineColor(kRed+1);
    reverse905_p->Draw();
    reverse905_bg_p->SetLineColor(kAzure-1);
    reverse905_bg_p->Draw("same");
    reverse905_s_p->SetLineColor(kTeal-7);
    reverse905_s_p->Draw("same");
    legend94pd->Draw("same");
    PID94_reverse_projections_highE->cd(2);
    pidsproj_3in1(reverse994_p);
    pidsproj_3in1(reverse994_bg_p);
    pidsproj_3in1(reverse994_s_p);
    reverse684_p->SetLineColor(kRed+1);
    //reverse684_p->GetYaxis()->SetRangeUser(-500,5500);
    reverse994_p->Draw();
    reverse994_bg_p->SetLineColor(kAzure-1);
    reverse994_bg_p->Draw("same");
    reverse994_s_p->SetLineColor(kTeal-7);
    reverse994_s_p->Draw("same");
    PID94_reverse_projections_highE->cd(3);
    pidsproj_3in1(reverse1092_p);
    pidsproj_3in1(reverse1092_bg_p);
    pidsproj_3in1(reverse1092_s_p);
    reverse1415_p->SetLineColor(kRed+1);
    //reverse1415_p->GetYaxis()->SetRangeUser(-200,2500);
    reverse1092_p->Draw();
    reverse1092_bg_p->SetLineColor(kAzure-1);
    reverse1092_bg_p->Draw("same");
    reverse1092_s_p->SetLineColor(kTeal-7);
    reverse1092_s_p->Draw("same");
	PID94_reverse_projections_highE->Write();





	//E vs dt germanium + labr3 for all isotopes
	TLatex latex5;
    latex5.SetTextSize(0.05);
    latex5.SetTextAlign(12);  //align at top
    latex5.SetTextFont(42);

	TCanvas *Evsdtpd96 = new TCanvas("Evsdtpd96","Evsdtpd96",w,h);
	Edtpd96(pd96edt);
	pd96edt->Draw("colz");
    latex5.DrawLatex(470,1415,"1415 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(470,684,"684 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(470,325,"325 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(470,106,"106 keV 8^{+} #rightarrow 6^{+}");
	Evsdtpd96->SetLogz();
	Evsdtpd96->Write();
	Evsdtpd96->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Evsdtpd96_labr3.png","png");


	TCanvas *Evsdtpd94 = new TCanvas("Evsdtpd94","Evsdtpd94",w,h);
	Edtpd94(pd94edt);
	pd94edt->Draw("colz");
    latex5.DrawLatex(470,1092,"1092 keV 10^{+} #rightarrow 8^{+}");
    latex5.DrawLatex(470,994,"994 keV 12^{+} #rightarrow 10^{+}");
    latex5.DrawLatex(470,905,"905 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(470,814,"814 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(470,659,"659 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(470,324,"324 keV 8^{+} #rightarrow 6^{+}");
    latex5.DrawLatex(470,120,"96 keV 14^{+} #rightarrow 12^{+}");
	Evsdtpd94->SetLogz();	
	Evsdtpd94->Write();
	Evsdtpd94->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Evsdtpd94_labr3.png","png");

	TCanvas *Evsdtru94 = new TCanvas("Evsdtru94","Evsdtru94",w,h);
	Edtru94(ru3edt);
	ru3edt->Draw("colz");
    latex5.DrawLatex(120,1353,"1431 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(165,700,"755 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(710,357,"311 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(710,220,"146 keV 8^{+} #rightarrow 6^{+}");
	Evsdtru94->SetLogz();	
	Evsdtru94->Write();
	Evsdtru94->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Evsdtru94_ge.png","png");

	TCanvas *Evsdtpd96germ = new TCanvas("Evsdtpd96germ","Evsdtpd96germ",w,h);
	Edtgerm(Edt96germ);
	Edt96germ->Draw("colz");
    latex5.DrawLatex(3000,1515,"1415 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(3000,784,"684 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(3000,425,"325 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(3000,206,"106 keV 8^{+} #rightarrow 6^{+}");
	Evsdtpd96germ->SetLogz();
	Evsdtpd96germ->Write();
	Evsdtpd96germ->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Evsdtpd96_germ.png","png");

	TCanvas *Evsdtpd94germ = new TCanvas("Evsdtpd94germ","Evsdtpd94germ",w,h);
	Edtgerm(Edt94germ);
	Edt94germ->Draw("colz");
    latex5.DrawLatex(2400,1092,"1092 keV 10^{+} #rightarrow 8^{+}");
    latex5.DrawLatex(2400,994,"994 keV 12^{+} #rightarrow 10^{+}");
    latex5.DrawLatex(2400,905,"905 keV 4^{+} #rightarrow 2^{+}");
    latex5.DrawLatex(2400,814,"814 keV 2^{+} #rightarrow 0^{+}");
    latex5.DrawLatex(2400,659,"659 keV 6^{+} #rightarrow 4^{+}");
    latex5.DrawLatex(2400,324,"324 keV 8^{+} #rightarrow 6^{+}");
    latex5.DrawLatex(2400,96,"96 keV 14^{+} #rightarrow 12^{+}");
	Evsdtpd94germ->SetLogz();
	Evsdtpd94germ->Write();
	Evsdtpd94germ->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/Evsdtpd94_germ.png","png");

	//PID96_reverse_projections->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/PID96_reverse_projections.png","png");



//Gamma-ray E for different gates (same plot one for each isotope)


	Stackedlabr3_energy(edt96proj_np_Plastic);
	Stackedlabr3_energy(edt96proj_np_SC41);
	Stackedlabr3_energy(edt96proj_np_AIDA);
	Stackedlabr3_energy(edt96proj_np_SC41_Plastic);
	Stackedlabr3_energy(edt96proj_np_Plastic_AIDA);
	Stackedlabr3_energy(edt96proj_np_SC41_AIDA);
	Stackedlabr3_energy(edt96proj_np_SC41_Plastic_AIDA);

	TCanvas *pd96_energy_gates_labr3 = new TCanvas("pd96_energy_gates_labr3","pd96_energy_gates_labr3",w,h);
	edt96proj_np->SetLineColor(1);
	edt96proj_np->Draw();
	edt96proj_np_Plastic->SetLineColor(2);
	edt96proj_np_Plastic->Draw("same");
	edt96proj_np_SC41->SetLineColor(3);
	edt96proj_np_SC41->Draw("same");
	edt96proj_np_AIDA->SetLineColor(4);
	edt96proj_np_AIDA->Draw("same");
	edt96proj_np_SC41_Plastic->SetLineColor(5);
	edt96proj_np_SC41_Plastic->Draw("same");
	edt96proj_np_Plastic_AIDA->SetLineColor(6);
	edt96proj_np_Plastic_AIDA->Draw("same");
	edt96proj_np_SC41_AIDA->SetLineColor(7);
	edt96proj_np_SC41_AIDA->Draw("same");
	edt96proj_np_SC41_Plastic_AIDA->SetLineColor(8);
	edt96proj_np_SC41_Plastic_AIDA->Draw("same");

    auto legend96 = new TLegend(0.1,0.7,0.48,0.9);
    legend96->SetHeader("Gamma Ray Gating Conditions","C"); // option "C" allows to center the header
    legend96->AddEntry(edt96proj_np,"PID","l");
    legend96->AddEntry(edt96proj_np_Plastic,"PID + Plastic Energy","l");
    legend96->AddEntry(edt96proj_np_SC41,"PID + SC41/SC42 Energy","l");
    legend96->AddEntry(edt96proj_np_AIDA,"PID + Stopped in AIDA","l");
    legend96->AddEntry(edt96proj_np_SC41_Plastic,"PID + SC41/SC42 Energy + Plastic Energy","l");
    legend96->AddEntry(edt96proj_np_Plastic_AIDA,"PID + Plastic Energy + Stopped in AIDA","l");
    legend96->AddEntry(edt96proj_np_SC41_AIDA,"PID + SC41/42 Energy + Stopped in AIDA","l");
    legend96->AddEntry(edt96proj_np_SC41_Plastic_AIDA,"PID + SC41/42 Energy + Stopped in AIDA + Plastic Energy","l");
    legend96->SetTextSize(0.04);
    legend96->Draw("same");

	pd96_energy_gates_labr3->Write();
	pd96_energy_gates_labr3->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/pd96_energy_gates_labr3.png","png");


	Stackedlabr3_energy(edt94proj_np_Plastic);
	Stackedlabr3_energy(edt94proj_np_SC41);
	Stackedlabr3_energy(edt94proj_np_AIDA);
	Stackedlabr3_energy(edt94proj_np_SC41_Plastic);
	Stackedlabr3_energy(edt94proj_np_Plastic_AIDA);
	Stackedlabr3_energy(edt94proj_np_SC41_AIDA);
	Stackedlabr3_energy(edt94proj_np_SC41_Plastic_AIDA);

	TCanvas *pd94_energy_gates_labr3 = new TCanvas("pd94_energy_gates_labr3","pd94_energy_gates_labr3",w,h);
	edt94proj_np->SetLineColor(1);
	edt94proj_np->Draw();
	edt94proj_np_Plastic->SetLineColor(2);
	edt94proj_np_Plastic->Draw("same");
	edt94proj_np_SC41->SetLineColor(3);
	edt94proj_np_SC41->Draw("same");
	edt94proj_np_AIDA->SetLineColor(4);
	edt94proj_np_AIDA->Draw("same");
	edt94proj_np_SC41_Plastic->SetLineColor(5);
	edt94proj_np_SC41_Plastic->Draw("same");
	edt94proj_np_Plastic_AIDA->SetLineColor(6);
	edt94proj_np_Plastic_AIDA->Draw("same");
	edt94proj_np_SC41_AIDA->SetLineColor(7);
	edt94proj_np_SC41_AIDA->Draw("same");
	edt94proj_np_SC41_Plastic_AIDA->SetLineColor(8);
	edt94proj_np_SC41_Plastic_AIDA->Draw("same");

    auto legend94 = new TLegend(0.1,0.7,0.48,0.9);
    legend94->SetHeader("Gamma Ray Gating Conditions","C"); // option "C" allows to center the header
    legend94->AddEntry(edt94proj_np,"PID","l");
    legend94->AddEntry(edt94proj_np_Plastic,"PID + Plastic Energy","l");
    legend94->AddEntry(edt94proj_np_SC41,"PID + SC41/SC42 Energy","l");
    legend94->AddEntry(edt94proj_np_AIDA,"PID + Stopped in AIDA","l");
    legend94->AddEntry(edt94proj_np_SC41_Plastic,"PID + SC41/SC42 Energy + Plastic Energy","l");
    legend94->AddEntry(edt94proj_np_Plastic_AIDA,"PID + Plastic Energy + Stopped in AIDA","l");
    legend94->AddEntry(edt94proj_np_SC41_AIDA,"PID + SC41/42 Energy + Stopped in AIDA","l");
    legend94->AddEntry(edt94proj_np_SC41_Plastic_AIDA,"PID + SC41/42 Energy + Stopped in AIDA + Plastic Energy","l");
    legend94->SetTextSize(0.04);
    legend94->SetLineWidth(0);

    legend94->Draw("same");

	pd94_energy_gates_labr3->Write();
	pd94_energy_gates_labr3->Print("/home/sj00239/Thesis/template/Figures/final_root_figs/pd94_energy_gates_labr3.png","png");
//SC41/42 Energy Gate

//AIDA Position

//LaBr3 Energy Drift
//LaBr3 Time Drift
//LaBr3 Alignment



//Germanium Energy for different gates
//Germanium isomer lifetime plots
//94Ru Isomer Lifetime plot
//94Ru background subtraction


//FATIMA Efficiency All Isotopes
//Germanium Efficiency All Isotopes
//FATIMA + Germanium Isomeric Ratios for 96Pd
//FATIMA + Germanium Isomeric Ratios for 94Pd
//FATIMA + Germanium Isomeric Ratios for 94Ru

	
//Lifetime plots
//96Pd Gate
//94Pd Gate
//94Ru Gate

//Simulation Comparison (DESPEC)
*/



lts->Close();



}
