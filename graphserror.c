//parte A
//scrip de grafico de errores desde un .txt

void graphserror()
{TCanvas *c1=new TCanvas();
 c1->SetGrid();
 TGraphErrors* g=new TGraphErrors("data_2.txt","%lg %lg %lg");
 g-> SetTitle("Muestra de errores");
 g->GetHistogram()->SetYTitle("Eventos");
 g->GetHistogram()->SetXTitle("X");
 g->SetFillColor(kGreen); 
 g->SetMarkerStyle(kFullCircle);
 g->Draw("APL");

 //gPad->Print("plot_1.png");
 
}
