//DetectorConstruction.hh
//Author: Stephen Padgett
//
//-----------------------------------------------------------------------
//Edits made by Barbara Wang:
//(Note: To view all lines edited, search for "bswang.")
//
//2/13/2015: Created "energy deposition" histograms for the Top and Right
//           HPGe detectors.
//-----------------------------------------------------------------------


#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "Analysis.hh"

#include "G4UImanager.hh"
#include "Randomize.hh"
#include "G4PhysListFactory.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"
#include "SteppingVerbose.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc,char** argv) {
 
	//choose the Random engine
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
	// Construct the default run manager
	#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	#else
	G4VSteppingVerbose::SetInstance(new SteppingVerbose);  
	G4RunManager* runManager = new G4RunManager;
	#endif

	// set mandatory initialization classes
	runManager->SetUserInitialization(new DetectorConstruction);
	//G4PhysListFactory *physListFactory = new G4PhysListFactory();
	//G4VUserPhysicsList *physicsList = physListFactory->GetReferencePhysList("QGSP_BERT");
	//runManager->SetUserInitialization(physicsList);
	runManager->SetUserInitialization(new PhysicsList);
    
	// set user action classes
	runManager->SetUserInitialization(new ActionInitialization());

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetVerboseLevel(1);  
	analysisManager->SetFirstHistoId(1);

	G4String fileName = "BDN";
	analysisManager->OpenFile(fileName); 
    
	// Creating histograms
	
	analysisManager->CreateH1("1","Left Plastic dE",2000,0,20000);
	analysisManager->CreateH1("2","Left Plastic E",2000,0,20000);
	analysisManager->CreateH1("3","Bottom Plastic dE",2000,0,20000);
	analysisManager->CreateH1("4","Bottom Plastic E",2000,0,20000);
	analysisManager->CreateH1("5","Top HPGe",2000,0,20000);  //Added by bswang, 2/13/2015
	analysisManager->CreateH1("6","Right HPGe",2000,0,20000);  //Added by bswang, 2/13/2015

	//Initialize G4 kernel
	runManager->Initialize();
    
//These 4 lines moved here by bswang (2/13/2015)
#ifdef G4VIS_USE
     G4VisManager* visManager = new G4VisExecutive;
     visManager->Initialize();
#endif

	// get the pointer to the User Interface manager 
	G4UImanager* UI = G4UImanager::GetUIpointer();
	//UI->ApplyCommand("/tracking/verbose 1"); // Added by Ryan for debug
	
  if (argc!=1)   // batch mode  
    { 
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
	 //UI->GetCurrentValues(command);
	 //G4double energy = G4UIcommand::ConvertToDouble(UI->GetCurrentValues("/gun/energy"));
	 //G4cout << energy << G4endl;
    }
    
  else           // define visualization and UI terminal for interactive mode 
    { 
//These 4 lines commented out by bswang (2/13/2015)
//#ifdef G4VIS_USE
//     G4VisManager* visManager = new G4VisExecutive;
//     visManager->Initialize();
//#endif
     
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);      
      ui->SessionStart();
      delete ui;
#endif
     
//These 3 lines commented out by bswang (2/13/2015)
//#ifdef G4VIS_USE
//     delete visManager;
//#endif     
    }

  // job termination
  //

//These 3 lines moved here by bswang (2/13/2015)
#ifdef G4VIS_USE
     delete visManager;
#endif     

  analysisManager->Write();
	analysisManager->CloseFile();
  delete runManager;
  delete analysisManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

