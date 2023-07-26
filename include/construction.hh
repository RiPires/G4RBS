#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4UImanager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4GenericMessenger.hh"
#include "G4SubtractionSolid.hh"

#include "detector.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();
    
    G4LogicalVolume *GetScoringVolume() const { return ScoringVolume;}
    
    virtual G4VPhysicalVolume *Construct();
    virtual void ConstructSDandField();

     
    
private:
    
    //G4double *xWorld, *yWorld, *zWorld;
    G4Box *solidWorld, *solidFrame;
    G4Tubs *solidHole, *solidHolder, *solidTarget, *solidWindow, *solidDetector;
    G4LogicalVolume  *logicTarget, *logicSubtraction, *logicWorld, *logicWindow, *logicDetector;
    G4VPhysicalVolume *physHolder, *physTarget, *physSubtraction, *physWorld, *physWindow, *physDetector;
    
    G4GenericMessenger *fMessenger;
    
    G4Material *holderMat, *targetMat, *worldMat, *detMat;
    G4Element *Al, *Sn, *Si;
    
    void DefineMaterial();
    
    G4LogicalVolume *ScoringVolume;
    
};

#endif



