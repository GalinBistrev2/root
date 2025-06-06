/// \file
/// \ingroup tutorial_spectrum
/// Example to illustrate the influence of the clipping window width on the
/// estimated background.
///
/// \macro_image
/// \macro_code
///
/// \authors Miroslav Morhac, Olivier Couet

void Background_width2()
{
   Int_t i;
   const Int_t nbins = 4096;
   Double_t xmin = 0;
   Double_t xmax = 4096;
   Double_t source[nbins];
   gROOT->ForceStyle();

   TH1F *d1 = new TH1F("d1", "", nbins, xmin, xmax);
   TH1F *d2 = new TH1F("d2", "", nbins, xmin, xmax);
   TH1F *d3 = new TH1F("d3", "", nbins, xmin, xmax);
   TH1F *d4 = new TH1F("d4", "", nbins, xmin, xmax);

   TString dir = gROOT->GetTutorialDir();
   TString file = dir + "/legacy/spectrum/TSpectrum.root";
   TFile *f = new TFile(file.Data());
   TH1F *back = (TH1F *)f->Get("back2");

   back->SetTitle("Influence of clipping window width on the estimated background");
   back->SetAxisRange(0, 1000);
   back->SetMaximum(7000);
   back->Draw("L");

   TSpectrum *s = new TSpectrum();

   for (i = 0; i < nbins; i++)
      source[i] = back->GetBinContent(i + 1);
   s->Background(source, nbins, 10, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kFALSE,
                 TSpectrum::kBackSmoothing3, kFALSE);
   for (i = 0; i < nbins; i++)
      d1->SetBinContent(i + 1, source[i]);
   d1->SetLineColor(kRed);
   d1->Draw("SAME L");

   for (i = 0; i < nbins; i++)
      source[i] = back->GetBinContent(i + 1);
   s->Background(source, nbins, 20, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kFALSE,
                 TSpectrum::kBackSmoothing3, kFALSE);
   for (i = 0; i < nbins; i++)
      d2->SetBinContent(i + 1, source[i]);
   d2->SetLineColor(kBlue);
   d2->Draw("SAME L");

   for (i = 0; i < nbins; i++)
      source[i] = back->GetBinContent(i + 1);
   s->Background(source, nbins, 30, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kFALSE,
                 TSpectrum::kBackSmoothing3, kFALSE);
   for (i = 0; i < nbins; i++)
      d3->SetBinContent(i + 1, source[i]);
   d3->SetLineColor(kGreen);
   d3->Draw("SAME L");

   for (i = 0; i < nbins; i++)
      source[i] = back->GetBinContent(i + 1);
   s->Background(source, nbins, 40, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kFALSE,
                 TSpectrum::kBackSmoothing3, kFALSE);
   for (i = 0; i < nbins; i++)
      d4->SetBinContent(i + 1, source[i]);
   d4->SetLineColor(kMagenta);
   d4->Draw("SAME L");
}
