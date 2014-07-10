#ifndef _CINT_
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooBreitWigner"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void rfExBreitWig(){
	// Declare Variables
	RooRealVar x("x","x",-10,10);
	RooRealVar mean("mean","mean of Breit Wigner",0,-10,10);
	RooRealVar sigma("sigma","width of Breit Wigner",3,0.1,10);

	// Create, generate, and plot the PDF
	RooBreitWigner brwi("brwi","Breit Wigner PDF",x,mean,sigma);
	RooDataSet* data = brwi.generate(x,1000);
	RooPlot* xframe = x.frame(Title("Breit Wigner P.d.f"));
	data->plotOn(xframe);
	brwi.plotOn(xframe);

	// Draw the Plot on a Canvas
	TCanvas* c = new TCanvas("rfExBreitWig","rfExBreitWig",800,400);
	xframe->Draw();
}
