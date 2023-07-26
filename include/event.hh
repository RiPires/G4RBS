#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "g4root.hh"
#include "run.hh"

class MyEventAction : public G4UserEventAction
{
    public:
        MyEventAction(MyRunAction*);
        ~MyEventAction();
    
        virtual void BeginOfEventAction(const G4Event*);
        virtual void EndOfEventAction(const G4Event*);

        void AddEdep(G4double edep) {Edep += edep;}
    
    private:
        G4double Edep;
    
};
#endif

///      G4UserEventAction.hh        ///
///38 // class description:
///39 //
///40 //  This is the base class of one of the user's optional action classes.
///41 // The two methods BeginOfEventAction() and EndOfEventAction() are invoked
///42 // at the beginning and the end of one event processing. These methods are
///43 // invoked by G4EventManager.
///44 //  Be aware that BeginOfEventAction() is invoked when a G4Event object is
///45 // sent to G4EventManager. Thus the primary vertexes/particles have already
///46 // been made by the primary generator. In case the user wants to do something
///47 // before generating primaries (i.e., store random number status), do it in
///48 // the G4VUserPrimaryGeneratorAction concrete class.