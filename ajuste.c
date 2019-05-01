//parte D Y E

#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"


// Quadratic background function
double background(double *x, double *par) 
{
   return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}


// Lorenzian Peak function
double lorentzianPeak(double *x, double *par) 
{
  return (0.5*par[0]*par[1]/TMath::Pi())/TMath::Max( 1.e-10,(x[0]-par[2])*(x[0]-par[2]) + .25*par[1]*par[1]);
}

// Sum of background and peak function

double fitFunction(double *x, double *par) 
{
  return background(x,par) + lorentzianPeak(x,&par[3]);
}

void ajuste() 
{
 //Bevington Exercise by Peter Malzacher, modified by Rene Brun

   const int nBins =50;

   Double_t data[nBins] = {315,290,297,304,308,309,283,314,321,229,247,295,285,293,254,258,279,270,255,261,263,243,277,
  309,326,325,264,224,206,146,161,149,130,145,127,138,124,113,118,94,85,98,60,62,68,61,53,46,35,40};
   
   TCanvas *c1 = new TCanvas("c1","Fitting Demo",10,10,700,500);
   c1->SetFillColor(10);
   c1->SetFrameFillColor(19);
   c1->SetGrid();

   TH1F *histo = new TH1F("histo","Ajuste senal + fondo",50,0,5);
   histo->SetMarkerStyle(21);
   histo->SetMarkerSize(0.8);
   histo->SetStats(0);

   for(int i=0; i < nBins;  i++) histo->SetBinContent(i+1,data[i]);
   // create a TF1 with the range from 0 to 5 and 6 parameters
   TF1 *fitFcn = new TF1("fitFcn",fitFunction,0,3,6);
   fitFcn->SetNpx(500);
   fitFcn->SetLineWidth(4);
   fitFcn->SetLineColor(kMagenta);

   fitFcn->SetParameters(1,1,1,1,1,1);
   histo->Fit("fitFcn","0");

   // second try: set start values for some parameters
   
   fitFcn->SetParameter(4,0.5); // width
   fitFcn->SetParameter(5,2.5);   // peak

   histo->Fit("fitFcn","V+","ep");

   // improve the picture:
   
   TF1 *backFcn = new TF1("backFcn",background,0,5,3);
   backFcn->SetLineColor(kRed);
   
   TF1 *signalFcn = new TF1("signalFcn",lorentzianPeak,0,5,3);
   signalFcn->SetLineColor(kBlue);
   signalFcn->SetNpx(500);
   
   double par[6];

   // writes the fit results into the par array
   
   fitFcn->GetParameters(par);
   backFcn->SetParameters(par);
   backFcn->Draw("same");
   signalFcn->SetParameters(&par[3]);
   signalFcn->Draw("same");

//Event
  double in=signalFcn->Integral(1.75,3.15);
  cout<<"Numero de eventos: "<<in<<endl;

   // draw the legend

   TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
   legend->SetTextFont(72);
   legend->SetTextSize(0.035);
   legend->AddEntry(histo,"Data","p");
   legend->AddEntry(backFcn,"Ajuste de fondo","l");
   legend->AddEntry(signalFcn,"Ajuste senal","l");
   legend->AddEntry(fitFcn,"Ajuste combinado","l");
   legend->Draw();

    gPad->Print("ajuste.png");

}
