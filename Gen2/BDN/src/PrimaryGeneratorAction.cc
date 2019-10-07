#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4GeneralParticleSource.hh"

#include "G4UImanager.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),fParticleGun(0),generator(0)
{
	
//--------------------------------------------------------------------------
//Select one of these two options:

      //Option 1: G4ParticleGun (commented out by Barbara Wang on 2/13/2015):
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);

      //Option 2: G4GeneralParticleSource (For more complicated sources.  
      //Added by Barbara Wang):
	//generator  = new G4GeneralParticleSource ();

//--------------------------------------------------------------------------

	/*
	// default particle kinematic
	
	G4ParticleDefinition* particle
			= G4ParticleTable::GetParticleTable()->FindParticle("neutron");
	fParticleGun->SetParticleDefinition(particle);
	//fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	fParticleGun->SetParticleEnergy(0.5*MeV);
	fParticleGun->SetParticlePosition(G4ThreeVector(0.*m,0.*m,0.*m));
	*/
	//generator = new G4GeneralParticleSource;
	

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
//--------------------------------------------------------------------------
      //Use this line if Option 1 was selected above.  Otherwise, comment out.
	delete fParticleGun;

      //Use this line if Option 2 was selected above.  Otherwise, comment out.
	//delete generator;
//--------------------------------------------------------------------------
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	/*
	G4UImanager* UI = G4UImanager::GetUIpointer();
	G4double energy = G4UIcommand::ConvertToDouble(UI->GetCurrentValues("/gun/energy"));
	G4cout << energy << G4endl;
	*/
	//this function is called at the begining of event
	//
	//distribution uniform in solid angle
	/*
	G4double cosTheta = 2*G4UniformRand() - 1., phi = twopi*G4UniformRand();
	G4double sinTheta = std::sqrt(1. - cosTheta*cosTheta);
	G4double ux = sinTheta*std::cos(phi),
			uy = sinTheta*std::sin(phi),
			uz = cosTheta;
	
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
	*/


//--------------------------------------------------------------------------
      //Use this line if Option 1 was selected above.  Otherwise, comment out.
	fParticleGun->GeneratePrimaryVertex(anEvent);
	
      //Use this line if Option 2 was selected above.  Otherwise, comment out.
	//generator->GeneratePrimaryVertex(anEvent);
//--------------------------------------------------------------------------
}
