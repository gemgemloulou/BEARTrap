#include "PlasHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4ios.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"

G4Allocator<PlasHit> PlasHitAllocator;

PlasHit::PlasHit()
{;}

PlasHit::~PlasHit()
{;}

PlasHit::PlasHit(const PlasHit& right):G4VHit(){
	edep = right.edep;
}

const PlasHit& PlasHit::operator=(const PlasHit& right){
	edep = right.edep;
	return *this;
}

//G4int He3Hit::operator==(const He3Hit &right) const
//{
//  return (this==&right) ? 1 : 0;
//}

void PlasHit::Draw()
{
 /* G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(position);
    circle.SetScreenSize(10.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(0.,0.,1.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
  */
}

void PlasHit::Print()
{;}


