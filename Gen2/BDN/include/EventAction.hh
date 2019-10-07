//-----------------------------------------------------------------------
//Edits made by Barbara Wang:
//(Note: To view all lines edited, search for "bswang.")
//
//2/13/2015: Added "hits collection" ids (HCID) for the Top and Right HPGe
//           detectors.  
//5/11/2015: Added statements to properly initialize the parameter EID
//           (Electron ID) 
//-----------------------------------------------------------------------

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"

//class PrimaryGeneratorAction;

class EventAction : public G4UserEventAction
{
  public:
    //EventAction(PrimaryGeneratorAction*);
	  EventAction();
   ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
    
    void addEdep(G4double Edep)     {fTotalEnergyDeposit += Edep;};      
    G4double GetEnergyDeposit()     {return fTotalEnergyDeposit;};

	void addEvent(G4int event_counter) {EID += event_counter;};
        void InitializeEID(G4int EID_value) {EID = EID_value;};  //bswang, 5/11/2015
        
  private:
    G4double fTotalEnergyDeposit;   // Energy deposited in c6f6

	//G4int PlashitsCollID;
	G4int Left_dE_HCID;
	G4int Left_E_HCID;
	G4int Bot_dE_HCID;
	G4int Bot_E_HCID;
	G4int Top_HPGe_HCID;  //Added by bswang, 2/13/2015
	G4int Right_HPGe_HCID;  //Added by bswang, 2/13/2015

	G4int counter;
	G4int EID;

	//PrimaryGeneratorAction* fName;

};

#endif

    
