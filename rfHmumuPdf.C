//
// Create a PDF to be used in the Hmumu analysis
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

void rfHmumuPdf(){
	// Declare Addition Coefficent
	RooRealVar coef("coef","coefficent for Addition",0.5,0,1);	

	// Declare observable
	RooRealVar x("x","x",110,160);

	// Declare Parameters for Breit Wigner
	RooRealVar mean("mean","mean of Breit Wigner",91.1876);
	RooRealVar sigma("sigma","width of Breit Wigner",2.4952);
	
	// Construct a nonrealitivistic Breit Wigner
	RooGenericPdf bWpdf("bWpdf","bWpdf","(sigma/((x-mean)*(x-mean)+(sigma/2)*(sigma/2)))",RooArgSet(x,mean,sigma));
	
	// Construct a realitivistic Breit Wigner
	RooGenericPdf relBW("relBW","relBW","((x*x)/((x*x-(mean*mean))*(x*x-(mean*mean))+(mean*mean*sigma*sigma)))",RooArgSet(x,mean,sigma));

	// Construct a Z Breit Wigner
	RooGenericPdf zBWpdf("zBWpdf","zBWpdf","((x*x)/((x*x-(mean*mean))*(x*x-(mean*mean))+((x*x*x*x*sigma*sigma)/(mean*mean))))",RooArgSet(x,mean,sigma));
	
	// Create a Photon Pdf
	RooGenericPdf phoPdf("phoPdf","phoPdf","(1/(x*x))",RooArgSet(x));
	
	// Add the Photon Term to the other Pdfs
	RooAddPdf phoBW("phoBW","Photon term added to a Breit Wigner",phoPdf,bWpdf,coef);
	RooAddPdf phoRelBW("phoRelBW","Photon added to a relativistic Breit Wigner",phoPdf,relBW,coef);
	RooAddPdf phoZBW("phoZBW","Photon added to a Z Breit Wigner",phoPdf,zBWpdf,coef);
	
	// Plot and draw on a canvas
	RooPlot* xframe = x.frame(Title("Breit Wigner Plots"));
	phoBW.plotOn(xframe);
	phoRelBW.plotOn(xframe,LineColor(kGreen),LineStyle(kDashed));
	phoZBW.plotOn(xframe,LineColor(kOrange),LineStyle(kDashed));
	TCanvas* c = new TCanvas("rfHmumuPdf","rfHmumuPdf",800,400);
	xframe->Draw();
}
	
