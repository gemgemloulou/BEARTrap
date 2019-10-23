//-----------------------------------------------------------------------
//Edits made by Barbara Wang:
//(Note: To view all lines edited, search for "bswang.")
//
//5/11/2015: Added statements to properly initialize the parameter EID
//           (Electron ID) 
//-----------------------------------------------------------------------

#include "RunAction.hh"
#include "EventAction.hh"  //bswang (5/11/2015)

#include "G4Run.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//RunAction::RunAction() //Both lines commented out by bswang (5/11/2015)
// : G4UserRunAction()  
RunAction::RunAction(EventAction* EvAct)  //bswang (5/11/2015)
 : G4UserRunAction(),fEventAction(EvAct)  
{/*
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->SetVerboseLevel(1);  
	analysisManager->SetFirstHistoId(1);
    
	// Creating histograms
	
	analysisManager->CreateH1("1","energy (MeV) deposited in He3",10000,0.,10.);
	analysisManager->CreateH1("2","Die-away time in He3",100000,0.,0.001);
	analysisManager->CreateH1("3","Die-away time in He3 with energy cut",100000,0.,0.001);
	*/
}

RunAction::~RunAction()
{
   //delete G4AnalysisManager::Instance();
}


//void RunAction::BeginOfRunAction(const G4Run*)  //commented out by bswang (5/11/2015)
void RunAction::BeginOfRunAction(const G4Run* aRun)  //bswang (5/11/2015)
{
        //bswang (5/11/2015):
        G4int runnum = aRun->GetRunID();
        if((runnum+1)%10000==0){
	  G4cout << "Run ID = " << runnum << G4endl;
	  G4cout.flush();
	}
        if (runnum == 0)
          {
          G4int initEID = 0; 
          fEventAction->InitializeEID(initEID); 
          }


	// save Rndm status
	//G4RunManager::GetRunManager()->SetRandomNumberStore(true);
	//if (isMaster) G4Random::showEngineStatus();

  /*
	// Get analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	// Open an output file
	//
	G4String fileName = "DDAA";
	analysisManager->OpenFile(fileName);    
	*/

}


void RunAction::EndOfRunAction(const G4Run*)
{  
	// show Rndm status
	//if (isMaster) G4Random::showEngineStatus();         
	/*
	//save histograms      
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
	*/
}
