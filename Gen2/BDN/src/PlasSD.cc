#include "PlasSD.hh"
#include "PlasHit.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"

PlasSD::PlasSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname=name);
  //collectionName.insert(HCname="PlashitsCollection");

  HCID = -1;//needed here (not static int) for more than one SD
}

PlasSD::~PlasSD()
{;}

void PlasSD::Initialize(G4HCofThisEvent* HCE)
{

  PlashitsCollection = new PlasHitsCollection
                      (SensitiveDetectorName,collectionName[0]); 
  //static G4int HCID = -1;
  if(HCID<0)
  { HCID = GetCollectionID(0); }
  HCE->AddHitsCollection(HCID,PlashitsCollection);
  
}

G4bool PlasSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();

  G4StepPoint* preStep = aStep->GetPreStepPoint();
  G4TouchableHistory* touchable = (G4TouchableHistory*)(preStep->GetTouchable());

  // Ensure counting incoming tracks only.
  //if ( preStep->GetStepStatus() == fGeomBoundary ){
    PlasHit* newHit = new PlasHit();
	newHit->SetEdep(edep);
    newHit->SetStripNo(  touchable->GetReplicaNumber(0) );
    newHit->SetPosition( aStep->GetPreStepPoint()->GetPosition() );
    newHit->SetMomentum( aStep->GetPreStepPoint()->GetMomentum() );
    newHit->SetEnergy( aStep->GetPreStepPoint()->GetTotalEnergy() );
    newHit->SetParticle( aStep->GetTrack()->GetDefinition() );
    PlashitsCollection->insert( newHit );
	newHit->SetTime(aStep->GetTrack()->GetGlobalTime());
  //}
  return true;
}

void PlasSD::EndOfEvent(G4HCofThisEvent*)
{;}

void PlasSD::clear()
{;} 

void PlasSD::DrawAll()
{;} 

void PlasSD::PrintAll()
{;} 