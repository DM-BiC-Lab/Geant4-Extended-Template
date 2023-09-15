#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name) {}
MySensitiveDetector::~MySensitiveDetector() {}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    // When a particle hits the detector, get its
    // tracker and et it to terminate upon hitting
    G4Track *track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);
    
    // Get the position of the particle upon entering
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    
    // The following is commented out for reference
    // G4ThreeVector posPhoton = preStepPoint->GetPosition();
    // G4cout << "Photon Position: " << posPhoton << G4endl;
    
    // Get the touchable that the particle hit, and from
    // that get the position of the touchable's volume
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();
    
    // The following is commented out for reference
    // G4int copyNum = touchable->GetCopyNumber();
    // G4cout << "Copy Number: " << copyNum << ", Position: " << posDetector << G4endl;
    
    // Get the event ID of the particle (aka the run it is a part of)
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    // Get the analysis manager and add all relevant data
    // a row of the output file
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector[0]);
    man->FillNtupleDColumn(2, posDetector[1]);
    man->FillNtupleDColumn(3, posDetector[2]);
    man->AddNtupleRow(0);
    
    // This return statement doesn't really do anything as far as I know
    return true;
}
