// ROOT macro file for plotting example B4 histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  // Draw histos filled by Geant4 simulation 
  //   
  // Open file filled by Geant4 simulation 
  TFile f("SiDetector.root");
  //TFile f("SiDetector.root");
  //Start making histos
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 500);
  c1->Divide(2);
  
  c1->cd(1);// Draw Eabs histogram in the pad 1
  TH1D* hist1 = (TH1D*)f.Get("StepEabs");
  hist1->SetTitle("Energy Deposited Per Antiproton in Active Region (MeV)");
  hist1->GetXaxis()->SetTitle("Depth (mm)");
  //normalizing to number of primaries
  Double_t norm = 1000000;
  hist1->Scale(1/norm);
  //hist1->GetYaxis()->SetTitle("Energy Deposited (MeV)");
  hist1->Draw("HIST");
  
  c1->cd(2);
  TH1* h_cumulative = hist1->GetCumulative(true);
  h_cumulative->SetTitle("Integral of Edep Per Antiproton in Active Region (MeV)");
  h_cumulative->GetXaxis()->SetTitle("Depth (mm)");
  //h_cumulative->GetYaxis()->SetTitle("Cumulative Energy Deposited (MeV)");  
  h_cumulative->Draw("histC");
  cout << "Integral of Edep per Event in Active Region: " << hist1->Integral() << endl;
  
  //make a new Canvas 
  TCanvas* c2 = new TCanvas("c2", "", 20, 20, 1000, 500);
  c2->Divide(2);    
  c2->cd(1);
  TH1D* hist2 = (TH1D*)f.Get("StepEabsWindow");
  hist2->Scale(1/norm);
  hist2->SetTitle("Energy Deposited per Antiproton in Inactive Window (MeV)");
  hist2->GetXaxis()->SetTitle("Depth (nm)");
  //hist2->GetYaxis()->SetTitle("Energy Deposited (MeV)");
  hist2->Draw("HIST");
  c2->cd(2);
  TH1* h_cumulative2 = hist2->GetCumulative(true);
  h_cumulative2->SetTitle("Integral of Edep in Inactive Window (MeV)");
  h_cumulative2->GetXaxis()->SetTitle("Depth (nm)");
  //h_cumulative2->GetYaxis()->SetTitle("Cumulative Energy Deposited (MeV)");
  h_cumulative2->Draw("histC");
  cout << "integral of edep in inactive window: " << hist2->Integral() << endl;
  
  //another one  
  TCanvas* c3 = new TCanvas("c3", "", 20, 20, 1000, 500);
  c3->Divide(2);  
  c3->cd(1);
  TH1D* hist3 = (TH1D*)f.Get("EventEabs");
  hist3->SetTitle("Edep Distribution per Antiproton in Active Region");
  hist3->Scale(1/norm);
  hist3->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hist3->GetYaxis()->SetTitle("# of Events");
  double totDep;
  for (int i = 1; i <= hist3->GetNbinsX();i++) {
	  totDep += (100./hist3->GetNbinsX())*i*hist3->GetBinContent(i);
  }
  double numDetEvents;
  for (int i = 1; i <= hist3->GetNbinsX();i++) {
	  numDetEvents += hist3->GetBinContent(i); //just add up all the tallies
  }
  cout << "total edep without threshold: " << totDep << endl;
  cout << "% events detected without threshold" << numDetEvents << endl;
  
  hist3->Draw("HIST");
  c3->cd(2);
  TH1D* hist4 = (TH1D*)f.Get("EventEabsWindow");
  hist4->Scale(1/norm);
  hist4->SetTitle("Edep Distribution per Antiproton in Inactive Window");
  hist4->GetXaxis()->SetTitle("Energy Deposited (keV)");
  //hist3->GetYaxis()->SetTitle("# of Events");
  hist4->Draw("HIST");
  //and another  
  
  TCanvas* c4 = new TCanvas("c4", "", 20 ,20 , 1000, 500);
  c4->Divide(2);  
  
  c4->cd(1);
  TH1D* hist5 = (TH1D*)f.Get("EabsProcess");
  hist5->Scale(1/norm);
  hist5->SetTitle("Edep by Physics Process per Antiproton (MeV)");
  hist5->GetXaxis()->SetTitle("Process index #");  
  hist5->Draw("HIST");
  cout << "Integral of edep by process: " << hist5->Integral() << endl;
  
  c4->cd(2);
  //Use hist5 (made from Geant4) to show only the top physics processes. 
  //The below works for FTFP_BERT and prob all others except LBE
  
  TH1D* testHist = new TH1D("h","Edep by Physics Process per Antiproton (MeV); ",8,0,8);
  testHist->SetBinContent(1,hist5->GetBinContent(4));
  testHist->GetXaxis()->SetBinLabel(1,"Rayl");
  testHist->SetBinContent(2,hist5->GetBinContent(5));
  testHist->GetXaxis()->SetBinLabel(2,"Transportation");
  testHist->SetBinContent(3,hist5->GetBinContent(15));
  testHist->GetXaxis()->SetBinLabel(3,"hBertiniCaptureAtRest");
  testHist->SetBinContent(4,hist5->GetBinContent(16));
  testHist->GetXaxis()->SetBinLabel(4,"hFritiofCaptureAtRest");
  testHist->SetBinContent(5,hist5->GetBinContent(17));
  testHist->GetXaxis()->SetBinLabel(5,"hIoni");
  testHist->SetBinContent(6,hist5->GetBinContent(18));
  testHist->GetXaxis()->SetBinLabel(6,"hadElastic");  
  testHist->SetBinContent(7,hist5->GetBinContent(19));
  testHist->GetXaxis()->SetBinLabel(7,"ionElastic");  
  testHist->SetBinContent(8,hist5->GetBinContent(20));
  testHist->GetXaxis()->SetBinLabel(8,"ionIoni");  
  testHist->Draw("HIST");
  
  
  //FOR LBE:
  /*
  TH1D* testHist = new TH1D("h","Edep by Physics Process per Antiproton (MeV); ",6,0,6);
  testHist->SetBinContent(1,hist5->GetBinContent(5));
  testHist->GetXaxis()->SetBinLabel(1,"Scintillation");
  testHist->SetBinContent(2,hist5->GetBinContent(10));
  testHist->GetXaxis()->SetBinLabel(2,"eIoni");
  testHist->SetBinContent(3,hist5->GetBinContent(11));
  testHist->GetXaxis()->SetBinLabel(3,"hIoni");
  testHist->SetBinContent(4,hist5->GetBinContent(14));
  testHist->GetXaxis()->SetBinLabel(4,"ionIoni");
  testHist->SetBinContent(5,hist5->GetBinContent(15));
  testHist->GetXaxis()->SetBinLabel(5,"msc");
  testHist->SetBinContent(6,hist5->GetBinContent(16));
  testHist->GetXaxis()->SetBinLabel(6,"muIoni");
  testHist->Draw("HIST");
  */
  
  //PION INITIAL ENERGY
  TCanvas* c5 = new TCanvas("c5", "", 20 , 20 , 1000, 500);
  c5->Divide(2); 
  c5->cd(1);
  TH1D* hist6 = (TH1D*)f.Get("PionEnergy");
  hist6->Draw("HIST");  
  //cout << "Total Charged Pion Count: " << hist6->Integral() << endl; //THIS INTEGRAL DOESNT GIVE THE TOTAL ENERGY, IT GIVES THE TOTAL COUNT!
  //PION COUNT  
  c5->cd(2);
  TH1D* hist7 = (TH1D*)f.Get("PionEnergy2");
  hist7->Draw("HIST");  
  //cout << "Sum of Initial Pion Energies (MeV): " << hist7->Integral() << endl;
  cout << "Avg Initial Charged Pion Energy (MeV): " << (hist7->Integral())/(hist6->Integral()) << endl;
  cout << "Avg Number of Charged Pions Produced Per Primary: " << (hist6->Integral())/norm << endl;

  //GET THE MEDIAN INITIAL PION ENERGY
  Double_t median;
  Double_t q = 0.5;
  hist6->ComputeIntegral();
  hist6->GetQuantiles(1,&median,&q);
  cout << "Median initial pion energy: " << median << endl;
 
  //PION EDEP
  TCanvas* c6 = new TCanvas("c6", "", 20, 20, 1000, 500);
  c6->Divide(2);
  c6->cd(1);
  TH1D* hist8 = (TH1D*)f.Get("PionStepEabs");
  hist8->Scale(1/norm);
  hist8->SetTitle("Pion Edep Per Antiproton in Window (MeV)");
  hist8->Draw("HIST");
  c6->cd(2);
  TH1* h_cumulativePion = hist8->GetCumulative(true);
  h_cumulativePion->SetTitle("Integral of Pion Edep Per Antiproton in Window (MeV)");
  h_cumulativePion->GetXaxis()->SetTitle("Depth (mm)");
  h_cumulativePion->Draw();
  cout << "Total energy deposited by pions in active region: " << hist8->Integral() << endl;    
  
  TCanvas* c7 = new TCanvas("c7", "", 20, 20, 500, 500);
  c7->cd(1);  
  TH1D* hist9 = (TH1D*)f.Get("SiStepEabs");
  hist9->Scale(1/norm);
  hist9->SetTitle("Si28 Edep Per Antiproton in Active Region (MeV)");
  hist9->Draw("HIST");
  cout << "Total energy deposited by Si28 in active region: " << hist9->Integral() << endl;    
  //KAON EDEP
  TCanvas* c8 = new TCanvas("c8", "", 20, 20, 500, 500);
  c8->cd(1);
  TH1D* hist10 = (TH1D*)f.Get("KaonStepEabs");
  hist10->Scale(1/norm);
  hist10->SetTitle("Kaon Edep Per Antiproton in Active Region (MeV)");
  hist10->Draw("HIST");
  cout << "Total energy deposited by kaons in active region: " << hist10->Integral() << endl;    
  
  //ALL PARTICLES
  TCanvas* c9 = new TCanvas("c9", "", 20, 20, 1500, 500);
  c9->cd(1);
  TH1D* hist11 = (TH1D*)f.Get("EabsParticle");
  hist11->Scale(1/norm);
  //hist11->Scale(1/norm);
  hist11->SetTitle("Energy Deposition by Particle Type");
  hist11->GetXaxis()->SetTitle("Particle Index #");
  hist11->Draw();
  cout << "total edep by all particles: " << hist11->Integral() << endl; //This does in fact give back the total !!
  
  //TOTAL EDIST PLOT WITH CUTOFF
  TCanvas* c10 = new TCanvas("c10", "", 20, 20, 500, 500);
  c10->cd(1);
  TH1D* hist12 = (TH1D*)f.Get("EventEabsThresh");  
  hist12->Scale(1/norm);
  hist12->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  hist12->Draw("HIST");
  double totDepThresh;
  for (int i = 1; i <= hist12->GetNbinsX();i++) {
	  totDepThresh += (100./hist12->GetNbinsX())*i*hist12->GetBinContent(i);
  }
  numDetEvents = 0;  
  for (int i = 1; i <= hist12->GetNbinsX();i++) {
	  numDetEvents += hist12->GetBinContent(i); //just add up all the tallies
  }
  cout << "total edep with threshold: " << totDepThresh << endl;
  cout << "% events detected with thresh: " << numDetEvents << endl;
  
  //PROTON INITIAL ENERGY DIST
  TCanvas* c11 = new TCanvas("c11", "", 20 , 20 , 500, 500);
  c11->cd(1);
  TH1D* hist13 = (TH1D*)f.Get("ProtonEnergy");
  hist13->Scale(1/norm);
  hist13->Draw("HIST");  
  cout << "Protons produced per antiproton: " << hist13->Integral() << endl; //THIS INTEGRAL DOESNT GIVE THE TOTAL ENERGY, IT GIVES THE TOTAL COUNT!
  double protDep = 0;
  for (int i = 1; i <= hist13->GetNbinsX();i++) {
	  protDep += (100./hist13->GetNbinsX())*i*hist13->GetBinContent(i);
  }
  cout << "Total Proton edep: " << protDep << endl;
  
  //DEUTERON INITIAL ENERGY DIST
  TCanvas* c12 = new TCanvas("c12", "", 20 , 20 , 500, 500);
  c12->cd(1);
  TH1D* hist14 = (TH1D*)f.Get("DeuteronEnergy");
  hist14->Scale(1/norm);
  hist14->Draw("HIST");  
  cout << "Deuterons produced per antiproton: " << hist14->Integral() << endl; //THIS INTEGRAL DOESNT GIVE THE TOTAL ENERGY, IT GIVES THE TOTAL COUNT!
  double deutDep = 0;
  for (int i = 1; i <= hist14->GetNbinsX();i++) {
	  deutDep += (100./hist14->GetNbinsX())*i*hist14->GetBinContent(i);
  }
  cout << "Total Deuteron edep: " << deutDep << endl;
  
  //TRITON INITIAL ENERGY DIST
  TCanvas* c13 = new TCanvas("c13", "", 20 , 20 , 500, 500);
  c13->cd(1);
  TH1D* hist15 = (TH1D*)f.Get("TritonEnergy");
  hist15->Scale(1/norm);
  hist15->Draw("HIST");  
  cout << "Tritons produced per antiproton: " << hist15->Integral() << endl; //THIS INTEGRAL DOESNT GIVE THE TOTAL ENERGY, IT GIVES THE TOTAL COUNT!
  double tritDep = 0;
  for (int i = 1; i <= hist15->GetNbinsX();i++) {
	  tritDep += (100./hist15->GetNbinsX())*i*hist15->GetBinContent(i);
  }
  cout << "Total Triton edep: " << tritDep << endl;
  
  //ALPHA INITIAL ENERGY DIST
  TCanvas* c14 = new TCanvas("c14", "", 20 , 20 , 500, 500);
  c14->cd(1);
  TH1D* hist16 = (TH1D*)f.Get("AlphaEnergy");
  hist16->Scale(1/norm);
  hist16->Draw("HIST");  
  cout << "Alphas produced per antiproton: " << hist16->Integral() << endl; //THIS INTEGRAL DOESNT GIVE THE TOTAL ENERGY, IT GIVES THE TOTAL COUNT!
  double alphDep = 0;
  for (int i = 1; i <= hist16->GetNbinsX();i++) {
	  alphDep += (100./hist16->GetNbinsX())*i*hist16->GetBinContent(i);
  }
  cout << "Total Alpha edep: " << alphDep << endl;
  
  //cout << "Detector efficiency given threshold: " << totDepThresh/totDep << endl;
  
  //KE REMAINING IN PIONS UPON ENTERING ACTIVE RGN
  //TCanvas* c15 = new TCanvas("c15", "", 20, 20, 500, 500);
  //c15->cd(1);
  TH1D* hist17 = (TH1D*)f.Get("PionCrossingEnergy");
  cout << "sum of pion crossing energies: " <<  hist17->Integral() << endl;
  
  TCanvas* c15 = new TCanvas("c15", "", 20, 20, 500, 500);
  c15->cd(1);
  TH1D* hist18 = (TH1D*)f.Get("PionProcesses");
  hist18->Scale(1/norm);
  hist18->Draw("HIST");
  
  
 //MAKE 2D (3D) histogram plot
 
 TCanvas* c16 = new TCanvas("c16", "", 20, 20, 500, 500);
 c16->cd(1);
 TH2D* testing2D = (TH2D*)f.Get("3DPionDist");
 testing2D->GetXaxis()->SetTitle("Depth (mm)");
 testing2D->GetYaxis()->SetTitle("Radius (mm)");
 c16->SetLogz(); 
 testing2D->Draw("COLZ");
 
 TCanvas* c17 = new TCanvas("c17", "", 20, 20, 500, 500);
 c17->cd(1);
 TH1D* hist19 = (TH1D*)f.Get("PionInitialAngle");
 hist19->Draw("HIST");
 
}  
