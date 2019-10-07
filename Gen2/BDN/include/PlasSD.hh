#ifndef PlasSD_h
#define PlasSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PlasHit.hh"
class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class PlasSD : public G4VSensitiveDetector
{

  public:
      PlasSD(G4String name);
      ~PlasSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);
      void clear();
      void DrawAll();
      void PrintAll();

  private:
      G4int HCID;
      PlasHitsCollection *PlashitsCollection;

  public:
};




#endif