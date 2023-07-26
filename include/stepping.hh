#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "construction.hh"
#include "event.hh"

class MySteppingAction : public G4UserSteppingAction
{
public:
    MySteppingAction(MyEventAction* eventAction);
    ~MySteppingAction();
    
    virtual void UserSteppingAction(const G4Step*);
    
private:
    MyEventAction *EventAction;
};

#endif


///31 //  G4UserSteppingAction.hh
///32 //
///33 // class description:
///34 //    This class represents actions taken place by the user at each
///35 //    end of stepping. 