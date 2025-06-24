/// \file
/// \ingroup tutorial_roofit_main
/// \notebook -js
/// Basic functionality: fitting, plotting, toy data generation on one-dimensional PDFs.
///
///  pdf = gauss(x,m,s)
///
/// \macro_image
/// \macro_code
/// \macro_output
///
/// \date July 2008
/// \author Wouter Verkerke

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void rf101_basics()
{
   // S e t u p   m o d e l
   // ---------------------

   // Declare variables x,mean,sigma with associated name, title, initial value and allowed range
   RooRealVar x("x", "x", -10, 10);
   RooRealVar mean("mean", "mean of gaussian", 1, -10, 10);
   RooRealVar sigma("sigma", "width of gaussian", 1, 0.1, 10);

   // Build gaussian pdf in terms of x,mean and sigma
   //RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);
   RooRealVar m1("mean1", "mean1", 0.);
   RooRealVar s1("sigma1", "sigma1", 1., 0.001, 10.);
   RooRealVar m2("mean2", "mean2", 2.);
   RooRealVar s2("sigma2", "sigma2", 1., 0.001, 10.);
   RooGaussian gaus1("gaus1", "gaus1", x, m1, s1);
   RooGaussian gaus2("gaus2", "gaus2", x, m2, s2);
   RooCategory indx("my_special_index", "my_index");

   RooArgList list{gaus1, gaus2};
   RooMultiPdf gauss("mult", "multi_pdf", indx, list);

   //indx.Print("v");
   //return;

   // Index should not be a free parameter in the fix
   indx.setConstant();

   // Select gaus1
   indx.setIndex(0);
   m1.setConstant(false);
   s1.setConstant(false);
   m2.setConstant(true);
   s2.setConstant(true);


   // Construct plot frame in 'x'
   RooPlot *xframe = x.frame(Title("Gaussian pdf."));

   // P l o t   m o d e l   a n d   c h a n g e   p a r a m e t e r   v a l u e s
   // ---------------------------------------------------------------------------

   // Plot gauss in frame (i.e. in x)
   gauss.plotOn(xframe);

   // Plot gauss in frame (i.e. in x) and draw frame on canvas
   gauss.plotOn(xframe, LineColor(kRed));

   // G e n e r a t e   e v e n t s
   // -----------------------------

   // Generate a dataset of 1000 events in x from gauss
   std::unique_ptr<RooDataSet> data{gauss.generate(x, 10000)};

   // Change the value of sigma to 3
   s1.setVal(3.0);
   s2.setVal(3.0);

   // Make a second plot frame in x and draw both the
   // data and the pdf in the frame
   RooPlot *xframe2 = x.frame(Title("Gaussian pdf with data"));
   data->plotOn(xframe2);
   gauss.plotOn(xframe2);

   // F i t   m o d e l   t o   d a t a
   // -----------------------------

   // Fit pdf to data
  std::unique_ptr<RooAbsReal> nll{gauss.createNLL(*data, RooFit::EvalBackend("codegen"))};

   // only works with "codegen"
   static_cast<RooFit::Experimental::RooFuncWrapper&>(*nll).writeDebugMacro("macro_1");

   RooMinimizer minim{*nll};
   minim.setStrategy(0);
   minim.minimize("Minuit2", "");

   gauss.fitTo(*data, PrintLevel(-1));

   // Print values of mean and sigma (that now reflect fitted values and errors)
   mean.Print();
   sigma.Print();

   // Draw all frames on a canvas
   TCanvas *c = new TCanvas("rf101_basics", "rf101_basics", 800, 400); c->Divide(2);
   c->cd(1);
   gPad->SetLeftMargin(0.15);
   xframe->GetYaxis()->SetTitleOffset(1.6);
   xframe->Draw();
   c->cd(2);
   gPad->SetLeftMargin(0.15);
   xframe2->GetYaxis()->SetTitleOffset(1.6);
   xframe2->Draw();
   
   // Save first plot
TCanvas *c1 = new TCanvas("c1", "Single PDF", 800, 600);
xframe->Draw();
c1->SaveAs("gaussian_plot_1.png");

// Save second plot (with data)
TCanvas *c2 = new TCanvas("c2", "PDF with Data", 800, 600);
xframe2->Draw();
c2->SaveAs("gaussian_plot_2.png");

}

