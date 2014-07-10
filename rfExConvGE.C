//
// Convolution of a Gaussian and Exponential
//

#ifndef _CINT_
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooExponential.h"
#include "RooFFTConvPdf.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
using namespace RooFit;

void rfExConvGE(){
	// Set up component pdfs
	// ---------------------
	
	// Construct observable
	RooRealVar x("x","x",0,20);
	
	// Construct Exponential
	RooRealVar lambda("lambda","lambda",-3,-20,0);
	RooExponential expo("expo","expo",x,lambda);
	
	// Construct Gaussian
	RooRealVar mean("mean", "mean of Gaussian",0,-20,20);
	RooRealVar sigma("sigma","width of Gaussian",2.,0.1,20);
	RooGaussian gaus("gaus","gaus",x,mean,sigma);

	// Construct convolution pdf
	// -------------------------
	
	// Set #bins to be used for FFT samplingto 1000
	x.setBins(1000,"cache");
	
	// Construct expo (x) gaus
	RooFFTConvPdf exg("exg","expo (x) gaus",x,expo,gaus);

	// Sample, fit and plot convoluted pdf
	// -----------------------------------
	
	// Generate 1000 events in x from exg
	RooDataSet* data = exg.generate(x,1000);
	
	// Fit exg to data
	// exg.fitTo(*data);

	// Plot data, expo pdf, expo (x) gaus pdf
	RooPlot* frame = x.frame(Title("expo (x) gaus convolution"));
	data->plotOn(frame);
	exg.plotOn(frame);
	expo.plotOn(frame,LineStyle(kDashed));
	//gaus.plotOn(frame,LineStyle(kDashed));

	// Draw frame on canvas
	TCanvas* c = new TCanvas("rfExConvGE","rfExConvGE",600,600);
	frame->Draw();
}
