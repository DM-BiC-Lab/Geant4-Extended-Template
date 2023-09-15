#include "run.hh"

MyRunAction::MyRunAction() {

}

MyRunAction::~MyRunAction() {

}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    // At the beginning of a run, get the analysis manager and
    // Open a file with a specified N-tuple within it
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    
    man->OpenFile("output_"  + to_string(Project::autoRunNum) + ".csv");
    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->FinishNtuple(0);
    
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    // At the end of a run, get the analyssi manager,
    // write to the previously opened file, and close it
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->Write();
    man->CloseFile();
}
