#ifndef PlasHit_h
#define PlasHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

class PlasHit : public G4VHit
{
  public:

      PlasHit();
      ~PlasHit();
	  PlasHit(const PlasHit &right);
      const PlasHit& operator=(const PlasHit &right);
      G4int operator==(const PlasHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      void Print();

  private:
      G4int         stripNo;
      G4ThreeVector position;
      G4ThreeVector momentum;
      G4double      energy;
      G4ParticleDefinition* particle;

	  G4double edep;

	  G4double Time; // Added

  public:
	  inline void SetEdep(G4double de) { edep = de; }
      inline void AddEdep(G4double de) { edep += de; }
	  inline G4double GetEdep() const { return edep; }
      inline void SetStripNo(G4int strip)
      { stripNo=strip; }
      inline G4int GetStripNo()
      { return stripNo; }
      inline void SetPosition(G4ThreeVector pos)
      { position=pos; }
      inline G4ThreeVector GetPosition()
      { return position; }
      inline void SetMomentum(G4ThreeVector mom)
      { momentum = mom; }
      inline G4ThreeVector GetMomentum()
      { return momentum; }
	  inline void SetTime(G4double t0) // Added
	  {Time = t0;} // Added
	  inline G4double GetTime() {return Time;} //Added
      inline void SetEnergy(G4double ene)
      { energy = ene; }
      inline G4double GetEnergy()
      { return energy; }
      inline void SetParticle(G4ParticleDefinition* pdef)
      { particle = pdef; }
      inline G4ParticleDefinition* GetParticle()
      { return particle; }

};

typedef G4THitsCollection<PlasHit> PlasHitsCollection;

extern G4Allocator<PlasHit> PlasHitAllocator;

inline void* PlasHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) PlasHitAllocator.MallocSingle();
  return aHit;
}

inline void PlasHit::operator delete(void *aHit)
{
  PlasHitAllocator.FreeSingle((PlasHit*) aHit);
}

#endif