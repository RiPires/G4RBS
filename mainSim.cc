#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"
//#include "detector.hh"

int main(int argc, char** argv)
{
    // Program starts with no user's interface
    G4UIExecutive *ui = 0;

    // Checks for MultiThreading mode
    #ifdef G4MULTITHREADED
        G4MTRunManager * runManager = new G4MTRunManager();
    #else
        G4RunManager *runManager = new G4RunManager();
    #endif
    
    // Initializes geometry Construction, Physics' lists and User Actions
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    
    // Setting User's Interface on
    if(argc == 1)
    {   ui = new G4UIExecutive(argc, argv);   }
    
    // Initializes Visual Manager
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    // Pointer to Users' Interface manager ??
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    
    // Checks for user's interface
    // applies visual commands in "vis.mac" and starts session, if set on
    if(ui)
    {   UImanager->ApplyCommand("/control/execute vis.mac");        
        ui->SessionStart();    }
    // runs commands writen in a file "fileName", or runs command "fileName" from console, if set off
    else
    {   G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);    }
    
    return 0; 
}