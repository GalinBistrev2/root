#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooCategory.h"
#include "RooArgList.h"
#include "RooMultiPdf.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "RooMinimizer.h"

using namespace RooFit;

void simple_RooMultiPdf() {
    // Observable
    RooRealVar x("x", "x", -10, 10);

    // Model 1: Gaussian with mean 0
    RooRealVar mean1("mean1", "mean1", 0);
    RooRealVar sigma1("sigma1", "sigma1", 1, 0.1, 10);
    RooGaussian gauss1("gauss1", "gauss1", x, mean1, sigma1);

    // Model 2: Gaussian with mean 2
    RooRealVar mean2("mean2", "mean2", 2);
    RooRealVar sigma2("sigma2", "sigma2", 1, 0.1, 10);
    RooGaussian gauss2("gauss2", "gauss2", x, mean2, sigma2);

    // MultiPDF setup
    RooCategory index("index", "index");
    RooArgList pdfList(gauss1, gauss2);
    RooMultiPdf multiPdf("multiPdf", "multiPdf", index, pdfList);

    // Generate toy data from model 0
    index.setIndex(0);
    auto* data = multiPdf.generate(x, 1000);

    // Optional: Let the index float
    index.setConstant(false);

    // Create NLL using modern API
    auto nll = multiPdf.createNLL(*data, EvalBackend("codegen"));
    RooMinimizer minim(*nll);
    minim.setStrategy(0);
    minim.minimize("Minuit2");

    std::cout << "Best model index = " << index.getIndex() << std::endl;

    // Plot
    RooPlot* frame = x.frame(Title("RooMultiPdf Fit"));
    data->plotOn(frame);
