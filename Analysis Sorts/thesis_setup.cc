   Double_t w = 1920;
   Double_t h = 1080;

  void pids(TH2F *q1){

	q1->SetXTitle("A/Q");
	q1->SetYTitle("Z");
	q1->GetXaxis()->SetRangeUser(2.115, 2.25);
	q1->GetYaxis()->SetRangeUser(45, 52);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->GetXaxis()->SetTitleOffset(0.8);
	q1->GetYaxis()->SetTitleOffset(0.8);
	q1->SetMinimum(1);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->Write();
 }

  void pids3in1(TH2F *q1){

	q1->SetXTitle("A/Q");
	q1->SetYTitle("Z");
	q1->GetXaxis()->SetRangeUser(2.115, 2.25);
	q1->GetYaxis()->SetRangeUser(45, 51);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetXaxis()->SetLabelSize(0.15);
	q1->GetYaxis()->SetLabelSize(0.15);
	q1->GetXaxis()->SetTitleSize(0.15);
	q1->GetYaxis()->SetTitleSize(0.15);
	q1->GetXaxis()->SetTitleOffset(0.8);
	q1->GetYaxis()->SetTitleOffset(0.3);
	q1->GetYaxis()->SetNdivisions(5,3,0);
	q1->SetMinimum(5);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->Write();
 }

 void gamma(TH1D *q1){
	q1->SetStats(0);
	q1->SetTitle("");
	q1->GetXaxis()->SetTitleOffset(1);
	q1->SetXTitle("Energy (keV)");
	q1->SetYTitle("Counts/ 5 keV");
	q1->SetLineWidth(3);
	q1->Rebin(5);
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->GetXaxis()->SetTitleOffset(0.9);
	q1->GetYaxis()->SetTitleOffset(0.9);
	q1->GetXaxis()->SetRangeUser(0, 2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);
	q1->Write();
 }

  void gammaru(TH1D *q1){
	q1->SetStats(0);
	q1->SetTitle("");
	q1->GetXaxis()->SetTitleOffset(1);
	q1->SetXTitle("Energy (keV)");
	q1->SetYTitle("Counts/ 5 keV");
	q1->SetLineWidth(3);
	q1->SetLineColor(kBlack);
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->GetXaxis()->SetTitleOffset(0.9);
	q1->GetYaxis()->SetTitleOffset(0.9);
	q1->GetXaxis()->SetRangeUser(0, 2000);
	q1->GetYaxis()->SetRangeUser(-200, 6000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);
	q1->GetYaxis()->SetNdivisions(5,3,0);
	q1->Write();
 }

  void lifetimeru(TH1D *q1){
	q1->SetStats(0);
	q1->SetTitle("");
	q1->Rebin(5);
	q1->GetXaxis()->SetTitleOffset(1);
	q1->SetXTitle("FATIMA - FRS WR #Deltat (#mus)");
	q1->SetYTitle("Counts/ 5 #mus");
	q1->SetLineWidth(3);
	q1->SetLineColor(kRed);
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->GetXaxis()->SetTitleOffset(0.9);
	q1->GetYaxis()->SetTitleOffset(0.9);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);
	q1->Write();
 }


  void gamma_germ(TH1D *q1){
	q1->SetStats(0);
	q1->SetTitle("");
	q1->SetXTitle("Energy (keV)");
	q1->SetYTitle("Counts/ 1 keV");
	q1->SetLineWidth(2);
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->GetXaxis()->SetTitleOffset(0.9);
	q1->GetYaxis()->SetTitleOffset(0.9);
	q1->GetXaxis()->SetRangeUser(0, 2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);
	q1->Write();
 }

   void pidsproj_3in1(TH1D *q1){

	q1->SetXTitle("A/Q");
	q1->SetYTitle("Counts");
	q1->GetXaxis()->SetRangeUser(2.115, 2.25);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetXaxis()->SetLabelSize(0.15);
	q1->GetYaxis()->SetLabelSize(0.15);
	q1->GetXaxis()->SetTitleSize(0.15);
	q1->GetYaxis()->SetTitleSize(0.15);
	q1->GetXaxis()->SetTitleOffset(0.8);
	q1->GetYaxis()->SetTitleOffset(0.35);
	q1->GetYaxis()->SetNdivisions(5,3,0);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->Write();
 }

    void Edtpd96(TH2D *q1){

    q1->SetMinimum(q1->GetMinimum(2)); // black magic 
	q1->SetXTitle("FATIMA - SC41 TDC #Deltat (ns)");
	q1->SetYTitle("Energy (keV)");
	q1->RebinX(100);
	q1->RebinY(5);
	q1->GetXaxis()->SetRangeUser(-100, 800);
	q1->GetYaxis()->SetRangeUser(0,2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetYaxis()->SetTitleOffset(0.9);
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->GetYaxis()->Draw();    
	q1->Write();
 }

   void Edtpd94(TH2D *q1){

    //q1->SetMinimum(q1->GetMinimum(2)); // black magic 
	q1->SetXTitle("FATIMA - SC41 TDC #Deltat (ns)");
	q1->SetYTitle("Energy (keV)");
	q1->RebinX(100);
	q1->RebinY(5);
	q1->GetXaxis()->SetRangeUser(-100, 800);
	q1->GetYaxis()->SetRangeUser(0,2000);
	q1->GetXaxis()->SetRangeUser(-100, 800);
	q1->GetYaxis()->SetRangeUser(0,2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetYaxis()->SetTitleOffset(0.9);
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->GetYaxis()->Draw();    
	q1->Write();
}


   void Edtru94(TH2D *q1){

    q1->SetMinimum(q1->GetMinimum(20)); // black magic 
	q1->SetXTitle("FATIMA - FRS WR #Deltat (#mus)");
	q1->SetYTitle("Energy (keV)");
	q1->RebinX(2);
	q1->RebinY(5);
	q1->GetXaxis()->SetRangeUser(0, 1000);
	q1->GetYaxis()->SetRangeUser(0,2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetYaxis()->SetTitleOffset(0.9);
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->GetYaxis()->Draw();    
	q1->Write();
 }


   void Edtgerm(TH2D *q1){

	q1->SetXTitle("GTC - SC41 TDC dt (ns)");
	q1->SetYTitle("Energy (keV)");
	q1->RebinX(10);
	q1->GetXaxis()->SetRangeUser(0,7000);
	q1->GetYaxis()->SetRangeUser(1,2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetYaxis()->SetTitleOffset(1);
	q1->GetYaxis()->Draw();    
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->Write();
 }

   void Stackedlabr3_energy(TH1D *q1){


	q1->RebinX(5);
	q1->GetXaxis()->SetRangeUser(0,2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);  
	q1->GetYaxis()->SetTitleOffset(1);
	q1->GetYaxis()->Draw();    
	q1->GetXaxis()->SetLabelSize(0.05);
	q1->GetYaxis()->SetLabelSize(0.05);
	q1->GetXaxis()->SetTitleSize(0.05);
	q1->GetYaxis()->SetTitleSize(0.05);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->Write();
 }

    void Stackedlabr3_energyru(TH1D *q1){


	q1->RebinX(5);
	q1->SetXTitle("Energy (keV)");
	q1->SetYTitle("Counts/ 5 keV");
	q1->GetXaxis()->SetRangeUser(0,2000);
	q1->GetXaxis()->CenterTitle(true);
	q1->GetYaxis()->CenterTitle(true);
	q1->SetLineWidth(3);
	q1->GetYaxis()->SetNdivisions(4, 1, 0, kTRUE);
	q1->GetYaxis()->SetTitleOffset(1);
	q1->GetYaxisaxis()->SetTitleOffset(0.85);
	q1->GetYaxis()->Draw();    
	q1->GetXaxis()->SetLabelSize(0.15);
	q1->GetYaxis()->SetLabelSize(0.15);
	q1->GetXaxis()->SetTitleSize(0.15);
	q1->GetYaxis()->SetTitleSize(0.15);
	q1->SetStats(0);
	q1->SetTitle("");
	q1->Write();
 }