#include "PhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4SystemOfUnits.hh"

#include "G4FissLib.hh"

PhysicsList::PhysicsList()
: G4VUserPhysicsList()
{
	defaultCutValue = 0.1*mm;
	SetVerboseLevel(1);
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructParticle()
{
	ConstructBosons();
	ConstructLeptons();
	ConstructHadrons();
	G4GenericIon::GenericIonDefinition();
}

void PhysicsList::ConstructBosons()
{
	G4Gamma::GammaDefinition();
}

void PhysicsList::ConstructLeptons()
{
	G4Electron::ElectronDefinition();
	G4Positron::PositronDefinition();
}

void PhysicsList::ConstructHadrons()
{
	G4Proton::ProtonDefinition();
	G4Neutron::NeutronDefinition();
}

void PhysicsList::ConstructProcess()
{
	AddTransportation();
	ConstructEM();
	ConstructNeutronPhys();
	ConstructProtonPhys();
}

#include "G4PhysicsListHelper.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4hIonisation.hh"
#include "G4hMultipleScattering.hh"
#include "G4hBremsstrahlung.hh"
#include "G4ionIonisation.hh"

void PhysicsList::ConstructEM()
{
	G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  
	theParticleIterator->reset();
	while( (*theParticleIterator)() ){
		G4ParticleDefinition* particle = theParticleIterator->value();
		G4String particleName = particle->GetParticleName();
     
		if (particleName == "gamma") {
          
			ph->RegisterProcess(new G4PhotoElectricEffect, particle);
			ph->RegisterProcess(new G4ComptonScattering,   particle);
			ph->RegisterProcess(new G4GammaConversion,     particle);
      
		} else if (particleName == "e-") {

			ph->RegisterProcess(new G4eMultipleScattering, particle);
			ph->RegisterProcess(new G4eIonisation,         particle);
			ph->RegisterProcess(new G4eBremsstrahlung,     particle);      

		} else if (particleName == "e+") {

			ph->RegisterProcess(new G4eMultipleScattering, particle);
			ph->RegisterProcess(new G4eIonisation,         particle);
			ph->RegisterProcess(new G4eBremsstrahlung,     particle);
			ph->RegisterProcess(new G4eplusAnnihilation,   particle); 

		} else if (particleName == "proton") {
		
			ph->RegisterProcess(new G4hMultipleScattering, particle);
			ph->RegisterProcess(new G4hIonisation, particle);
			ph->RegisterProcess(new G4hBremsstrahlung,particle);
		
		} else if(particleName == "alpha" || 
			particleName == "deuteron" || particleName == "triton") {
		
			ph->RegisterProcess(new G4hMultipleScattering,particle);
			ph->RegisterProcess(new G4ionIonisation, particle);
		
		} else if (particleName == "GenericIon") {
	
			ph->RegisterProcess(new G4hMultipleScattering,particle);
			ph->RegisterProcess(new G4ionIonisation,particle);
		}
	}
}

#include "G4HadronElasticProcess.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronHPThermalScatteringData.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPThermalScattering.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4NeutronHPCapture.hh"
#include "G4HadronFissionProcess.hh"
#include "G4NeutronHPFissionData.hh"
#include "G4NeutronHPFission.hh"

void PhysicsList::ConstructNeutronPhys()
{
	G4ProcessManager* pManager = G4Neutron::Neutron()->GetProcessManager();
   
   // process: elastic
   //
   G4HadronElasticProcess* process1 = new G4HadronElasticProcess();
   pManager->AddDiscreteProcess(process1);   
   //
   // cross section data set
   G4NeutronHPElasticData* dataSet1a = new G4NeutronHPElasticData();
   G4NeutronHPThermalScatteringData* dataSet1b 
                               = new G4NeutronHPThermalScatteringData();
   process1->AddDataSet(dataSet1a);                               
   process1->AddDataSet(dataSet1b);
   //
   // models
   G4NeutronHPElastic*           model1a = new G4NeutronHPElastic();
   G4NeutronHPThermalScattering* model1b = new G4NeutronHPThermalScattering();
   model1a->SetMinEnergy(4.*eV);
   model1b->SetMaxEnergy(4.*eV);
   process1->RegisterMe(model1a);    
   process1->RegisterMe(model1b);

   // process: inelastic
   //
   G4NeutronInelasticProcess* process2 = new G4NeutronInelasticProcess();
   pManager->AddDiscreteProcess(process2);   
   //
   // cross section data set
   G4NeutronHPInelasticData* dataSet2 = new G4NeutronHPInelasticData();
   process2->AddDataSet(dataSet2);                               
   //
   // models
   G4NeutronHPInelastic* model2 = new G4NeutronHPInelastic();
   process2->RegisterMe(model2);    

   // process: nCapture   
   //
   G4HadronCaptureProcess* process3 = new G4HadronCaptureProcess();
   pManager->AddDiscreteProcess(process3);    
   //
   // cross section data set
   G4NeutronHPCaptureData* dataSet3 = new G4NeutronHPCaptureData();
   process3->AddDataSet(dataSet3);                               
   //
   // models
   G4NeutronHPCapture* model3 = new G4NeutronHPCapture();
   process3->RegisterMe(model3);
   
   // process: nFission   
   //
   G4HadronFissionProcess* process4 = new G4HadronFissionProcess();
   pManager->AddDiscreteProcess(process4);    
   //
   // cross section data set
   G4NeutronHPFissionData* dataSet4 = new G4NeutronHPFissionData();
   process4->AddDataSet(dataSet4);                               
   //
   // models
   G4NeutronHPFission* model4 = new G4NeutronHPFission();
   process4->RegisterMe(model4);

}

#include "G4ChipsElasticModel.hh"
#include "G4ChipsProtonElasticXS.hh"
#include "G4ProtonInelasticProcess.hh"
#include "G4GlauberGribovCrossSection.hh"
#include "G4CascadeInterface.hh"

void PhysicsList::ConstructProtonPhys()
{
	G4ProcessManager* pManager = G4Proton::Proton()->GetProcessManager();
   
   // process: elastic
   //
   G4HadronElasticProcess* process1 = new G4HadronElasticProcess();
   pManager->AddDiscreteProcess(process1);   
   //
   // cross section data set
   G4ChipsProtonElasticXS* dataSet1 = new G4ChipsProtonElasticXS();
   process1->AddDataSet(dataSet1);                              
   //
   // models
   G4ChipsElasticModel*           model1 = new G4ChipsElasticModel();
   process1->RegisterMe(model1);
   
   // process: inelastic
   //
   G4ProtonInelasticProcess* process2 = new G4ProtonInelasticProcess();
   pManager->AddDiscreteProcess(process2);   
   //
   // cross section data set
   G4GlauberGribovCrossSection* dataSet2 = new G4GlauberGribovCrossSection();
   process2->AddDataSet(dataSet2);                               
   //
   // models
   G4CascadeInterface* bertiniModel = new G4CascadeInterface();
   process2->RegisterMe(bertiniModel);    
   
}

/*
void PhysicsList::ConstructHadrons()
{
	G4Proton::ProtonDefinition();
	G4Neutron::NeutronDefinition();

	
	G4ParticleDefinition* particle = theParticleIterator->value();
	G4ProcessManager* pmanager = particle->GetProcessManager();
	G4String particleName = particle->GetParticleName();

	if (particleName == "neutron"){

		G4HadronFissionProcess *theFissionProcess = new G4HadronFissionProcess();
		G4FissLib* theFissionModel = new G4FissLib;
		theFissionProcess->RegisterMe(theFissionModel);
		pmanager->AddDiscreteProcess(theFissionProcess);
	}
}
*/
void PhysicsList::SetCuts()
{
	if (verboseLevel >0){
		G4cout << "PhysicsList::SetCuts:";
		G4cout << "CutLength : " << defaultCutValue/mm << " (mm)" << G4endl;
	}
     
	// set cut values for gamma at first and for e- second and next for e+,
	// because some processes for e+/e- need cut values for gamma 
	SetCutValue(defaultCutValue, "gamma");
	SetCutValue(defaultCutValue, "e-");
	SetCutValue(defaultCutValue, "e+");
}




