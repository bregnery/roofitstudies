//
// Create my own Breit Wigner PDF and generate data
// Compare it to roofit's Breit Wigner with the same parameters
// Create a relativistic Breit Wigner PDF
//

#ifndef _CINT_
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooBreitWigner.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooConstVar.h"

using namespace RooFit;

void rfExUsrPdf(){
	// Declare observable
	RooRealVar x("x","x",-20,20);

	// Declare Parameters for Breit Wigner
	RooRealVar mean("mean","mean of Breit Wigner",5,-20,20);
	RooRealVar sigma("sigma","width of Breit Wigner",3,0.1,10);
	
	// Construct generic pdf from interpreted expression
	RooGenericPdf genpdf("genpdf","genpdf","(sigma/((x-mean)*(x-mean)+(sigma/2)*(sigma/2)))",RooArgSet(x,mean,sigma));

	// Generate a dataset
	RooDataSet* data = genpdf.generate(x,1000);
	
	// Construct a realitivistic Breit Wigner
	RooGenericPdf relBW("relBW","relBW","1/((x*x-(mean*mean))*(x*x-(mean*mean))+(mean*mean*sigma*sigma))",RooArgSet(x,mean,sigma));

	// Create a Breit Wigner from roofit
	RooBreitWigner brwi("brwi","Breit Wigner PDF",x,mean,sigma);
	
	// Plot and draw on a canvas
	RooPlot* xframe = x.frame(Title("Breit Wigner Plots"));
	data->plotOn(xframe);
	genpdf.plotOn(xframe);
	brwi.plotOn(xframe,LineColor(kGreen),LineStyle(kDashed));
	relBW.plotOn(xframe,LineColor(kOrange));
	TCanvas* c = new TCanvas("rfExUsrPdf","rfExUsrPdf",800,400);
	xframe->Draw();
}
	
	
