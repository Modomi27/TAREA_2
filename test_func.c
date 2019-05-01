//parte B

void test_func()
{
 TGraph* g=new TGraph("data_2.txt");
 g-> SetTitle("Funcion de ajuste");
 TF1* cuad=new TF1("Cuadratica","[0]+[1]*x+[2]*x*x",0.05,4.95);
 TF1* lin=new TF1("lineal","[0]+[1]*x",0.05,4.95);
 g->SetMarkerStyle(24);
 g->GetHistogram()->SetYTitle("Eventos");
 g->GetHistogram()->SetXTitle("X");
 g->Fit(cuad,"R");
 //g->Fit(lin,"R"); //segunda funcion de prueba 
 g->Draw("APL");
}
