#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4SubtractionSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;

const G4int MaxCentElec = 4;
const G4int MaxEndElec = 8;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();
     
    G4VPhysicalVolume* Construct();

	G4double GetWorldSizeX()           {return WorldSizeX;};

	private:
	G4double	 WorldSizeX;

	G4SubtractionSolid*	solidCentElec[MaxCentElec];
	G4LogicalVolume*	logicCentElec[MaxCentElec];
	G4VPhysicalVolume*	physiCentElec[MaxCentElec];

	G4SubtractionSolid*	solidEndElec[MaxEndElec];
	G4LogicalVolume*	logicEndElec[MaxEndElec];
	G4VPhysicalVolume*	physiEndElec[MaxEndElec];
};

#endif

