#include "action.hh"
#include "generator.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::BuildForMaster() const
{   MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);}    

void MyActionInitialization::Build() const
{   MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);
    
    MyRunAction *runAction = new MyRunAction();
    SetUserAction(runAction);
    
    MyEventAction *eventAction = new MyEventAction(runAction);
    SetUserAction(eventAction);
    
    MySteppingAction *steppingAction = new MySteppingAction(eventAction);
    SetUserAction(steppingAction);}   

    // Id: G4VUserActionInitialization.hh 
    // class description:
    //
    //  This is the abstract base class for instantiating all the user action classes.
    // It has a pure virtual method Build() which is invoked by G4RunManager for
    // sequential execution and G4WorkerRunManager for multi-threaded execution.
    // The additional virtual method BuildForMaster() will be invoked from G4MTRunManager
    // for multi-threaded execution.
    //
    //  Note that these virtual methods are const. It means the user may construct
    // user action objects, but should not store the pointers of these objects as
    // data members of the derived class.
    //
    // Note for multi-threaded mode:
    //  The only action class the user may set to G4MTRunManager is a run action. It is
    // then used at the beginning and the end of a run. It may be the same class or a
    // dedicated class different from the run action instantiated for G4WorkerRunManager.