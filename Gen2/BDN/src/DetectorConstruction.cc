//-----------------------------------------------------------------------
//Edits made by Barbara Wang:
//(Note: To view all lines edited, search for "bswang.")
//
//12/18/2014: Moved right MCP from -z to +z.  
//12/18/2014: Moved left dE-E detector from +z to -z.
//12/18/2014: Changed locations of the four triangular frame rails.
//12/21/2014 - 12/22/2014: Changed thicknesses of Kapton and Al foils in both dE-E detectors.
//12/22/2014: Changed radius of Mylar foil in both dE-E detectors.
//12/21/2014 - 12/22/2014: Adjusted locations of all dE-E detector components.
//2/13/2015: Added Top and Right HPGe detectors.
//2/13/2015: Added re-entrant ports in front of Top and Right HPGe.
//2/13/2015: Added "sensitive detector" commands for Top and Right HPGe.
//4/2/2015: Distance between front of right-HPGe crystal and center of trap = 103 mm 
//4/2/2015: Right-HPGe outer-dead-layer thickness = 0.7 mm + 0.25 mm
//4/2/2015: Added 1-mm-thick ceramic plate behind each MCP
//4/2/2015: Set MCP glass density to 2.5 g/cm3
//4/2/2015: Added 0.205-inch-thick ceramic base plate behind each 1-mm-thick ceramic plate. 
//5/27/2015: Changed dimensions of solidSecondShieldBox and solidSecondShieldWindow
//6/7/2016: Changed the locations of physiSecondShield_T,B,L,R
//6/7/2016: Changed the dimensions of solidSecondShieldWindow from 48x48 mm2 back to 44x44 mm2
//-----------------------------------------------------------------------


#include "DetectorConstruction.hh"

#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"

#include "G4SDManager.hh"
#include "PlasSD.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
	static const G4double inch = 2.54*cm;
	G4NistManager* manager = G4NistManager::Instance();
manager->SetVerbose(0);

G4double a, z;
G4double density, fractionmass;  
G4int ncomponents, natoms;

G4Element* C = new G4Element("Carbon"  ,"C" , z= 6., a= 12.01*g/mole);
G4Element* Na = new G4Element("Sodium"   ,"Na", z=11., a=  22.98977*g/mole);
G4Element* Pb = new G4Element("Lead", "Pb", z=82., a=207.19*g/mole);
G4Element* K = new G4Element("Potassium", "K", z=19., a=39.0983*g/mole);
G4Element* Ba = new G4Element("Barium", "Ba", z=56., a=137.327*g/mole);
G4Element* As = new G4Element("Arsenic", "As", z=33., a=74.9216*g/mole);
G4Element* Ti = new G4Element("Titanium", "Ti", z=22., a=47.467*g/mole);
G4Element* Al = new G4Element("Aluminum", "Al", z=13., a=26.98*g/mole);
G4Element* H  = manager->FindOrBuildElement(1);
   G4Element* N  = manager->FindOrBuildElement(7);//added Nitrogen
G4Element* O  = manager->FindOrBuildElement(8);
G4Element* Bi = manager->FindOrBuildElement(83);
G4Element* Ge = manager->FindOrBuildElement(32);
G4Element* Si = manager->FindOrBuildElement(14);
G4Element* I  = manager->FindOrBuildElement(53);
G4Element* Cs = manager->FindOrBuildElement(55);
G4Element* Be = manager->FindOrBuildElement("Be");
G4Element* Rb = manager->FindOrBuildElement("Rb");
G4Element* Fe = manager->FindOrBuildElement("Fe");
G4Element* Cr = manager->FindOrBuildElement("Cr");
G4Element* Ni = manager->FindOrBuildElement("Ni");
   G4Element* Cu = manager->FindOrBuildElement("Cu");//new for electron source

G4Material* Scintillator = 
new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
Scintillator->AddElement(C, natoms=9);
Scintillator->AddElement(H, natoms=10);

//Scintillator->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

G4Material* Germanium =
new G4Material("Germanium", density= 5.3*g/cm3, ncomponents=1);
Germanium->AddElement(Ge, natoms=1);

G4Material* Alumina =
new G4Material("Alumina", density= 3.95*g/cm3, ncomponents=2);
Alumina->AddElement(Al, natoms=2);
Alumina->AddElement(O, natoms=3);

G4Material* Delrin =
new G4Material("Delrin", density= 1.51*g/cm3, ncomponents=3);
Delrin->AddElement(C, natoms=6);
Delrin->AddElement(H, natoms=10);
Delrin->AddElement(O, natoms=4);

G4Material* BGO = 
new G4Material("BGO", density= 7.10*g/cm3, ncomponents=3);
BGO->AddElement(O , natoms=12);
BGO->AddElement(Ge, natoms= 3);
BGO->AddElement(Bi, natoms= 4);

G4Material* CsI = 
new G4Material("CsI", density= 4.534*g/cm3, ncomponents=2);
CsI->AddElement(Cs, natoms=1);
CsI->AddElement(I , natoms=1);

G4Material* NaI = 
new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
NaI->AddElement(Na, natoms=1);
NaI->AddElement(I , natoms=1);

G4Material* Lead =
new G4Material("Lead", density= 11.34*g/cm3, ncomponents=1);
Lead->AddElement(Pb, natoms=1);

G4Material* Silicon = 
new G4Material("Silicon", density= 2.330*g/cm3, ncomponents=1);
Silicon->AddElement(Si, natoms=1);

G4Material* Steel = new G4Material("Steel", density= 7.93*g/cm3, ncomponents=3);
Steel->AddElement(Ni, fractionmass=0.11);
Steel->AddElement(Cr, fractionmass=0.18);
Steel->AddElement(Fe, fractionmass=0.71);

G4Material* Beryllium = 
new G4Material("Beryllium", density= 1.850*g/cm3, ncomponents=1);
Beryllium->AddElement(Be, natoms=1);

G4Material* Titanium =
new G4Material("Titanium", density= 4.540*g/cm3, ncomponents=1);
Titanium->AddElement(Ti, natoms=1);

G4Material* Aluminum =
new G4Material("Aluminum", density= 2.7*g/cm3, ncomponents=1);
Aluminum->AddElement(Al, natoms=1);

G4Material* Mylar =
new G4Material("Mylar", density= 1.39*g/cm3, ncomponents=3);
Mylar->AddElement(C, fractionmass=0.625);
Mylar->AddElement(H, fractionmass=0.042);
Mylar->AddElement(O, fractionmass=0.333);

//Use density that reproduces gamma attenuation through MCP seen in calibration
//measurement taken on Feb. 2013.
G4Material* MCPglass =
//new G4Material("MCPglass", density= 1.6*g/cm3, ncomponents=9);//density was 4.0g/cm^3, try 1.6 because holes make it less dense
//new G4Material("MCPglass", density= 2.0*g/cm3, ncomponents=9);
new G4Material("MCPglass", density= 2.5*g/cm3, ncomponents=9);
MCPglass->AddElement(Pb, fractionmass=0.478);
MCPglass->AddElement(O, fractionmass=0.258);
MCPglass->AddElement(Si, fractionmass=0.182);
MCPglass->AddElement(K, fractionmass=0.042);
MCPglass->AddElement(Rb, fractionmass=0.018);
MCPglass->AddElement(Ba, fractionmass=0.013);
MCPglass->AddElement(As, fractionmass=0.004);
MCPglass->AddElement(Cs, fractionmass=0.003);
MCPglass->AddElement(Na, fractionmass=0.002);
   
   G4Material* Kapton =
   new G4Material("Kapton", density=1.42*g/cm3, ncomponents=4);//added Kapton material
   Kapton->AddElement(H, fractionmass=0.026362);
   Kapton->AddElement(C, fractionmass=0.691133);
Kapton->AddElement(N, fractionmass=0.073270);
   Kapton->AddElement(O, fractionmass=0.209235);
   
   G4Material* pmma =
   new G4Material("pmma", density=1.18*g/cm3, ncomponents=3);//for the light guide
   pmma->AddElement(C, natoms=5);
   pmma->AddElement(H, natoms=8);
   pmma->AddElement(O, natoms=2);
   
   G4Material* ceramic =
   new G4Material("ceramic", density=3.95*g/cm3, ncomponents=2);//ceramic braces
   ceramic->AddElement(Al, natoms=2);
   ceramic->AddElement(O, natoms=3);
   
   G4Material* copper =
   new G4Material("copper", density=8.96*g/cm3,ncomponents=1);
   copper->AddElement(Cu, natoms=1);
   
   
// Rotation matrices===================================================

G4RotationMatrix* rm45 = new G4RotationMatrix();
rm45->rotateX(45.*deg);

G4RotationMatrix* rm315 = new G4RotationMatrix();
rm315->rotateX(315.*deg);

G4RotationMatrix* rm225 = new G4RotationMatrix();
rm225->rotateX(225.*deg);

G4RotationMatrix* rm135 = new G4RotationMatrix();
rm135->rotateX(135.*deg);

G4RotationMatrix* rm90 = new G4RotationMatrix();
rm90->rotateX(90.*deg);

G4RotationMatrix* rm180 = new G4RotationMatrix();
rm180->rotateX(180.*deg);

G4RotationMatrix* rm270 = new G4RotationMatrix();
rm270->rotateX(270.*deg);

G4RotationMatrix* rmy90 = new G4RotationMatrix();
rmy90->rotateY(90.*deg);

G4RotationMatrix* rmy135 = new G4RotationMatrix();
rmy135->rotateY(135.*deg);

G4RotationMatrix* rmz90 = new G4RotationMatrix();
rmz90->rotateZ(90.*deg);

G4RotationMatrix* rmz180 = new G4RotationMatrix();
rmz180->rotateZ(180.*deg);

G4RotationMatrix* rmz270 = new G4RotationMatrix();
rmz270->rotateZ(270.*deg);
   
   //newer rotation matrices, to go around more than one axis
   G4RotationMatrix* rm45rmy180 = new G4RotationMatrix();
rm45rmy180->rotateX(45.*deg);
   rm45rmy180->rotateY(180.*deg);
   
   G4RotationMatrix* rm315rmy180 = new G4RotationMatrix();
rm315rmy180->rotateX(315.*deg);
   rm315rmy180->rotateY(180.*deg);
   
   G4RotationMatrix* rm225rmy180 = new G4RotationMatrix();
rm225rmy180->rotateX(225.*deg);
   rm225rmy180->rotateY(180.*deg);
   
   G4RotationMatrix* rm135rmy180 = new G4RotationMatrix();
rm135rmy180->rotateX(135.*deg);
   rm135rmy180->rotateY(180.*deg);
   
//=====================================================================
   

// Define a vacuum in the trap==========================================

G4double pressure, temperature;

G4Material* Vacuum = 
new G4Material("Vacuum", z=1., a=1.008*g/mole, density= 1.e-25*g/cm3, kStateGas, temperature= 273.*kelvin, pressure= 1.3e-7*pascal);

// Air at room temperature

//G4Material* Air = manager->FindOrBuildMaterial("G4_AIR");
//manager->ConstructNewGasMaterial("Air20","Air20",293.*kelvin,1.*atmosphere);

//======================================================================



// World (vacuum)========================================================

G4double WorldSizeX = 0.8*m;//was 0.5*m
G4double WorldSizeY = 0.8*m;
G4double WorldSizeZ = 0.8*m;

G4Box* solidWorld
= new G4Box("World",WorldSizeX, WorldSizeY, WorldSizeZ);

G4LogicalVolume* logicWorld
= new G4LogicalVolume(solidWorld,Vacuum,"World");

//logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

G4VPhysicalVolume* physiWorld = new G4PVPlacement(0,	 //no rotation
 G4ThreeVector(),	//at (0,0,0)
 logicWorld,	 //its logical volume
 "World",	 //its name
 0,	 //its mother  volume
 false,	 //no boolean operation
 0);	 //copy number

//=======================================================================
   

//copper source holder==================================================
   /*
   G4Tubs*
   CopperHolder = new G4Tubs("CopperHolder",0.*mm,5.*mm,0.5*mm,0.*deg,360.*deg);
   
   G4LogicalVolume*
   logicCopperHolder = new G4LogicalVolume(CopperHolder,
                                           copper,
                                           "CopperHolder");
   
   G4VisAttributes* CopperHolderVisAtt = new G4VisAttributes(G4Colour(5.,2.,0.));
   CopperHolderVisAtt->SetForceSolid(true);
   logicCopperHolder->SetVisAttributes(CopperHolderVisAtt);
   
   
   G4VPhysicalVolume* physiCopperHolder = new G4PVPlacement(0,  //rotation?
                                                            G4ThreeVector(0.,0.*mm,-0.501*mm),//0.501mm in the y or -z
                                                            logicCopperHolder,
                                                            "CopperHolder",
                                                            logicWorld,
                                                            false,
                                                            0);
    
    
   */
//=======================================================================
   

   
//Kapton window=========================================================
   G4Tubs*
//KaptonWindow = new G4Tubs("KaptonWindow",0.*mm,57.15*mm,3.75*um,0.*deg,360.*deg);//thickness=7.5um, outer radius = 5.715cm 
KaptonWindow = new G4Tubs("KaptonWindow",0.*mm,57.15*mm,4*um,0.*deg,360.*deg);//Changed by bswang (12/21/2014) 
   
   G4LogicalVolume*                         
logicKaptonWindow = new G4LogicalVolume(KaptonWindow,	 //its solid
                                           Kapton,	 //its material
                                           "KaptonWindow");	 //its name
   
   G4VPhysicalVolume* physiKaptonWindow = new G4PVPlacement(0,	 //no rotation
                                                            //G4ThreeVector(0.,0.,82.11045*mm),//91.75775mm 72.73685mm + 7.0209mm
                                                            //G4ThreeVector(0.,0.,-82.11045*mm),//Changed by bswang (12/18/2014)
                                                            G4ThreeVector(0.,0.,-82.10956*mm),//Changed by bswang (12/22/2014)
                                                            logicKaptonWindow, //its logical volume
                                                            "KaptonWindow", //its name
                                                            logicWorld,	 //its mother  volume
                                                            false,	 //no boolean operation
                                                            0);	 //copy number
    
   //was 83.26645mm left
   
   
   //for second scintillator detector
   
   G4VPhysicalVolume* physiKaptonWindow2 = new G4PVPlacement(rm90,	 //rotation about x-axis 90 deg
                                                             //G4ThreeVector(0.,-81.21045*mm,0.),//
                                                             G4ThreeVector(0.,-81.20956*mm,0.),//Changed by bswang (12/21/2014)
                                                             logicKaptonWindow,	 //its logical volume
                                                             "KaptonWindow", //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
  //was -83.26645mm bottom
   
//=======================================================================   
   
//Aluminium layer on Kapton==============================================
   G4Tubs*
//AlLayer= new G4Tubs("AlLayer",0.*mm,57.15*mm,0.75*um,0.*deg,360.*deg);//same as Kapton but 1.5um thick
AlLayer= new G4Tubs("AlLayer",0.*mm,57.15*mm,0.18*um,0.*deg,360.*deg);//Changed by bswang (12/21/2014)
   
   G4LogicalVolume*                         
logicAlLayer = new G4LogicalVolume(AlLayer,	 //its solid
                                      Aluminum,	 //its material
                                      "AlLayer");	 //its name
   
   G4VPhysicalVolume* physiAlLayer1 = new G4PVPlacement(0,	 //no rotation
                                                        //G4ThreeVector(0.,0.,82.11495*mm),//91.76225mm was 72.74135mm, then add 7.0209mm
                                                        //G4ThreeVector(0.,0.,-82.11495*mm),//Changed by bswang (12/18/2014)
                                                        G4ThreeVector(0.,0.,-82.11374*mm),//Changed by bswang (12/22/2014)
                                                        logicAlLayer,	 //its logical volume
                                                        "AlLayer",	 //its name
                                                        logicWorld,	 //its mother  volume
                                                        false,	 //no boolean operation
                                                        0);	 //copy number
   
   G4VPhysicalVolume* physiAlLayer2 = new G4PVPlacement(0,	 //no rotation
                                                        //G4ThreeVector(0.,0.,82.10595*mm),//91.75325mm was 72.73235mm, add 7.0209mm
                                                        //G4ThreeVector(0.,0.,-82.10595*mm),//Changed by bswang (12/18/2014)
                                                        G4ThreeVector(0.,0.,-82.10538*mm),//Changed by bswang (12/22/2014)
                                                        logicAlLayer,	 //its logical volume
                                                        "AlLayer",	 //its name
                                                        logicWorld,	 //its mother  volume
                                                        false,	 //no boolean operation
                                                        0);	 //copy number
   
   G4VPhysicalVolume* physiAlLayer3 = new G4PVPlacement(rm90,	 //no rotation
                                                        //G4ThreeVector(0.,-81.21495*mm,0.),//91.76225mm was -72.74135mm, add 7.0209mm
                                                        G4ThreeVector(0.,-81.21374*mm,0.),//Changed by bswang (12/21/2014)
                                                        logicAlLayer,	 //its logical volume
                                                        "AlLayer",	 //its name
                                                        logicWorld,	 //its mother  volume
                                                        false,	 //no boolean operation
                                                        0);	 //copy number
   
   G4VPhysicalVolume* physiAlLayer4 = new G4PVPlacement(rm90,	 //no rotation
                                                        //G4ThreeVector(0.,-81.20595*mm,0.),//91.75325mm was -72.73235mm, add 7.0209mm
                                                        G4ThreeVector(0.,-81.20538*mm,0.),//Changed by bswang (12/21/2014)
                                                        logicAlLayer,	 //its logical volume
                                                        "AlLayer",	 //its name
                                                        logicWorld,	 //its mother  volume
                                                        false,	 //no boolean operation
                                                        0);	 //copy number
   
   //was 83.27095mm and 83.26195mm left, was same on bottom 
   
//=======================================================================   

   
//sandwich pieces for Kapton window======================================
   G4Tubs*
KaptonSandwich = new G4Tubs("KaptonSandwich",1.62*inch,2.6*inch,0.069*inch,0.*deg,360.*deg);
   
   G4LogicalVolume*                         
logicKaptonSandwich = new G4LogicalVolume(KaptonSandwich,	 //its solid
                                             Steel,	 //its material
                                             "KaptonSandwich");	 //its name
   
   G4VisAttributes* SandwichVisAtt = new G4VisAttributes(G4Colour(5.,3.,0.));
//SandwichVisAtt->SetForceWireframe(true);
   SandwichVisAtt->SetForceSolid(true);
logicKaptonSandwich->SetVisAttributes(SandwichVisAtt);
   
   
   
   G4VPhysicalVolume* physiKaptonSandwich1 = new G4PVPlacement(0,	 //no rotation
                                                               //G4ThreeVector(0.,0.,83.8683*mm),//93.5156mm was 74.4947mm, add 7.0209mm
                                                               G4ThreeVector(0.,0.,-83.86652*mm),//93.5156mm was 74.4947mm, add 7.0209mm
                                                               logicKaptonSandwich,	 //its logical volume
                                                               "KaptonSandwich",	 //its name
                                                               logicWorld, //its mother  volume
                                                               false,	 //no boolean operation
                                                               0);	 //copy number
   
   G4VPhysicalVolume* physiKaptonSandwich2 = new G4PVPlacement(0,	 //no rotation
                                                               //G4ThreeVector(0.,0.,80.3526*mm),//89.999mm was 70.979mm, add 7.0209mm
                                                               G4ThreeVector(0.,0.,-80.3526*mm),//Changed by bswang (12/18/2014)
                                                               logicKaptonSandwich,	 //its logical volume
                                                               "KaptonSandwich",	 //its name
                                                               logicWorld, //its mother  volume
                                                               false,	 //no boolean operation
                                                               0);	 //copy number
   
   
   
   G4VPhysicalVolume* physiKaptonSandwich3 = new G4PVPlacement(rm90, //rotation
                                                               //G4ThreeVector(0.,-82.9683*mm,0.),	//was -74.4947mm, add 7.0209mm
                                                               G4ThreeVector(0.,-82.96652*mm,0.),	//Changed by bswang (12/21/2014)
                                                               logicKaptonSandwich,	 //its logical volume
                                                               "KaptonSandwich",	 //its name
                                                               logicWorld, //its mother  volume
                                                               false,	 //no boolean operation
                                                               0);	 //copy number
   
   G4VPhysicalVolume* physiKaptonSandwich4 = new G4PVPlacement(rm90, //rotation
                                                               G4ThreeVector(0.,-79.4526*mm,0.),	//was -70.979mm, add 7.0209mm
                                                               logicKaptonSandwich,	 //its logical volume
                                                               "KaptonSandwich",	 //its name
                                                               logicWorld, //its mother  volume
                                                               false,	 //no boolean operation
                                                               0);	 //copy number
   
   //was 85.0243mm and 81.5086mm left, same on bottom
   
//=======================================================================   

   
//Steel entry ports (scintillators)======================================   
   G4Cons* 
   solidEntryPortA = new G4Cons("solidEntryPortA",41.275*mm,67.31*mm,46.355*mm,74.50*mm,5.08*mm,0*deg,360*deg);//second outer radius matches outer radius of Delta E?? no
   
   
  G4Cons* 
   solidEntryPortB = new G4Cons("solidEntryPortB",70.055*mm,74.50*mm,84.455*mm,88.9*mm,6.985*mm,0*deg,360*deg);//second outer radius matches outer radius of Delta E//max 1 was 83.045mm (second number)
   
   
   G4LogicalVolume*
logicEntryPortA = new G4LogicalVolume(solidEntryPortA,
                                         Steel,
                                         "logicEntryPortA");
   
   G4LogicalVolume*
logicEntryPortB = new G4LogicalVolume(solidEntryPortB,
                                         Steel,
                                         "logicEntryPortB");
   
   G4VisAttributes * EntryPortAVisAtt = new G4VisAttributes(G4Colour(0.9,0.7,0.));//yellow
   G4VisAttributes * EntryPortBVisAtt = new G4VisAttributes(G4Colour(0.7,0.7,0.));
//EntryPortBVisAtt->SetForceWireframe(true);
   EntryPortBVisAtt->SetForceSolid(true);
   EntryPortAVisAtt->SetForceSolid(true);
logicEntryPortA->SetVisAttributes(EntryPortAVisAtt);
   logicEntryPortB->SetVisAttributes(EntryPortBVisAtt);
   
   
   
   //G4VPhysicalVolume* physiEntryPortA1 = new G4PVPlacement(0,
   G4VPhysicalVolume* physiEntryPortA1 = new G4PVPlacement(rm180, //Changed by bswang (12/18/2014)
                                                          //G4ThreeVector(0.,0.,90.7256*mm),//was 100.3729mm
                                                          //G4ThreeVector(0.,0.,-90.7256*mm),//Changed by bswang (12/18/2014)
                                                          G4ThreeVector(0.,0.,-90.69912*mm),//Changed by bswang (12/22/2014)
                                                          logicEntryPortA,
                                                          "EntryPort",
                                                          logicWorld,
                                                          false,
                                                          0);
    
   //was 91.8816mm
   //G4VPhysicalVolume* physiEntryPortB1 = new G4PVPlacement(0,
   G4VPhysicalVolume* physiEntryPortB1 = new G4PVPlacement(rm180,  //Changed by bswang (12/18/2014)
                                                           //G4ThreeVector(0.,0.,102.7906*mm),//was 112.4379mm
                                                           //G4ThreeVector(0.,0.,-102.7906*mm),//Changed by bswang (12/18/2014)
                                                           G4ThreeVector(0.,0.,-102.76412*mm),//Changed by bswang (12/22/2014)
                                                           logicEntryPortB,
                                                           "EntryPort",
                                                           logicWorld,
                                                           false,
                                                           0);
   //was 103.9466mm
   
   //second steel entry port
   G4VPhysicalVolume* physiEntryPortA2 = new G4PVPlacement(rm270,//rotate correct way
                                                         //G4ThreeVector(0.,-89.8256*mm,0.),//was 100.3729mm
                                                         G4ThreeVector(0.,-89.79912*mm,0.),//Changed by bswang (12/21/2014)
                                                         logicEntryPortA,
                                                         "EntryPort",
                                                         logicWorld,
                                                         false,
                                                         0);
   //was -91.8816mm
   
   G4VPhysicalVolume* physiEntryPortB2 = new G4PVPlacement(rm270,//rotate correct way
                                                           //G4ThreeVector(0.,-101.8906*mm,0.),//was 112.4379mm
                                                           G4ThreeVector(0.,-101.86412*mm,0.),//Changed by bswang (12/21/2014)
                                                           logicEntryPortB,
                                                           "EntryPort",
                                                           logicWorld,
                                                           false,
                                                           0);
    
   //was -103.9466mm
//=======================================================================   
   
//add on surrounding metal housing for whole plastic scintillator========
   G4Tubs*
   SolidLongerHousing = new G4Tubs("SolidLongerHousing",84.455*mm,88.9*mm,47.1629*mm,0.*deg,360.*deg);
   
   G4LogicalVolume*
logicLongerHousing = new G4LogicalVolume(SolidLongerHousing,
                                         Steel,
                                         "logicLongerHousing");
   
   G4VisAttributes * longerHousingVisAtt = new G4VisAttributes(G4Colour(0.5,0.7,0.0));
   longerHousingVisAtt->SetForceSolid(true);
   logicLongerHousing->SetVisAttributes(longerHousingVisAtt);
   
   G4VPhysicalVolume* physiLongerHousingA = new G4PVPlacement(0,
                                                           //G4ThreeVector(0.,0.,156.9385*mm),//156.9385mm
                                                           //G4ThreeVector(0.,0.,-156.9385*mm),//Changed by bswang (12/18/2014)
                                                           G4ThreeVector(0.,0.,-156.91202*mm),//Changed by bswang (12/22/2014)
                                                           logicLongerHousing,
                                                           "longerHousingA",
                                                           logicWorld,
                                                           false,
                                                           0);
   
   G4VPhysicalVolume* physiLongerHousingB = new G4PVPlacement(rm270,
                                                              //G4ThreeVector(0.,-156.0385*mm,0.),//
                                                              G4ThreeVector(0.,-156.01202*mm,0.),//Changed by bswang (12/21/2014)
                                                              logicLongerHousing,
                                                              "longerHousingB",
                                                              logicWorld,
                                                              false,
                                                              0);
   
   
//=======================================================================   
   
   
//need light guide======================================================
   
   
   
   G4Tubs*
solidLightGuide = new G4Tubs("lightGuide",53.34*mm,66.675*mm,3.175*mm,0.*deg,360.*deg);//full thickness is 6.35mm, inner radius should match dE radius???? should be slightly larger than dE radius I think, 53.34mm not 53.0225mm
   
   G4LogicalVolume*
logicLightGuide = new G4LogicalVolume(solidLightGuide,
                                         pmma,
                                         "logicLightGuide");
   
   G4VisAttributes* lightGuideVisAtt = new G4VisAttributes(G4Colour(0.4,0.,0.4));//shade of purple
lightGuideVisAtt->SetForceSolid(true);
   //lightGuideVisAtt->SetForceWireframe(true);
logicLightGuide->SetVisAttributes(lightGuideVisAtt);

G4VPhysicalVolume* physiLightGuide = new G4PVPlacement(0,
                                                          //G4ThreeVector(0.,0.,99.3264*mm),//was 108.9737 mm
                                                          //G4ThreeVector(0.,0.,-99.3264*mm),//Changed by bswang (12/18/2014)
                                                          G4ThreeVector(0.,0.,-98.95412*mm),//Changed by bswang (12/22/2014)
                                                          logicLightGuide,
                                                          "lightGuide",
                                                          logicWorld,
                                                          false,
                                                          0);
   //was 100.4824mm
   
   
   G4VPhysicalVolume* physiLightGuide2 = new G4PVPlacement(rm270,//rotate 270*deg NOT 90*deg!!!!
                                                           //G4ThreeVector(0.,-98.4264*mm,0.),//was 108.9737 mm
                                                           G4ThreeVector(0.,-98.05412*mm,0.),//Changed by bswang (12/21/2014)
                                                           logicLightGuide,
                                                           "lightGuide2",
                                                           logicWorld,
                                                           false,
                                                           0);
   //was -100.4824mm
//=======================================================================   
   
//extra part of light guide slightly overlapping Delta E=================
   
   G4Tubs*
//solidLightGuideExtra = new G4Tubs("lightGuideExtra",50.8*mm,53.34*mm,2.675*mm,0.*deg,360.*deg);//full thickness is 5.334mm???, inner radius normally is 50.8mm
solidLightGuideExtra = new G4Tubs("lightGuideExtra",50.8*mm,53.34*mm,2.6712*mm,0.*deg,360.*deg);//Changed by bswang (12/21/2014)
   
   G4LogicalVolume*
logicLightGuideExtra = new G4LogicalVolume(solidLightGuideExtra,
                                         pmma,
                                         "logicLightGuideExtra");
   
   G4VisAttributes* lightGuide2VisAtt = new G4VisAttributes(G4Colour(0.,0.7,0.3));//shade of green
lightGuide2VisAtt->SetForceSolid(true);
   //lightGuide2VisAtt->SetForceWireframe(true);
logicLightGuideExtra->SetVisAttributes(lightGuide2VisAtt);
   
   
   
   G4VPhysicalVolume* physiLightGuideExtra1 = new G4PVPlacement(0,//rotate
                                                           //G4ThreeVector(0.,0.,108.4617*mm),//
                                                           //G4ThreeVector(0.,0.,-108.4617*mm),//Changed by bswang (12/18/2014)
                                                           //G4ThreeVector(0.,0.,-98.8104*mm),//Changed by bswang (12/19/2014)
                                                           G4ThreeVector(0.,0.,-98.45032*mm),//Changed by bswang (12/22/2014)
                                                           logicLightGuideExtra,
                                                           "lightGuideExtra1",
                                                           logicWorld,
                                                           false,
                                                           0);
   
   G4VPhysicalVolume* physiLightGuideExtra2 = new G4PVPlacement(rm270,//rotate 270*deg NOT 90*deg!!!!
                                                           //G4ThreeVector(0.,-108.4617*mm,0.),//
                                                           //G4ThreeVector(0.,-97.9104*mm,0.),//Changed by bswang (12/19/2014)
                                                           G4ThreeVector(0.,-97.55032*mm,0.),//Changed by bswang (12/21/2014)
                                                           logicLightGuideExtra,
                                                           "lightGuideExtra2",
                                                           logicWorld,
                                                           false,
                                                           0);
   
   
   
//=======================================================================   
   
   
// Delta E detector(s)===================================================
   G4Tubs*
solidPlastic = new G4Tubs("Scintillator",0.*mm,53.0225*mm,0.5*mm,0.*deg,360.*deg);  // now outer radius is 53.0225mm, 0.5mm half Z
   
   G4LogicalVolume*                         
logicdE1 = new G4LogicalVolume(solidPlastic,	 //its solid
  Scintillator,	 //its material
  "Scintillator dE1");	 //its name
   G4LogicalVolume*
   logicdE2 = new G4LogicalVolume(solidPlastic,	 //its solid
  Scintillator,	 //its material
  "Scintillator dE2");	 //its name
   
   G4VisAttributes * plasticVisAtt = new G4VisAttributes(G4Colour(1.,0.,0.));
//plasticVisAtt->SetForceSolid(true);
   plasticVisAtt->SetForceWireframe(true);
logicdE1->SetVisAttributes(plasticVisAtt);
   logicdE2->SetVisAttributes(plasticVisAtt);
   
   G4VPhysicalVolume* physiPlastic = new G4PVPlacement(0,	 //no rotation
//G4ThreeVector(0.,0.,101.9854*mm),	//was 111.6327 mm
//G4ThreeVector(0.,0.,-101.9854*mm),	//Changed by bswang (12/18/2014)
G4ThreeVector(0.,0.,-101.62912*mm),	//Changed by bswang (12/22/2014)
logicdE1,	 //its logical volume
"Scintillator dE1",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number
   //was 103.1414mm
   
   //need for second scintillator detector
   
   G4VPhysicalVolume* physiPlastic2 = new G4PVPlacement(rm90,	 //rotate around x-axis 90 deg
//G4ThreeVector(0.,-101.0854*mm,0.0),
G4ThreeVector(0.,-100.72912*mm,0.0), //Changed by bswang (12/21/2014)
logicdE2,	 //its logical volume
"Scintillator dE2",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number
   //was -103.1414mm
   
//=======================================================================   
   

// Thin mylar foils======================================================

G4Tubs*
//solidMylar = new G4Tubs("Mylar",0.*mm,66.675*mm,3.8*um,0.*deg,360.*deg);//outer radius should match E det and light guide
solidMylar = new G4Tubs("Mylar",0.*mm,53.34*mm,3.8*um,0.*deg,360.*deg);//Changed by bswang (12/22/2014): Outer radius currently matches outer radius of extra light guide material

G4LogicalVolume*                         
logicMylar = new G4LogicalVolume(solidMylar,	 //its solid
                                  Mylar,	 //its material
                                  "Mylar");	 //its name

G4VisAttributes * mylarVisAtt = new G4VisAttributes(G4Colour(0.,0.,1.));//dark blue
mylarVisAtt->SetForceSolid(true);
logicMylar->SetVisAttributes(mylarVisAtt);
   
//NO MYLAR BETWEEN E SCINT AND LIGHT GUIDE, BUT YES IN FRONT OF dE 
   //position of Mylar was too far away from Delta E, too close to trap
   
G4VPhysicalVolume* physiMylar = new G4PVPlacement(0,	 //no rotation
//G4ThreeVector(0.,0.,101.4816*mm),	//was 111.1289 mm
//G4ThreeVector(0.,0.,-101.4816*mm),	//Changed by bswang (12/18/2014)
G4ThreeVector(0.,0.,-101.12532*mm),	//Changed by bswang (12/22/2014)
logicMylar,	 //its logical volume
"Mylar",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number
   
   //was 102.6376mm 
   
   G4VPhysicalVolume* physiMylar2 = new G4PVPlacement(rm90,	 //no rotation
//G4ThreeVector(0.,-100.5816*mm,0.),	//was 111.1289 mm
G4ThreeVector(0.,-100.22532*mm,0.),	//Changed by bswang (12/21/2014)
logicMylar,	 //its logical volume
"Mylar",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number
    
   //was -102.6376mm
       
//=======================================================================   
  
   
//E detector(s)==========================================================
   G4Tubs* solidE
= new G4Tubs("E scint",0.*mm,66.675*mm,50.8*mm,0.*deg,360.*deg);//outer radius now 66.675mm, half Z length now 50.8mm
   
   G4LogicalVolume* logicE1
= new G4LogicalVolume(solidE,Scintillator,"E1 scint");
   
   G4LogicalVolume* logicE2
= new G4LogicalVolume(solidE,Scintillator,"E2 scint");
   
   G4VisAttributes * DSSDVisAtt = new G4VisAttributes(G4Colour(0.,0.4,0.));
DSSDVisAtt->SetForceSolid(true);
logicE1->SetVisAttributes(DSSDVisAtt);
   logicE2->SetVisAttributes(DSSDVisAtt);
   
   
   
   G4VPhysicalVolume* physiE1 = new G4PVPlacement(0,	 //no rotation
//G4ThreeVector(0.,0.,153.3014*mm),
//G4ThreeVector(0.,0.,-153.3014*mm),  //Changed by bswang (12/18/2014)
G4ThreeVector(0.,0.,-152.92912*mm),  //Changed by bswang (12/22/2014)
logicE1,	 //its logical volume add 20 more mm because E is overlapping the electrodes + 5mm space for light guide
"E1 scint",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number
   //was 154.4574mm
  
   
   G4VPhysicalVolume* physiE2 = new G4PVPlacement(rm90,	 //rotation around x-axis 90 deg
//G4ThreeVector(0.,-152.4014*mm,0.),	//was 162.9487 mm
G4ThreeVector(0.,-152.02912*mm,0.),	//Changed by bswang (12/21/2014)
logicE2,	 //its logical volume
"E2 scint",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number

   
 //was -154.4574*mm 
   
//=======================================================================   

  
   
//new MCP plates===============================================================
   G4Box* MCPone 
   = new G4Box("MCPone", 25*mm, 25*mm, 0.64*mm);//50mm by 50 mm by 1.28mm both layers of MCP
   
   G4LogicalVolume* logicMCPtop
= new G4LogicalVolume(MCPone, MCPglass, "MCPtop");
   
   G4LogicalVolume* logicMCPright
= new G4LogicalVolume(MCPone, MCPglass, "MCPright");
   
   G4VisAttributes * MCPVisAtt = new G4VisAttributes(G4Colour(0.0,0.329,0.329));//bluish-green
//MCPVisAtt->SetForceSolid(true);
   MCPVisAtt->SetForceWireframe(true);
logicMCPtop->SetVisAttributes(MCPVisAtt);
   logicMCPright->SetVisAttributes(MCPVisAtt);
   
   
   G4VPhysicalVolume* physiMCPone = new G4PVPlacement(rm90,	 //rotation
  G4ThreeVector(0.,52.5*mm,0.),	//was 48.26775mm.
  logicMCPtop,	 //its logical volume
  "MCPtop",	 //its name
  logicWorld,	 //its mother  volume
  false,	 //no boolean operation
  0);	 //copy number
   
   
    
   //second MCP
   
   G4VPhysicalVolume* physiMCPtwo = new G4PVPlacement(0,	 //no rotation
  //G4ThreeVector(0.,0.,-52.5*mm),	//was -48.26775mm
  G4ThreeVector(0.,0.,52.5*mm),	//Changed by bswang (12/18/2014)
  logicMCPright,	 //its logical volume
  "MCPright",	 //its name
  logicWorld,	 //its mother  volume
  false,	 //no boolean operation
  0);	 //copy number
    
    
//=============================================================================
   


//Thin ceramic plates behind MCP plates (Added by bswang (3/5/2015))=====

   G4Box* MCPCeramicPlate
   = new G4Box("MCPCeramicPlate", 30*mm, 30*mm, 0.50*mm);//60mm by 60 mm by 1.0 mm both layers of ceramic (need to get actual dimensions from engineering drawings)
   
   G4LogicalVolume* logicMCPCeramicPlatetop
   = new G4LogicalVolume(MCPCeramicPlate, Alumina, "MCPCeramicPlatetop");
   
   G4LogicalVolume* logicMCPCeramicPlateright
   = new G4LogicalVolume(MCPCeramicPlate, Alumina, "MCPCeramicPlateright");
   
   G4VisAttributes * MCPCeramicPlateVisAtt = new G4VisAttributes(G4Colour(0.0,0.329,0.329));//bluish-green
//MCPCeramicPlateVisAtt->SetForceSolid(true);
   MCPCeramicPlateVisAtt->SetForceWireframe(true);
   logicMCPCeramicPlatetop->SetVisAttributes(MCPCeramicPlateVisAtt);
   logicMCPCeramicPlateright->SetVisAttributes(MCPCeramicPlateVisAtt);
   
   //top MCP Ceramic Plate
   G4VPhysicalVolume* physiMCPCeramicPlatetop = new G4PVPlacement(rm90,	 //rotation
   G4ThreeVector(0.,57*mm,0.),	//need to get actual distance from engineering drawings.
   logicMCPCeramicPlatetop,	 //its logical volume
   "MCPCeramicPlatetop",	 //its name
   logicWorld,	 //its mother  volume
   false,	 //no boolean operation
   0);	 //copy number
   
   
    
   //right MCP Ceramic Plate
   G4VPhysicalVolume* physiMCPCeramicPlateright = new G4PVPlacement(0,	 //no rotation
   G4ThreeVector(0.,0.,57*mm),	//need to get actual distance from engineering drawings.
   logicMCPCeramicPlateright,	 //its logical volume
   "MCPCeramicPlateright",	 //its name
   logicWorld,	 //its mother  volume
   false,	 //no boolean operation
   0);	 //copy number
    
    
//=============================================================================



//MCP border pieces=======================================================
   
   
   G4Box* MCPBorderOuter
   = new G4Box("MCPBorderOuter", 35.156225*mm, 29.182*mm, 0.6405*mm);//70.31245mm by 58.364mm by 1.281mm
   
   G4Box* MCPBorderInner 
   = new G4Box("MCPBorderInner", 24.816*mm, 24.816*mm, 0.65*mm);//49.632mm by 49.632mm by 1.281mm
   
   G4SubtractionSolid* MCPBorder
   = new G4SubtractionSolid("MCPBorder",MCPBorderOuter,MCPBorderInner,0,G4ThreeVector(0.,0.,0.));
   
   
   G4LogicalVolume* logicMCPBorder
= new G4LogicalVolume(MCPBorder, ceramic, "MCPBorder");//what is material here?
   
   G4VisAttributes * MCPBorderVisAtt = new G4VisAttributes(G4Colour(0.8,0.5,0.4));
   //MCPBorderVisAtt->SetForceSolid(true);
   MCPBorderVisAtt->SetForceWireframe(true);
   logicMCPBorder->SetVisAttributes(MCPBorderVisAtt);
   
   
   G4VPhysicalVolume* physiMCPBorder1 = new G4PVPlacement(rm90,	 //rotation 
                                                         G4ThreeVector(0.,51.2195*mm,0.),//was 46.98725mm
                                                         logicMCPBorder,	 //its logical volume      
                                                         "MCPBorder",	 //its name
                                                         logicWorld,	 //its mother  volume
                                                         false,	 //no boolean operation
                                                         0);	 //copy number
   
   G4VPhysicalVolume* physiMCPBorder2 = new G4PVPlacement(rm90,	 //rotation 
                                                         G4ThreeVector(0.,48.017*mm,0.),//was 43.78475mm
                                                         logicMCPBorder,	 //its logical volume      
                                                         "MCPBorder",	 //its name
                                                         logicWorld,	 //its mother  volume
                                                         false,	 //no boolean operation
                                                         0);	 //copy number
   
   G4VPhysicalVolume* physiMCPBorder3 = new G4PVPlacement(0,	 //rotation 
                                                          //G4ThreeVector(0.,0.,-51.2195*mm),//was 46.98725mm
                                                          G4ThreeVector(0.,0.,51.2195*mm),//Changed by bswang (12/18/2014)
                                                          logicMCPBorder, //its logical volume      
                                                          "MCPBorder",	 //its name
                                                          logicWorld,	 //its mother  volume
                                                          false,	 //no boolean operation
                                                          0);	 //copy number
   
   G4VPhysicalVolume* physiMCPBorder4 = new G4PVPlacement(0,	 //rotation 
                                                          //G4ThreeVector(0.,0.,-48.017*mm),//was 43.78475mm
                                                          G4ThreeVector(0.,0.,48.017*mm),//Changed by bswang (12/18/2014)
                                                          logicMCPBorder, //its logical volume      
                                                          "MCPBorder",	 //its name
                                                          logicWorld,	 //its mother  volume
                                                          false,	 //no boolean operation
                                                          0);	 //copy number
   
   
//=============================================================================
    
    

//Ceramic base plates attached to MCPs (Added by bswang on 4/2/2015)=================
   
   
   G4Box* CeramicBasePlateOuter
   = new G4Box("CeramicBasePlateOuter", 101.6*mm/2, 62.484*mm/2, 5.207*mm/2);
   
   G4Box* CeramicBasePlateInner 
   = new G4Box("CeramicBasePlateInner", 50.292*mm/2, 50.292*mm/2, 5.3*mm/2);
   
   G4SubtractionSolid* CeramicBasePlate
   = new G4SubtractionSolid("CeramicBasePlate",CeramicBasePlateOuter,CeramicBasePlateInner,0,G4ThreeVector(0.,0.,0.));
   
   
   G4LogicalVolume* logicCeramicBasePlate
= new G4LogicalVolume(CeramicBasePlate, ceramic, "CeramicBasePlate");
   
   G4VisAttributes * CeramicBasePlateVisAtt = new G4VisAttributes(G4Colour(0.8,0.5,0.4));
   //CeramicBasePlateVisAtt->SetForceSolid(true);
   CeramicBasePlateVisAtt->SetForceWireframe(true);
   logicCeramicBasePlate->SetVisAttributes(CeramicBasePlateVisAtt);
   
   G4VPhysicalVolume* physiCeramicBasePlate1 = new G4PVPlacement(rm90,	 //rotation 
                                                         G4ThreeVector(0.,62.9217*mm,0.),
                                                         logicCeramicBasePlate,	 //its logical volume      
                                                         "CeramicBasePlate",	 //its name
                                                         logicWorld,	 //its mother  volume
                                                         false,	 //no boolean operation
                                                         0);	 //copy number
   
   G4VPhysicalVolume* physiCeramicBasePlate2 = new G4PVPlacement(0,	 //rotation 
                                                          G4ThreeVector(0.,0.,62.9217*mm),
                                                          logicCeramicBasePlate, //its logical volume      
                                                          "CeramicBasePlate",	 //its name
                                                          logicWorld,	 //its mother  volume
                                                          false,	 //no boolean operation
                                                          0);	 //copy number
   
//=============================================================================
    
    

//Construct the center blade electrodes========================================


   
   G4Box* fullcent
   = new G4Box("fullcent", 1.22*inch, 0.5555*inch, 0.04*inch);//2.44in by 1.111in by 0.08in
   
   G4Box* sidecent
   = new G4Box("sidecent", 0.286*inch, 0.3055*inch, 0.045*inch);//0.57inch by 0.611inch by 0.08inch

   
   
   G4SubtractionSolid*
   fcentminussideone = new G4SubtractionSolid("fcentminussideone",
   fullcent,sidecent,0,G4ThreeVector(0.936*inch,-0.25*inch,0.));

   G4SubtractionSolid*
   fcentminussidetwo = new G4SubtractionSolid("fcentminussidetwo",
   fullcent,sidecent,0,G4ThreeVector(-0.936*inch,-0.25*inch,0.));
   
   G4IntersectionSolid*
   solidCentElec = new G4IntersectionSolid("solidCentElec",
                                        fcentminussideone,fcentminussidetwo,0,G4ThreeVector(0.,0.,0.));
   
   G4LogicalVolume* logicCentElec = new G4LogicalVolume(solidCentElec,	 //its solid
                                        Steel,	 //its material
                                        "logicCenterelec");	 //its name
   
   
   G4VisAttributes * CentElecVisAtt = new G4VisAttributes(G4Colour(0.753,0.753,0.753));
   CentElecVisAtt->SetForceSolid(true);
   //CentElecVisAtt->SetForceWireframe(true);
   logicCentElec->SetVisAttributes(CentElecVisAtt);
   
   
   G4VPhysicalVolume* physiCentElec1 = new G4PVPlacement(rm45,	 //rotation 
                                      G4ThreeVector(0.,17.755*mm,-17.755*mm),        
                                      logicCentElec,	 //its logical volume      
                                      "CenterElecBlade",	 //its name
                                      logicWorld,	 //its mother  volume
                                      false,	 //no boolean operation
                                      0);	 //copy number
   
   
   G4VPhysicalVolume* physiCentElec2 = new G4PVPlacement(rm315,	 //rotation 
                                                        G4ThreeVector(0.,17.755*mm,17.755*mm),        
                                                        logicCentElec,	 //its logical volume      
                                                        "CenterElecBlade", //its name
                                                        logicWorld,	 //its mother  volume
                                                        false,	 //no boolean operation
                                                        0);	 //copy number
   
   G4VPhysicalVolume* physiCentElec3 = new G4PVPlacement(rm225,	 //rotation 
                                                        G4ThreeVector(0.,-17.755*mm,17.755*mm),        
                                                        logicCentElec,	 //its logical volume      
                                                        "CenterElecBlade", //its name
                                                        logicWorld,	 //its mother  volume
                                                        false,	 //no boolean operation
                                                        0);	 //copy number
   
   G4VPhysicalVolume* physiCentElec4 = new G4PVPlacement(rm135,	 //rotation 
                                                        G4ThreeVector(0.,-17.755*mm,-17.755*mm),        
                                                        logicCentElec,	 //its logical volume      
                                                        "CenterElecBlade", //its name
                                                        logicWorld,	 //its mother  volume
                                                        false,	 //no boolean operation
                                                        0);	 //copy number
   
//=============================================================================
   
   
//construct top center electrodes and center ceramics=========================
   G4Box* topCentElec
   = new G4Box("topCentElec", 1.22*inch, 0.9575*inch, 0.04*inch);//2.44in by 1.915in by 0.08in
   
   G4LogicalVolume* 
   logicTopCentElec = new G4LogicalVolume(topCentElec, Steel, "logicTopCentElec");
  
   G4VisAttributes* TopCentElecVisAtt = new G4VisAttributes(G4Colour(0.753,0.753,0.753));
   //TopCentElecVisAtt->SetForceSolid(true);
   TopCentElecVisAtt->SetForceWireframe(true);
   logicTopCentElec->SetVisAttributes(TopCentElecVisAtt);
   
   
   G4VPhysicalVolume* physiTopCentElec1 = new G4PVPlacement(rm45,	 //rotation 
                                                         G4ThreeVector(0.,47.12066*mm,-47.12066*mm), //50.527=y,50.0985=z      
                                                         logicTopCentElec, //its logical volume      
                                                         "TopCentElec",	 //its name
                                                         logicWorld,	 //its mother  volume
                                                         false,	 //no boolean operation
                                                         0);	 //copy number
   
   G4VPhysicalVolume* physiTopCentElec2 = new G4PVPlacement(rm315,	 //rotation 
                                                           G4ThreeVector(0.,47.12066*mm,47.12066*mm), //50.527=y,50.0985=z      
                                                           logicTopCentElec, //its logical volume      
                                                           "TopCentElec", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopCentElec3 = new G4PVPlacement(rm225,	 //rotation 
                                                           G4ThreeVector(0.,-47.12066*mm,47.12066*mm), //50.527=y,50.0985=z      
                                                           logicTopCentElec, //its logical volume      
                                                           "TopCentElec", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopCentElec4 = new G4PVPlacement(rm135,	 //rotation 
                                                           G4ThreeVector(0.,-47.12066*mm,-47.12066*mm), //50.527=y,50.0985=z      
                                                           logicTopCentElec, //its logical volume      
                                                           "TopCentElec", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   
   
   G4Box* CentCeramic
   = new G4Box("CentCeramic", 1.22*inch, 0.4625*inch, 0.0625*inch);//2.44in by 0.925in by 0.125in

   G4LogicalVolume* 
   logicCentCeramic = new G4LogicalVolume(CentCeramic, ceramic, "logicCentCeramic");
   
   G4VisAttributes* CentCeramicVisAtt = new G4VisAttributes(G4Colour(0.8,0.4,0.));//dark orange
   //TopCentElecVisAtt->SetForceSolid(true);
   CentCeramicVisAtt->SetForceWireframe(true);
   logicCentCeramic->SetVisAttributes(CentCeramicVisAtt);
   
   
   G4VPhysicalVolume* physiCentCeramic1 = new G4PVPlacement(rm45,	 //rotation 
                                                           G4ThreeVector(0.,30.6953*mm,-27.014*mm),//        
                                                           logicCentCeramic, //its logical volume      
                                                           "logicCentCeramic", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   
     
   
   G4VPhysicalVolume* physiCentCeramic2 = new G4PVPlacement(rm315,	 //rotation 
                                                           G4ThreeVector(0.,27.014*mm,30.6953*mm),//        
                                                           logicCentCeramic, //its logical volume      
                                                           "logicCentCeramic", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiCentCeramic3 = new G4PVPlacement(rm225,	 //rotation 
                                                           G4ThreeVector(0.,-30.6953*mm,27.014*mm),//        
                                                           logicCentCeramic, //its logical volume      
                                                           "logicCentCeramic", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiCentCeramic4 = new G4PVPlacement(rm135,	 //rotation 
                                                           G4ThreeVector(0.,-27.014*mm,-30.6953*mm),//    
                                                           logicCentCeramic, //its logical volume      
                                                           "logicCentCeramic", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
//=============================================================================



// Construct the end electrodes================================================


   
   G4Box* fullend
   = new G4Box("fullend", 2.2535*inch, 0.555*inch, 0.04*inch);//4.507inch by 1.111inch by 0.08inch
   
   G4Box* sideend
   = new G4Box("sideend", 0.285*inch, 0.2895*inch, 0.045*inch);//0.57inch by 0.579inch by 0.08inch

G4SubtractionSolid*
    endElecBlade= new G4SubtractionSolid("endElecBlade",
fullend,sideend,0,G4ThreeVector(-1.9685*inch,0.266*inch,0.));

    G4LogicalVolume* 
    logicEndElecBlade = new G4LogicalVolume(endElecBlade, Steel, "logicEndElecBlade");
   
    G4VisAttributes* EndElecBladeVisAtt = new G4VisAttributes(G4Colour(0.753,0.753,0.753));
    EndElecBladeVisAtt->SetForceSolid(true);
    logicEndElecBlade->SetVisAttributes(EndElecBladeVisAtt);
   
   
   G4VPhysicalVolume* physiEndElecBlade1 = new G4PVPlacement(rm45,	
                                       G4ThreeVector(75.7809*mm,17.755*mm,-17.755*mm),//x position?
                                       logicEndElecBlade,	 //its logical volume
                                       "EndElec",	 //its name
                                       logicWorld,	 //its mother  volume
                                       false,	 //no boolean operation
                                       0);	 //copy number
   
   G4VPhysicalVolume* physiEndElecBlade2 = new G4PVPlacement(rm315,	
                                                             G4ThreeVector(75.7809*mm,17.755*mm,17.755*mm),//x position?
                                                             logicEndElecBlade,	 //its logical volume
                                                             "EndElec",	 //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
   
   
   G4VPhysicalVolume* physiEndElecBlade3 = new G4PVPlacement(rm225,	
                                                             G4ThreeVector(75.7809*mm,-17.755*mm,17.755*mm),//x position?
                                                             logicEndElecBlade,	 //its logical volume
                                                             "EndElec",	 //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
   
   
   G4VPhysicalVolume* physiEndElecBlade4 = new G4PVPlacement(rm135,	
                                                             G4ThreeVector(75.7809*mm,-17.755*mm,-17.755*mm),//x position?
                                                             logicEndElecBlade,	 //its logical volume
                                                             "EndElec",	 //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
   
   
   
   G4VPhysicalVolume* physiEndElecBlade5 = new G4PVPlacement(rm45rmy180,	
                                                             G4ThreeVector(-75.7809*mm,17.755*mm,-17.755*mm),//x position?
                                                             logicEndElecBlade,	 //its logical volume
                                                             "EndElec",	 //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
   
   
   G4VPhysicalVolume* physiEndElecBlade6 = new G4PVPlacement(rm315rmy180,	
                                                             G4ThreeVector(-75.7809*mm,17.755*mm,17.755*mm),//x position?
                                                             logicEndElecBlade,	 //its logical volume
                                                             "EndElec",	 //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
   
   
   G4VPhysicalVolume* physiEndElecBlade7 = new G4PVPlacement(rm225rmy180,	
                                                             G4ThreeVector(-75.7809*mm,-17.755*mm,17.755*mm),//x position?
                                                             logicEndElecBlade,	 //its logical volume
                                                             "EndElec",	 //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
   
   
   G4VPhysicalVolume* physiEndElecBlade8 = new G4PVPlacement(rm135rmy180,	
                                                             G4ThreeVector(-75.7809*mm,-17.755*mm,-17.755*mm),//x position?
                                                             logicEndElecBlade,	 //its logical volume
                                                             "EndElec",	 //its name
                                                             logicWorld,	 //its mother  volume
                                                             false,	 //no boolean operation
                                                             0);	 //copy number
   

//=============================================================================

   
   
//end ceramic braces===========================================================
   G4Box* endCeramic
   = new G4Box("endCeramic", 1.7685*inch, 0.4625*inch, 0.0625*inch);//3.537inch by 0.925inch by 0.125inch
   
   G4LogicalVolume* 
   logicEndCeramic = new G4LogicalVolume(endCeramic, ceramic, "logicEndCeramic");
   
   G4VisAttributes* EndCeramicVisAtt = new G4VisAttributes(G4Colour(0.8,0.4,0.));//dark orange
   //EndCeramicVisAtt->SetForceSolid(true);
   EndCeramicVisAtt->SetForceWireframe(true);
   logicEndCeramic->SetVisAttributes(EndCeramicVisAtt);
   
   
   G4VPhysicalVolume* physiEndCeramic1 = new G4PVPlacement(rm45,	 //rotation 
                                                            G4ThreeVector(83.0199*mm,30.6953*mm,-27.014*mm),//        
                                                            logicEndCeramic, //its logical volume      
                                                            "EndCeramic", //its name
                                                            logicWorld,	 //its mother  volume
                                                            false,	 //no boolean operation
                                                            0);	 //copy number
   
   G4VPhysicalVolume* physiEndCeramic2 = new G4PVPlacement(rm315,	 //rotation 
                                                            G4ThreeVector(83.0199*mm,27.014*mm,30.6953*mm),//        
                                                            logicEndCeramic, //its logical volume      
                                                            "EndCeramic", //its name
                                                            logicWorld,	 //its mother  volume
                                                            false,	 //no boolean operation
                                                            0);	 //copy number
   
   G4VPhysicalVolume* physiEndCeramic3 = new G4PVPlacement(rm225,	 //rotation 
                                                            G4ThreeVector(83.0199*mm,-30.6953*mm,27.014*mm),//        
                                                            logicEndCeramic, //its logical volume      
                                                            "EndCeramic", //its name
                                                            logicWorld,	 //its mother  volume
                                                            false,	 //no boolean operation
                                                            0);	 //copy number
   
   G4VPhysicalVolume* physiEndCeramic4 = new G4PVPlacement(rm135,	 //rotation 
                                                            G4ThreeVector(83.0199*mm,-27.014*mm,-30.6953*mm),//    
                                                            logicEndCeramic, //its logical volume      
                                                            "EndCeramic", //its name
                                                            logicWorld,	 //its mother  volume
                                                            false,	 //no boolean operation
                                                            0);	 //copy number
   
   G4VPhysicalVolume* physiEndCeramic5 = new G4PVPlacement(rm45,	 //rotation 
                                                           G4ThreeVector(-83.0199*mm,30.6953*mm,-27.014*mm),//        
                                                           logicEndCeramic, //its logical volume      
                                                           "EndCeramic",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiEndCeramic6 = new G4PVPlacement(rm315,	 //rotation 
                                                           G4ThreeVector(-83.0199*mm,27.014*mm,30.6953*mm),//        
                                                           logicEndCeramic, //its logical volume      
                                                           "EndCeramic",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiEndCeramic7 = new G4PVPlacement(rm225,	 //rotation 
                                                           G4ThreeVector(-83.0199*mm,-30.6953*mm,27.014*mm),//        
                                                           logicEndCeramic, //its logical volume      
                                                           "EndCeramic",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiEndCeramic8 = new G4PVPlacement(rm135,	 //rotation 
                                                           G4ThreeVector(-83.0199*mm,-27.014*mm,-30.6953*mm),//    
                                                           logicEndCeramic, //its logical volume      
                                                           "EndCeramic",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number

//=============================================================================



//construct end top electrodes=================================================
   
   
   G4Box* topEndElecFull
   = new G4Box("topEndElecFull", 1.9685*inch, 0.9575*inch, 0.04*inch);//3.937in by 1.915in by 0.08in
   
   G4Box* topEndElecPart
   = new G4Box("topEndElecPart", 0.2515*inch, 0.3*inch, 0.041*inch);//0.503inch by 0.6inch by 0.08inch
   
   
   G4SubtractionSolid*
   topEndElec = new G4SubtractionSolid("topEndElec",
                                       topEndElecFull,topEndElecPart,0,G4ThreeVector(1.97*inch,0.6575*inch,0.));
   
   G4LogicalVolume* 
   logicTopEndElec = new G4LogicalVolume(topEndElec, Steel, "logicTopEndElec");
   
   G4VisAttributes* topEndElecVisAtt = new G4VisAttributes(G4Colour(0.,0.7,0.3));//green-ish
   //topEndElecVisAtt->SetForceSolid(true);
   topEndElecVisAtt->SetForceWireframe(true);
   logicTopEndElec->SetVisAttributes(topEndElecVisAtt);
   
   
   G4VPhysicalVolume* physiTopEndElec1 = new G4PVPlacement(rm45,	 //rotation 
                                                           G4ThreeVector(83.0199*mm,47.12066*mm,-47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopEndElec2 = new G4PVPlacement(rm315,	 //rotation 
                                                           G4ThreeVector(83.0199*mm,47.12066*mm,47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopEndElec3 = new G4PVPlacement(rm225,	 //rotation 
                                                           G4ThreeVector(83.0199*mm,-47.12066*mm,47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopEndElec4 = new G4PVPlacement(rm135,	 //rotation 
                                                           G4ThreeVector(83.0199*mm,-47.12066*mm,-47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopEndElec5 = new G4PVPlacement(rm45rmy180, //rotation 
                                                           G4ThreeVector(-83.0199*mm,47.12066*mm,-47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopEndElec6 = new G4PVPlacement(rm315rmy180, //rotation 
                                                           G4ThreeVector(-83.0199*mm,47.12066*mm,47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopEndElec7 = new G4PVPlacement(rm225rmy180, //rotation 
                                                           G4ThreeVector(-83.0199*mm,-47.12066*mm,47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiTopEndElec8 = new G4PVPlacement(rm135rmy180, //rotation 
                                                           G4ThreeVector(-83.0199*mm,-47.12066*mm,-47.12066*mm),//change y and z   
                                                           logicTopEndElec, //its logical volume      
                                                           "topEndElec",	 //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
//=============================================================================
   



//need metal covering (shields) for grounded top center and end electrodes=====
   
    
   G4Box* centerCoverPlateFull
   = new G4Box("centerCoverPlateFull", 1.22*inch, 0.3*inch, 0.09*inch);//2.44inch by 0.6 inch by 0.18 inch
   
   G4Box* centerCoverPlatePart
   = new G4Box("centerCoverPlatePart", 1.24*inch, 0.2378*inch, 0.052*inch);//2.44inch by 0.475inch by 0.1inch

   G4SubtractionSolid* 
   centerCoverPlate = new G4SubtractionSolid("centerCoverPlate",centerCoverPlateFull,centerCoverPlatePart,0,G4ThreeVector(0.,0.0625*inch,-0.04*inch));
   
   G4LogicalVolume* logicCenterCoverPlate
   =new G4LogicalVolume(centerCoverPlate, Steel, "logicCenterCoverPlate");
   
   G4VisAttributes * centerCoverPlateVisAtt = new G4VisAttributes(G4Colour(0.5,0.5,0.));//yellow?
   centerCoverPlateVisAtt->SetForceSolid(true);
   logicCenterCoverPlate->SetVisAttributes(centerCoverPlateVisAtt);
   
   
   
   G4VPhysicalVolume* physiCenterCoverPlate1 = new G4PVPlacement(rm45, //rotation 
                                                                 G4ThreeVector(0.,26.3381*mm,-20.388*mm),//y,z 
                                                                 logicCenterCoverPlate,	 //its logical volume      
                                                                 "centerCoverPlate",	 //its name
                                                                 logicWorld, //its mother  volume
                                                                 false,	 //no boolean operation
                                                                 0);	 //copy number
   
   G4VPhysicalVolume* physiCenterCoverPlate2 = new G4PVPlacement(rm315, //rotation 
                                                           G4ThreeVector(0.,20.388*mm,26.3381*mm),//change y,z 
                                                           logicCenterCoverPlate,	 //its logical volume      
                                                           "centerCoverPlate", //its name
                                                           logicWorld,	 //its mother  volume
                                                           false,	 //no boolean operation
                                                           0);	 //copy number
   
   G4VPhysicalVolume* physiCenterCoverPlate3 = new G4PVPlacement(rm225, //rotation 
                                                                 G4ThreeVector(0.,-26.3381*mm,20.388*mm),//change y,z 
                                                                 logicCenterCoverPlate,	 //its logical volume      
                                                                 "centerCoverPlate",	 //its name
                                                                 logicWorld, //its mother  volume
                                                                 false,	 //no boolean operation
                                                                 0);	 //copy number
   
   G4VPhysicalVolume* physiCenterCoverPlate4 = new G4PVPlacement(rm135, //rotation 
                                                                 G4ThreeVector(0.,-20.388*mm,-26.3381*mm),//change y,z 
                                                                 logicCenterCoverPlate,	 //its logical volume      
                                                                 "centerCoverPlate",	 //its name
                                                                 logicWorld, //its mother  volume
                                                                 false,	 //no boolean operation
                                                                 0);	 //copy number
   //20.388mm  26.3381mm
   
//=============================================================================

   

//Al shielding cap============================================================
// 3X front surface of Al shielding cap (none on the plastic telescope side)
//now 2X front surface of Al shielding cap (none for the two plastic scintillators)
   
   
G4Box* frontAlsolid
= new G4Box("frontAlsolid", 4.27*inch, 1.25*inch, 0.8*mm);//now 8.54 inch by 3 inch? maybe 2.5inch instead? Was 3.97 inch by 1.25 inch, same thickness (1.58 mm = 0.0625inch)

G4Box* frontAlwindow
= new G4Box("frontAlwindow", 1.00*inch, 1.00*inch, 0.9*mm);//still 2 inch by 2 inch opening (remember half_x, half_y, etc.)

   
G4SubtractionSolid*
frontAlcap = new G4SubtractionSolid("frontAlcap",
frontAlsolid,frontAlwindow,0,G4ThreeVector(0.,0.,0.));

G4LogicalVolume* logicfrontAlcap = new G4LogicalVolume(frontAlcap,	 //its solid
 Aluminum,	 //its material
 "logicfrontAlcap");	 //its name
   
   G4VisAttributes * frontAlcapVisAtt = new G4VisAttributes(G4Colour(0.5,0.,0.5));//purple
   //frontAlcapVisAtt->SetForceSolid(true);
   frontAlcapVisAtt->SetForceWireframe(true);
   logicfrontAlcap->SetVisAttributes(frontAlcapVisAtt);


G4PVPlacement* physifrontAlcap_T = new G4PVPlacement(rm270,	 //rotation   //modify for new MCP
G4ThreeVector(0.,41.731*mm,0.),  //was 37.49875mm
logicfrontAlcap,	 //its logical volume
"physifrontAlcap_T",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number
   
   
    

    
G4PVPlacement* physifrontAlcap_R = new G4PVPlacement(0,	 //no rotation
//G4ThreeVector(0.,0.,-41.731*mm),
G4ThreeVector(0.,0.,41.731*mm), //Added by bswang (12/18/2014)
logicfrontAlcap,	 //its logical volume   
"physifrontAlcap_R",	 //its name
logicWorld,	 //its mother  volume
false,	 //no boolean operation
0);	 //copy number
    
    
//=============================================================================
   
   

   
//3 detector mounting plates (none on the plastic telescope side)=============

G4Box* solidMountPlate = new G4Box("solidMountPlate",4.75*inch,1.5*inch,1.6*mm);

G4LogicalVolume* logicMountPlate = new G4LogicalVolume(solidMountPlate,
  Steel,
  "logicMountPlate");


/*G4PVPlacement* physiMountPlate_T = new G4PVPlacement(rm90,
G4ThreeVector(0.,70.6*mm,0.),//modify for new MCP setup?
logicMountPlate,
"physiMountPlate_T",
logicWorld,
false,
0);
    

G4PVPlacement* physiMountPlate_B = new G4PVPlacement(rm90,
G4ThreeVector(0.,-70.6*mm,0.),//not needed since there's a scint. on bottom?
logicMountPlate,
"physiMountPlate_B",
logicWorld,
false,
0);

G4PVPlacement* physiMountPlate_R = new G4PVPlacement(0,
G4ThreeVector(0.,0.,-70.6*mm),//modify for new MCP setup?
logicMountPlate,
"physiMountPlate_R",
logicWorld,
false,
0);
    */


//4 "second shields", stainless steel instead

//G4Box* solidSecondShieldBox = new G4Box("solidSecondShieldBox",109.5*mm,32.5*mm,0.205*mm);//219mm by 65mm by same thickness? == Commented out by bswang, 5/27/2015
G4Box* solidSecondShieldBox = new G4Box("solidSecondShieldBox",109.5*mm,32.5*mm,0.127*mm);//Added by bswang, 5/27/2015 (0.01 inches thick)

//G4Box* solidSecondShieldWindow = new G4Box("solidSecondShieldWindow",22.*mm,22.*mm,0.206*mm);//44 mm by 44 mm window  == Commented out by bswang, 5/27/2015
//G4Box* solidSecondShieldWindow = new G4Box("solidSecondShieldWindow",24.*mm,24.*mm,0.129*mm);//Added by bswang, 5/27/2015 (48 mm by 48 mm window), Commented out by bswang, 6/7/2016
G4Box* solidSecondShieldWindow = new G4Box("solidSecondShieldWindow",22.*mm,22.*mm,0.129*mm);//Added by bswang, 6/7/2016 (44 mm by 44 mm window)

G4SubtractionSolid*
solidSecondShield = new G4SubtractionSolid("solidSecondShield",
solidSecondShieldBox,solidSecondShieldWindow,0,G4ThreeVector(0.,0.,0.));

G4LogicalVolume* logicSecondShield = new G4LogicalVolume(solidSecondShield,
  Steel,//Steel instead of Aluminum?
  "logicMountPlate");
   
   G4VisAttributes * shieldVisAtt = new G4VisAttributes(G4Colour(0.8,0.4,0.5));//pink
   //shieldVisAtt->SetForceSolid(true);
   shieldVisAtt->SetForceWireframe(true);
   logicSecondShield->SetVisAttributes(shieldVisAtt);
   

G4PVPlacement* physiSecondShield_T = new G4PVPlacement(rm90,
//G4ThreeVector(0.,36.5*mm,0.*mm),//may subtract 3mm from this? since diff L brackets...  (commented out by bswang, 6/7/2016)
G4ThreeVector(0.,(39.5*mm + 0.127*mm),0.*mm),//added by bswang, 6/7/2016
logicSecondShield,
"physiSecondShield_T",
logicWorld,
false,
0);
    
//debating a 1mm adjustment to compensate for where shield overlaps ceramic pieces, also don't want gaps
G4PVPlacement* physiSecondShield_B = new G4PVPlacement(rm90,
//G4ThreeVector(0.,-36.5*mm,0.*mm),//was 39.5mm, now 36.5mm (commented out by bswang, 6/7/2016)
G4ThreeVector(0.,-(39.5*mm + 0.127*mm),0.*mm),//added by bswang, 6/7/2016
logicSecondShield,
"physiSecondShield_B",
logicWorld,
false,
0);

G4PVPlacement* physiSecondShield_L = new G4PVPlacement(0,
//G4ThreeVector(0.,0.*mm,36.5*mm), //commented out by bswang, 6/7/2016
G4ThreeVector(0.,0.*mm,(39.5*mm + 0.127*mm)), //added by bswang, 6/7/2016
logicSecondShield,
"physiSecondShield_L",
logicWorld,
false,
0);

G4PVPlacement* physiSecondShield_R = new G4PVPlacement(0,
//G4ThreeVector(0.,0.*mm,-36.5*mm), //commented out by bswang, 6/7/2016
G4ThreeVector(0.,0.*mm,-(39.5*mm + 0.127*mm)), //added by bswang, 6/7/2016
logicSecondShield,
"physiSecondShield_R",
logicWorld,
false,
0);
    
//=============================================================================


// Two end plates 6"x6"x3mm  ---  modify from new drawings====================

G4Box* solidEndPlateFull = new G4Box("solidEndPlateFull",3*inch,3*inch,1.5875*mm);//still 6inch by 6inch, thickness was 6mm, now 3.175mm
   
   G4Tubs* solidEndPlateHole = new G4Tubs("solidEndPlateHole",0.*mm,5.*mm,1.6*mm,0.*deg,360.*deg);
   
   G4SubtractionSolid* solidEndPlate = new G4SubtractionSolid("solidEndPlateFinal",solidEndPlateFull,solidEndPlateHole,0,G4ThreeVector(0.,0.,0.));
   

G4LogicalVolume* logicEndPlate = new G4LogicalVolume(solidEndPlate,
Steel,
"logicEndPlate");
   
   G4VisAttributes * endPlateVisAtt = new G4VisAttributes(G4Colour(0.5,0.2,0.));
   //endPlateVisAtt->SetForceSolid(true);
   endPlateVisAtt->SetForceWireframe(true);
   logicEndPlate->SetVisAttributes(endPlateVisAtt);
   

G4PVPlacement* physiEndPlate_U = new G4PVPlacement(rmy90,
G4ThreeVector(143.5875*mm,0.,0.),//was 145mm, subtract 1.4125mm
logicEndPlate,
"physiEndPlate_U",
logicWorld,
false,
0);

G4PVPlacement* physiEndPlate_D = new G4PVPlacement(rmy90,
  G4ThreeVector(-143.5875*mm,0.,0.),
  logicEndPlate,
  "physiEndPlate_D",
  logicWorld,
  false,
  0);
    
//=============================================================================
   


//need nipple part of endplates================================================
   
   G4Tubs* solidEndPlateNipple = new G4Tubs("solidEndPlateNipple",5.*mm,7.*mm,8.4074*mm,0.*deg,360.*deg);//just part that sticks out, no overlapping
   
   G4LogicalVolume* logicEndPlateNipple = new G4LogicalVolume(solidEndPlateNipple,
Steel,
"logicEndPlateNipple");
   
   G4VisAttributes * NippleVisAtt = new G4VisAttributes(G4Colour(0.5,0.2,0.));//?
   NippleVisAtt->SetForceSolid(true);
   //NippleVisAtt->SetForceWireframe(true);
   logicEndPlateNipple->SetVisAttributes(NippleVisAtt);
   
   
   G4PVPlacement* physiEndPlateNipple_U = new G4PVPlacement(rmy90,
                                                      G4ThreeVector(133.5926*mm,0.,0.),//
                                                      logicEndPlateNipple,
                                                      "physiEndPlateNipple_U",
                                                      logicWorld,
                                                      false,
                                                      0);
   
   G4PVPlacement* physiEndPlateNipple_D = new G4PVPlacement(rmy90,
                                                            G4ThreeVector(-133.5926*mm,0.,0.),//
                                                            logicEndPlateNipple,
                                                            "physiEndPlateNipple_D",
                                                            logicWorld,
                                                            false,
                                                            0);

//=============================================================================



// 4 Frame rails Gang Li version which intersects electrodes==================

//G4Box* frame_box = new G4Box("frame_box", 122.5*mm,29/2*mm,29/2*mm);
//G4Box* frame_cut = new G4Box("frame_cut", 123*mm,41/2*mm,41/2*mm);
//G4SubtractionSolid* frame_solid = new G4SubtractionSolid("frame_solid",frame_box,frame_cut,rmy135,G4ThreeVector(0,14.5,14.5) );

//G4LogicalVolume* frame_log  = new G4LogicalVolume(frame_solid,Steel,"frame_log",0,0,0);

//G4PVPlacement* frameUL_phys = new G4PVPlacement(rm90,G4ThreeVector(0.,53.55*mm,51.85*mm),frame_log,"frameUL_phys",logicWorld,false,0);
//G4PVPlacement* frameUR_phys = new G4PVPlacement(rm180,G4ThreeVector(0.,53.55*mm,-51.85*mm),frame_log,"frameUR_phys",logicWorld,false,0);
//G4PVPlacement* frameDL_phys = new G4PVPlacement(0,G4ThreeVector(0.,-53.55*mm,51.85*mm),frame_log,"frameDL_phys",logicWorld,false,0);
//G4PVPlacement* frameDR_phys = new G4PVPlacement(rm270,G4ThreeVector(0.,-53.55*mm,-51.85*mm),frame_log,"frameDR_phys",logicWorld,false,0);


// 4 frame rails 1.2414"x1.2414"x10.474" cut into triangles then placed on both sides of electrodes

G4Box* frame_box = new G4Box("frame_box", 122.5*mm,0.6207*inch,0.6207*inch);
G4Box* frame_cut = new G4Box("frame_cut", 123.*mm,0.8778*inch,0.8778*inch);
G4SubtractionSolid* frame_solid = new G4SubtractionSolid("frame_solid",frame_box,frame_cut,rm45,G4ThreeVector(0.,0.6207*inch,0.6207*inch) );

G4LogicalVolume* frame_log  = new G4LogicalVolume(frame_solid,Steel,"frame_log",0,0,0);
   

//G4PVPlacement* frameUL_phys = new G4PVPlacement(rm90,G4ThreeVector(0.,53.55*mm,58.*mm),frame_log,"frameUL_phys",logicWorld,false,0);
G4PVPlacement* frameUL_phys = new G4PVPlacement(rm270,G4ThreeVector(0.,58*mm,53.55*mm),frame_log,"frameUL_phys",logicWorld,false,0);  //Changed by bswang (12/18/2014)
//G4PVPlacement* frameUR_phys = new G4PVPlacement(rm180,G4ThreeVector(0.,58*mm,-53.55*mm),frame_log,"frameUR_phys",logicWorld,false,0);
G4PVPlacement* frameUR_phys = new G4PVPlacement(0,G4ThreeVector(0.,53.55*mm,-58*mm),frame_log,"frameUR_phys",logicWorld,false,0);  //Changed by bswang (12/18/2014)
//G4PVPlacement* frameDL_phys = new G4PVPlacement(0,G4ThreeVector(0.,-58*mm,53.55*mm),frame_log,"frameDL_phys",logicWorld,false,0);
G4PVPlacement* frameDL_phys = new G4PVPlacement(rm180,G4ThreeVector(0.,-53.55*mm,58*mm),frame_log,"frameDL_phys",logicWorld,false,0);  //Changed by bswang (12/18/2014)
//G4PVPlacement* frameDR_phys = new G4PVPlacement(rm270,G4ThreeVector(0.,-53.55*mm,-58.*mm),frame_log,"frameDR_phys",logicWorld,false,0);
G4PVPlacement* frameDR_phys = new G4PVPlacement(rm90,G4ThreeVector(0.,-58*mm,-53.55*mm),frame_log,"frameDR_phys",logicWorld,false,0);  //Changed by bswang (12/18/2014)


   /*
G4PVPlacement* frameULtwo_phys = new G4PVPlacement(rm270,G4ThreeVector(0.,58.*mm,53.55*mm),frame_log,"frameUL_phystwo",logicWorld,false,0);
G4PVPlacement* frameURtwo_phys = new G4PVPlacement(0,G4ThreeVector(0.,53.55*mm,-58*mm),frame_log,"frameUR_phystwo",logicWorld,false,0);
G4PVPlacement* frameDLtwo_phys = new G4PVPlacement(rm180,G4ThreeVector(0.,-53.55*mm,58*mm),frame_log,"frameDL_phystwo",logicWorld,false,0);
G4PVPlacement* frameDRtwo_phys = new G4PVPlacement(rm90,G4ThreeVector(0.,-58.*mm,-53.55*mm),frame_log,"frameDR_phystwo",logicWorld,false,0);
*/
    

//=============================================================================



// 4 frame rail sides==========================================================

G4Box* frameF_box    = new G4Box("frameF_box", 3*inch,3*inch,7.5*mm);
G4Box* frameHole_box = new G4Box("frameHole_box", 60*mm,60*mm,7.6*mm);
G4SubtractionSolid* frameSide_solid = new G4SubtractionSolid("frameSide_solid",frameF_box,frameHole_box);

G4LogicalVolume* frameSide_log = new G4LogicalVolume(frameSide_solid,Steel,"frameSide_log",0,0,0);

G4PVPlacement* frameSideU_phys = new G4PVPlacement(rmy90,G4ThreeVector(133.5*mm,0.,0.),frameSide_log,"frameSideU_phys",logicWorld,false,0);
G4PVPlacement* frameSideD_phys = new G4PVPlacement(rmy90,G4ThreeVector(-133.5*mm,0.,0.),frameSide_log,"frameSideD_phys",logicWorld,false,0);

//=============================================================================



//===Right 80% HPGe Detector (Added by bswang)==========================

//Crystal length
  //G4double CL_right = 78*mm; 
  G4double CL_right = 72.7*mm; 
//Crystal length decrease
  G4double CL_dec_right = 0*mm;

//Crystal hole length
  G4double HL_right = 61.9*mm;

//Crystal outer diameter
  //G4double COD_right = 81.5*mm;
  //G4double COD_right = 65.0*mm;
  //G4double COD_right = 67.0*mm;
  G4double COD_right = 76.1*mm;

//Crystal inner diameter (i.e., hole diameter)
  G4double CID_right = 11.5*mm; 

//Inner dead layer front thickness increase
  G4double DLIF_inc_right = 0*mm;
//Inner dead layer side thickness increase
  G4double DLIS_inc_right = 0*mm;
//Inner dead layer front thickness
  G4double DLIF_right = 0.0003*mm+DLIF_inc_right;
//Inner dead layer side thickness
  G4double DLIS_right = 0.0003*mm+DLIS_inc_right;

//Outer dead layer front thickness increase
  //G4double DLOF_inc_right = 0*mm;
  G4double DLOF_inc_right = 0.25*mm;
  //G4double DLOF_inc_right = 1*mm;
//Outer dead layer side thickness increase
  //G4double DLOS_inc_right = 0*mm;
  G4double DLOS_inc_right = 0.25*mm;
  //G4double DLOS_inc_right = 1*mm;
//Outer dead layer front thickness;
  G4double DLOF_right = 0.7*mm+DLOF_inc_right;
//Outer dead layer side thickness;
  G4double DLOS_right = 0.7*mm+DLOS_inc_right;

//Back dead layer thickness
  G4double DLB_right = 0*mm; 

//Distance between back of re-entrant port and front of detector endcap
  //G4double PortEndcapDist_right = 7.5*mm;
  G4double PortEndcapDist_right = 7.5*mm + 12*mm;

//Thickness and diameter of detector endcap
  G4double EndcapThickness_right = 1.5*mm;  
  G4double EndcapDiameter_right = 95*mm;  //Don't know this value yet 

//Distance between back of detector endcap and front of crystal
  G4double EndcapCrystalDist_right = 4*mm; 

//Distance between front of crystal and front of re-entrant port
  //G4double CPD_right = 10.175*mm;
  G4double CPD_right = 3.175*mm + PortEndcapDist_right + EndcapThickness_right + EndcapCrystalDist_right;

//Parameters from detector diagram
  G4double A_ht_right = DLOF_right;
  G4double B_ht_right = CL_right-CL_dec_right-DLOF_right;
  G4double C_ht_right = DLIF_right;
  G4double D_ht_right = HL_right-CL_dec_right;
  G4double E_ht_right = CL_right-HL_right-DLOF_right-DLIF_right;
  G4double F_ht_right = HL_right-CL_dec_right+DLIF_right-DLB_right;
  G4double G_ht_right = DLB_right;
  G4double R1_right = CID_right/2;
  G4double R2_right = CID_right/2+DLIS_right;
  G4double R3_right = COD_right/2-DLOS_right;
  G4double R4_right = COD_right/2;
  G4double PD_right = 7.493*cm; //Distance from center of trap to front of re-entrant port 

//---------------------------------------------------------------------------

//Detector dead layer (outer front) 
  G4double OuterDeadLayerFrontInnerRadius_right = 0*cm;
  G4double OuterDeadLayerFrontOuterRadius_right = R4_right;
  G4double OuterDeadLayerFrontHeight_right = A_ht_right;
  G4double OuterDeadLayerFrontStartAngle_right = 0*deg;
  G4double OuterDeadLayerFrontSpanAngle_right = 360*deg;

  G4Tubs* solidOuterDeadLayerFront_right 
  = new G4Tubs("OuterDeadLayerFront_right",		        	//its name
                      OuterDeadLayerFrontInnerRadius_right,OuterDeadLayerFrontOuterRadius_right,OuterDeadLayerFrontHeight_right/2,OuterDeadLayerFrontStartAngle_right,OuterDeadLayerFrontSpanAngle_right); //dimensions
                       

  G4LogicalVolume* logicOuterDeadLayerFront_right = new G4LogicalVolume(solidOuterDeadLayerFront_right,  	//its solid
                                       Germanium,	//its material
                                       "OuterDeadLayerFront_right");	//its name
  G4double OuterDeadLayerFrontPosX_right = 0*cm;
  G4double OuterDeadLayerFrontPosY_right = 0*cm;
  G4double OuterDeadLayerFrontPosZ_right = PD_right+CPD_right+(A_ht_right/2); 

  G4PVPlacement* physiOuterDeadLayerFront_right = new G4PVPlacement(0,	        	//no rotation
                                     G4ThreeVector(OuterDeadLayerFrontPosX_right,OuterDeadLayerFrontPosY_right,OuterDeadLayerFrontPosZ_right),	//its position in World 
                                     logicOuterDeadLayerFront_right,	//its logical volume				     
                                     "OuterDeadLayerFront_right",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector dead layer (outer side) 
  G4double OuterDeadLayerSideInnerRadius_right = R3_right;
  G4double OuterDeadLayerSideOuterRadius_right = R4_right;
  G4double OuterDeadLayerSideHeight_right = B_ht_right;
  G4double OuterDeadLayerSideStartAngle_right = 0*deg;
  G4double OuterDeadLayerSideSpanAngle_right = 360*deg;

  G4Tubs* solidOuterDeadLayerSide_right 
  = new G4Tubs("OuterDeadLayerSide_right",		        	//its name
                      OuterDeadLayerSideInnerRadius_right,OuterDeadLayerSideOuterRadius_right,OuterDeadLayerSideHeight_right/2,OuterDeadLayerSideStartAngle_right,OuterDeadLayerSideSpanAngle_right); //dimensions
                       

  G4LogicalVolume* logicOuterDeadLayerSide_right = new G4LogicalVolume(solidOuterDeadLayerSide_right,  	//its solid
                                       Germanium,	//its material
                                       "OuterDeadLayerSide_right");	//its name
  G4double OuterDeadLayerSidePosX_right = 0*cm;
  G4double OuterDeadLayerSidePosY_right = 0*cm;
  G4double OuterDeadLayerSidePosZ_right = PD_right+CPD_right+A_ht_right+(B_ht_right/2); 

  G4PVPlacement* physiOuterDeadLayerSide_right = new G4PVPlacement(0,	        	//no rotation
                                     G4ThreeVector(OuterDeadLayerSidePosX_right,OuterDeadLayerSidePosY_right,OuterDeadLayerSidePosZ_right),	//its position in World 
                                     logicOuterDeadLayerSide_right,	//its logical volume				     
                                     "OuterDeadLayerSide_right",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector dead layer (inner front) 
  G4double InnerDeadLayerFrontInnerRadius_right = 0*cm;
  G4double InnerDeadLayerFrontOuterRadius_right = R2_right;
  G4double InnerDeadLayerFrontHeight_right = C_ht_right;
  G4double InnerDeadLayerFrontStartAngle_right = 0*deg;
  G4double InnerDeadLayerFrontSpanAngle_right = 360*deg;

  G4Tubs* solidInnerDeadLayerFront_right 
  = new G4Tubs("InnerDeadLayerFront_right",		        	//its name
                      InnerDeadLayerFrontInnerRadius_right,InnerDeadLayerFrontOuterRadius_right,InnerDeadLayerFrontHeight_right/2,InnerDeadLayerFrontStartAngle_right,InnerDeadLayerFrontSpanAngle_right); //dimensions
                       

  G4LogicalVolume* logicInnerDeadLayerFront_right = new G4LogicalVolume(solidInnerDeadLayerFront_right,  	//its solid
                                       Germanium,	//its material
                                       "InnerDeadLayerFront_right");	//its name
  G4double InnerDeadLayerFrontPosX_right = 0*cm;
  G4double InnerDeadLayerFrontPosY_right = 0*cm;
  G4double InnerDeadLayerFrontPosZ_right = PD_right+CPD_right+A_ht_right+E_ht_right+(C_ht_right/2); 

  G4PVPlacement* physiInnerDeadLayerFront_right = new G4PVPlacement(0,	        	//no rotation
                                     G4ThreeVector(InnerDeadLayerFrontPosX_right,InnerDeadLayerFrontPosY_right,InnerDeadLayerFrontPosZ_right),	//its position in World 
                                     logicInnerDeadLayerFront_right,	//its logical volume				     
                                     "InnerDeadLayerFront_right",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector dead layer (inner side) 
  G4double InnerDeadLayerSideInnerRadius_right = R1_right; 
  G4double InnerDeadLayerSideOuterRadius_right = R2_right;
  G4double InnerDeadLayerSideHeight_right = D_ht_right;
  G4double InnerDeadLayerSideStartAngle_right = 0*deg;
  G4double InnerDeadLayerSideSpanAngle_right = 360*deg;

  G4Tubs* solidInnerDeadLayerSide_right 
  = new G4Tubs("InnerDeadLayerSide_right",		        	//its name
                      InnerDeadLayerSideInnerRadius_right,InnerDeadLayerSideOuterRadius_right,InnerDeadLayerSideHeight_right/2,InnerDeadLayerSideStartAngle_right,InnerDeadLayerSideSpanAngle_right); //dimensions
                       

  G4LogicalVolume* logicInnerDeadLayerSide_right = new G4LogicalVolume(solidInnerDeadLayerSide_right,  	//its solid
                                       Germanium,	//its material
                                       "InnerDeadLayerSide_right");	//its name
  G4double InnerDeadLayerSidePosX_right = 0*cm;
  G4double InnerDeadLayerSidePosY_right = 0*cm;
  G4double InnerDeadLayerSidePosZ_right = PD_right+CPD_right+A_ht_right+E_ht_right+C_ht_right+(D_ht_right/2); 

  G4PVPlacement* physiInnerDeadLayerSide_right = new G4PVPlacement(0,	        	//no rotation
                                     G4ThreeVector(InnerDeadLayerSidePosX_right,InnerDeadLayerSidePosY_right,InnerDeadLayerSidePosZ_right),	//its position in World 
                                     logicInnerDeadLayerSide_right,	//its logical volume				     
                                     "InnerDeadLayerSide_right",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//HPGe crystal (end)
  G4double GeCrystalEndInnerRadius_right = 0*cm;
  G4double GeCrystalEndOuterRadius_right = R3_right;
  G4double GeCrystalEndHeight_right = E_ht_right;
  G4double GeCrystalEndStartAngle_right = 0*deg;
  G4double GeCrystalEndSpanAngle_right = 360*deg;

  G4Tubs* solidGeCrystalEnd_right 
  = new G4Tubs("GeCrystalEnd_right",		        	//its name
                      GeCrystalEndInnerRadius_right,GeCrystalEndOuterRadius_right,GeCrystalEndHeight_right/2,GeCrystalEndStartAngle_right,GeCrystalEndSpanAngle_right); //dimensions
                       
    
//HPGe crystal (body)
  G4double GeCrystalBodyInnerRadius_right = R2_right;
  G4double GeCrystalBodyOuterRadius_right = R3_right;
  G4double GeCrystalBodyHeight_right = F_ht_right;
  G4double GeCrystalBodyStartAngle_right = 0*deg;
  G4double GeCrystalBodySpanAngle_right = 360*deg;

  G4Tubs* solidGeCrystalBody_right 
  = new G4Tubs("GeCrystalBody_right",		        	//its name
                      GeCrystalBodyInnerRadius_right,GeCrystalBodyOuterRadius_right,GeCrystalBodyHeight_right/2,GeCrystalBodyStartAngle_right,GeCrystalBodySpanAngle_right); //dimensions
                       

//HPGe crystal    
  G4double GeCrystalBodyTransX_right = 0*cm;
  G4double GeCrystalBodyTransY_right = 0*cm;
  G4double GeCrystalBodyTransZ_right = (E_ht_right/2)+(F_ht_right/2);
 
  G4UnionSolid* solidGeCrystal_right
  = new G4UnionSolid("GeCrystal_right",                  //its name
                     solidGeCrystalEnd_right,solidGeCrystalBody_right,  //solids to be joined  
                      0,                           //no rotation
                      G4ThreeVector(GeCrystalBodyTransX_right,GeCrystalBodyTransY_right,GeCrystalBodyTransZ_right)); //translation of GeCrystalBody
  
  G4LogicalVolume* logicGeCrystal_right = new G4LogicalVolume(solidGeCrystal_right,  	//its solid
                                       Germanium,	//its material
                                       "GeCrystal_right");	//its name
  G4double GeCrystalPosX_right = 0*cm;
  G4double GeCrystalPosY_right = 0*cm;
  G4double GeCrystalPosZ_right = PD_right+CPD_right+A_ht_right+(E_ht_right/2); 

  G4PVPlacement* physiGeCrystal_right = new G4PVPlacement(0,	        	//no rotation
                                     G4ThreeVector(GeCrystalPosX_right,GeCrystalPosY_right,GeCrystalPosZ_right),	//its position in World 
                                     logicGeCrystal_right,	//its logical volume				     
                                     "GeCrystal_right",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector endcap (Right)
  G4double DetEndcap_rightInnerRadius = 0*cm;
  G4double DetEndcap_rightOuterRadius = EndcapDiameter_right/2;  
  G4double DetEndcap_rightHeight = EndcapThickness_right;
  G4double DetEndcap_rightStartAngle = 0*deg;
  G4double DetEndcap_rightSpanAngle = 360*deg;

  G4Tubs* solidDetEndcap_right 
  = new G4Tubs("DetEndcap_right",		        	//its name
                      DetEndcap_rightInnerRadius,DetEndcap_rightOuterRadius,DetEndcap_rightHeight/2,DetEndcap_rightStartAngle,DetEndcap_rightSpanAngle); //dimensions

  G4LogicalVolume* logicDetEndcap_right = new G4LogicalVolume(solidDetEndcap_right,  	//its solid
                                       Aluminum,	//its material
                                       "DetEndcap_right");	//its name
  G4double DetEndcap_rightPosX = 0*cm;
  G4double DetEndcap_rightPosY = 0*cm;
  G4double DetEndcap_rightPosZ = PD_right + 3.175*mm + PortEndcapDist_right + EndcapThickness_right/2; 

  G4PVPlacement* physiDetEndcap_right = new G4PVPlacement(0,	        	//no rotation
                                     G4ThreeVector(DetEndcap_rightPosX,DetEndcap_rightPosY,DetEndcap_rightPosZ),	//its position in World 
                                     logicDetEndcap_right,	//its logical volume				     
                                     "DetEndcap_right",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Visualization

  G4VisAttributes * OuterDeadLayerFront_rightVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  OuterDeadLayerFront_rightVisAtt->SetForceWireframe(true);
  logicOuterDeadLayerFront_right->SetVisAttributes(OuterDeadLayerFront_rightVisAtt);

  G4VisAttributes * OuterDeadLayerSide_rightVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  OuterDeadLayerSide_rightVisAtt->SetForceWireframe(true);
  logicOuterDeadLayerSide_right->SetVisAttributes(OuterDeadLayerSide_rightVisAtt);

  G4VisAttributes * InnerDeadLayerFront_rightVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  InnerDeadLayerFront_rightVisAtt->SetForceWireframe(true);
  logicInnerDeadLayerFront_right->SetVisAttributes(InnerDeadLayerFront_rightVisAtt);

  G4VisAttributes * InnerDeadLayerSide_rightVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  InnerDeadLayerSide_rightVisAtt->SetForceWireframe(true);
  logicInnerDeadLayerSide_right->SetVisAttributes(InnerDeadLayerSide_rightVisAtt);

  G4VisAttributes * GeCrystal_rightVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0));  //Green
  GeCrystal_rightVisAtt->SetForceWireframe(true);
  logicGeCrystal_right->SetVisAttributes(GeCrystal_rightVisAtt);

  G4VisAttributes * DetEndcap_rightVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0));  //Green
  DetEndcap_rightVisAtt->SetForceWireframe(true);
  logicDetEndcap_right->SetVisAttributes(DetEndcap_rightVisAtt);


//===End Right HPGe Detector=============================================


//===Top 140% HPGe Detector (Added by bswang)==========================

//Crystal length
  G4double CL_top = 98.3*mm; 
//Crystal length decrease
  G4double CL_dec_top = 0*mm;

//Crystal hole length
  G4double HL_top = 87.5*mm;  //Don't know this value yet.

//Crystal outer diameter
  //G4double COD_top = 81.5*mm;
  //G4double COD_top = 80*mm;
  G4double COD_top = 89.9*mm;

//Crystal inner diameter (i.e., hole diameter)
  G4double CID_top = 11.5*mm;  //Don't know this value yet. 

//Inner dead layer front thickness increase
  G4double DLIF_inc_top = 0*mm;
//Inner dead layer side thickness increase
  G4double DLIS_inc_top = 0*mm;
//Inner dead layer front thickness
  G4double DLIF_top = 0.0003*mm+DLIF_inc_top;
//Inner dead layer side thickness
  G4double DLIS_top = 0.0003*mm+DLIS_inc_top;

//Outer dead layer front thickness increase
  G4double DLOF_inc_top = 0*mm;
  //G4double DLOF_inc_top = 1*mm;
  //G4double DLOF_inc_top = 1.5*mm;
//Outer dead layer side thickness increase
  G4double DLOS_inc_top = 0*mm;
  //G4double DLOS_inc_top = 1*mm;
  //G4double DLOS_inc_top = 1.5*mm;
//Outer dead layer front thickness;
  G4double DLOF_top = 0.7*mm+DLOF_inc_top;
//Outer dead layer side thickness;
  G4double DLOS_top = 0.7*mm+DLOS_inc_top;

//Back dead layer thickness
  G4double DLB_top = 0*mm; 

//Distance between back of re-entrant port and front of detector endcap
  G4double PortEndcapDist_top = 7.5*mm;

//Thickness and diameter of detector endcap
  G4double EndcapThickness_top = 3.5*mm;  
  G4double EndcapDiameter_top = 107.95*mm; 

//Distance between back of detector endcap and front of crystal
  G4double EndcapCrystalDist_top = 6.5*mm; 

//Distance between front of crystal and front of re-entrant port
  //G4double CPD_top = 10.175*mm;
  G4double CPD_top = 3.175*mm + PortEndcapDist_top + EndcapThickness_top + EndcapCrystalDist_top;

//Parameters from detector diagram
  G4double A_ht_top = DLOF_top;
  G4double B_ht_top = CL_top-CL_dec_top-DLOF_top;
  G4double C_ht_top = DLIF_top;
  G4double D_ht_top = HL_top-CL_dec_top;
  G4double E_ht_top = CL_top-HL_top-DLOF_top-DLIF_top;
  G4double F_ht_top = HL_top-CL_dec_top+DLIF_top-DLB_top;
  G4double G_ht_top = DLB_top;
  G4double R1_top = CID_top/2;
  G4double R2_top = CID_top/2+DLIS_top;
  G4double R3_top = COD_top/2-DLOS_top;
  G4double R4_top = COD_top/2;
  G4double PD_top = 7.493*cm; //Distance from center of trap to front of re-entrant port 

//---------------------------------------------------------------------------

//Detector dead layer (outer front) 
  G4double OuterDeadLayerFrontInnerRadius_top = 0*cm;
  G4double OuterDeadLayerFrontOuterRadius_top = R4_top;
  G4double OuterDeadLayerFrontHeight_top = A_ht_top;
  G4double OuterDeadLayerFrontStartAngle_top = 0*deg;
  G4double OuterDeadLayerFrontSpanAngle_top = 360*deg;

  G4Tubs* solidOuterDeadLayerFront_top 
  = new G4Tubs("OuterDeadLayerFront_top",		        	//its name
                      OuterDeadLayerFrontInnerRadius_top,OuterDeadLayerFrontOuterRadius_top,OuterDeadLayerFrontHeight_top/2,OuterDeadLayerFrontStartAngle_top,OuterDeadLayerFrontSpanAngle_top); //dimensions
                       

  G4LogicalVolume* logicOuterDeadLayerFront_top = new G4LogicalVolume(solidOuterDeadLayerFront_top,  	//its solid
                                       Germanium,	//its material
                                       "OuterDeadLayerFront_top");	//its name
  G4double OuterDeadLayerFrontPosX_top = 0*cm;
  G4double OuterDeadLayerFrontPosY_top = PD_top+CPD_top+(A_ht_top/2); 
  G4double OuterDeadLayerFrontPosZ_top = 0*cm;

  G4PVPlacement* physiOuterDeadLayerFront_top = new G4PVPlacement(rm90,	        	//no rotation
                                     G4ThreeVector(OuterDeadLayerFrontPosX_top,OuterDeadLayerFrontPosY_top,OuterDeadLayerFrontPosZ_top),	//its position in World 
                                     logicOuterDeadLayerFront_top,	//its logical volume				     
                                     "OuterDeadLayerFront_top",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector dead layer (outer side) 
  G4double OuterDeadLayerSideInnerRadius_top = R3_top;
  G4double OuterDeadLayerSideOuterRadius_top = R4_top;
  G4double OuterDeadLayerSideHeight_top = B_ht_top;
  G4double OuterDeadLayerSideStartAngle_top = 0*deg;
  G4double OuterDeadLayerSideSpanAngle_top = 360*deg;

  G4Tubs* solidOuterDeadLayerSide_top 
  = new G4Tubs("OuterDeadLayerSide_top",		        	//its name
                      OuterDeadLayerSideInnerRadius_top,OuterDeadLayerSideOuterRadius_top,OuterDeadLayerSideHeight_top/2,OuterDeadLayerSideStartAngle_top,OuterDeadLayerSideSpanAngle_top); //dimensions
                       

  G4LogicalVolume* logicOuterDeadLayerSide_top = new G4LogicalVolume(solidOuterDeadLayerSide_top,  	//its solid
                                       Germanium,	//its material
                                       "OuterDeadLayerSide_top");	//its name
  G4double OuterDeadLayerSidePosX_top = 0*cm;
  G4double OuterDeadLayerSidePosY_top = PD_top+CPD_top+A_ht_top+(B_ht_top/2); 
  G4double OuterDeadLayerSidePosZ_top = 0*cm;

  G4PVPlacement* physiOuterDeadLayerSide_top = new G4PVPlacement(rm90,	        	//no rotation
                                     G4ThreeVector(OuterDeadLayerSidePosX_top,OuterDeadLayerSidePosY_top,OuterDeadLayerSidePosZ_top),	//its position in World 
                                     logicOuterDeadLayerSide_top,	//its logical volume				     
                                     "OuterDeadLayerSide_top",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector dead layer (inner front) 
  G4double InnerDeadLayerFrontInnerRadius_top = 0*cm;
  G4double InnerDeadLayerFrontOuterRadius_top = R2_top;
  G4double InnerDeadLayerFrontHeight_top = C_ht_top;
  G4double InnerDeadLayerFrontStartAngle_top = 0*deg;
  G4double InnerDeadLayerFrontSpanAngle_top = 360*deg;

  G4Tubs* solidInnerDeadLayerFront_top 
  = new G4Tubs("InnerDeadLayerFront_top",		        	//its name
                      InnerDeadLayerFrontInnerRadius_top,InnerDeadLayerFrontOuterRadius_top,InnerDeadLayerFrontHeight_top/2,InnerDeadLayerFrontStartAngle_top,InnerDeadLayerFrontSpanAngle_top); //dimensions
                       

  G4LogicalVolume* logicInnerDeadLayerFront_top = new G4LogicalVolume(solidInnerDeadLayerFront_top,  	//its solid
                                       Germanium,	//its material
                                       "InnerDeadLayerFront_top");	//its name
  G4double InnerDeadLayerFrontPosX_top = 0*cm;
  G4double InnerDeadLayerFrontPosY_top = PD_top+CPD_top+A_ht_top+E_ht_top+(C_ht_top/2); 
  G4double InnerDeadLayerFrontPosZ_top = 0*cm;

  G4PVPlacement* physiInnerDeadLayerFront_top = new G4PVPlacement(rm90,	        	//no rotation
                                     G4ThreeVector(InnerDeadLayerFrontPosX_top,InnerDeadLayerFrontPosY_top,InnerDeadLayerFrontPosZ_top),	//its position in World 
                                     logicInnerDeadLayerFront_top,	//its logical volume				     
                                     "InnerDeadLayerFront_top",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector dead layer (inner side) 
  G4double InnerDeadLayerSideInnerRadius_top = R1_top; 
  G4double InnerDeadLayerSideOuterRadius_top = R2_top;
  G4double InnerDeadLayerSideHeight_top = D_ht_top;
  G4double InnerDeadLayerSideStartAngle_top = 0*deg;
  G4double InnerDeadLayerSideSpanAngle_top = 360*deg;

  G4Tubs* solidInnerDeadLayerSide_top 
  = new G4Tubs("InnerDeadLayerSide_top",		        	//its name
                      InnerDeadLayerSideInnerRadius_top,InnerDeadLayerSideOuterRadius_top,InnerDeadLayerSideHeight_top/2,InnerDeadLayerSideStartAngle_top,InnerDeadLayerSideSpanAngle_top); //dimensions
                       

  G4LogicalVolume* logicInnerDeadLayerSide_top = new G4LogicalVolume(solidInnerDeadLayerSide_top,  	//its solid
                                       Germanium,	//its material
                                       "InnerDeadLayerSide_top");	//its name
  G4double InnerDeadLayerSidePosX_top = 0*cm;
  G4double InnerDeadLayerSidePosY_top = PD_top+CPD_top+A_ht_top+E_ht_top+C_ht_top+(D_ht_top/2); 
  G4double InnerDeadLayerSidePosZ_top = 0*cm;

  G4PVPlacement* physiInnerDeadLayerSide_top = new G4PVPlacement(rm90,	        	//no rotation
                                     G4ThreeVector(InnerDeadLayerSidePosX_top,InnerDeadLayerSidePosY_top,InnerDeadLayerSidePosZ_top),	//its position in World 
                                     logicInnerDeadLayerSide_top,	//its logical volume				     
                                     "InnerDeadLayerSide_top",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//HPGe crystal (end)
  G4double GeCrystalEndInnerRadius_top = 0*cm;
  G4double GeCrystalEndOuterRadius_top = R3_top;
  G4double GeCrystalEndHeight_top = E_ht_top;
  G4double GeCrystalEndStartAngle_top = 0*deg;
  G4double GeCrystalEndSpanAngle_top = 360*deg;

  G4Tubs* solidGeCrystalEnd_top 
  = new G4Tubs("GeCrystalEnd_top",		        	//its name
                      GeCrystalEndInnerRadius_top,GeCrystalEndOuterRadius_top,GeCrystalEndHeight_top/2,GeCrystalEndStartAngle_top,GeCrystalEndSpanAngle_top); //dimensions
                       
    
//HPGe crystal (body)
  G4double GeCrystalBodyInnerRadius_top = R2_top;
  G4double GeCrystalBodyOuterRadius_top = R3_top;
  G4double GeCrystalBodyHeight_top = F_ht_top;
  G4double GeCrystalBodyStartAngle_top = 0*deg;
  G4double GeCrystalBodySpanAngle_top = 360*deg;

  G4Tubs* solidGeCrystalBody_top 
  = new G4Tubs("GeCrystalBody_top",		        	//its name
                      GeCrystalBodyInnerRadius_top,GeCrystalBodyOuterRadius_top,GeCrystalBodyHeight_top/2,GeCrystalBodyStartAngle_top,GeCrystalBodySpanAngle_top); //dimensions
                       

//HPGe crystal    
  G4double GeCrystalBodyTransX_top = 0*cm;
  G4double GeCrystalBodyTransY_top = 0*cm;
  G4double GeCrystalBodyTransZ_top = (E_ht_top/2)+(F_ht_top/2);
 
  G4UnionSolid* solidGeCrystal_top
  = new G4UnionSolid("GeCrystal_top",                  //its name
                     solidGeCrystalEnd_top,solidGeCrystalBody_top,  //solids to be joined  
                      0,                           //no rotation
                      G4ThreeVector(GeCrystalBodyTransX_top,GeCrystalBodyTransY_top,GeCrystalBodyTransZ_top)); //translation of GeCrystalBody
  
  G4LogicalVolume* logicGeCrystal_top = new G4LogicalVolume(solidGeCrystal_top,  	//its solid
                                       Germanium,	//its material
                                       "GeCrystal_top");	//its name
  G4double GeCrystalPosX_top = 0*cm;
  G4double GeCrystalPosY_top = PD_top+CPD_top+A_ht_top+(E_ht_top/2); 
  G4double GeCrystalPosZ_top = 0*cm;

  G4PVPlacement* physiGeCrystal_top = new G4PVPlacement(rm90,	        	//no rotation
                                     G4ThreeVector(GeCrystalPosX_top,GeCrystalPosY_top,GeCrystalPosZ_top),	//its position in World 
                                     logicGeCrystal_top,	//its logical volume				     
                                     "GeCrystal_top",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Detector endcap (Top)
  G4double DetEndcap_topInnerRadius = 0*cm;
  G4double DetEndcap_topOuterRadius = EndcapDiameter_top/2;  
  G4double DetEndcap_topHeight = EndcapThickness_top;
  G4double DetEndcap_topStartAngle = 0*deg;
  G4double DetEndcap_topSpanAngle = 360*deg;

  G4Tubs* solidDetEndcap_top 
  = new G4Tubs("DetEndcap_top",		        	//its name
                      DetEndcap_topInnerRadius,DetEndcap_topOuterRadius,DetEndcap_topHeight/2,DetEndcap_topStartAngle,DetEndcap_topSpanAngle); //dimensions

  G4LogicalVolume* logicDetEndcap_top = new G4LogicalVolume(solidDetEndcap_top,  	//its solid
                                       Aluminum,	//its material
                                       "DetEndcap_top");	//its name
  G4double DetEndcap_topPosX = 0*cm;
  G4double DetEndcap_topPosY = PD_top + 3.175*mm + PortEndcapDist_top + EndcapThickness_top/2; 
  G4double DetEndcap_topPosZ = 0*cm;

  G4PVPlacement* physiDetEndcap_top = new G4PVPlacement(rm90,	        	//no rotation
                                     G4ThreeVector(DetEndcap_topPosX,DetEndcap_topPosY,DetEndcap_topPosZ),	//its position in World 
                                     logicDetEndcap_top,	//its logical volume				     
                                     "DetEndcap_top",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Visualization

  G4VisAttributes * OuterDeadLayerFront_topVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  OuterDeadLayerFront_topVisAtt->SetForceWireframe(true);
  logicOuterDeadLayerFront_top->SetVisAttributes(OuterDeadLayerFront_topVisAtt);

  G4VisAttributes * OuterDeadLayerSide_topVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  OuterDeadLayerSide_topVisAtt->SetForceWireframe(true);
  logicOuterDeadLayerSide_top->SetVisAttributes(OuterDeadLayerSide_topVisAtt);

  G4VisAttributes * InnerDeadLayerFront_topVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  InnerDeadLayerFront_topVisAtt->SetForceWireframe(true);
  logicInnerDeadLayerFront_top->SetVisAttributes(InnerDeadLayerFront_topVisAtt);

  G4VisAttributes * InnerDeadLayerSide_topVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  InnerDeadLayerSide_topVisAtt->SetForceWireframe(true);
  logicInnerDeadLayerSide_top->SetVisAttributes(InnerDeadLayerSide_topVisAtt);

  G4VisAttributes * GeCrystal_topVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0));  //Green
  GeCrystal_topVisAtt->SetForceWireframe(true);
  logicGeCrystal_top->SetVisAttributes(GeCrystal_topVisAtt);

  G4VisAttributes * DetEndcap_topVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,0.0));  //Green
  DetEndcap_topVisAtt->SetForceWireframe(true);
  logicDetEndcap_top->SetVisAttributes(DetEndcap_topVisAtt);



//===End Top HPGe Detector==================================================


//===Top Re-entrant Port (Added by bswang)=============================

  //Outer box 1
  G4double OuterBox1SizeX = 14.605*cm;
  G4double OuterBox1SizeY = 14.605*cm;
  G4double OuterBox1SizeZ = 2.2225*cm;

  G4Box* solidOuterBox1 
  = new G4Box("OuterBox1",		        	//its name
                       OuterBox1SizeX/2,OuterBox1SizeY/2,OuterBox1SizeZ/2); //size
                       
  //Inner box 11
  G4double InnerBox11SizeX = 13.6525*cm;
  G4double InnerBox11SizeY = 13.6525*cm;
  G4double InnerBox11SizeZ = 2.2225*cm; 

  G4Box* solidInnerBox11 
  = new G4Box("InnerBox11",		        	//its name
                       InnerBox11SizeX/2,InnerBox11SizeY/2,InnerBox11SizeZ/2); //size
                       
  //Inner box 12
  G4double InnerBox12SizeX = 12.38504*cm;
  G4double InnerBox12SizeY = 12.38504*cm;
  G4double InnerBox12SizeZ = 2.2225*cm; 

  G4Box* solidInnerBox12 
  = new G4Box("InnerBox12",		        	//its name
                       InnerBox12SizeX/2,InnerBox12SizeY/2,InnerBox12SizeZ/2); //size
                       
  //Box 1    
  G4SubtractionSolid* solidBox1
  = new G4SubtractionSolid("Box1",                  //its name
                     solidOuterBox1,solidInnerBox11,  //solid1 - solid2  
                      0,                           //no rotation
                      G4ThreeVector(0,0,0.3175*cm)); //translation of solid2 
  
  G4SubtractionSolid* solidTopReentrantPort
  = new G4SubtractionSolid("TopReentrantPort",                  //its name
                     solidBox1,solidInnerBox12,  //solid1 - solid2  
                      0,                           //no rotation
                      G4ThreeVector(0,0,-2.06248*cm)); //translation of solid2 
  G4LogicalVolume* logicTopReentrantPort = new G4LogicalVolume(solidTopReentrantPort,  	//its solid
                                       Steel,	//its material
                                       "TopReentrantPort");	//its name
//  G4LogicalVolume* logicBox1 = new G4LogicalVolume(solidBox1,  	//its solid
//                                       Steel,	//its material
//                                       "Box1");	//its name

  G4double TopReentrantPortPosX = 0*cm;
  G4double TopReentrantPortPosY = 0*cm;
  G4double TopReentrantPortPosZ = PD_right + 1.11125*cm; 

  G4PVPlacement* physiTopReentrantPort = new G4PVPlacement(0,	        	//no rotation
                                     G4ThreeVector(TopReentrantPortPosX,TopReentrantPortPosY,TopReentrantPortPosZ),	//its position in World 
                                     logicTopReentrantPort,	//its logical volume				     
                                     "TopReentrantPort",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Visualization

  G4VisAttributes * TopReentrantPortVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  TopReentrantPortVisAtt->SetForceWireframe(true);
  logicTopReentrantPort->SetVisAttributes(TopReentrantPortVisAtt);

//===End Top Re-entrant Port=================================================



//===Right Re-entrant Port (Added by bswang)=============================

  //Outer box 1
  G4double OuterBox2SizeX = 14.605*cm;
  G4double OuterBox2SizeY = 14.605*cm;
  G4double OuterBox2SizeZ = 2.2225*cm;

  G4Box* solidOuterBox2 
  = new G4Box("OuterBox2",		        	//its name
                       OuterBox2SizeX/2,OuterBox2SizeY/2,OuterBox2SizeZ/2); //size
                       
  //Inner box 11
  G4double InnerBox21SizeX = 13.6525*cm;
  G4double InnerBox21SizeY = 13.6525*cm;
  G4double InnerBox21SizeZ = 2.2225*cm; 

  G4Box* solidInnerBox21 
  = new G4Box("InnerBox21",		        	//its name
                       InnerBox21SizeX/2,InnerBox21SizeY/2,InnerBox21SizeZ/2); //size
                       
  //Inner box 12
  G4double InnerBox22SizeX = 12.38504*cm;
  G4double InnerBox22SizeY = 12.38504*cm;
  G4double InnerBox22SizeZ = 2.2225*cm; 

  G4Box* solidInnerBox22 
  = new G4Box("InnerBox22",		        	//its name
                       InnerBox22SizeX/2,InnerBox22SizeY/2,InnerBox22SizeZ/2); //size
                       
  //Box 1    
  G4SubtractionSolid* solidBox2
  = new G4SubtractionSolid("Box2",                  //its name
                     solidOuterBox2,solidInnerBox21,  //solid1 - solid2  
                      0,                           //no rotation
                      G4ThreeVector(0,0,0.3175*cm)); //translation of solid2 
  
  G4SubtractionSolid* solidRightReentrantPort
  = new G4SubtractionSolid("RightReentrantPort",                  //its name
                     solidBox2,solidInnerBox22,  //solid1 - solid2  
                      0,                           //no rotation
                      G4ThreeVector(0,0,-2.06248*cm)); //translation of solid2 
  G4LogicalVolume* logicRightReentrantPort = new G4LogicalVolume(solidRightReentrantPort,  	//its solid
                                       Steel,	//its material
                                       "RightReentrantPort");	//its name
//  G4LogicalVolume* logicBox2 = new G4LogicalVolume(solidBox2,  	//its solid
//                                       Steel,	//its material
//                                       "Box2");	//its name

  G4double RightReentrantPortPosX = 0*cm;
  G4double RightReentrantPortPosY = PD_right + 1.11125*cm; 
  G4double RightReentrantPortPosZ = 0*cm;

  G4PVPlacement* physiRightReentrantPort = new G4PVPlacement(rm90,	        	//no rotation
                                     G4ThreeVector(RightReentrantPortPosX,RightReentrantPortPosY,RightReentrantPortPosZ),	//its position in World 
                                     logicRightReentrantPort,	//its logical volume				     
                                     "RightReentrantPort",		//its name
                                     logicWorld,	//its mother  volume
                                     false,		//no boolean operation
                                     0);		//copy number     

//---------------------------------------------------------------------------

//Visualization

  G4VisAttributes * RightReentrantPortVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));  //Yellow
  RightReentrantPortVisAtt->SetForceWireframe(true);
  logicRightReentrantPort->SetVisAttributes(RightReentrantPortVisAtt);

//===End Right Re-entrant Port=================================================



	
	//  Sensitive detector
	
	PlasSD* left_dE = new PlasSD("left_dE");
	PlasSD* left_E = new PlasSD("left_E");
	PlasSD* bot_dE = new PlasSD("bot_dE");
	PlasSD* bot_E = new PlasSD("bot_E");
	PlasSD* top_HPGe = new PlasSD("top_HPGe");  //Added by bswang
	PlasSD* right_HPGe = new PlasSD("right_HPGe");  //Added by bswang

	G4SDManager* SDman = G4SDManager::GetSDMpointer();

	SDman->AddNewDetector(left_dE);
	SDman->AddNewDetector(left_E);
	SDman->AddNewDetector(bot_dE);
	SDman->AddNewDetector(bot_E);
	SDman->AddNewDetector(top_HPGe);  //Added by bswang
	SDman->AddNewDetector(right_HPGe);  //Added by bswang

	logicdE1->SetSensitiveDetector(left_dE);
	logicE1->SetSensitiveDetector(left_E);
	logicdE2->SetSensitiveDetector(bot_dE);
	logicE2->SetSensitiveDetector(bot_E);
        logicGeCrystal_top->SetSensitiveDetector(top_HPGe);  //Added by bswang
        logicGeCrystal_right->SetSensitiveDetector(right_HPGe);  //Added by bswang
	
	return physiWorld;
}
