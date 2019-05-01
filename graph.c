//parte C
//graficar datos desde un .txt

void graph()
{
 TGraph* g=new TGraph("data_2.txt");
 g-> SetTitle("Ajuste de la senal");
 TF1* fitg=new TF1("fitg","gaus",2.15,2.95);
 g->SetMarkerStyle(24);
 g->Fit(fitg,"R");
 g->GetHistogram()->SetYTitle("Eventos");
 g->GetHistogram()->SetXTitle("X");
 g->Draw("APL");


}
