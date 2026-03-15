int line_width[12] = {2,2,2,2,2,2,2,2,2,2,2,2};
int line_style[12] = {1,1,1,1,1,1,1,1,1,1,1,1};                                                                              
int line_color[9] = {kBlue,kRed,kGreen+2,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2};
int line_color1[9]= {kBlue,kGreen+2,kGray+1,kRed+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2};
int line_color2[9] = {kGreen+2,kBlue,kViolet,kGray,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta};
vector<int> col={kGreen+2,kBlue,kViolet,kGray,kViolet+2,kGreen-2,kYellow+1,kGray+2,kMagenta,kBlue+2,kMagenta,kCyan};
vector<int> Style={3008,1001,3008,1001};
void decorate(TH1F*,int);
void decorate(TH1F* hist,int i){
  hist->SetLineWidth(3);                                                                                                                        
}
void setLastBinAsOverFlow(TH1F*);
TH1F* setMyRange(TH1F*,double,double);

TH1F* setMyRange(TH1F *h1,double xLow,double xHigh){
  //call it after setting last bin as overflow                                                                                                                               
  double err=0;
  if(xHigh > 13000) return h1;
  if(xLow < -13000) return h1;                                                                                                                     
  int nMax=h1->FindBin(xHigh);
  h1->SetBinContent(nMax,h1->IntegralAndError(nMax,h1->GetNbinsX(),err));
  h1->SetBinError(nMax,err);                                                                                                                 
  for(int i=nMax+1;i<=h1->GetNbinsX()+1;i++){
    h1->SetBinContent(i,0);
    h1->SetBinError(i,0);
                                                                                                                         
  }
  h1->GetXaxis()->SetRangeUser(xLow,xHigh);
  cout<<xLow<<"\t"<<xHigh<<"\t"<<"set range"<<endl;
   return h1;
}

TH1F* DrawOverflow(TH1F*);
TH1F* DrawOverflow(TH1F* h,int xmin, int xrange){

   UInt_t nx    = h->GetNbinsX()+1;
   Double_t *xbins= new Double_t[nx+1];
   for (UInt_t i=0;i<nx;i++)
     xbins[i]=h->GetBinLowEdge(i+1);
   xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
   char *tempName= new char[strlen(h->GetName())+10];
   sprintf(tempName,"%swtOverFlow",h->GetName());
   h->GetXaxis()->SetLimits(xmin,xrange);
   // Book a temporary histogram having ab extra bin for overflows
   TH1F *htmp = new TH1F(tempName, h->GetTitle(), nx, xbins);
   htmp->GetXaxis()->SetRange(xmin,xrange);
   // Reset the axis labels
   htmp->SetXTitle(h->GetXaxis()->GetTitle());
   htmp->SetYTitle(h->GetYaxis()->GetTitle());
   // Fill the new hitogram including the extra bin for overflows
   for (UInt_t i=1; i<=nx; i++)
     htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
   // Fill the underflows
   htmp->Fill(h->GetBinLowEdge(1)-1, h->GetBinContent(0));
   
   htmp->SetEntries(h->GetEntries());
   
   return htmp;
}
void setLastBinAsOverFlow(TH1F* h_hist){
  double lastBinCt =h_hist->GetBinContent(h_hist->GetNbinsX()),overflCt =h_hist->GetBinContent(h_hist->GetNbinsX()+1);
  double lastBinErr=h_hist->GetBinError(h_hist->GetNbinsX()),  overflErr=h_hist->GetBinError(h_hist->GetNbinsX()+1);

  if(lastBinCt!=0 && overflCt!=0)
    lastBinErr = (lastBinCt+overflCt)* (sqrt( ((lastBinErr/lastBinCt)*(lastBinErr/lastBinCt)) + ((overflErr/overflCt)*(overflErr/overflCt)) ) );

  else if(lastBinCt==0 && overflCt!=0)
    lastBinErr = overflErr;
  else if(lastBinCt!=0 && overflCt==0)
    lastBinErr = lastBinErr;
  else lastBinErr=0;

  lastBinCt = lastBinCt+overflCt;
  h_hist->SetBinContent(h_hist->GetNbinsX(),lastBinCt);
  h_hist->SetBinError(h_hist->GetNbinsX(),lastBinErr);
  cout<<lastBinCt<<"\t"<<"Last bin values"<<endl;

}
void generate_1Dplot(vector<TH1F*> hist,char const *tag_name="",char const *xlabel="",char const *ylabel="",  int rebin=-1,double ymin=0,double ymax=0,double xmin=-1,double xmax=-1,char const *leg_head="",bool normalize=false, bool log_flag=false, bool DoRebin=false, bool save_canvas=true, char const *title="", vector<string> legend_texts={"nil"},bool stat=false)
{  
     TCanvas *canvas_n1 = new TCanvas(tag_name, tag_name,950,850);
       canvas_n1->Range(-60.25,-0.625,562.25,0.625);
       canvas_n1->SetFillColor(0);
       canvas_n1->SetBorderMode(0);
       canvas_n1->SetBorderSize(1);
       canvas_n1->SetLeftMargin(0.124);
       canvas_n1->SetRightMargin(0.035);
       canvas_n1->SetTopMargin(0.04);
       canvas_n1->SetBottomMargin(0.1);
       //THStack *hs_var=new THStack("var_Stack","");
       gStyle->SetOptStat(1111111);
       //   gStyle->SetOptStat(0);
       //double pvt_x_min = 0.6;
  double pvt_x_min = 0.75;
  double pvt_x_max = 0.99;
  double pvt_y_min = 0.9;
  //double pvt_dely = 0.18;
  double pvt_dely = 0.15;
  //gStyle->SetOptStat(0);
  /*if(stat){gStyle->SetOptStat(1);
	   gStyle->SetStatX(0.95);
  gROOT->ForceStyle();
	}
  else {gStyle->SetOptStat(0);
  gROOT->ForceStyle();
	}
  gPad->Modified();
  gPad->Update();*/
  //gStyle->SetOptFit(0);
  vector<TString> legName;
  //TLegend *legend = new TLegend(0.65,0.95,0.99,0.75);
  std::string leg_head_str = leg_head;
  double x = 0.15;
  double y = 0.90;
  TLegend *legend;
  //legend = new TLegend(0.60,0.88,0.98,0.72);  
  legend = new TLegend(0.21,0.82,0.65,0.95);  
  legend->SetTextSize(0.05);
  legend->SetLineColor(kWhite);
  legend->SetNColumns(4);
  char* lhead = new char[100];

  sprintf(lhead,"#bf{%s} ",title);
  legend->SetHeader(lhead);
  legend->SetLineColor(kWhite);

  TLegendEntry* leg_entry[11];
  float x_label_size = 0.04;
  double xrange = xmax;
  
  vector<TH1F*> hist_list_temp;
  cout<<" hist.size() = "<<hist.size()<<endl;
  
  for(int i =0;i<(int)hist.size(); i ++) {
    
    if(normalize) {
      
      hist.at(i)->GetYaxis()->SetTitle("Normalized");
    }
    else {
      hist.at(i)->GetYaxis()->SetTitle("Entries");
      
    }
    
    hist.at(i)->SetLineWidth(line_width[i]);
    hist.at(i)->SetLineStyle(line_style[i]);
    hist.at(i)->SetLineColor(line_color[i]);
    hist.at(i)->SetTitle(" ");
    hist.at(i)->GetXaxis()->SetTitleSize(0.05);
    hist.at(i)->GetXaxis()->SetLabelSize(0.05);
    hist.at(i)->GetYaxis()->SetTitleSize(0.05);
    hist.at(i)->GetYaxis()->SetLabelSize(0.05);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.11);
    hist.at(i)->GetYaxis()->SetLabelSize(x_label_size);
    hist.at(i)->SetLineColor(line_color[i]);
    hist.at(i)->SetTitle("");
    //
    hist.at(i)->GetXaxis()->SetTitleSize(0.04);
    hist.at(i)->GetXaxis()->SetTitle(xlabel);
    hist.at(i)->GetYaxis()->SetTitleSize(0.05);
    hist.at(i)->GetYaxis()->SetLabelSize(0.040);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.2);
     decorate(hist.at(i),i);
    hist.at(i)->SetMarkerSize(0.8);
    hist.at(i)->SetMarkerStyle(20);
    hist.at(i)->SetMarkerColor(line_color[i]);
    hist.at(i)->GetYaxis()->SetTitleOffset(1.3);
    hist.at(i)->GetXaxis()->SetLabelSize(0.04);

    legName.push_back(hist.at(i)->GetName());
    leg_entry[i] = legend->AddEntry(hist.at(i),legend_texts[i].c_str(),"l");
    leg_entry[i]->SetTextColor(hist.at(i)->GetLineColor());
    
    if(hist.at(i)->GetMaximum() > ymax) ymax = hist.at(i)->GetMaximum();
    if(hist.at(i)->GetMinimum() < ymin) ymin = hist.at(i)->GetMinimum();
     TPaveStats *ps = (TPaveStats*)hist.at(i)->GetListOfFunctions()->FindObject("stats");

    

  }
  if(ymin == 0.0) ymin = 1e-3;
  if(ymin<0.0) ymin = 1e-4;
  //  if(ymax<=10) ymax=10;
  cout << "XMIN" <<"\t"<<xmin <<"\t" << "XMAX"<<"\t"<<xmax<<endl;
  for(int i = 0;i<(int)hist.size(); i++) {
    if(!normalize) {
    if (log_flag){ hist.at(i)->GetYaxis()->SetRangeUser(0.1,10*ymax);//hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);
}
    else {
    hist.at(i)->GetYaxis()->SetRangeUser(0.0001,1.2*ymax);//hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);
	}    
}
    
    else
      {  hist.at(i)->GetYaxis()->SetRangeUser(0.0001,2.0); //hist.at(i)->GetXaxis()->SetRangeUser(xmin,xmax);

      }
    cout<<"i"<<i<<endl;
    if(i==0) hist.at(i)->Draw("hist ");
    else hist.at(i)->Draw("hist sames");
  }
  legend->Draw();
  if(log_flag) {
      gPad->SetLogy();
    }
  if(!stat){gStyle->SetOptStat(0);}
  else {gStyle->SetOptStat(1); gStyle->SetStatX(0.95);}
gPad->Modified();
gPad->Update(); 
  TLatex* textOnTop = new TLatex();
  //new
    textOnTop->SetTextSize(0.054);
  //textOnTop->DrawLatexNDC(0.146,0.925,"CMS #it{#bf{Simulation Preliminary}}");
  char* en_lat = new char[500];
  textOnTop->SetTextSize(0.054);
  //textOnTop->DrawLatexNDC(0.72,0.925,en_lat);


  //gPad->Modified();
                                                                                       
    
 char* canvas_name = new char[1000];
  //c->Print(canvas_name);
  
  if(save_canvas) {
    sprintf(canvas_name,"%s.png",tag_name);
     canvas_n1->SaveAs(canvas_name);   
     sprintf(canvas_name,"%s.pdf",tag_name);
    canvas_n1->SaveAs(canvas_name);  
  } 
}


struct MixedData {
    std::string str1;
    std::string str2;
    int intData;
    double double1;
    double double2;
    double double3;
    double double4;
    std::string str3;
};

const int nfiles=100;                                                                                                                                                             
TFile *f[nfiles];

void generate1Dplot()
{
  char* hname = new char[200];
  
  char* hist_name = new char[200];
  
  char* title= new char[2000];
 
  char *leg_head = new char[200];
 
  int n=0;
  int n_files=1;
 
    f[0] = new TFile("EB_plot.root");
    //f[0] = new TFile("plot.root");
    //f[0] = new TFile("testplot.root");
    
    //vector<string> filetag=  {"M_a = 1GeV"};
    vector<string> filetag=  {"Sample size: 4.3M (EB)"};
    //vector<string> filetag=  {"Sample size: 5M (EE)"};
MixedData varName[] = { // { Name of the plot , xLabel , rebin , ymin , ymax , xmin , xmax , Legend label }
{"M_gen","Mass (GeV)",10,0,20,0,2.1,"mass of A"},  
{"A_gen_pT","pT (GeV)",10,1,20,0,120,"Gen pT of A"},
{"A_gen_eta","#eta",10,0,20,-3,3,"Gen #eta of A"},  
{"A_gen_phi","#phi",10,0,20,-4,4,"Gen #phi of A"},
{"A_gen_energy","Energy (GeV)",10,0,20,0,1000,"Gen energy of A"},
{"Lorentz boost of A","Lorentz boost (#gamma)",10,0,200,1,7000,"Lorentz boost of A"},
{"No. of gen photons","No. of photons",10,0,200,0,4,"No. of gen photons"},
{"Photon1 gen eta","#eta",10,0,20,-3,3,"Pho1 gen #eta"},
{"Photon1 gen phi","#phi",10,0,20,-4,4,"Pho1 gen #phi"},
{"Photon1 gen pT","pT (GeV)",10,0,20,0,150,"Pho1 gen pT"},
{"Photon1 gen E","Energy (GeV)", 10,0,20,0,1000,"Pho1 gen energy"},
{"Photon2 gen eta","#eta",10,0,200,-3,3,"Pho2 gen #eta"},
{"Photon2 gen phi","#phi",10,0,200,-4,4,"Pho2 gen #phi"},
{"Photon2 gen pT","pT (GeV)",10,0,20,0,150,"Pho2 gen pT"},
{"Photon2 gen E","energy (GeV)",10,0,200,0,1000,"Pho2 gen energy"},
{"E_sublead_by_E_lead","ratio",10,0,200,0,1.2,"E_sublead/E_lead"},
{"No. of reco photons","No. of photons",10,0,200,0,4,"No. of reco photons"},
{"Photon1 EE rechit eta","#eta",10,0,200,-3,3,"Pho1 EE rechit #eta"},
{"Pho1_hit_phi","#phi",10,0,200,-4,4,"Pho1 EE rechit #phi"},
{"Photon2 EE rechit eta","#eta",10,0,200,-4,4,"Pho2 EE rechit #eta"},
{"Pho2_hit_phi","#phi",10,0,200,-4,4,"Pho2 EE rechit #phi"},
{"Pho1_hit_X","ECAL X (in cm)",10,0,200,-160,160,"Pho1 EE rechit x"},
{"Pho1_hit_Y","ECAL Y (in cm)",10,0,200,-160,160,"Pho1 EE rechit y"},
{"Pho1_hit_Z","ECAL Z (in cm)",10,0,200,250,350,"Pho1 EE rechit z"},
{"Pho1_hit_E","Energy (GeV)",10,0,200,0,100,"Pho1 EE rechit energy"},
{"Pho2_hit_X","ECAL X (in cm)", 10,0,200,-160,160,"Pho2 EE rechit x"},
{"Pho2_hit_Y","ECAL Y (in cm)",10,0,200,-160,160,"Pho2 EE rechit y"},
{"Pho2_hit_Z","ECAL Z (in cm)",10,0,200,250,350,"Pho2 EE rechit z"},
{"Pho2_hit_E","Energy (GeV)",10,0,200,0,100,"Pho2 EE rechit energy"},

{"Pho1_ES_hit_eta","#eta",10,0,200,-3,3,"Pho1 ES rechit #eta"},
{"Pho1_ES_hit_phi","#phi",10,0,200,-4,4,"Pho1 ES rechit #phi"},
{"Pho2_ES_hit_eta","#eta",10,0,200,-3,3,"Pho2 ES rechit #eta"},
{"Pho2_ES_hit_phi","#phi",10,0,200,-4,4,"Pho2 ES rechit #phi"},
{"Pho1_ES_hit_X", "X (in cm)",10,0,200,-160,160,"Pho1 ES rechit X"},
{"Pho1_ES_hit_Y", "Y (in cm)",10,0,200,-160  , 160, "Pho1 ES rechit Y"},
{"Pho1_ES_hit_Z", "Z (in cm)",10,0,200,250,350,"Pho1 ES rechit Z"},
{"Pho1_ES_hit_E","Energy (GeV)",10,0,200,0,0.2,"Pho1 ES rechit energy"},
{"Pho2_ES_hit_X", "X (in cm)",10,0,200,-160,160,"Pho2 ES rechit X"},
{"Pho2_ES_hit_Y", "Y (in cm)",10,0,200,-160  , 160, "Pho2 ES rechit Y"},
{"Pho2_ES_hit_Z", "Z (in cm)",10,0,200,250,350,"Pho2 ES rechit Z"},
{"Pho2_ES_hit_E","Energy (GeV)",10,0,200,0,0.2,"Pho2 ES rechit energy"},
{"Pho_sig_iEiE_Ma_200_300","#sigmai_{i#eta i#eta}",10,0,200,0,0.1,"#sigmai_{i#eta i#eta}"},
{"Pho_sig_iPhiiPhi" ,"#sigma_{i#phi i#phi}",10,0,200,0,0.1,"#sigma_{i#phi i#phi}"},

{"Unc_RH_E_ma_100","Unclustered rechit energy (GeV)",10,0,200,-2,5,"0.08 < M_{a} < 0.12 GeV"},
{"Unc_RH_E_ma_200","Unclustered rechit energy (GeV)",10,0,200,-2,5,"0.18 < M_{a} < 0.22 GeV"},
{"Unc_RH_E_ma_400","Unclustered rechit energy (GeV)",10,0,200,-2,5,"0.38 < M_{a} < 0.42 GeV"},
{"Unc_RH_E_ma_800","Unclustered rechit energy (GeV)",10,0,200,-2,5,"0.78 < M_{a} < 0.82 GeV"},
{"Unc_RH_E_ma_1800","Unclustered rechit energy (GeV)",10,0,200,-2,5,"1.78 < M_{a} < 1.82 GeV"},
{"Clu_rec_E_ma_100","Clustered rechit energy (GeV)",10,0,200,-2,5,"0.08 < M_{a} < 0.12 GeV"},
{"Clu_rec_E_ma_200","Clustered rechit energy (GeV)",10,0,200,-2,5,"0.18 < M_{a} < 0.22 GeV"},
{"Clu_rec_E_ma_400","Clustered rechit energy (GeV)",10,0,200,-2,5,"0.38 < M_{a} < 0.42 GeV"},
{"Clu_rec_E_ma_800","Clustered rechit energy (GeV)",10,0,200,-2,5,"0.78 < M_{a} < 0.82 GeV"},
{"Clu_rec_E_ma_1800","Clustered rechit energy (GeV)",10,0,200,-2,5,"1.78 < M_{a} < 1.82 GeV"},
{"Clu_rec_E_ma_400","Clustered rechit energy (GeV)",2,0,200,0,0.3,"0.38 < M_{a} < 0.42 GeV"},
{"Clu_rec_E_ma_1800","Clustered rechit energy (GeV)",2,0,200,0,0.3,"1.78 < M_{a} < 1.82 GeV"},

{"Unc_rec_E_ma_400_500","Unclustered rechit energy (GeV)",10,0,200,-2,5,"0.4 < M_{a} < 0.5 GeV"},
{"Unc_rec_E_ma_1700_1800","Unclustered rechit energy (GeV)",10,0,200,-2,5,"1.7 < M_{a} < 1.8 GeV"},
{"Unc_rec_E_ma_400_500","Unclustered rechit energy (GeV)",2,0,200,-2,2,"0.4 < M_{a} < 0.5 GeV"},
{"Unc_rec_E_ma_1700_1800","Unclustered rechit energy (GeV)",2,0,200,-2,2,"1.7 < M_{a} < 1.8 GeV"},
{"Unc_RH_E_ma_400","Unclustered rechit energy (GeV)",2,0,200,-2,2,"0.38 < M_{a} < 0.42 GeV"},
{"Unc_RH_E_ma_1800","Unclustered rechit energy (GeV)",2,0,200,-2,2,"1.78 < M_{a} < 1.82 GeV"},
{"Unc_RH_E_ma_400","Unclustered rechit energy (GeV)",1,0,200,-0.2,0.2,"0.38 < M_{a} < 0.42 GeV"},
{"Unc_RH_E_ma_1800","Unclustered rechit energy (GeV)",1,0,200,-0.2,0.2,"1.78 < M_{a} < 1.82 GeV"},
{"Hit_noise_ma_100","Rechit Noise (GeV)",10,0,200,-2,5,"0.08 < M_{a} < 0.12 GeV"},
{"Hit_noise_ma_200","Rechit Noise (GeV)",10,0,200,-2,5,"0.18 < M_{a} < 0.22 GeV"},
{"Hit_noise_ma_400","Rechit Noise (GeV)",10,0,200,-2,5,"0.38 < M_{a} < 0.42 GeV"} ,
{"Hit_noise_ma_800","Rechit Noise (GeV)",10,0,200,-2,5,"0.78 < M_{a} < 0.82 GeV"} ,
{"Hit_noise_ma_1600","Rechit Noise (GeV)",10,0,200,-2,5,"1.58 < M_{a} < 1.62 GeV"} ,
{"Hit_noise_ma_1800","Rechit Noise (GeV)",10,0,200,-2,5,"1.78 < M_{a} < 1.82 GeV"} ,
{"Clu_Hit_noise_ma_100","Clustered Rechit Noise (GeV)",10,0,200,-2,5,"0.08 < M_{a} < 0.12 GeV"} ,
{"Clu_Hit_noise_ma_200","Clustered Rechit Noise (GeV)",10,0,200,-2,5,"0.18 < M_{a} < 0.22 GeV"} ,
{"Clu_Hit_noise_ma_400","Clustered Rechit Noise (GeV)",10,0,200,-2,5,"0.38 < M_{a} < 0.42 GeV"} ,
{"Clu_Hit_noise_ma_800","Clustered Rechit Noise (GeV)",10,0,200,-2,5,"0.78 < M_{a} < 0.82 GeV"} ,
{"Clu_Hit_noise_ma_1600","Clustered Rechit Noise (GeV)",10,0,200,-2,5,"1.58 < M_{a} < 1.62 GeV"} ,
{"Clu_Hit_noise_ma_1800","Clustered Rechit Noise (GeV)",10,0,200,-2,5,"1.78 < M_{a} < 1.82 GeV"} ,
{"Unc_Hit_noise_ma_100","Unclustered Rechit Noise (GeV)",10,0,200,-2,5,"0.08 < M_{a} < 0.12 GeV"} ,
{"Unc_Hit_noise_ma_200","Unclustered Rechit Noise (GeV)",10,0,200,-2,5,"0.18 < M_{a} < 0.22 GeV"} ,
{"Unc_Hit_noise_ma_400","Unclustered Rechit Noise (GeV)",10,0,200,-2,5,"0.38 < M_{a} < 0.42 GeV"} ,
{"Unc_Hit_noise_ma_800","Unclustered Rechit Noise (GeV)",10,0,200,-2,5,"0.78 < M_{a} < 0.82 GeV"} ,
{"Unc_Hit_noise_ma_1600","Unclustered Rechit Noise (GeV)",10,0,200,-2,5,"1.58 < M_{a} < 1.62 GeV"} ,
{"Unc_Hit_noise_ma_1800","Unclustered Rechit Noise (GeV)",10,0,200,-2,5,"1.78 < M_{a} < 1.82 GeV"} ,
//========================= new skim plots ========================================
/* 
{"N_supcl_hits0_100","No. of supercluster rechits",10,0,200,0,300,"0 < M_{a} < 0.1 GeV"},
{"N_supcl_hits100_200","No. of supercluster rechits",10,0,200,0,300,"0.1 < M_{a} < 0.2 GeV"},
{"N_supcl_hits200_300","No. of supercluster rechits",10,0,200,0,300,"0.2 < M_{a} < 0.3 GeV"},
{"N_supcl_hits300_400","No. of supercluster rechits",10,0,200,0,300,"0.3 < M_{a} < 0.4 GeV"},
{"N_supcl_hits400_500","No. of supercluster rechits",10,0,200,0,300,"0.4 < M_{a} < 0.5 GeV"},
{"N_supcl_hits500_600","No. of supercluster rechits",10,0,200,0,300,"0.5 < M_{a} < 0.6 GeV"},
{"N_supcl_hits600_700","No. of supercluster rechits",10,0,200,0,300,"0.6 < M_{a} < 0.7 GeV"},
{"N_supcl_hits700_800","No. of supercluster rechits",10,0,200,0,300,"0.7 < M_{a} < 0.8 GeV"},
{"N_supcl_hits800_900","No. of supercluster rechits",10,0,200,0,300,"0.8 < M_{a} < 0.9 GeV"},
{"N_supcl_hits900_1000","No. of supercluster rechits",10,0,200,0,300,"0.9 < M_{a} < 1.0 GeV"},
{"N_supcl_hits1000_1100","No. of supercluster rechits",10,0,200,0,300,"1.0 < M_{a} < 1.1 GeV"},
{"N_supcl_hits1100_1200","No. of supercluster rechits",10,0,200,0,300,"1.1 < M_{a} < 1.2 GeV"},
{"N_supcl_hits1200_1300","No. of supercluster rechits",10,0,200,0,300,"1.2 < M_{a} < 1.3 GeV"},
{"N_supcl_hits1300_1400","No. of supercluster rechits",10,0,200,0,300,"1.3 < M_{a} < 1.4 GeV"},
{"N_supcl_hits1400_1500","No. of supercluster rechits",10,0,200,0,300,"1.4 < M_{a} < 1.5GeV"},
{"N_supcl_hits1500_1600","No. of supercluster rechits",10,0,200,0,300,"1.5 < M_{a} < 1.6 GeV"},
{"N_supcl_hits1600_1700","No. of supercluster rechits",10,0,200,0,300,"1.6 < M_{a} < 1.7 GeV"},
{"N_supcl_hits1700_1800","No. of supercluster rechits",10,0,200,0,300,"1.7 < M_{a} < 1.8 GeV"},
{"N_supcl_hits1800_1900","No. of supercluster rechits",10,0,200,0,300,"1.8 < M_{a} < 1.9 GeV"},
{"N_supclu_dRhits_0_100","No. of supercluster + dR rechits",10,0,200,0,300,"0 < M_{a} < 0.1 GeV"},
{"N_supclu_dRhits_100_200","No. of supercluster + dR rechits",10,0,200,0,300,"0.1 < M_{a} < 0.2 GeV"},
{"N_supclu_dRhits_200_300","No. of supercluster + dR rechits",10,0,200,0,300,"0.2 < M_{a} < 0.3 GeV"},
{"N_supclu_dRhits_300_400","No. of supercluster + dR rechits",10,0,200,0,300,"0.3 < M_{a} < 0.4 GeV"},
{"N_supclu_dRhits_400_500","No. of supercluster + dR rechits",10,0,200,0,300,"0.4 < M_{a} < 0.5 GeV"},
{"N_supclu_dRhits_500_600","No. of supercluster + dR rechits",10,0,200,0,300,"0.5 < M_{a} < 0.6 GeV"},
{"N_supclu_dRhits_600_700","No. of supercluster + dR rechits",10,0,200,0,300,"0.6 < M_{a} < 0.7 GeV"},
{"N_supclu_dRhits_700_800","No. of supercluster + dR rechits",10,0,200,0,300,"0.7 < M_{a} < 0.8 GeV"},
{"N_supclu_dRhits_800_900","No. of supercluster + dR rechits",10,0,200,0,300,"0.8 < M_{a} < 0.9 GeV"},
{"N_supclu_dRhits_900_1000","No. of supercluster + dR rechits",10,0,200,0,300,"0.9 < M_{a} < 1.0 GeV"},
{"N_supclu_dRhits_1000_1100","No. of supercluster + dR rechits",10,0,200,0,300,"1.0 < M_{a} < 1.1 GeV"},
{"N_supclu_dRhits_1100_1200","No. of supercluster + dR rechits",10,0,200,0,300,"1.1 < M_{a} < 1.2 GeV"},
{"N_supclu_dRhits_1200_1300","No. of supercluster + dR rechits",10,0,200,0,300,"1.2 < M_{a} < 1.3 GeV"},
{"N_supclu_dRhits_1300_1400","No. of supercluster + dR rechits",10,0,200,0,300,"1.3 < M_{a} < 1.4 GeV"},
{"N_supclu_dRhits_1400_1500","No. of supercluster + dR rechits",10,0,200,0,300,"1.4 < M_{a} < 1.5 GeV"},
{"N_supclu_dRhits_1500_1600","No. of supercluster + dR rechits",10,0,200,0,300,"1.5 < M_{a} < 1.6 GeV"},
{"N_supclu_dRhits_1600_1700","No. of supercluster + dR rechits",10,0,200,0,300,"1.6 < M_{a} < 1.7 GeV"},
{"N_supclu_dRhits_1700_1800","No. of supercluster + dR rechits",10,0,200,0,300,"1.7 < M_{a} < 1.8 GeV"},
{"N_supclu_dRhits_1800_1900","No. of supercluster + dR rechits",10,0,200,0,300,"1.8 < M_{a} < 1.9 GeV"},

{"N_raw_hits_0_100","No. of raw rechits",10,0,200,0,300,"0 < M_{a} < 0.1 GeV"},
{"N_raw_hits_100_200","No. of raw rechits",10,0,200,0,300,"0.1 < M_{a} < 0.2 GeV"},
{"N_raw_hits_200_300","No. of raw rechits",10,0,200,0,300,"0.2 < M_{a} < 0.3 GeV"},
{"N_raw_hits_300_400","No. of raw rechits",10,0,200,0,300,"0.3 < M_{a} < 0.4 GeV"},
{"N_raw_hits_400_500","No. of raw rechits",10,0,200,0,300,"0.4 < M_{a} < 0.5 GeV"},
{"N_raw_hits_500_600","No. of raw rechits",10,0,200,0,300,"0.5 < M_{a} < 0.6 GeV"},
{"N_raw_hits_600_700","No. of raw rechits",10,0,200,0,300,"0.6 < M_{a} < 0.7 GeV"},
{"N_raw_hits_700_800","No. of raw rechits",10,0,200,0,300,"0.7 < M_{a} < 0.8 GeV"},
{"N_raw_hits_800_900","No. of raw rechits",10,0,200,0,300,"0.8 < M_{a} < 0.9 GeV"},
{"N_raw_hits_900_1000","No. of raw rechits",10,0,200,0,300,"0.9 < M_{a} < 1.0 GeV"},
{"N_raw_hits_1000_1100","No. of raw rechits",10,0,200,0,300,"1.0 < M_{a} < 1.1 GeV"},
{"N_raw_hits_1100_1200","No. of raw rechits",10,0,200,0,300,"1.1 < M_{a} < 1.2 GeV"},
{"N_raw_hits_1200_1300","No. of raw rechits",10,0,200,0,300,"1.2 < M_{a} < 1.3 GeV"},
{"N_raw_hits_1300_1400","No. of raw rechits",10,0,200,0,300,"1.3 < M_{a} < 1.4 GeV"},
{"N_raw_hits_1400_1500","No. of raw rechits",10,0,200,0,300,"1.4 < M_{a} < 1.5 GeV"},
{"N_raw_hits_1500_1600","No. of raw rechits",10,0,200,0,300,"1.5 < M_{a} < 1.6 GeV"},
{"N_raw_hits_1600_1700","No. of raw rechits",10,0,200,0,300,"1.6 < M_{a} < 1.7 GeV"},
{"N_raw_hits_1700_1800","No. of raw rechits",10,0,200,0,300,"1.7 < M_{a} < 1.8 GeV"},
{"N_raw_hits_1800_1900","No. of raw rechits",10,0,200,0,300,"1.8 < M_{a} < 1.9 GeV"},

{"Raw_E_dist_0_100","Energy of raw rechits (GeV)", 10,0,200,0,100,"0 < M_{a} < 0.1 GeV"},
{"Raw_E_dist_100_200","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.1 < M_{a} < 0.2 GeV"},
{"Raw_E_dist_200_300","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.2 < M_{a} < 0.3 GeV"},
{"Raw_E_dist_300_400","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.3 < M_{a} < 0.4 GeV"},
{"Raw_E_dist_400_500","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.4 < M_{a} < 0.5 GeV"},
{"Raw_E_dist_500_600","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.5 < M_{a} < 0.6 GeV"},
{"Raw_E_dist_600_700","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.6 < M_{a} < 0.7 GeV"},
{"Raw_E_dist_700_800","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.7 < M_{a} < 0.8 GeV"},
{"Raw_E_dist_800_900","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.8 < M_{a} < 0.9 GeV"},
{"Raw_E_dist_900_1000","Energy of raw rechits (GeV)", 10,0,200,0,100,"0.9 < M_{a} < 1.0 GeV"},
{"Raw_E_dist_1000_1100","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.0 < M_{a} < 1.1 GeV"},
{"Raw_E_dist_1100_1200","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.1 < M_{a} < 1.2 GeV"},
{"Raw_E_dist_1200_1300","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.2 < M_{a} < 1.3 GeV"},
{"Raw_E_dist_1300_1400","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.3 < M_{a} < 1.4 GeV"},
{"Raw_E_dist_1400_1500","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.4 < M_{a} < 1.5 GeV"},
{"Raw_E_dist_1500_1600","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.5 < M_{a} < 1.6 GeV"},
{"Raw_E_dist_1600_1700","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.6 < M_{a} < 1.7 GeV"},
{"Raw_E_dist_1700_1800","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.7 < M_{a} < 1.8 GeV"},
{"Raw_E_dist_1800_1900","Energy of raw rechits (GeV)", 10,0,200,0,100,"1.8 < M_{a} < 1.9 GeV"},

{"Tot_raw_Energy_0_100","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0 < M_{a} < 0.1 GeV"},
{"Tot_raw_Energy_100_200","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.1 < M_{a} < 0.2 GeV"},
{"Tot_raw_Energy_200_300","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.2 < M_{a} < 0.3 GeV"},
{"Tot_raw_Energy_300_400","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.3 < M_{a} < 0.4 GeV"},
{"Tot_raw_Energy_400_500","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.4 < M_{a} < 0.5 GeV"},
{"Tot_raw_Energy_500_600","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.5 < M_{a} < 0.6 GeV"},
{"Tot_raw_Energy_600_700","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.6 < M_{a} < 0.7 GeV"},
{"Tot_raw_Energy_700_800","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.7 < M_{a} < 0.8 GeV"},
{"Tot_raw_Energy_800_900","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.8 < M_{a} < 0.9 GeV"},
{"Tot_raw_Energy_900_1000","Total energy of raw rechits (GeV)",10,0,200,0,1000,"0.9 < M_{a} < 1.0 GeV"},
{"Tot_raw_Energy_1000_1100","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.0 < M_{a} < 1.1 GeV"},
{"Tot_raw_Energy_1100_1200","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.1 < M_{a} < 1.2 GeV"},
{"Tot_raw_Energy_1200_1300","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.2 < M_{a} < 1.3 GeV"},
{"Tot_raw_Energy_1300_1400","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.3 < M_{a} < 1.4 GeV"},
{"Tot_raw_Energy_1400_1500","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.4 < M_{a} < 1.5 GeV"},
{"Tot_raw_Energy_1500_1600","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.5 < M_{a} < 1.6 GeV"},
{"Tot_raw_Energy_1600_1700","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.6 < M_{a} < 1.7 GeV"},
{"Tot_raw_Energy_1700_1800","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.7 < M_{a} < 1.8 GeV"},
{"Tot_raw_Energy_1800_1900","Total energy of raw rechits (GeV)",10,0,200,0,1000,"1.8 < M_{a} < 1.9 GeV"},
*/
};


 vector<string>GEN ={"M_gen","A_gen_pT","A_gen_eta","A_gen_phi","A_gen_energy","Lorentz boost of A","No. of gen photons","Photon1 gen eta","Photon1 gen phi","Photon1 gen pT","Photon1 gen E",
   "Photon2 gen eta","Photon2 gen phi","Photon2 gen pT","Photon2 gen E","E_sublead_by_E_lead","E_pho2_by_E_pho1"}  ;

  vector<string> loghist  ={"Lorentz boost of A","E_pho2_by_E_pho1","Pho1_hit_E","Pho2_hit_E","Pho1_ES_hit_E","Pho2_ES_hit_E","Unc_rec_E_ma_400_500","Unc_rec_E_ma_1700_1800","Unc_RH_E_ma_100","Unc_RH_E_ma_200","Unc_RH_E_ma_800","Unc_RH_E_ma_400","Unc_RH_E_ma_1800","Clu_rec_E_ma_100","Clu_rec_E_ma_200","Clu_rec_E_ma_400","Clu_rec_E_ma_800","Clu_rec_E_ma_1800","Hit_noise_ma_100","Hit_noise_ma_200","Hit_noise_ma_400","Hit_noise_ma_800","Hit_noise_ma_1600","Hit_noise_ma_1800"} ;

                

vector<string> with_stat ={"AA_angle_EBEE","AA_angle_EEEE","AA_angle_EBEB"};
  bool flag=false;
 
  sprintf(hname,"temp.root");
  TFile* fout = new TFile(hname,"RECREATE");
 
    n_files=1;  
    
  for(int i_file=0; i_file<n_files;i_file++)
    {      
     
      for(int i_cut=0; i_cut<size(varName);i_cut++)
	{
          int rebin = varName[i_cut].intData;
          string xLabel = varName[i_cut].str2;
          double ymin = varName[i_cut].double1;
          double ymax = varName[i_cut].double2;
          double xmin = varName[i_cut].double3;
          double xmax = varName[i_cut].double4;
          vector<string> legend_texts = {varName[i_cut].str3}; 
	  vector<TH1F*> hist_list;
	  
	  sprintf(hist_name,"%s",varName[i_cut].str1.c_str());

	  cout<<hist_name<<"\t"<<i_cut<<"\t"<<i_file<<"\t"<<f[i_file]->GetName()<<endl;
	  TH1F* h_orig = (TH1F*)f[i_file]->Get(hist_name); // SR
          string hist_name_ = varName[i_cut].str1 + "_";

	  TH1F* h_resp2 = (TH1F*)h_orig->Clone(hist_name_.c_str());; // SR
	  h_resp2->GetXaxis()->SetTitle(xLabel.c_str());
	  cout<<"resp2 "<<h_resp2->Integral()<<"\t"<<rebin<<"\t"<<xmin<<"\t"<<xmax<<endl;
	  
	  h_resp2->Rebin(rebin);
	 
	  
	  //h_resp2= setMyRange(h_resp2,xmin,xmax+0.01*xmax);
	  h_resp2= setMyRange(h_resp2,xmin,xmax);
	  setLastBinAsOverFlow(h_resp2);
	  
	  
	  hist_list.push_back(h_resp2); 
	
	  	 
	  cout<<h_resp2->Integral()<<"\t"<<f[i_file]->GetName()<<endl;	 
	  cout<<" hist_list.size() "<<hist_list.size()<<"\t "<<endl;
          std::ostringstream oss;
          oss << std::setw(4) << std::setfill('0') << i_cut <<hist_name;
          string hst_name = oss.str();

          int gen = count(GEN.begin(),GEN.end(),varName[i_cut].str1);
          //int reco = count(Reco.begin(),Reco.end(),varName[i_cut].str1);
	  int LOG = count(loghist.begin(), loghist.end(),varName[i_cut].str1);
	  int Stat = count(with_stat.begin(),with_stat.end(),varName[i_cut].str1);

          if(gen){hst_name = "GEN_"+hst_name;}
          //if(!reco){hst_name = "GEN_"+hst_name;}
	  else {hst_name = "RECO_" + hst_name;}
	 cout << "xMAX	" << xmax <<endl; 
generate_1Dplot(hist_list,hst_name.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,false,false,false,true,filetag[i_file].c_str(),legend_texts);
	  if(Stat){string hst_name3=hst_name +  "_stat";
 generate_1Dplot(hist_list,hst_name3.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,false,false,false,true,filetag[i_file].c_str(),legend_texts,true);}
	  if(LOG && Stat){string hst_name1=hst_name + "_logY" + "_stat";
generate_1Dplot(hist_list,hst_name1.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,false,true,false,true,filetag[i_file].c_str(),legend_texts,true);}
	  else if(LOG && !Stat){string hst_name2=hst_name + "_logY";
 generate_1Dplot(hist_list,hst_name2.c_str(),xLabel.c_str(),"Entries",rebin,ymin,ymax,xmin,xmax,leg_head,false,true,false,true,filetag[i_file].c_str(),legend_texts);}
	  	  }
	        //fout->Close();
      
    }
    }
    
