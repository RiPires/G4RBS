#include "construction.hh"
#include "G4PhysicalConstants.hh"


MyDetectorConstruction::MyDetectorConstruction()
{
    fMessenger = new G4GenericMessenger(this, "/detector/", "DetectorConstruction");
    
    DefineMaterial();
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterial()
{
        //  Materials  //
    G4NistManager *nist = G4NistManager::Instance();

    // Carbon Epoxy: C21H25ClO5  //
    Epoxy = new G4Material("Epoxy", 1.600*g/cm3, 4);
    Epoxy->AddElement(nist->FindOrBuildElement("C"), 21);
    Epoxy->AddElement(nist->FindOrBuildElement("H"), 25);
    Epoxy->AddElement(nist->FindOrBuildElement("Cl"), 1);
    Epoxy->AddElement(nist->FindOrBuildElement("O"), 5);
    
    //   Elements   //
    Al = nist->FindOrBuildElement("Al");
    C = nist->FindOrBuildElement("C");
    Ge = nist->FindOrBuildElement("Ge");
    Sn = nist->FindOrBuildElement("Sn");
    Si = nist->FindOrBuildElement("Si");

    
    //   Defines world material as Air  - as it's own properties  //
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    //   Defines target Holder material as Al   //
    holderMat = new G4Material("Aluminium", 2.7*g/cm3, 1);
    holderMat->AddElement(Al, 1.);
    
    //   Defines target material as Sn   //
    targetMat = new G4Material("Tin", 7.31*g/cm3, 1);
    targetMat->AddElement(Sn, 1.);
    
    // Defines detector material as Ge  //
    detMat =  new G4Material("Germanium", 5.323*g/cm3, 1);
    detMat->AddElement(Ge, 1.);

    silicon = new G4Material("Silicon", 2.329*g/cm3, 1);
    silicon->AddElement(Si, 1.);
    
    //   WHICH ENERGY???   //
    G4double energy[2] = {1.239841939*eV/0.2, 1.239841939*eV/0.9};
    
    //   Refraction indexes   //
    G4double rindexWorld[2] = {1.0, 1.0};

    //   Defines world material refraction index   //
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld);
}
///OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO///
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4double xWorld = 100*mm;//World half lenght
    G4double yWorld = 100*mm;//World half height
    G4double zWorld = 100*mm;//World half depth
           
    //   Defines WORLD volume   //
    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld); 
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "LogicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "PhysWorld", 0, false, 0, true);
    
    //   Defines Case volume for detector active volume   ///
    solidCase = new G4Tubs("SolidCase", 61.*mm, 62*mm, 40*mm, 0., 2*pi);
    logicCase = new G4LogicalVolume(solidCase, holderMat, "LogicCase");
    physCase = new G4PVPlacement(0, G4ThreeVector(0., 0., 40.*mm), logicCase, "PhysCase", logicWorld, false, 0., true);

    //   Defines cylinder for target frame hole   //
    solidHole = new G4Tubs("SolidHole", 0., 5.*mm, 1.*mm, 0., 2*pi);
    //   Defines entire solid target frame   //
    solidFrame = new G4Box("SolidFrame", 6.*mm, 15.*mm, 0.5*mm);
    //   Subtracts target holder solid hole from the entire target frame   //
    G4SubtractionSolid *subtraction = new G4SubtractionSolid("RealTargetFrame", solidFrame, solidHole);
    //   Defines subtraction logical volume   //
    logicSubtraction = new G4LogicalVolume(subtraction, holderMat, "LogicSubtraction");
    //   Defines subtraction physical volume   //
    physSubtraction = new G4PVPlacement(0, G4ThreeVector(0., 0., -50.*mm), logicSubtraction, "PhysSubtraction", logicWorld, false, 0, true);
    
    //   Defines TARGET volume   //
    solidTarget = new G4Tubs("SolidTarget", 0.*m, 5.5*mm, 100*nm, 0., 2*pi);
    logicTarget = new G4LogicalVolume(solidTarget, targetMat, "LogicTarget");
    physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., -49.5*mm), logicTarget, "PhysTarget", logicWorld, false, 0., true);
    
    //   Defines detector WINDOW volume   //
    solidWindow = new G4Tubs("SolidWindow", 0.*m, 60.*mm, 0.3*mm, 0., 2*pi);
    logicWindow = new G4LogicalVolume(solidWindow, Epoxy, "LogicWindow");
    physWindow = new G4PVPlacement(0, G4ThreeVector(0., 0., 5.*mm), logicWindow, "PhysWindow", logicWorld, false, 0., true);
    
    //   Defines Ge DETECTOR volume  //
    solidDetector = new G4Tubs("SolidDetector", 0.*m, 0.060*m, 0.013*m, 0., 2*pi);
    logicDetector = new G4LogicalVolume(solidDetector, detMat, "LogicDetector");
    physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 20.*mm), logicDetector, "PhysDetector", logicWorld, false, 0., true);
    
    ScoringVolume = logicDetector;
        
  return physWorld;
}    

//   Defines sensitive detector//
void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet); 
}
