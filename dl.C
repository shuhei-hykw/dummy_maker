#include <fstream>
#include <iostream>

#include <TGraph.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TString.h>

void
dl( void )
{
  std::string file_name = "dl.txt";

  TCanvas *c = new TCanvas( "c", "c", 1200, 800 );
  const int nh = 50;
  TH1D    *h[nh];
  for( int ih=0; ih<nh; ++ih ){
    h[ih] = new TH1D( Form( "h%d", ih ),  Form( "h%d", ih ),
		      2000, 0., 20. );
  }

  std::ifstream f( file_name.c_str() );
  if( !f.is_open() ) return;
  std::string line;
  int i=0;
  while( f.good() && std::getline( f, line ) ){
    if( i==100000 ) break;
    if( i%1000==0 ) std::cout << "read " << i << std::endl;
    if( line.empty() || line[0]=='#' ) continue;
    std::string name[nh];
    double value[nh];
    if( f >> name[0] >> value[0] >> name[1] >> value[1]
	>> name[2] >> value[2] >> name[3] >> value[3] ){
      int lid = (int)value[1];
      if( lid<10 && value[3]>=3.0 ) continue;
      if( 30<lid && lid<35 && value[3]>=4.5 ) continue;
      if( 34<lid && value[3]>=10.0 ) continue;
      h[lid]->Fill( value[3] );
    }
    i++;
  }

  c->Divide(8,5);
  for( int ih=1; ih<=nh-1; ++ih ){
    c->cd( ih );
    h[ih]->Draw();
  }
  // TGraph *g = new TGraph( file_name.c_str(), "%*s %*lf %*s %lf %*s %*lf %*s %lf", "" );
  // if( !g ) return;
  // g->SetMarkerStyle(8);
  // g->SetMarkerSize(2);
  // g->Draw("AP");
}
