#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(EventAction* EvAct)
:G4UserSteppingAction(),fEventAction(EvAct)
{ }

SteppingAction::~SteppingAction()
{ }

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4double EdepStep = aStep->GetTotalEnergyDeposit();
	if (EdepStep > 0.) fEventAction->addEdep(EdepStep);
	
	G4Track* aTrack = aStep->GetTrack();
	G4String pName = aTrack->GetParticleDefinition()->GetParticleName();
	G4int PID = aTrack->GetParentID();
	G4int SID = aTrack->GetCurrentStepNumber();

	G4int event_counter = 0;

	if (PID == 0 && SID == 1 && pName == "e-"){
		event_counter = 1;
		fEventAction->addEvent(event_counter);
		//G4cout << pName << G4endl;
	}
}
