//
// Create a basic a basic Exponential PDF with lamda = 
//

#ifndef _CINT_
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void rfExExpo(){
	// Declare Eponential Variables
	RooRealVar x("x","x",0,10);
	RooRealVar lambda("lambda","lambda",-3,-10,0);

	// Create an Exponential PDF with variables
	RooExponential expo("expo","eponential PDF",x,lambda);
	
	// Generate a dataset of 1000 and plot it, then plot the PDF
	RooDataSet* data = expo.generate(x,1000);
	RooPlot* xframe = x.frame(Title("Exponential p.d.f."));
	data->plotOn(xframe);
	expo.plotOn(xframe);
	
	// Draw the plot on a TCanvas
	TCanvas* c = new TCanvas("rfExExpo","rfExExpo",800,400);
	xframe->Draw();
}

