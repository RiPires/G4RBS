#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
    EventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
    // Gets the volume where the step is occurring
    G4LogicalVolume *volume = 
    step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    
    // Gets info. on the geometry construction
    const MyDetectorConstruction *detectorConstruction = 
    static_cast<const MyDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    // Gets the scoring volume from the geometric construction
    G4LogicalVolume *ScoringVolume =    detectorConstruction->GetScoringVolume();
    
    //
    if(volume != ScoringVolume) // If the 'volume' is not the SensitiveDetector  //  
        return;                 //   do nothing                                  //
    
    //
    G4double edep = step->GetTotalEnergyDeposit(); // Else, we record the energy deposition,'edep', on the step     //
    EventAction->AddEdep(edep);                    // and add it to the total energy deposited in the event, 'Edep' //  

    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleDColumn(3, 0, edep);
    man->AddNtupleRow(3);
}