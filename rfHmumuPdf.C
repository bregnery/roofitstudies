//
// Create a PDF to be used in the Hmumu analysis
//

#ifndef _CINT_
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooBreitWigner.h"
#include "RooExponential.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
#include "RooConstVar.h"

using namespace RooFit;

void rfHmumuPdf(){
	// Declare Addition Coefficent
	RooRealVar coef("coef","coefficent for Addition",0,0,1);	

	// Declare observable
	RooRealVar x("x","x",110,160);
	//x.setRange("zPeak",90,92);

	// Declare Parameters for Breit Wigner
	RooRealVar mean("mean","mean of Breit Wigner",91.1876);
	RooRealVar sigma("sigma","width of Breit Wigner",2.4952);
	
	// Declare Parameter for Exponential
	RooRealVar lambda("lambda","lambda of Exponential",-0.001,-0.1,-0.0001);
	
	// Declare Parameters for Gaussian
	RooRealVar meanG("meanG","mean of Gaussian",0);
	RooRealVar sigmaG("sigmaG","width of Gaussian",3);
	/*
		// Construct a nonrealitivistic Breit Wigner
		//RooBreitWigner bWpdf("bWpdf","bWpdf",x,mean,sigma);
		RooGenericPdf bWpdf("bWpdf","bWpdf","(@2/((@0-@1)*(@0-@1)+(@2/2)*(@2/2)))",RooArgList(x,mean,sigma));
	
		// Construct a realitivistic Breit Wigner
		RooGenericPdf relBW("relBW","relBW","((@0*@0)/((@0*@0-(@1*@1))*(@0*@0-(@1*@1))+(@1*@1*@2*@2)))",RooArgList(x,mean,sigma));

		// Construct a Z Breit Wigner
		RooGenericPdf zBWpdf("zBWpdf","zBWpdf","((@0*@0)/((@0*@0-(@1*@1))*(@0*@0-(@1*@1))+((@0*@0*@0*@0*@2*@2)/(@1*@1))))",RooArgList(x,mean,sigma));
	
		// Create a Photon Pdf
		RooGenericPdf phoPdf("phoPdf","phoPdf","(1/(@0*@0))",RooArgList(x));
	*/

	// Construct a nonrealitivistic Breit Wigner
	//RooBreitWigner bWpdf("bWpdf","bWpdf",x,mean,sigma);
	RooGenericPdf bWpdf("bWpdf","bWpdf","(@2/((@0-@1)*(@0-@1)+(@2/2)*(@2/2)))*TMath::Exp(@3*@0)",RooArgList(x,mean,sigma,lambda));
	
	// Construct a realitivistic Breit Wigner
	RooGenericPdf relBW("relBW","relBW","((@0*@0)/((@0*@0-(@1*@1))*(@0*@0-(@1*@1))+(@1*@1*@2*@2)))*TMath::Exp(@3*@0)",RooArgList(x,mean,sigma,lambda));

	// Construct a Z Breit Wigner
	RooGenericPdf zBWpdf("zBWpdf","zBWpdf","((@0*@0)/((@0*@0-(@1*@1))*(@0*@0-(@1*@1))+((@0*@0*@0*@0*@2*@2)/(@1*@1))))*TMath::Exp(@3*@0)",RooArgList(x,mean,sigma,lambda));
	
	// Create a Photon Pdf
	RooGenericPdf phoPdf("phoPdf","phoPdf","(1/(@0*@0))*TMath::Exp(@1*@0)",RooArgList(x,lambda));
	
	// Add the Photon Term to the other Pdfs
	RooAddPdf phoBW("phoBW","Photon term added to a Breit Wigner",phoPdf,bWpdf,coef);
	RooAddPdf phoRelBW("phoRelBW","Photon added to a relativistic Breit Wigner",phoPdf,relBW,coef);
	RooAddPdf phoZBW("phoZBW","Photon added to a Z Breit Wigner",phoPdf,zBWpdf,coef);
	
	// Create a Gaussian Pdf
	RooGaussian gaus("gaus","gaus",x,meanG,sigmaG);
	
	/*	
		// Construct an Exponential Pdf
		RooExponential expo("expo","exponential PDF",x,lambda);
	
		// Multiply the exponential by the other PDFs
		RooProdPdf exPhoBW("exPhoBW","Exponential multiplied to BW",phoBW,expo);
	       	 exPhoRBWArgSet = RooArgSet(phoRelBW,expo);
		RooProdPdf exPhoRBW("exPhoRBW","Expo multiplied to a Relativistic BW",exPhoRBWArgSet,Conditional(exPhoRBWArgSet,x));
		RooProdPdf exPhoZBW("exPhoZBW","Expo multiplied to a Z BW",phoZBW,expo);
	*/
	
	// Convolute Pdfs with Gaussian
	x.setBins(1000,"cache");
	RooFFTConvPdf phoBWxg("phoBWxg","phoBW (x) gaus",x,phoBW,gaus);
	phoBWxg.setBufferFraction(0.5);
	RooFFTConvPdf phoRelBWxg("phoRelBWxg","phoRelBW (x) gaus",x,phoRelBW,gaus);
	phoRelBWxg.setBufferFraction(0.5);
	RooFFTConvPdf phoZBWxg("phoZBWxg","phoZBW (x) gaus",x,phoZBW,gaus);
	phoZBWxg.setBufferFraction(0.5);
	
	// Test by generating a data set
	RooDataSet* data = phoBWxg.generate(x,10000);
	
	// Plot and draw on a canvas
	RooPlot* xframe = x.frame(Title("Breit Wigner Plots"));
	data->plotOn(xframe);
	//exPhoBW.plotOn(xframe,Range("zPeak"));
	//exPhoRBW.plotOn(xframe,LineColor(kGreen),LineStyle(kDashed));
	//exPhoZBW.plotOn(xframe,LineColor(kOrange),LineStyle(kDashed));
	phoBWxg.plotOn(xframe,Range("zPeak"));
	phoRelBWxg.plotOn(xframe,LineColor(kGreen),LineStyle(kDashed));
	phoZBWxg.plotOn(xframe,LineColor(kOrange),LineStyle(kDashed));
	TCanvas* c = new TCanvas("rfHmumuPdf","rfHmumuPdf",800,400);
	xframe->Draw();
}
	
