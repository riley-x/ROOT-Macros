/* test.cxx
 * Riley Xu -- May 18, 2023
 *
 * Simple test file creating a single histogram to test ROOT compilation works.
 */

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include <iostream>
#include <iomanip>

///////////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////////

/**
 * Modified from https://root.cern.ch/doc/v614/fillrandom_8C.html
 */
void fillrandom(std::string const & output_path)
{
    TCanvas *c1 = new TCanvas("c1","The FillRandom example",200,10,700,900);
    auto pad1 = new TPad("pad1","The pad with the function",0.05,0.50,0.95,0.95);
    auto pad2 = new TPad("pad2","The pad with the histogram",0.05,0.05,0.95,0.45);
    pad1->Draw();
    pad2->Draw();
    pad1->cd();
    gBenchmark->Start("fillrandom");
    //
    // A function (any dimension) or a formula may reference
    // an already defined formula
    //
    auto form1 = new TFormula("form1","abs(sin(x)/x)");
    auto sqroot = new TF1("sqroot","x*gaus(0) + [3]*form1",0,10);
    sqroot->SetParameters(10,4,1,20);
    pad1->SetGridx();
    pad1->SetGridy();
    pad1->GetFrame()->SetBorderMode(-1);
    pad1->GetFrame()->SetBorderSize(5);
    sqroot->SetLineColor(4);
    sqroot->SetLineWidth(6);
    sqroot->Draw();
    auto lfunction = new TPaveLabel(5,39,9.8,46,"The sqroot function");
    lfunction->Draw();
    c1->Update();
    //
    // Create a one dimensional histogram (one float per bin)
    // and fill it following the distribution in function sqroot.
    //
    pad2->cd();
    pad2->GetFrame()->SetBorderMode(-1);
    pad2->GetFrame()->SetBorderSize(5);
    auto h1f = new TH1F("h1f","Test random numbers",200,0,10);
    h1f->SetFillColor(45);
    h1f->FillRandom("sqroot",10000);
    h1f->Draw();
    c1->Update();

    c1->Print(output_path);
}

///////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////

int help()
{
    cerr << "./test output_path\n";
    cerr << "\n";
    cerr << "    [output_path]          Path to save the image to.";
    cerr << endl;
    return 1;
}


int main(int argc, char* argv[])
{
    /// Set errors to sqrt(sum w^2) instead of sqrt(n) ///
    TH1::SetDefaultSumw2();

    /// Input parsing ///
    if (argc < 2) return help();
    std::string output_path(argv[1]);

    /// Run ///
    fillrandom(output_path);
    return 0;
}


