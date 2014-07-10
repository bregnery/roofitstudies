// 
// Create a basic Gaussian PDF with mean = 0 and sigma = 3
// Create data based off of this gaussian and plot the PDF on top
//

#ifndef _CINT_
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void rfExGaus(){
	// Declare Gaussian Variables
	RooRealVar x("x","x",-10,10);
	RooRealVar mean("mean","mean of gaussian",0,-10,10);
	RooRealVar sigma("sigma","width of gaussian",3,0.1,10);

	// Create a Gaussian PDF with variables
	RooGaussian gauss("gauss","gaussian PDF",x,mean,sigma);

	// Generate a dataset of 1000 and plot it, then plot the PDF
	RooDataSet* data = gauss.generate(x,1000);
	RooPlot* xframe = x.frame(Title("Gaussian p.d.f. with data"));
	data->plotOn(xframe);
	gauss.plotOn(xframe);

	// Draw the Plot on a Canvas
	TCanvas* c = new TCanvas("rfExGaus","rfExGaus",800,400);
	xframe->Draw();
}


