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



void aoq_subtract() {

	TFile g("./hists/reversegate_labr3_bgs.root");

	 TH2F *zvsaoq = (TH2F*)g.Get("zvsaoq");
	 TH2F *reverse1415 = (TH2F*)g.Get("zvsaoqreversecut96pd1415");
	 TH2F *reverse684 = (TH2F*)g.Get("zvsaoqreversecut96pd684");
	 TH2F *reverse325 = (TH2F*)g.Get("zvsaoqreversecut96pd325");
	 TH2F *reverse106 = (TH2F*)g.Get("zvsaoqreversecut96pd106");

	 TH2F *reverse1415_bg = (TH2F*)g.Get("zvsaoqreversecut96pd1415_bg");
	 TH2F *reverse684_bg = (TH2F*)g.Get("zvsaoqreversecut96pd684_bg");
	 TH2F *reverse325_bg = (TH2F*)g.Get("zvsaoqreversecut96pd325_bg");
	 TH2F *reverse106_bg = (TH2F*)g.Get("zvsaoqreversecut96pd106_bg");


	 TH2F *reverse905 = (TH2F*)g.Get("zvsaoqreversecut94pd905");
	 TH2F *reverse814 = (TH2F*)g.Get("zvsaoqreversecut94pd814");
	 TH2F *reverse324 = (TH2F*)g.Get("zvsaoqreversecut94pd324");
	 TH2F *reverse1092 = (TH2F*)g.Get("zvsaoqreversecut94pd1092");
	 TH2F *reverse660 = (TH2F*)g.Get("zvsaoqreversecut94pd660");
	 TH2F *reverse994 = (TH2F*)g.Get("zvsaoqreversecut94pd994");
	 TH2F *reverse96 = (TH2F*)g.Get("zvsaoqreversecut94pd96");

	 TH2F *reverse905_bg = (TH2F*)g.Get("zvsaoqreversecut94pd905_bg");
	 TH2F *reverse814_bg = (TH2F*)g.Get("zvsaoqreversecut94pd814_bg");
	 TH2F *reverse324_bg = (TH2F*)g.Get("zvsaoqreversecut94pd324_bg");
	 TH2F *reverse1092_bg = (TH2F*)g.Get("zvsaoqreversecut94pd1092_bg");
	 TH2F *reverse660_bg = (TH2F*)g.Get("zvsaoqreversecut94pd660_bg");
	 TH2F *reverse994_bg = (TH2F*)g.Get("zvsaoqreversecut94pd994_bg");
	 TH2F *reverse96_bg = (TH2F*)g.Get("zvsaoqreversecut94pd96_bg");

	 zvsaoq->SetDirectory(0);
	 reverse1415->SetDirectory(0);
	 reverse684->SetDirectory(0);
	 reverse325->SetDirectory(0);
	 reverse106->SetDirectory(0);

	 reverse1415_bg->SetDirectory(0);
	 reverse684_bg->SetDirectory(0);
	 reverse325_bg->SetDirectory(0);
	 reverse106_bg->SetDirectory(0);
	 
	 reverse905->SetDirectory(0);
	 reverse814->SetDirectory(0);
	 reverse324->SetDirectory(0);
	 reverse1092->SetDirectory(0);
	 reverse660->SetDirectory(0);
	 reverse994->SetDirectory(0);
	 reverse96->SetDirectory(0);

	 reverse905_bg->SetDirectory(0); 
	 reverse814_bg->SetDirectory(0);
	 reverse324_bg->SetDirectory(0); 
	 reverse1092_bg->SetDirectory(0);
	 reverse660_bg->SetDirectory(0);
	 reverse994_bg->SetDirectory(0);
	 reverse96_bg->SetDirectory(0);
	 
	 
	 TH2F *ivstot106 = (TH2F*)g.Get("ivstot106");
	 TH2F *ivstot325 = (TH2F*)g.Get("ivstot325");
	 TH2F *ivstot684 = (TH2F*)g.Get("ivstot684");
	 TH2F *ivstot1415 = (TH2F*)g.Get("ivstot1415");
	 TH2F *ivstot96 = (TH2F*)g.Get("ivstot96");
	 TH2F *ivstot324 = (TH2F*)g.Get("ivstot324");
	 TH2F *ivstot660 = (TH2F*)g.Get("ivstot660");
	 TH2F *ivstot814 = (TH2F*)g.Get("ivstot814");
	 TH2F *ivstot905 = (TH2F*)g.Get("ivstot905");
	 TH2F *ivstot994 = (TH2F*)g.Get("ivstot994");
	 TH2F *ivstot1092 = (TH2F*)g.Get("ivstot1092");

	 ivstot106->SetDirectory(0);	 
	 ivstot325->SetDirectory(0);	 
	 ivstot684->SetDirectory(0);	 
	 ivstot1415->SetDirectory(0);	 
	 ivstot96->SetDirectory(0);	 
	 ivstot324->SetDirectory(0);	 
	 ivstot660->SetDirectory(0);	 
	 ivstot814->SetDirectory(0);	 
	 ivstot905->SetDirectory(0);	 
	 ivstot994->SetDirectory(0);	 
	 ivstot1092->SetDirectory(0);	 


	 TH1D *AIDAStopped1415 = (TH1D*)g.Get("AIDAstopped96pd1415");
	 TH1D *AIDAStopped1092 = (TH1D*)g.Get("AIDAstopped94pd1092");
	 AIDAStopped1415->SetDirectory(0);	 
	 AIDAStopped1092->SetDirectory(0);	 


	 // to decouple it from the open file directory

	 g.Close();

/* OUTFILE MIGHT NEED
	int gate_info [gate_num][6];
	ifstream outFile;
	outFile.open(gates);
	if (!outFile){
    		cerr << "Unable to open file your data file";
    		exit(1);   // call system to stop
		}
*/

	double lambda, constant;
	

	TFile *lts = new TFile("aoq_subs.root","RECREATE");

	 zvsaoq->Write();

    //TCanvas *can = new TCanvas();
	//TH2F* reverse1415_s = reverse1415;
    TH2F *reverse1415_s = new TH2F("reverse1415_s","reverse1415_s",1500,0,5, 1500,0,100);
    reverse1415_s->Add(reverse1415);
    TH2F *reverse684_s = new TH2F("reverse684_s","reverse684_s",1500,0,5, 1500,0,100);
    reverse684_s->Add(reverse684);
    TH2F *reverse325_s = new TH2F("reverse325_s","reverse325_s",1500,0,5, 1500,0,100);
    reverse325_s->Add(reverse325);
    TH2F *reverse106_s = new TH2F("reverse106_s","reverse106_s",1500,0,5, 1500,0,100);
    reverse106_s->Add(reverse106);

    TH2F *reverse905_s = new TH2F("reverse905_s","reverse905_s",1500,0,5, 1500,0,100);
    reverse905_s->Add(reverse905);
    TH2F *reverse814_s = new TH2F("reverse814_s","reverse814_s",1500,0,5, 1500,0,100);
    reverse814_s->Add(reverse814);
    TH2F *reverse324_s = new TH2F("reverse324_s","reverse324_s",1500,0,5, 1500,0,100);
    reverse324_s->Add(reverse324);
    TH2F *reverse1092_s = new TH2F("reverse1092_s","reverse1092_s",1500,0,5, 1500,0,100);
    reverse1092_s->Add(reverse1092);
    TH2F *reverse660_s = new TH2F("reverse660_s","reverse660_s",1500,0,5, 1500,0,100);
    reverse660_s->Add(reverse660);
    TH2F *reverse994_s = new TH2F("reverse994_s","reverse994_s",1500,0,5, 1500,0,100);
    reverse994_s->Add(reverse994);
    TH2F *reverse96_s = new TH2F("reverse96_s","reverse96_s",1500,0,5, 1500,0,100);
    reverse96_s->Add(reverse96);

    TH2F *pd94total_s = new TH2F("pd94total_s","pd94total_s",1500,0,5, 1500,0,100);
    TH2F *pd96total_s = new TH2F("pd96total_s","pd96total_s",1500,0,5, 1500,0,100);

    reverse1415_s->Add(reverse1415_bg, -1);
    reverse684_s->Add(reverse684_bg, -1);
    reverse325_s->Add(reverse325_bg, -1);
    reverse106_s->Add(reverse106_bg, -1);

    reverse905_s->Add(reverse905_bg, -3);
    reverse814_s->Add(reverse814_bg, -3);
    reverse324_s->Add(reverse324_bg, -1);
    reverse660_s->Add(reverse660_bg, -1);
    reverse994_s->Add(reverse994_bg, -2);
    reverse96_s->Add(reverse96_bg, -1);
    reverse1092_s->Add(reverse1092_bg, -1);

/*
	for (int i = 0; i < 1500; i++){
		for (int j = 0; j < 1500; j++){

			if(reverse1415_s->GetBinContent(i,j) < 0 ){
				//reverse1415_s->SetBinContent(i, j, 0);
			}
			if(reverse684_s->GetBinContent(i,j) > 0 && reverse684_bg->GetBinContent(i,j) > 0 && reverse684_bg->GetBinContent(i,j) <= reverse684_s->GetBinContent(i,j) ){
				reverse684_s->SetBinContent(i,j, reverse684_s->GetBinContent(i,j) - reverse684_bg->GetBinContent(i,j));
			}
			if(reverse325_s->GetBinContent(i,j) > 0 && reverse325_bg->GetBinContent(i,j) > 0 && reverse325_bg->GetBinContent(i,j) <= reverse325_s->GetBinContent(i,j) ){
				reverse325_s->SetBinContent(i,j, reverse325_s->GetBinContent(i,j) - reverse325_bg->GetBinContent(i,j));
			}
			if(reverse106_s->GetBinContent(i,j) > 0 && reverse106_bg->GetBinContent(i,j) > 0 && reverse106_bg->GetBinContent(i,j) <= reverse106_s->GetBinContent(i,j) ){
				reverse106_s->SetBinContent(i,j, reverse106_s->GetBinContent(i,j) - reverse106_bg->GetBinContent(i,j));
			}

			if(reverse905_s->GetBinContent(i,j) > 0 && reverse905_bg->GetBinContent(i,j) > 0 && reverse905_bg->GetBinContent(i,j) <= reverse905_s->GetBinContent(i,j) ){
				reverse905_s->SetBinContent(i,j, reverse905_s->GetBinContent(i,j) - reverse905_bg->GetBinContent(i,j));
			}
			if(reverse814_s->GetBinContent(i,j) > 0 && reverse814_bg->GetBinContent(i,j) > 0 && reverse814_bg->GetBinContent(i,j) <= reverse814_s->GetBinContent(i,j) ){
				reverse814_s->SetBinContent(i,j, reverse814_s->GetBinContent(i,j) - reverse814_bg->GetBinContent(i,j));
			}
			if(reverse324_s->GetBinContent(i,j) > 0 && reverse324_bg->GetBinContent(i,j) > 0 && reverse324_bg->GetBinContent(i,j) <= reverse324_s->GetBinContent(i,j) ){
				reverse324_s->SetBinContent(i,j, reverse324_s->GetBinContent(i,j) - reverse324_bg->GetBinContent(i,j));
			}
			if(reverse1092_s->GetBinContent(i,j) > 0 && reverse1092_bg->GetBinContent(i,j) > 0 && reverse1092_bg->GetBinContent(i,j) <= reverse1092_s->GetBinContent(i,j) ){
				reverse1092_s->SetBinContent(i,j, reverse1092_s->GetBinContent(i,j) - reverse1092_bg->GetBinContent(i,j));
			}
			if(reverse660_s->GetBinContent(i,j) < 0.1){
				reverse660_s->SetBinContent(i,j, 0.);
			}
			if(reverse994_s->GetBinContent(i,j) > 0 && reverse994_bg->GetBinContent(i,j) > 0 && reverse994_bg->GetBinContent(i,j) <= reverse994_s->GetBinContent(i,j) ){
				reverse994_s->SetBinContent(i,j, reverse994_s->GetBinContent(i,j) - reverse994_bg->GetBinContent(i,j));
			}
			if(reverse96_s->GetBinContent(i,j) > 0 && reverse96_bg->GetBinContent(i,j) > 0 && reverse96_bg->GetBinContent(i,j) <= reverse96_s->GetBinContent(i,j) ){
				reverse96_s->SetBinContent(i,j, reverse96_s->GetBinContent(i,j) - reverse96_bg->GetBinContent(i,j));
			}

		}
	}*/

	TH1D* zvsaoq_p = zvsaoq->ProjectionX("zvsaoq_p",732,746);
	TH1D* reverse1415_p = reverse1415->ProjectionX("reverse1415_p",732,746);
	TH1D* reverse1415_bg_p = reverse1415_bg->ProjectionX("reverse1415_bg_p",732,746);
	TH1D* reverse1415_s_p = reverse1415_s->ProjectionX("reverse1415_s_p",732,746);
	aoverqproj(zvsaoq_p);
	aoverqproj(reverse1415_p);
	aoverqproj(reverse1415_bg_p);
	aoverqproj_subs(reverse1415_s_p);


	TH1D* reverse684_p = reverse684->ProjectionX("reverse684_p",732,746);
	TH1D* reverse684_bg_p = reverse684_bg->ProjectionX("reverse684_bg_p",732,746);
	TH1D* reverse684_s_p = reverse684_s->ProjectionX("reverse684_s_p",732,746);
	aoverqproj(reverse684_p);
	aoverqproj(reverse684_bg_p);
	aoverqproj_subs(reverse684_s_p);

	TH1D* reverse325_p = reverse325->ProjectionX("reverse325_p",732,746);
	TH1D* reverse325_bg_p = reverse325_bg->ProjectionX("reverse325_bg_p",732,746);
	TH1D* reverse325_s_p = reverse325_s->ProjectionX("reverse325_s_p",732,746);
	aoverqproj(reverse325_p);
	aoverqproj(reverse325_bg_p);
	aoverqproj_subs(reverse325_s_p);
	
	TH1D* reverse106_p = reverse106->ProjectionX("reverse106_p",732,746);
	TH1D* reverse106_bg_p = reverse106_bg->ProjectionX("reverse106_bg_p",732,746);
	TH1D* reverse106_s_p = reverse106_s->ProjectionX("reverse106_s_p",732,746);
	aoverqproj(reverse106_p);
	aoverqproj(reverse106_bg_p);
	aoverqproj_subs(reverse106_s_p);
	
	TH1D* reverse905_p = reverse905->ProjectionX("reverse905_p",732,746);
	TH1D* reverse905_bg_p = reverse905_bg->ProjectionX("reverse905_bg_p",732,746);
	TH1D* reverse905_s_p = reverse905_s->ProjectionX("reverse905_s_p",732,746);
	aoverqproj(reverse905_p);
	aoverqproj(reverse905_bg_p);
	aoverqproj_subs(reverse905_s_p);
	
	TH1D* reverse814_p = reverse814->ProjectionX("reverse814_p",732,746);
	TH1D* reverse814_bg_p = reverse814_bg->ProjectionX("reverse814_bg_p",732,746);
	TH1D* reverse814_s_p = reverse814_s->ProjectionX("reverse814_s_p",732,746);
	aoverqproj(reverse814_p);
	aoverqproj(reverse814_bg_p);
	aoverqproj_subs(reverse814_s_p);
	
	TH1D* reverse324_p = reverse324->ProjectionX("reverse324_p",732,746);
	TH1D* reverse324_bg_p = reverse324_bg->ProjectionX("reverse324_bg_p",732,746);
	TH1D* reverse324_s_p = reverse324_s->ProjectionX("reverse324_s_p",732,746);
	aoverqproj(reverse324_p);
	aoverqproj(reverse324_bg_p);
	aoverqproj_subs(reverse324_s_p);
	
	TH1D* reverse1092_p = reverse1092->ProjectionX("reverse1092_p",732,746);
	TH1D* reverse1092_bg_p = reverse1092_bg->ProjectionX("reverse1092_bg_p",732,746);
	TH1D* reverse1092_s_p = reverse1092_s->ProjectionX("reverse1092_s_p",732,746);
	aoverqproj(reverse1092_p);
	aoverqproj(reverse1092_bg_p);
	aoverqproj_subs(reverse1092_s_p);
	
	TH1D* reverse660_p = reverse660->ProjectionX("reverse660_p",732,746);
	TH1D* reverse660_bg_p = reverse660_bg->ProjectionX("reverse660_bg_p",732,746);
	TH1D* reverse660_s_p = reverse660_s->ProjectionX("reverse660_s_p",732,746);
	aoverqproj(reverse660_p);
	aoverqproj(reverse660_bg_p);
	aoverqproj_subs(reverse660_s_p);
	
	TH1D* reverse994_p = reverse994->ProjectionX("reverse994_p",732,746);
	TH1D* reverse994_bg_p = reverse994_bg->ProjectionX("reverse994_bg_p",732,746);
	TH1D* reverse994_s_p = reverse994_s->ProjectionX("reverse994_s_p",732,746);
	aoverqproj(reverse994_p);
	aoverqproj(reverse994_bg_p);
	aoverqproj_subs(reverse994_s_p);
	
	TH1D* reverse96_p = reverse96->ProjectionX("reverse96_p",732,746);
	TH1D* reverse96_bg_p = reverse96_bg->ProjectionX("reverse96_bg_p",732,746);
	TH1D* reverse96_s_p = reverse96_s->ProjectionX("reverse96_s_p",732,746);
	aoverqproj(reverse96_p);
	aoverqproj(reverse96_bg_p);
	aoverqproj_subs(reverse96_s_p);


	pd94total_s->Add(reverse994_s);
	pd94total_s->Add(reverse814_s);
	pd94total_s->Add(reverse1092_s);
	pd94total_s->Add(reverse905_s);
	pd94total_s->Add(reverse660_s);
	pids(pd94total_s);
	TH1D* pd94total_s_p = pd94total_s->ProjectionX("pd94total_s_p",732,746);
	aoverqproj_subs(pd94total_s_p);


	pd96total_s->Add(reverse1415_s);
	pd96total_s->Add(reverse684_s);
	pids(pd96total_s);
	TH1D* pd96total_s_p = pd96total_s->ProjectionX("pd96total_s_p",732,746);
	aoverqproj_subs(pd96total_s_p);

pids(reverse1415);
pids(reverse1415_bg);
pids(reverse1415_s);
pids(reverse684);
pids(reverse684_bg);
pids(reverse684_s);
pids(reverse325);
pids(reverse325_bg);
pids(reverse325_s);
pids(reverse106);
pids(reverse106_bg);
pids(reverse106_s);
pids(reverse905);
pids(reverse905_bg);
pids(reverse905_s);
pids(reverse814);
pids(reverse814_bg);
pids(reverse814_s);
pids(reverse324);
pids(reverse324_bg);
pids(reverse324_s);
pids(reverse1092);
pids(reverse1092_bg);
pids(reverse1092_s);
pids(reverse660);
pids(reverse660_bg);
pids(reverse660_s);
pids(reverse994);
pids(reverse994_bg);
pids(reverse994_s);
pids(reverse96);
pids(reverse96_bg);
pids(reverse96_s);


	TCanvas *c5 = new TCanvas("c5","multipads",900,700);
    gROOT->ForceStyle();    
    c5->Divide(1,5,0,0);
    c5->cd(1);
    zvsaoq_p->Draw();
    c5->cd(2);
    reverse1415_p->Draw();
    c5->cd(3);
    reverse1415_bg_p->Draw();
    c5->cd(4);
    reverse1415_s_p->Draw();
    c5->cd(5);
    pd96total_s_p->Draw();
	c5->Write();

	TCanvas *c2 = new TCanvas("c2","multipads2",900,700);
    gROOT->ForceStyle();    
    c2->Divide(1,5,0,0);
    c2->cd(1);
    zvsaoq_p->Draw();
    c2->cd(2);
    reverse1092_p->Draw();
    c2->cd(3);
    reverse1092_bg_p->Draw();
    c2->cd(4);
    reverse1092_s_p->Draw();
    c2->cd(5);
    pd94total_s_p->Draw();
	c2->Write();

	TCanvas *c3 = new TCanvas("c3","multipads3",900,700);
    gROOT->ForceStyle();    
    c3->Divide(1,3,0,0);
    c3->cd(1);
    reverse1415->Draw("colz");
    c3->cd(2);
    reverse1415_bg->Draw("colz");
    c3->cd(3);
    reverse1415_s->Draw("colz");
	c3->Write();

	TCanvas *c4 = new TCanvas("c4","multipads4",900,700);
    gROOT->ForceStyle();    
    reverse1415_p->Draw();
    reverse1415_bg_p->SetLineColor(kBlue);
    reverse1415_bg_p->Draw("same");
    reverse1415_s_p->SetLineColor(kGreen);
    reverse1415_s_p->Draw("same");
    auto legend96 = new TLegend(0.1,0.7,0.48,0.9);
    legend96->AddEntry(reverse1415_p,"1415 keV Gate","l");
    legend96->AddEntry(reverse1415_bg_p,"1415 keV Background Gate","l");
    legend96->AddEntry(reverse1415_s_p,"1415 keV Background Subtracted Gate","l");
    legend96->Draw("same");
	c4->Write();


	TCanvas *c8 = new TCanvas("c8","multipads8",900,700);
    gROOT->ForceStyle();    
    reverse684_p->Draw();
    reverse684_bg_p->SetLineColor(kBlue);
    reverse684_bg_p->Draw("same");
    reverse684_s_p->SetLineColor(kGreen);
    reverse684_s_p->Draw("same");
    auto legend8 = new TLegend(0.1,0.7,0.48,0.9);
    legend8->AddEntry(reverse684_p,"684 keV Gate","l");
    legend8->AddEntry(reverse684_bg_p,"684 keV Background Gate","l");
    legend8->AddEntry(reverse684_s_p,"684 keV Background Subtracted Gate","l");
    legend8->Draw("same");
	c8->Write();

	TCanvas *c9 = new TCanvas("c9","multipads8",900,700);
    gROOT->ForceStyle();    
    reverse106_p->Draw();
    reverse106_bg_p->SetLineColor(kBlue);
    reverse106_bg_p->Draw("same");
    reverse106_s_p->SetLineColor(kGreen);
    reverse106_s_p->Draw("same");
    auto legend9 = new TLegend(0.1,0.7,0.48,0.9);
    legend9->AddEntry(reverse684_p,"106 keV Gate","l");
    legend9->AddEntry(reverse684_bg_p,"106 keV Background Gate","l");
    legend9->AddEntry(reverse684_s_p,"106 keV Background Subtracted Gate","l");
    legend9->Draw("same");
	c9->Write();

	TCanvas *c10 = new TCanvas("c10","multipads8",900,700);
    c10->Divide(1,3,0,0);
    c10->cd(1);
    gROOT->ForceStyle();    
    reverse106_p->Draw();
    reverse106_bg_p->SetLineColor(kBlue);
    reverse106_bg_p->Draw("same");
    reverse106_s_p->SetLineColor(kGreen);
    reverse106_s_p->Draw("same");
    legend9->Draw("same");
    c10->cd(2);
    reverse684_p->Draw();
    reverse684_bg_p->SetLineColor(kBlue);
    reverse684_bg_p->Draw("same");
    reverse684_s_p->SetLineColor(kGreen);
    reverse684_s_p->Draw("same");
    legend8->Draw("same");
    c10->cd(3);
    reverse1415_p->Draw();
    reverse1415_bg_p->SetLineColor(kBlue);
    reverse1415_bg_p->Draw("same");
    reverse1415_s_p->SetLineColor(kGreen);
    reverse1415_s_p->Draw("same");
    legend96->Draw("same");
	c10->Write();

	TCanvas *c11 = new TCanvas("c11","multipads8",900,700);
    c11->Divide(1,6,0,0);
    c11->cd(1);
    gROOT->ForceStyle();    
    
    reverse96_p->Draw();
    reverse96_bg_p->SetLineColor(kBlue);
    reverse96_bg_p->Draw("same");
    reverse96_s_p->SetLineColor(kGreen);
    reverse96_s_p->Draw("same");
    auto legend94pd = new TLegend(0.1,0.7,0.48,0.9);
    legend94pd->AddEntry(reverse684_p,"Gamma Ray Energy Gate","l");
    legend94pd->AddEntry(reverse684_bg_p,"Background Gate","l");
    legend94pd->AddEntry(reverse684_s_p,"Background Subtracted Gate","l");
    legend94pd->Draw("same");
    c11->cd(2);
    reverse660_p->Draw();
    reverse660_bg_p->SetLineColor(kBlue);
    reverse660_bg_p->Draw("same");
    reverse660_s_p->SetLineColor(kGreen);
    reverse660_s_p->Draw("same");    
    
    c11->cd(3);
    reverse814_p->Draw();
    reverse814_bg_p->SetLineColor(kBlue);
    reverse814_bg_p->Draw("same");
    reverse814_s_p->SetLineColor(kGreen);
    reverse814_s_p->Draw("same");

    c11->cd(4);
    reverse905_p->Draw();
    reverse905_bg_p->SetLineColor(kBlue);
    reverse905_bg_p->Draw("same");
    reverse905_s_p->SetLineColor(kGreen);
    reverse905_s_p->Draw("same");
	
    c11->cd(5);
    reverse994_p->Draw();
    reverse994_bg_p->SetLineColor(kBlue);
    reverse994_bg_p->Draw("same");
    reverse994_s_p->SetLineColor(kGreen);
    reverse994_s_p->Draw("same");
	
    c11->cd(6);
    reverse1092_p->Draw();
    reverse1092_bg_p->SetLineColor(kBlue);
    reverse1092_bg_p->Draw("same");
    reverse1092_s_p->SetLineColor(kGreen);
    reverse1092_s_p->Draw("same");
	
	c11->Write();


	TCanvas *c12 = new TCanvas("c12","pad12",900,700);
	ivstot1415->ProjectionX("P1415",281,281)->Draw();
	ivstot1092->ProjectionX("P1092",281,281)->Draw("same");
    auto legendbplast = new TLegend(0.1,0.7,0.48,0.9);
    legendbplast->AddEntry("P1415","1415 keV Gate","l");
    legendbplast->AddEntry("P1092","1092 keV Gate","l");
    legendbplast->Draw("same");	
	c12->Write();



	aidastopped(AIDAStopped1415);
	aidastopped(AIDAStopped1092);
	AIDAStopped1092->SetLineColor(kRed);

	TCanvas *c13 = new TCanvas("c13","pad13",900,700);
	AIDAStopped1415->Draw();
	AIDAStopped1092->Draw("same");
	auto aidalegend = new TLegend(0.1,0.7,0.48,0.9);
    aidalegend->AddEntry(AIDAStopped1415,"1415 keV Gate","l");
    aidalegend->AddEntry(AIDAStopped1092,"1092 keV Gate","l");
    aidalegend->Draw("same");
	c13->Write();

	lts->Close();



}
