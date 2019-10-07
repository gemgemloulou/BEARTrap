//-----------------------------------------------------------------------
//Edits made by Barbara Wang:
//(Note: To view all lines edited, search for "bswang.")
//
//2/13/2015: Added statements to determine the total energy deposited in
//           the Top and Right HPGe's during each event and write the
//           energy to an output file/histogram.
//-----------------------------------------------------------------------

#include "EventAction.hh"
#include "Analysis.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"

#include "PlasHit.hh"

#include <iostream>
#include <fstream>


using namespace std;

ofstream outputFile("GEANT4_output.txt");

//EventAction::EventAction(PrimaryGeneratorAction* name)
EventAction::EventAction()
:G4UserEventAction(),
 fTotalEnergyDeposit(0.)
 // fTotalEnergyDeposit(0.), fName(name)
{ 
	//PlashitsCollID = -1;
	Left_dE_HCID = -1;
	Left_E_HCID = -1;
	Bot_dE_HCID = -1;
	Bot_E_HCID = -1;
	Top_HPGe_HCID = -1;  //Added by bswang, 2/13/2015
	Right_HPGe_HCID = -1;  //Added by bswang, 2/13/2015

	counter = 0;

	//G4double Ekin = fName->GetParticleGun()->GetParticleEnergy();

	//outputFile << "DecayCounter, " << "Top MCP, " << "Right MCP, " << "left dE, " << "left E, "<< "bottom dE, " << "bottom E\n" << endl;
	outputFile << "DecayCounter, " << "Top MCP, " << "Right MCP, " << "left dE, " << "left E, "<< "bottom dE, " << "bottom E, " << "Top HPGe, " <<"Right HPGe\n" << endl;  //Edited by bswang, 2/13/2015
}

EventAction::~EventAction()
{ 
}

void EventAction::BeginOfEventAction( const G4Event* evt)
{ 

//Added by bswang (2/13/2015)---------------------------------------

 //Print out event number:
 //G4int evtNb = evt->GetEventID();
    //G4cout << "\n---> Begin of event: " << evtNb << G4endl;

//------------------------------------------------------------------------

 //initializations   
 fTotalEnergyDeposit = 0.;
 //G4String line;
 //G4int id;
	
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	if (Left_dE_HCID<0){
		Left_dE_HCID = SDman->GetCollectionID("left_dE");
	}
	if (Left_E_HCID<0){
		Left_E_HCID = SDman->GetCollectionID("left_E");
	}
	if (Bot_dE_HCID<0){
		Bot_dE_HCID = SDman->GetCollectionID("bot_dE");
	}
	if (Bot_E_HCID<0){
		Bot_E_HCID = SDman->GetCollectionID("bot_E");
	}
	if (Top_HPGe_HCID<0){
		Top_HPGe_HCID = SDman->GetCollectionID("top_HPGe");
	}  //Added by bswang, 2/13/2015
	if (Right_HPGe_HCID<0){
		Right_HPGe_HCID = SDman->GetCollectionID("right_HPGe");
	}  //Added by bswang, 2/13/2015

	/*
	ifstream inputFile("gamma_geant_input.txt");
	if (inputFile.is_open()){
		while (getline (inputFile,line))
		{
			if (sscanf(line, "# %d", &id)){

			//G4cout << line << "\n" << G4endl;
			G4cout << id << G4endl;
			}
		}
	}
	*/
}

void EventAction::EndOfEventAction( const G4Event* evt)
{
	G4double l_dE = 0.;
	G4double l_E = 0.;
	G4double b_dE = 0.;
	G4double b_E = 0.;
	G4double t_HPGe = 0.;  //Added by bswang, 2/13/2015
	G4double r_HPGe = 0.;  //Added by bswang, 2/13/2015

	//if(Left_dE_HCID<0 && Left_E_HCID<0 && Bot_dE_HCID<0 && Bot_E_HCID<0) return;
	if(Left_dE_HCID<0 && Left_E_HCID<0 && Bot_dE_HCID<0 && Bot_E_HCID<0 && Top_HPGe_HCID<0 && Right_HPGe_HCID<0) return;  //Edited by bswang, 2/13/2015

	G4HCofThisEvent * PlasHCE = evt->GetHCofThisEvent();
	PlasHitsCollection* Left_dE_HC = 0;
	PlasHitsCollection* Left_E_HC = 0;
	PlasHitsCollection* Bot_dE_HC = 0;
	PlasHitsCollection* Bot_E_HC = 0;
	PlasHitsCollection* Top_HPGe_HC = 0;  //Added by bswang, 2/13/2015
	PlasHitsCollection* Right_HPGe_HC = 0;  //Added by bswang, 2/13/2015

	if(PlasHCE){
		Left_dE_HC = (PlasHitsCollection*)(PlasHCE->GetHC(Left_dE_HCID));
		Left_E_HC = (PlasHitsCollection*)(PlasHCE->GetHC(Left_E_HCID));
		Bot_dE_HC = (PlasHitsCollection*)(PlasHCE->GetHC(Bot_dE_HCID));
		Bot_E_HC = (PlasHitsCollection*)(PlasHCE->GetHC(Bot_E_HCID));
		Top_HPGe_HC = (PlasHitsCollection*)(PlasHCE->GetHC(Top_HPGe_HCID));  //Added by bswang, 2/13/2015
		Right_HPGe_HC = (PlasHitsCollection*)(PlasHCE->GetHC(Right_HPGe_HCID));  //Added by bswang, 2/13/2015
	}

	if (Left_dE_HC){
		G4double l_dE_totalE = 0;
		int n_hit = Left_dE_HC->entries();
		
		for ( int i = 0 ; i < n_hit; i++){

			l_dE_totalE += (*Left_dE_HC)[i]->GetEdep();
			
		}
		l_dE = l_dE_totalE;
	}

	if (Left_E_HC){
		G4double l_E_totalE = 0;
		int n_hit = Left_E_HC->entries();
		
		for ( int i = 0 ; i < n_hit; i++){

			l_E_totalE += (*Left_E_HC)[i]->GetEdep();
			
		}
		l_E = l_E_totalE;
	}

	if (Bot_dE_HC){
		G4double b_dE_totalE = 0;
		int n_hit = Bot_dE_HC->entries();
		
		for ( int i = 0 ; i < n_hit; i++){

			b_dE_totalE += (*Bot_dE_HC)[i]->GetEdep();
			
		}
		b_dE = b_dE_totalE;
	}

	if (Bot_E_HC){
		G4double b_E_totalE = 0;
		int n_hit = Bot_E_HC->entries();
		
		for ( int i = 0 ; i < n_hit; i++){

			b_E_totalE += (*Bot_E_HC)[i]->GetEdep();
			
		}
		b_E = b_E_totalE;
	}

	if (Top_HPGe_HC){
		G4double t_HPGe_totalE = 0;
		int n_hit = Top_HPGe_HC->entries();
		
		for ( int i = 0 ; i < n_hit; i++){

			t_HPGe_totalE += (*Top_HPGe_HC)[i]->GetEdep();
			
		}
		t_HPGe = t_HPGe_totalE;
	}  //Added by bswang, 2/13/2015

	if (Right_HPGe_HC){
		G4double r_HPGe_totalE = 0;
		int n_hit = Right_HPGe_HC->entries();
		
		for ( int i = 0 ; i < n_hit; i++){

			r_HPGe_totalE += (*Right_HPGe_HC)[i]->GetEdep();
			
		}
		r_HPGe = r_HPGe_totalE;
	}  //Added by bswang, 2/13/2015

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	if (l_dE>0.0){
	analysisManager->FillH1(1, l_dE/keV);
	}

	if (l_E>0.0){
		analysisManager->FillH1(2, l_E/keV);
	}

	if (b_dE>0.0){
	analysisManager->FillH1(3, b_dE/keV);
	}

	if (b_E>0.0){
		analysisManager->FillH1(4, b_E/keV);
	}

	if (t_HPGe>0.0){
		analysisManager->FillH1(5, t_HPGe/keV);
	}  //Added by bswang, 2/13/2015

	if (r_HPGe>0.0){
		analysisManager->FillH1(6, r_HPGe/keV);
	}  //Added by bswang, 2/13/2015
	counter++;

	if(EID%50000 == 0) G4cout << EID << G4endl;
	
	//outputFile << EID << ", 0, 0, " << l_dE/keV << ", " << l_E/keV << ", " << b_dE/keV << ", " << b_E/keV << endl;
	outputFile << EID << ", 0, 0, " << l_dE/keV << ", " << l_E/keV << ", " << b_dE/keV << ", " << b_E/keV << ", " << t_HPGe/keV << ", " << r_HPGe/keV << endl;  //Edited by bswang, 2/13/2015
}
