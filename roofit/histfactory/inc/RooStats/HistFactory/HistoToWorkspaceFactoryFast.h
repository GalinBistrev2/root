// @(#)root/roostats:$Id:  cranmer $
// Author: Kyle Cranmer, Akira Shibata
/*************************************************************************
 * Copyright (C) 1995-2008, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOSTATS_HISTOTOWORKSPACEFACTORYFAST
#define ROOSTATS_HISTOTOWORKSPACEFACTORYFAST

#include <RooStats/HistFactory/Systematics.h>

#include <RooArgSet.h>
#include <RooDataSet.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooWorkspace.h>

#include <TH1.h>
#include <TObject.h>

#include <vector>
#include <string>
#include <map>
#include <memory>


class ParamHistFunc;
class RooProduct;
class RooHistFunc;

namespace RooStats {
namespace HistFactory {

// Forward Declarations FTW
class Measurement;
class Channel;
class Sample;

class HistoToWorkspaceFactoryFast : public TObject {

public:
   /// \brief Configuration settings for HistFactory behavior.
   struct Configuration {
      /// \brief Enable or disable optimization for binned likelihood fits (default `true`).
      bool binnedFitOptimization = true;
      /// \brief Control whether whether combined workspace is written to a ROOT file (default `true`).
      bool createWorkspaceFile = true;
      /// \brief Control whether individual workspace files are created for each channel (default `true`).
      bool createPerRegionWorkspaces = true;
      /// \brief Control whether errors on the data histograms are stored in the workspace (default `false`).
      bool storeDataError = false;
   };

      HistoToWorkspaceFactoryFast() {}
      HistoToWorkspaceFactoryFast(RooStats::HistFactory::Measurement& Meas);
      HistoToWorkspaceFactoryFast(RooStats::HistFactory::Measurement& Meas, Configuration const& cfg);

      static void ConfigureWorkspaceForMeasurement( const std::string& ModelName,
                      RooWorkspace* ws_single,
                      Measurement& measurement );

      RooFit::OwningPtr<RooWorkspace> MakeSingleChannelModel( Measurement& measurement, Channel& channel );
      RooFit::OwningPtr<RooWorkspace>  MakeCombinedModel(std::vector<std::string>, std::vector<std::unique_ptr<RooWorkspace>>&);

      static RooFit::OwningPtr<RooWorkspace> MakeCombinedModel( Measurement& measurement, const Configuration& config);
      static RooFit::OwningPtr<RooWorkspace> MakeCombinedModel( Measurement& measurement );
      static void PrintCovarianceMatrix(RooFitResult* result, RooArgSet* params,
               std::string filename);

      void SetFunctionsToPreprocess(std::vector<std::string> lines) { fPreprocessFunctions=lines; }

    protected:

       void AddConstraintTerms(RooWorkspace& proto, Measurement& measurement, std::string prefix, std::string interpName,
               std::vector<OverallSys>& systList,
               std::vector<std::string>& likelihoodTermNames,
               std::vector<std::string>& totSystTermNames);

      std::unique_ptr<RooProduct> CreateNormFactor(RooWorkspace& proto, std::string& channel,
            std::string& sigmaEpsilon, Sample& sample, bool doRatio);

      std::unique_ptr<RooWorkspace> MakeSingleChannelWorkspace(Measurement& measurement, Channel& channel);

      void MakeTotalExpected(RooWorkspace& proto, const std::string& totName,
              const std::vector<RooProduct*>& sampleScaleFactors,
              std::vector<std::vector<RooAbsArg*>>&  sampleHistFuncs) const;

      RooHistFunc* MakeExpectedHistFunc(const TH1* hist, RooWorkspace& proto, std::string prefix,
          const RooArgList& observables) const;

      std::unique_ptr<TH1> MakeScaledUncertaintyHist(const std::string& Name,
                 std::vector< std::pair<const TH1*, std::unique_ptr<TH1>> > const& HistVec ) const;

      TH1* MakeAbsolUncertaintyHist( const std::string& Name, const TH1* Hist );

      void ConfigureHistFactoryDataset(RooDataSet& obsData, TH1 const& nominal, RooWorkspace& proto,
                   std::vector<std::string> const& obsNameVec);

      std::vector<std::string> fSystToFix;
      std::map<std::string, double> fParamValues;
      double fNomLumi = 1.0;
      double fLumiError = 0.0;
      int fLowBin = 0;
      int fHighBin = 0;

    private:

      void GuessObsNameVec(const TH1* hist);

      std::vector<std::string> fObsNameVec;
      std::string fObsName;
      std::vector<std::string> fPreprocessFunctions;
      const Configuration fCfg;

      RooArgList createObservables(const TH1 *hist, RooWorkspace &proto) const;

      ClassDefOverride(RooStats::HistFactory::HistoToWorkspaceFactoryFast,3)
    };

  }
}

#endif
