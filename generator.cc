#include "generator.hh"

//   Primary particle generator constuctor and destructor   //
MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="geantino"; // What we call to this geantino particle
    G4ParticleDefinition *particle = particleTable->FindParticle("geantino"); // Sets prim .particle as GEANTINO  ///
    
    G4ThreeVector pos(0.,0.,-5.*mm); //  Position for particle gun
    G4ThreeVector mom(0.,0.,1.);     //  Momentum direction vector for prim. particle
    
    fParticleGun->SetParticlePosition(pos);          // Particle Position
    fParticleGun->SetParticleMomentumDirection(mom); // Particle Momentum Direction
    fParticleGun->SetParticleMomentum(0.*keV);       // Particle Momentum magnitude
    fParticleGun->SetParticleDefinition(particle);   // Sets particle as GEANTINO prev. deffined
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}


///   Generate primary particle as a radioactive punctual source   ///
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{    
    G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
    
    if(particle == G4Geantino::Geantino())
    {
        // Cobalt-60 source //
        //G4int Z = 27;
        //G4int A = 60;
        
        // Sb-117 source //
        G4int Z = 51;
        G4int A = 117;
        
        G4double charge = 0.;
        G4double energy = 0.;
        
        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
        
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(charge);
    }

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
///    ///   ///   ///   ///   ///   ///   ///   ///   ///   ///   ///


/*
///   *************   Generation of primary GAMMAS   ***********   ///
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{   
    G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
    if(particle == G4Geantino::Geantino())
    {   
        G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition *gamma = particleTable->FindParticle("gamma");
        fParticleGun->SetParticleMomentum(135.*MeV);
        fParticleGun->SetParticleDefinition(gamma);
    }

    fParticleGun->GeneratePrimaryVertex(anEvent);
}
///   *********************************************************   ///
*/