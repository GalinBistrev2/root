double roo_codegen_0(double* params, double const* obs, double const* xlArr) {
double RooNLLVarNewWeightSum = 0.0;
double RooNLLVarNewResult = 0.0;
  // Begin -- RooAddition::nll_mult_multData[ RooNLLVarNew ] = 0
    // Begin -- RooFit::Detail::RooNLLVarNew::RooNLLVarNew[ pdf=mult weightVar=_weight _weight_sumW2=_weight_sumW2 ] = 0
        // Begin -- RooCategory::my_special_index = _pdf0(idx = 0)

        // End -- RooCategory::my_special_index = _pdf0(idx = 0)


          // Begin -- RooRealIntegral::gaus1_Int[x][ Int gaus1d[Ana](x) ] = 7.51343
          const double t2 = RooFit::Detail::MathFuncs::gaussianIntegral(-10.000000, 10.000000, params[0], params[2]);
          // End -- RooRealIntegral::gaus1_Int[x][ Int gaus1d[Ana](x) ] = 7.51343

          // Begin -- RooRealIntegral::gaus2_Int[x][ Int gaus2d[Ana](x) ] = 7.49084
          const double t5 = RooFit::Detail::MathFuncs::gaussianIntegral(-10.000000, 10.000000, params[1], params[3]);
          // End -- RooRealIntegral::gaus2_Int[x][ Int gaus2d[Ana](x) ] = 7.49084

    for(int loopIdx1 = 0; loopIdx1 < 10000; loopIdx1++) {
      // Begin -- RooMultiPdf::mult[ _pdfs=(gaus1_over_gaus1_Int[x],gaus2_over_gaus2_Int[x]) _corrs=(constgaus1,constgaus2) _index=my_special_index ] = 0.133095
        // Begin -- RooFit::Detail::RooNormalizedPdf::gaus1_over_gaus1_Int[x][ numerator=gaus1 denominator=gaus1_Int[x] ] = 0.133095
          // Begin -- RooGaussian::gaus1[ x=x mean=mean1 sigma=sigma1 ] = 1
          const double t3 = RooFit::Detail::MathFuncs::gaussian(obs[0 + loopIdx1], params[0], params[2]);
          // End -- RooGaussian::gaus1[ x=x mean=mean1 sigma=sigma1 ] = 1

        const double t4 = t3/t2;
        // End -- RooFit::Detail::RooNormalizedPdf::gaus1_over_gaus1_Int[x][ numerator=gaus1 denominator=gaus1_Int[x] ] = 0.133095

        // Begin -- RooFit::Detail::RooNormalizedPdf::gaus2_over_gaus2_Int[x][ numerator=gaus2 denominator=gaus2_Int[x] ] = 0.106896
          // Begin -- RooGaussian::gaus2[ x=x mean=mean2 sigma=sigma2 ] = 0.800737
          const double t6 = RooFit::Detail::MathFuncs::gaussian(obs[0 + loopIdx1], params[1], params[3]);
          // End -- RooGaussian::gaus2[ x=x mean=mean2 sigma=sigma2 ] = 0.800737

        const double t7 = t6/t5;
        // End -- RooFit::Detail::RooNormalizedPdf::gaus2_over_gaus2_Int[x][ numerator=gaus2 denominator=gaus2_Int[x] ] = 0.106896

      // End -- RooMultiPdf::mult[ _pdfs=(gaus1_over_gaus1_Int[x],gaus2_over_gaus2_Int[x]) _corrs=(constgaus1,constgaus2) _index=my_special_index ] = 0.133095

    RooNLLVarNewResult += RooFit::Detail::MathFuncs::nll(multipdf(obs[1], {t4, t7}, 2), obs[10000 + loopIdx1], 0, 0);    }
    // End -- RooFit::Detail::RooNLLVarNew::RooNLLVarNew[ pdf=mult weightVar=_weight _weight_sumW2=_weight_sumW2 ] = 0

  // End -- RooAddition::nll_mult_multData[ RooNLLVarNew ] = 0


 return RooNLLVarNewResult;

}