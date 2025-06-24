#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooCategory.h"
#include "RooMultiPdf.h"
#include "RooFitResult.h"
#include "RooMinimizer.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "RooFuncWrapper.h" // for writeDebugMacro

using namespace RooFit;

void trial_RooMultiPdf() {
    // Observable
    RooRealVar x("x", "x", -10, 10);

    // Two Gaussians
    RooRealVar m1("m1", "mean1", 0);
    RooRealVar s1("s1", "sigma1", 1, 0.1, 10);
    RooGaussian g1("g1", "Gaus1", x, m1, s1);

    RooRealVar m2("m2", "mean2", 3);
    RooRealVar s2("s2", "sigma2", 1, 0.1, 10);
    RooGaussian g2("g2", "Gaus2", x, m2, s2);

    // Index category
    RooCategory index("index", "PDF index");
    index.defineType("model1", 0);
    index.defineType("model2", 1);

    // List of PDFs
    RooArgList pdfs(g1, g2);
    RooMultiPdf multiPdf("multi", "multi", index, pdfs);

    // Generate toy data from g1
    std::unique_ptr<RooDataSet> data{g1.generate(x, 10000)};

    // Choose one component of the RooMultiPdf
    RooAbsPdf* chosenPdf = multiPdf.getPdf(0);  // Select g1

    // Build codegen-based NLL for this component
    RooAbsReal* nll = chosenPdf->createNLL(*data, EvalBackend("codegen"));

    // Write the compiled macro for inspection
    static_cast<RooFit::Experimental::RooFuncWrapper&>(*nll).writeDebugMacro("macro_codegen_nll");

    // Fit
    RooMinimizer minim(*nll);
    minim.minimize("Minuit2", "migrad");

    // Plot
    RooPlot* frame = x.frame();
    data->plotOn(frame);
    chosenPdf->plotOn(frame);

    TCanvas* c = new TCanvas("c", "Fit with Codegen", 800, 600);
    frame->Draw();
}

