#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "g4root.hh"

class MyRunAction : public G4UserRunAction
{
public:
    MyRunAction();
    ~MyRunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};
#endif

///      G4UserRunAction.hh     ///
///35 // class description:
///36 //
///37 //  This is the base class of a user's action class which defines the
///38 // user's action at the begining and the end of each run. The user can
///39 // override the following two methods but the user should not change 
///40 // any of the contents of G4Run object.
///41 //    virtual void BeginOfRunAction(const G4Run* aRun);
///42 //    virtual void EndOfRunAction(const G4Run* aRun);
///43 // The user can override the following method to instanciate his/her own
///44 // concrete Run class. G4Run has a virtual method RecordEvent, so that
///45 // the user can store any information useful to him/her with event statistics.
///46 //    virtual G4Run* GenerateRun();
///47 //  The user's concrete class derived from this class must be set to
///48 // G4RunManager via G4RunManager::SetUserAction() method.