#include "RooCategory.h"
#include "RooRealVar.h"
#include "RooDataSet.h"

using namespace RooFit;

void RooMultipdf_translate() {
   RooCategory cat("cat", "cat");
   cat.defineType("A");
   cat.defineType("B");

   RooRealVar x("x", "x", -10, 10);

   // Create dummy dataset (needed to call createNLL)
   RooDataSet data("data", "data", RooArgSet(x));

   try {
      // This will try to codegen RooCategory and fail
      auto nll = cat.createNLL(data, RooFit::EvalBackend("codegen"));
   } catch (const std::exception& e) {
      std::cerr << "Caught exception: " << e.what() << std::endl;
   }
}
