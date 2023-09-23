#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TPie.h>
#include <TCanvas.h>
#include <TString.h>
#include <TMath.h>
#include <TLatex.h>

void CharmedHadrons() {

    // Particle Names in latex
           TString name[10] = {"1)\\ D^{0}", "2)\\ D^{+}", "3)\\ D^{-}", "4)\\ D_{s}^{+}", "5)\\ \\Lambda_{c}^{+}", "6)\\ \\Xi^{0}_{c}", "7)\\ \\Xi^{c+}_{c}", "8)\\ \\Xi^{++}_{cc}", "9)\\ \\Xi^{+}_{cc}", "10)\\ \\Omega^{0}_{c}"};

    Double_t lifetime[10] = {410.3, 1033.0, 1033.0, 504.0, 201.5, 151.9, 453.0, 255.0, 33.0, 268.0};

    // 	Hadron Compositions, (total = 1)
    Double_t comp[10][8] = {
    //Up      Down     Charm    Strange   Anti-Up  Anti-Down  Anti-Charm  Anti-Strange 
    {0.0000,  0.0000,  0.5000,  0.0000,   0.5000,  0.0000,    0.0000,     0.0000},
    {0.0000,  0.0000,  0.5000,  0.0000,   0.0000,  0.5000,    0.0000,     0.0000},
    {0.0000,  0.5000,  0.0000,  0.0000,   0.0000,  0.0000,    0.5000,     0.0000},
    {0.0000,  0.0000,  0.5000,  0.0000,   0.0000,  0.0000,    0.0000,     0.5000},
    {0.3333,  0.3333,  0.3333,  0.0000,   0.0000,  0.0000,    0.0000,     0.0000},
    {0.0000,  0.3333,  0.3333,  0.3333,   0.0000,  0.0000,    0.0000,     0.0000},
    {0.3333,  0.0000,  0.3333,  0.3333,   0.0000,  0.0000,    0.0000,     0.0000},
    {0.3333,  0.0000,  0.6666,  0.0000,   0.0000,  0.0000,    0.0000,     0.0000},
    {0.0000,  0.3333,  0.6666,  0.0000,   0.0000,  0.0000,    0.0000,     0.0000},
    {0.0000,  0.0000,  0.3333,  0.5000,   0.0000,  0.0000,    0.0000,     0.0000}
    };

    // Quark composition labels
    TString compLabels[8] = {"Up", "Down", "#scale[1.5]{#diamond} Charm", "Strange", "Anti-Up", "Anti-Down", "#scale[1.5]{#diamond} Anti-Charm", "Anti-Strange"};

    // Colors for quark compositions
    Int_t colors[8] = {kRed, kBlue, kGreen, kOrange, kMagenta, kCyan, kYellow, kPink};

    // Creating and Diving a canvas for all the pie charts (scale = 3.7)
    TCanvas *cpie = new TCanvas("cpie", "Charmed Hadron and Their Compositions", 1480, 1110);
    cpie->Divide(4, 3);

    // Create TPie objects for each charmed hadron
    TPie *pies[10];

    // Loop over charmed hadrons
    for (Int_t i = 0; i < 10; i++) {
    
    	// Scalling Factor for the radius
    	// Radius as the function of lifetime
        Double_t radius = TMath::Sqrt(lifetime[i]) / 120.0; 

	// Setting up the pie chart
        pies[i] = new TPie("pie", name[i], 8, comp[i]);
        pies[i]->SetLabelsOffset(0.02);
        
        
        // Colors and labels for quark compositions based on composition values
        for (Int_t j = 0; j < 8; j++) {
        
            if (comp[i][j] > 0.0) {
                pies[i]->SetEntryFillColor(j, colors[j]);
                pies[i]->SetEntryLabel(j, TString::Format("%s (%.1f%%)", compLabels[j].Data(), comp[i][j] * 100.0));
                
            } else {
            
                // If composition is 0.00, color to white and set empty label
                pies[i]->SetEntryFillColor(j, kWhite);
                pies[i]->SetEntryLabel(j, "");
            }
        }
        
	// Setting attributes: x , y coordinate on the canvas 
	// Setting the radius for each of the pie chart
        pies[i]->SetCircle(0.565, 0.42, radius);

    }

    // Place pie charts on the canvas
    for (Int_t i = 0; i < 10; i++) {
        cpie->cd(i + 1);
        
        // Pad attributes
        TPad *pad = new TPad("pad", "pad", 0, 0, 1, 1, 11, 2 , -1);
        pad->Draw();
        pad->cd();
        
        pies[i]->Draw("> nol");

        // Add text with lifetime information for the particle using LaTeX
        TLatex *latex = new TLatex(0.525, 0.9, Form("#bf{#it{Lifetime: %.2f x 10^{-15} s}}", lifetime[i]));
        latex->SetTextAlign(23);
        latex->SetTextSize(0.05);
        latex->Draw();
        
    }

    // Save the canvas as an image
    cpie->SaveAs("charmed_hadrons.png");
}
