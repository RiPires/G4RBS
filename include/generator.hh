#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
// Primary particle generator constuctor and destructor   //
public:
    MyPrimaryGenerator();
    ~MyPrimaryGenerator();
    
    virtual void GeneratePrimaries(G4Event*);

private:
    G4ParticleGun *fParticleGun;
};
#endif

// $Id: G4VUserPrimaryGeneratorAction.hh 66892 2013-01-17 10:57:59Z gunter $
// class description:
//
//  This is the abstract base class of the user's mandatory action class
// for primary vertex/particle generation. This class has only one pure
// virtual method GeneratePrimaries() which is invoked from G4RunManager
// during the event loop.
//  Note that this class is NOT intended for generating primary vertex/particle
// by itself. This class should 
//  - have one or more G4VPrimaryGenerator concrete classes such as G4ParticleGun 
//  - set/change properties of generator(s)
//  - pass G4Event object so that the generator(s) can generate primaries.


// G4ParticleGun.hh class definition
//  This is a concrete class of G4VPrimaryGenerator. It shoots a particle of given type
///47 // into a given direction with either a given kinetic energy or momentum.
///48 //  The position and time of the primary particle must be set by the corresponding
///49 // set methods of G4VPrimaryGenerator base class, otherwise zero will be set.
///50 //
///51 //  The FAQ to this class is for randomizing position/direction/kinetic energy of primary
///52 // particle. But, G4ParticleGun does NOT have any way of randomization. Instead, the user's
///53 // concrete implementation of G4VUserPrimaryGeneratorAction which transmits G4Event object
///54 // to this particle gun can randomize these quantities and set to this particle gun before
///55 // invoking GeneratePrimaryVertex() method.
///56 //  Note that, even if the particle gun shoots more than one particles at one invokation of
///57 // GeneratePrimaryVertex() method, all particles have the same physical quantities. If the
///58 // user wants to shoot two particles with different momentum, position, etc., invoke
///59 // GeneratePrimaryVertex() method twice and set quantities on demand to the particle gun.



        
///66  //  G4ParticleTable Class Description
       //
///67  //   G4ParticleTable is the table of pointer to G4ParticleDefinition
///68  //   G4ParticleTable is a "singleton" (only one and staic object)
///69  //   In G4ParticleTable, each G4ParticleDefinition pointer is stored
///70  //   with its name as a key to itself. So, each  G4ParticleDefinition 
///71  //   object must have unique name for itself. 