#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class PhysicsList: public G4VUserPhysicsList
{
	public:
		PhysicsList();
		~PhysicsList();

	protected:
		// Construct particle and physics
		virtual void ConstructParticle();
		virtual void ConstructProcess();
 
		virtual void SetCuts();
    
	protected:
		// these methods Construct particles 
		void ConstructBosons();
		void ConstructLeptons();
		void ConstructHadrons();

	protected:
		// these methods Construct physics processes and register them
		//void ConstructGeneral();
		void ConstructEM();
		void ConstructNeutronPhys();
		void ConstructProtonPhys();
    
};

#endif



