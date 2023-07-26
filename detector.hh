#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

// Declares the user's MySensitiveDetector derived from the public class G4VSensitiveDetector
class MySensitiveDetector : public G4VSensitiveDetector
{
// Sensitive detector constuctor and destructor   //
public:
    MySensitiveDetector(G4String);
    ~MySensitiveDetector();
    
private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    
    G4PhysicsOrderedFreeVector *quantEff;
};

#endif
