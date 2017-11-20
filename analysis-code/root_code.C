void root_code(){
  TCanvas *c1 = new TCanvas("c1","c1",800,500);
  //gStyle->SetOptStat(kFALSE);
  //Load the files
  TFile *_file1 = TFile::Open("../plots/tau/gluon_1e5_13tev.root");
  TFile *_file2 = TFile::Open("../plots/tau/quark_1e5_13tev.root");
  //Get the Histograms
  TH1F *h1 = (TH1F*)_file1->Get("hist");
  TH1F *h2 = (TH1F*)_file2->Get("hist");
  //Normalising the Histograms
  Float_t norm = 1.0;
  h1->Scale(norm/h1->Integral());
  h2->Scale(norm/h2->Integral());
//Drawing the histograms
Float_t max = 0;
if(h1->GetMaximum() > max ) max = h1->GetMaximum();
if(h2->GetMaximum() > max ) max = h2->GetMaximum();
max += 0.1*max;
h1->SetMaximum(max);
h2->SetMaximum(max);


h2->SetLineColor(kRed);
h1->Draw("hist");
h2->Draw("SAME:hist"); 
c1->Print("plot.png");
exit(0);
}

