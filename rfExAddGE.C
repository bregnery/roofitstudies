//
// Add a Gaussian and Exponential PDF
// Then plot the PDF and Data points from the PDF
//

#ifndef _CINT_
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "RooAddPdf.h"
using namespace RooFit;

void rfExAddGE(){
	// Declare Coefficent
	RooRealVar coef("coef","coefficent for Addition",0.5,0,1);

	// Declare Exponential parameters
	RooRealVar x("x","x",0,20);
	RooRealVar lambda("lambda","lambda",-1,-20,0);

	// Declare Gaussian parameters
	//RooRealVar y("y","y",0,20);
	RooRealVar mean("mean","mean of gaussian",0,0,20);
	RooRealVar sigma("sigma","width of gaussian",0.5,0.1,20);

	// Create Gaussian and Exponential PDFs
	RooGaussian gaus("gauss","gaussian PDF",x,mean,sigma);
	RooExponential expo("expo","Exponential PDF",x,lambda);

	// Add the PDFs
	RooAddPdf gausExpo("gausExpo","Gaussian added to an Exponential",gaus,expo,coef);
	
	// Generate a dataset of 1000 and plot it, then plot the PDF
	RooDataSet* data = gausExpo.generate(x,1000);
	RooPlot* xframe = x.frame(Title("Gaussian + Exponential with data"));
	data->plotOn(xframe);
	gausExpo.plotOn(xframe);

	// Draw the Plot on a Canvas
	TCanvas* c = new TCanvas("rfExAddGE","rfExAddGE",800,400);
	xframe->Draw();
}
