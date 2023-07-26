#include "detector.hh"

// Sensitive detector constuctor and destructor   //
MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    quantEff = new G4PhysicsOrderedFreeVector();
    
    std::ifstream datafile;
    datafile.open("hpge_eff.dat");
    
    while(1)
    {   G4double photonEnergy, qEff;
        datafile >> photonEnergy >> qEff;
        
        if(datafile.eof())
            break;
        
        ///G4cout << photonEnergy << "\t" << qEff << G4endl;
        
        quantEff->InsertValues(photonEnergy, qEff);
    }
    
    datafile.close();
    
    quantEff->SetSpline(false);
}

MySensitiveDetector::~MySensitiveDetector()
{}

//   Creates a Hit when a step takes place in a definded sensitive logical detector
// in a user sensitive detector function called ProcessHits(...)
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{   G4Track *track = aStep->GetTrack();// Gets particle info. in a step   ////////////////////
    ///track->SetTrackStatus(fStopAndKill);// ?????? fStopAndKill: O que é que isto FAZ ??????
    
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();   // Info. no início do passo
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint(); // Info. no fim do passo
    
    G4ThreeVector posPhoton = preStepPoint->GetPosition();  // Posição no início do passo
    G4ThreeVector momPhoton = preStepPoint->GetMomentum();  // Momento no início do passo
    
    G4double cdo /*[nm]*/ = (1.239841939*eV/momPhoton.mag())*1E+03;//Converte o momento em comprtimento de onda
    G4double photonEnergy = momPhoton.mag();                // Magnitude do momento do fotão  
                                                    //???? Porque é que é a energia????? 
    ///G4cout << "Photon position: " << posPhoton << G4endl;//Prints photon position//////////
    
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable(); //Gets detector info. in a step   ///
    
    G4int copynr = touchable->GetCopyNumber();
    ///G4cout << "Copy number = " << copynr << G4endl;
    
    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();
    
    ///G4cout << "Detector position = " << posDetector << G4endl;  ////////////////////////////////////////////////                                            
    

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleIColumn(0, 0, evt);
    man->FillNtupleDColumn(0, 1, posPhoton[0]);
    man->FillNtupleDColumn(0, 2, posPhoton[1]);
    man->FillNtupleDColumn(0, 3, posPhoton[2]);
    man->FillNtupleDColumn(0, 4, cdo);
    man->FillNtupleDColumn(0, 5, photonEnergy);
    man->AddNtupleRow(0);
    
    if(G4UniformRand() < quantEff->Value(photonEnergy))  /// verificar isto !!!!!!
    {
    man->FillNtupleIColumn(1, 0, evt);
    man->FillNtupleDColumn(1, 1, posDetector[0]);
    man->FillNtupleDColumn(1, 2, posDetector[1]);
    man->FillNtupleDColumn(1, 3, posDetector[2]);
    man->AddNtupleRow(1);
    }    

    return true; //Because it's a Boolean, ProcessHits function expects a return
                // better to be True
}


/*
00084   protected: // with description
00085       virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist) = 0;
00086       //  The user MUST implement this method for generating hit(s) using the 
00087       // information of G4Step object. Note that the volume and the position
00088       // information is kept in PreStepPoint of G4Step.
00089       //  Be aware that this method is a protected method and it sill be invoked 
00090       // by Hit() method of Base class after Readout geometry associated to the
00091       // sensitive detector is handled.
00092       //  "ROhist" will be given only is a Readout geometry is defined to this
00093       // sensitive detector. The G4TouchableHistory object of the tracking geometry
00094       // is stored in the PreStepPoint object of G4Step.*/