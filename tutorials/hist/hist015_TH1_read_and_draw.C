/// \file
/// \ingroup tutorial_hist
/// \notebook -js
/// \preview  Read a 1-D histogram from a ROOT File and draw it.
/// We attach (or generate) the ROOT file in `$ROOTSYS/tutorials/hsimple.root`
/// or `$PWD/hsimple.root`
/// We draw one histogram in different formats.
///
/// \macro_image
/// \macro_code
///
/// \date August 2021
/// \author Rene Brun

#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"

void hist015_TH1_read_and_draw()
{
   // Fetch and open the hsimple.root File
   TFile *example = TFile::Open(gROOT->GetTutorialDir() + "/hsimple.root");

   example->ls(); // Show the file contents
   // Get the histogram from the ROOT File
   TH1 *hpx = nullptr; // pointer to base class TH1 is enough
   example->GetObject("hpx", hpx);

   TCanvas *c1 = new TCanvas("c1", "Histogram Drawing Options", 200, 10, 700, 900);
   TPad *pad1 = new TPad("pad1", "The pad with the function", 0.03, 0.62, 0.50, 0.92);
   TPad *pad2 = new TPad("pad2", "The pad with the histogram", 0.51, 0.62, 0.98, 0.92);
   TPad *pad3 = new TPad("pad3", "The pad with the histogram", 0.03, 0.02, 0.97, 0.57);
   pad1->Draw();
   pad2->Draw();
   pad3->Draw();

   // Draw a global picture title
   TPaveLabel *title = new TPaveLabel(0.1, 0.94, 0.9, 0.98, "Drawing options for one dimensional histograms");
   title->SetTextFont(52);
   title->Draw();

   // Draw histogram hpx in first pad with the default option.
   pad1->cd();
   pad1->GetFrame()->SetFillColor(18);
   hpx->SetFillColor(45);
   hpx->DrawCopy();
   TPaveLabel *label1 = new TPaveLabel(-3.5, 700, -1, 800, "Default option");
   label1->Draw();

   // Draw hpx as a lego. Clicking on the lego area will show
   // a "transparent cube" to guide you rotating the lego in real time.
   pad2->cd();
   hpx->DrawCopy("lego1");
   TPaveLabel *label2 = new TPaveLabel(-0.72, 0.74, -0.22, 0.88, "option Lego1");
   label2->Draw();
   TPaveLabel *label2a = new TPaveLabel(-0.93, -1.08, 0.25, -0.92, "Click on lego to rotate");
   label2a->Draw();

   // Draw hpx with its errors and a marker.
   pad3->cd();
   pad3->SetGridx();
   pad3->SetGridy();
   hpx->SetMarkerStyle(21);
   hpx->Draw("e1p");
   TPaveLabel *label3 = new TPaveLabel(2, 600, 3.5, 650, "option e1p");
   label3->Draw();

   // The following illustrates how to add comments using a PaveText.
   // Attributes of text/lines/boxes added to a PaveText can be modified.
   // The AddText function returns a pointer to the added object.
   TPaveText *pave = new TPaveText(-3.78, 500, -1.2, 750);
   TText *t1 = pave->AddText("You can move");
   t1->SetTextColor(4);
   t1->SetTextSize(0.05);
   pave->AddText("Title and Stats pads");
   pave->AddText("X and Y axis");
   pave->AddText("You can modify bin contents");
   pave->Draw();
   c1->Update();
}
