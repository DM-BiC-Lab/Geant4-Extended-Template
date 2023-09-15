// Generally required libraries
#include  <iostream>
#include <string>

// Include Geant4 headers
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

// Include custom headers
#include "construction.hh"
#include "physics.hh"
#include "action.hh"
#include "init.hh"

using namespace std;

int main(int argc, char** argv) {

    // Initialize the project
    Project::Initialize();

    // Construct the run manager
    G4RunManager *runManager = new G4RunManager();
    
    // Initialize a detector construction, a physics list, and an
    // action initialization within the run manager. These are
    // all required for any project to be able to build successfully
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());
    runManager->SetUserInitialization(new MyActionInitialization());
    runManager->Initialize();

    // Construct a UIExecutive (ie enables the GUI)
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    // Construct a VisManager, which manages the visualizer in the GUI
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    
    // Construct a UImanager, which allows project commands to be called
    // through this source code file
    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    
    std::string command = "/control/execute ../";
    
    // If program has been specified to run automatically
    if (argc > 1 && strcmp(argv[1], "AUTOMATIC") == 0) {
    	if (argc > 2 && strcmp(argv[2], "SPECIAL") == 0) {
    	    int numberOfRuns = stoi(argv[4]);
    	    Project::autoRunNum = numberOfRuns;
    	    UImanager->ApplyCommand(command.append(argv[3]));
    	} else {
    	    // Don't show the UI, just run an action and quit
    	    int numberOfRuns = stoi(argv[2]);
            Project::autoRunNum = numberOfRuns;
            UImanager->ApplyCommand("/control/execute ../auto.mac");
        }
    } else {
        Project::autoRunNum = 0;
        // Run several project commands through the UImanager
        UImanager->ApplyCommand("/vis/open OGL");
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 0.25 -0.5");
        UImanager->ApplyCommand("/vis/drawVolume");
        UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
        UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate -1");
        UImanager->ApplyCommand("/control/execute ../UI-init.mac");
        if (argc > 1 && strcmp(argv[1], "MACRO") == 0) {
            UImanager->ApplyCommand("/control/execute ../auto.mac");
        } else if (argc > 1 && strcmp(argv[1], "SPECIAL") == 0) {
            UImanager->ApplyCommand(command.append(argv[2]));
        }
        // Otherwise, start the UI session (displays the GUI to the user)
        ui->SessionStart();
    }

    return 0;
}
