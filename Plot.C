#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TH2.h"
#include <cmath>
using namespace std;

void Plot(){

    TFile *InputTFile = TFile::Open("add.root");
    
    TTree *ScoringTTRee = InputTFile->Get<TTree>("Scoring");

    int variable;
    ScoringTTRee->SetBranchAddress("Edep", &variable);

    for (int iEntry = 0; ScoringTTRee->LoadTree(iEntry) >= 0; ++iEntry) {
   // Load the data for the given tree entry
        ScoringTTRee->GetEntry(iEntry);

   // Now, `variable` is set to the value of the branch
   // "branchName" in tree entry `iEntry`
   printf("%d\n", variable);
}

}
