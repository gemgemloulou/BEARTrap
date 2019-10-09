/*
bdn_efficiency_subsort3.cpp

This version of the subsort code is identical to 
bdn_efficiency_subsort2.cpp, except for the following modifications:

6/9/2016 (bswang): The addresses of "s", "g", and "m" were cast as void when setting the branch addresses for "oldtree."  This gets rid of an error message from root complaining that s, g, and m are of the incorrect type. 

*/


#include "TMath.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH1I.h"
#include "stdio.h"
#include "string.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TRandom3.h"
using namespace std;

const int MAXLEN=300;
const int NSI=13;//number of datawords to read from SIMION output
const int NG4=7;//number of datawords to read from GEANT4 output
const int MAXG=10; //max number of gammas in cascade
const int MAXCE=5; //max number of conversion electrons in decay
const int MAXN=1; //max number of neutrons in decay

typedef struct{
  int evtnum;
  int evttype;
  float tof;
  float mass;
  int q;
  float pos_x;
  float pos_y;
  float pos_z;
  float vel;
  float phi;
  float theta;
  float ke;
  float ke_err;
} SIMION_OUT;

typedef struct{
  int evtnum;
  int pid[MAXG+MAXCE+1]; //0 for beta, 1 for gamma, 2 for conversion electron, 3 for neutron
  float mcp_t[MAXG+MAXCE+1];
  //  float sum_t_mcp;
  float mcp_r[MAXG+MAXCE+1];
  //float sum_r_mcp;
  float de_l[MAXG+MAXCE+1];
  float sum_de_l;
  float e_l[MAXG+MAXCE+1];
  float sum_e_l;
  float de_b[MAXG+MAXCE+1];
  float sum_de_b;
  float e_b[MAXG+MAXCE+1];
  float sum_e_b;
} GEANT4_OUT;

typedef struct{
  int evtnum;
  float tob;
  int num_state;
  float e_state;
  int q_state;
  float decay_x, decay_y, decay_z;
  float nu_E, nu_px, nu_py, nu_pz;
  float beta_E, beta_px, beta_py, beta_pz;
  float rec_E, rec_px, rec_py, rec_pz;
  int gammanum;
  float g_E[MAXG], g_px[MAXG], g_py[MAXG], g_pz[MAXG];
  int cenum;
  float ce_E[MAXCE], ce_px[MAXCE], ce_py[MAXCE], ce_pz[MAXCE];
  int nnum;
  float n_E[MAXN], n_px[MAXN], n_py[MAXN], n_pz[MAXN];
} MASTER_EVT;


int bdn_efficiency_subsort(char *oldfnm="",char *newfnm="small.root",Long64_t num=-1){
  //Event *event   = 0;
  static SIMION_OUT s;
  static GEANT4_OUT g; 
  static MASTER_EVT m;
  TRandom3 *r3=new TRandom3();
  //gSystem->Load("$ROOTSYS/test/libEvent");	
  if(oldfnm==""){fprintf(stderr,"Require a file name to run bdn_efficiency_subsort!!!\n\n"); return -1;}
  
  //Get old file, old tree and set top branch address
  TFile *oldfile = new TFile(oldfnm);
  if(oldfile->IsZombie()) {fprintf(stderr,"Problem opening the file %s\n\n",oldfnm); return -2;}  
  
  TTree *oldtree = (TTree*)oldfile->Get("bdntree");
  Long64_t nentries=oldtree->GetEntries();
  if(num==-1||num>nentries) num=nentries;
  fprintf(stderr,"sorting %i entries from tree \"%s\"\n\n",(int)num,oldtree->GetName());

  Long64_t j=0;
  Long64_t k=0;
  //oldtree->SetBranchAddress("event",&event);
  //oldtree->SetBranchAddress("simion",&s);
  //oldtree->SetBranchAddress("geant",&g);
  //oldtree->SetBranchAddress("master",&m);
  oldtree->SetBranchAddress("simion",(void*)&s);
  oldtree->SetBranchAddress("geant",(void*)&g);
  oldtree->SetBranchAddress("master",(void*)&m);

  oldtree->SetBranchStatus("*",1);      //set all branches to "Process"
  //oldtree->SetBranchStatus("simion",1); //set simion branch status to "Process"

  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile(newfnm,"recreate");
  TTree *newtree = oldtree->CloneTree(0);
  
  //define leaf pointer
  TLeaf *vel=(TLeaf*)oldtree->GetBranch("simion")->GetLeaf("vel");
  TLeaf *pos_x=(TLeaf*)oldtree->GetBranch("simion")->GetLeaf("pos_x");
  TLeaf *pos_y=(TLeaf*)oldtree->GetBranch("simion")->GetLeaf("pos_y");
  TLeaf *pos_z=(TLeaf*)oldtree->GetBranch("simion")->GetLeaf("pos_z");
  for (Long64_t i=0;i<num; i++) {
    oldtree->GetEntry(i);
	
    //read only the leaf data for each entry...use to define subset conditions
    vel->GetBranch()->GetEntry(i);
	pos_x->GetBranch()->GetEntry(i);
	pos_y->GetBranch()->GetEntry(i);
	pos_z->GetBranch()->GetEntry(i);
	
    float v=((float)vel->GetValue())/1000.0;
	float x=(float)pos_x->GetValue();
	float y=(float)pos_y->GetValue();
	float z=(float)pos_z->GetValue();
	float r=r3->Rndm();
	if (i%1000==0)
		fprintf(stderr,"%i sorted:%i %i last velocity:%f\n",i,j,k,v);

    if(z<52.6 && z>52.4)
		if (x<23 && x>-23 && y<23 && y>-23){
			float e=getInterpRight((Float_t)v,(Float_t)x,(Float_t)y);
			if(e>r){
				newtree->Fill();
				j++;
			}
		}
	if(y<52.6 && y>52.4)
		if (x<23 && x>-23 && z<23 && z>-23){
			float e=getInterpTop((Float_t)v,(Float_t)x,(Float_t)z);
			if(e>r){
				newtree->Fill();
				k++;
			}
		}
  }
  newtree->Print();
  newtree->Write("",TObject::kOverwrite);
  delete oldfile;
  delete newfile; 
  return 0;
}

float applyEfficiency(Float_t ionMass, Int_t charge, Float_t tofNum, Float_t coordX, Float_t coordY, Float_t coordZ){
    
    // Sb-134, mass in amu
    // precursorMass = 133.9113940
    // daughterMass = 132.9109690
    
    Float_t tof = tofNum*1000.0; // convert us to ns
    Float_t mcpDist = 52.5; // distance from center of trap to MCP, mm
    Float_t Vmcp = 2.5;    // MCP voltage, kV
    Int_t whichMCP;
    Float_t theEfficiency = 0;
    Float_t mcpX, mcpY;
    
    if ((coordZ > 45.0) && (coordX >= -23.0) && (coordX <= 23.0) && (coordY >= -23.0) && (coordY <= 23.0) ) {
        
        // Right 
        mcpX = coordX;
        mcpY = coordY;
        whichMCP = 1;
        
    }
    if ((coordY > 45.0) && (coordX >= -23.0) && (coordX <= 23.0) && (coordZ >= -23.0) && (coordZ <= 23.0) ) {
        
        // Top
        mcpX = coordX;
        mcpY = coordZ;
        whichMCP = 2;
        
    }
    
    Float_t mcpDistNum = sqrt((mcpDist*mcpDist) + (mcpX*mcpX) + (mcpY*mcpY));
    Float_t ionVelTOF = mcpDistNum/tof;
    Float_t impactVel = sqrt( (ionVelTOF*ionVelTOF) + (0.096485337*(2.0/ionMass)*float(charge)*Vmcp) );

    if (whichMCP == 1) theEfficiency = getInterpRight(impactVel, mcpX, mcpY);
    if (whichMCP == 2) theEfficiency = getInterpTop(impactVel, mcpX, mcpY);
    
    return theEfficiency;
    
}

// functions called by applyEfficiency(), nothing needs to be changed here

float getInterpTop(Float_t ionVel, Float_t xCoord, Float_t yCoord){

    static Float_t x1, x2, y1, y2, R1, R2, P, Q11, Q22, Q12, Q21;
    
    static Int_t theX, theY;
    static Float_t xArr[6] = {-28.75, -17.25, -5.75, 5.75, 17.25, 28.75};
    static Float_t yArr[6] = {-28.75, -17.25, -5.75, 5.75, 17.25, 28.75};
    
    // get coordinates of the X, Y matrix
    for (Int_t i = 0; i<5; i++) {
        if (xCoord > xArr[i]) theX = i;
        if (yCoord > yArr[i]) theY = i;
    }
    
    // get the pixel efficiencies
    Q11 = QmatrixFuncTop(ionVel, theX, theY);
    Q21 = QmatrixFuncTop(ionVel, theX+1, theY);
    Q12 = QmatrixFuncTop(ionVel, theX, theY+1);
    Q22 = QmatrixFuncTop(ionVel, theX+1, theY+1);
    
    x1 = xArr[theX];
    x2 = xArr[theX+1];
    y1 = yArr[theY];
    y2 = yArr[theY+1];

    R1 = ((x2 - xCoord)/(x2 - x1))*Q11 + ((xCoord - x1)/(x2 - x1))*Q21;
    R2 = ((x2 - xCoord)/(x2 - x1))*Q12 + ((xCoord - x1)/(x2 - x1))*Q22;
    P = ((y2 - yCoord)/(y2 - y1))*R1 + ((yCoord - y1)/(y2 - y1))*R2;
    
    return P;
    
}

float QmatrixFuncTop(Float_t ionVel, Int_t xVal, Int_t yVal){
 
    // efficiency matrix; only load/compute pixel you want
    
    static Float_t Qval = 0;
    
    if (yVal == 0) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutTop(ionVel,41)) - getEfficiencyOutTop(ionVel,43);
        if (xVal == 1) Qval = (2.0*getEfficiencyOutTop(ionVel,41)) - getEfficiencyOutTop(ionVel,43);
        if (xVal == 2) Qval = (2.0*getEfficiencyOutTop(ionVel,42)) - getEfficiencyOutTop(ionVel,44);
        if (xVal == 3) Qval = (2.0*getEfficiencyOutTop(ionVel,31)) - getEfficiencyOutTop(ionVel,33);
        if (xVal == 4) Qval = (2.0*getEfficiencyOutTop(ionVel,32)) - getEfficiencyOutTop(ionVel,34);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutTop(ionVel,32)) - getEfficiencyOutTop(ionVel,33);
   
    } 
    
    if (yVal == 1) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutTop(ionVel,41)) - getEfficiencyOutTop(ionVel,42);
        if (xVal == 1) Qval = getEfficiencyOutTop(ionVel,41);
        if (xVal == 2) Qval = getEfficiencyOutTop(ionVel,42);
        if (xVal == 3) Qval = getEfficiencyOutTop(ionVel,31);
        if (xVal == 4) Qval = getEfficiencyOutTop(ionVel,32);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutTop(ionVel,32)) - getEfficiencyOutTop(ionVel,31);
        
    }
    
    if (yVal == 2) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutTop(ionVel,43)) - getEfficiencyOutTop(ionVel,44);
        if (xVal == 1) Qval = getEfficiencyOutTop(ionVel,43);
        if (xVal == 2) Qval = getEfficiencyOutTop(ionVel,44);
        if (xVal == 3) Qval = getEfficiencyOutTop(ionVel,33);
        if (xVal == 4) Qval = getEfficiencyOutTop(ionVel,34);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutTop(ionVel,34)) - getEfficiencyOutTop(ionVel,33);

    }
    
    if (yVal == 3) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutTop(ionVel,21)) - getEfficiencyOutTop(ionVel,22);
        if (xVal == 1) Qval = getEfficiencyOutTop(ionVel,21);
        if (xVal == 2) Qval = getEfficiencyOutTop(ionVel,22);
        if (xVal == 3) Qval = getEfficiencyOutTop(ionVel,11);
        if (xVal == 4) Qval = getEfficiencyOutTop(ionVel,12);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutTop(ionVel,12)) - getEfficiencyOutTop(ionVel,11);
        
    }
    
    if (yVal == 4) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutTop(ionVel,23)) - getEfficiencyOutTop(ionVel,24);
        if (xVal == 1) Qval = getEfficiencyOutTop(ionVel,23);
        if (xVal == 2) Qval = getEfficiencyOutTop(ionVel,24);
        if (xVal == 3) Qval = getEfficiencyOutTop(ionVel,13);
        if (xVal == 4) Qval = getEfficiencyOutTop(ionVel,14);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutTop(ionVel,14)) - getEfficiencyOutTop(ionVel,13);
        
    }
    
    if (yVal == 5) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutTop(ionVel,23)) - getEfficiencyOutTop(ionVel,22);
        if (xVal == 1) Qval = (2.0*getEfficiencyOutTop(ionVel,23)) - getEfficiencyOutTop(ionVel,21);
        if (xVal == 2) Qval = (2.0*getEfficiencyOutTop(ionVel,24)) - getEfficiencyOutTop(ionVel,22);
        if (xVal == 3) Qval = (2.0*getEfficiencyOutTop(ionVel,13)) - getEfficiencyOutTop(ionVel,11);
        if (xVal == 4) Qval = (2.0*getEfficiencyOutTop(ionVel,14)) - getEfficiencyOutTop(ionVel,12);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutTop(ionVel,14)) - getEfficiencyOutTop(ionVel,11);
        
    }
    
    return Qval;
}

float getInterpRight(Float_t ionVel, Float_t xCoord, Float_t yCoord){
    
    static Float_t x1, x2, y1, y2, R1, R2, P, Q11, Q22, Q12, Q21;
    
    static Int_t theX, theY;
    static Float_t xArr[6] = {-28.75, -17.25, -5.75, 5.75, 17.25, 28.75};
    static Float_t yArr[6] = {-28.75, -17.25, -5.75, 5.75, 17.25, 28.75};
    
    // get coordinates of the X, Y matrix
    for (Int_t i = 0; i<5; i++) {
        if (xCoord > xArr[i]) theX = i;
        if (yCoord > yArr[i]) theY = i;
    }
    
    // get the pixel efficiencies
    Q11 = QmatrixFuncRight(ionVel, theX, theY);
    Q21 = QmatrixFuncRight(ionVel, theX+1, theY);
    Q12 = QmatrixFuncRight(ionVel, theX, theY+1);
    Q22 = QmatrixFuncRight(ionVel, theX+1, theY+1);
    
    x1 = xArr[theX];
    x2 = xArr[theX+1];
    y1 = yArr[theY];
    y2 = yArr[theY+1];
    
    R1 = ((x2 - xCoord)/(x2 - x1))*Q11 + ((xCoord - x1)/(x2 - x1))*Q21;
    R2 = ((x2 - xCoord)/(x2 - x1))*Q12 + ((xCoord - x1)/(x2 - x1))*Q22;
    P = ((y2 - yCoord)/(y2 - y1))*R1 + ((yCoord - y1)/(y2 - y1))*R2;
    
    return P;
    
}

float QmatrixFuncRight(Float_t ionVel, Int_t xVal, Int_t yVal){
    
    // efficiency matrix; only load/compute pixel you want
    
    static Float_t Qval = 0;
    
    if (yVal == 0) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutRight(ionVel,41)) - getEfficiencyOutRight(ionVel,43);
        if (xVal == 1) Qval = (2.0*getEfficiencyOutRight(ionVel,41)) - getEfficiencyOutRight(ionVel,43);
        if (xVal == 2) Qval = (2.0*getEfficiencyOutRight(ionVel,42)) - getEfficiencyOutRight(ionVel,44);
        if (xVal == 3) Qval = (2.0*getEfficiencyOutRight(ionVel,31)) - getEfficiencyOutRight(ionVel,33);
        if (xVal == 4) Qval = (2.0*getEfficiencyOutRight(ionVel,32)) - getEfficiencyOutRight(ionVel,34);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutRight(ionVel,32)) - getEfficiencyOutRight(ionVel,33);
        
    }
    
    if (yVal == 1) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutRight(ionVel,41)) - getEfficiencyOutRight(ionVel,42);
        if (xVal == 1) Qval = getEfficiencyOutRight(ionVel,41);
        if (xVal == 2) Qval = getEfficiencyOutRight(ionVel,42);
        if (xVal == 3) Qval = getEfficiencyOutRight(ionVel,31);
        if (xVal == 4) Qval = getEfficiencyOutRight(ionVel,32);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutRight(ionVel,32)) - getEfficiencyOutRight(ionVel,31);
        
    }
    
    if (yVal == 2) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutRight(ionVel,43)) - getEfficiencyOutRight(ionVel,44);
        if (xVal == 1) Qval = getEfficiencyOutRight(ionVel,43);
        if (xVal == 2) Qval = getEfficiencyOutRight(ionVel,44);
        if (xVal == 3) Qval = getEfficiencyOutRight(ionVel,33);
        if (xVal == 4) Qval = getEfficiencyOutRight(ionVel,34);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutRight(ionVel,34)) - getEfficiencyOutRight(ionVel,33);
        
    }
    
    if (yVal == 3) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutRight(ionVel,21)) - getEfficiencyOutRight(ionVel,22);
        if (xVal == 1) Qval = getEfficiencyOutRight(ionVel,21);
        if (xVal == 2) Qval = getEfficiencyOutRight(ionVel,22);
        if (xVal == 3) Qval = getEfficiencyOutRight(ionVel,11);
        if (xVal == 4) Qval = getEfficiencyOutRight(ionVel,12);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutRight(ionVel,12)) - getEfficiencyOutRight(ionVel,11);
        
    }
    
    if (yVal == 4) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutRight(ionVel,23)) - getEfficiencyOutRight(ionVel,24);
        if (xVal == 1) Qval = getEfficiencyOutRight(ionVel,23);
        if (xVal == 2) Qval = getEfficiencyOutRight(ionVel,24);
        if (xVal == 3) Qval = getEfficiencyOutRight(ionVel,13);
        if (xVal == 4) Qval = getEfficiencyOutRight(ionVel,14);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutRight(ionVel,14)) - getEfficiencyOutRight(ionVel,13);
        
    }
    
    if (yVal == 5) {
        
        if (xVal == 0) Qval = (2.0*getEfficiencyOutRight(ionVel,23)) - getEfficiencyOutRight(ionVel,22);
        if (xVal == 1) Qval = (2.0*getEfficiencyOutRight(ionVel,23)) - getEfficiencyOutRight(ionVel,21);
        if (xVal == 2) Qval = (2.0*getEfficiencyOutRight(ionVel,24)) - getEfficiencyOutRight(ionVel,22);
        if (xVal == 3) Qval = (2.0*getEfficiencyOutRight(ionVel,13)) - getEfficiencyOutRight(ionVel,11);
        if (xVal == 4) Qval = (2.0*getEfficiencyOutRight(ionVel,14)) - getEfficiencyOutRight(ionVel,12);
        if (xVal == 5) Qval = (2.0*getEfficiencyOutRight(ionVel,14)) - getEfficiencyOutRight(ionVel,11);
        
    }

    return Qval;
}

/// EFFICIENCY FUNCTIONS

// efficiency for charge state 2+
float getEfficiencyOutTop(Float_t ionVel, Int_t pixelNum)
{
    
    static Float_t ionVel, peak11;
    static Float_t theCentroid, theSigma;
    
    // this is for peak in pixel 11, sum of three charge states
    static Float_t centroidSlope = 12520.6;
    static Float_t centroidInt = 393.188;
    
    static Float_t sigmaArr[16] = {485.91,381.899,576.64,502.958,410.753,464.835,431.876,605.832,839.113,818.464,591.189,545.761,571.117,780.73,400.136,549.793};
    static Float_t theSigma;
	theSigma = sigmaArr[getArrayNum(pixelNum)]; // sigma for charge2

    static Float_t centroidArr[16] = {1.0,0.763260787,1.014539569,0.675400451,0.715620051,0.97977073,0.656537551,1.030410471,1.202446852,1.220517959,1.077911067,0.860413134,0.642984571,1.055257368,0.723741189,0.944133021};
    
    static Float_t corrVal, theEfficiency = 0;
    peak11 =  ionVel*centroidSlope + centroidInt;
    // determine centroid for charge 2 from the centroid of sum of three charges
    theCentroid = (0.9466*peak11*centroidArr[getArrayNum(pixelNum)]) + 3.3906;

    theEfficiency = pixelFunctionTop(pixelNum, theCentroid, theSigma);
    corrVal = corrFuncTop(pixelNum, ionVel);
    theEfficiency = theEfficiency*corrVal;

    return theEfficiency;

}

float pixelFunctionTop(Int_t pixelNum, Float_t theCentroid, Float_t theSigma)
{
    
    static Float_t trArr[16] = {1095.0, 915.0, 875.0, 755.0, 885.0, 1065.0, 705.0, 855.0, 845.0, 715.0, 1095.0, 935.0, 765.0, 925.0, 915.0, 1085.0};
    static Float_t thresVal;
	thresVal	= trArr[getArrayNum(pixelNum)];
    
    static Float_t fractionBelow;
    fractionBelow	= (TMath::Erf((thresVal-theCentroid)/(sqrt(2.0)*theSigma)) - TMath::Erf(((-5000.0)-theCentroid)/(sqrt(2.0)*theSigma)))/2.0;
    
    static Float_t efficiencyVal;
    efficiencyVal = (1.0-fractionBelow);
    
    return efficiencyVal;
    
}

static Float_t corrArr[16][16] = {
    {1.21156,1.1595,1.11705,1.08326,1.05718,1.03774,1.02384,1.01436,1.00822,1.00447,1.00229,1.00111,1.00051,1.00022,1.00009,1.00003},
    {1.32925,1.25208,1.1889,1.13807,1.09805,1.0674,1.04466,1.02841,1.0173,1.01005,1.00556,1.00292,1.00145,1.00069,1.00031,1.00013},
    {1.11763,1.08975,1.06684,1.04846,1.03411,1.02325,1.01531,1.00972,1.00594,1.00349,1.00197,1.00106,1.00055,1.00027,1.00013,1.00006},
    {1.2305,1.19377,1.16123,1.13265,1.10779,1.0864,1.06825,1.05306,1.04054,1.03042,1.02239,1.01614,1.01139,1.00787,1.00531,1.0035},
    {1.33162,1.26527,1.20893,1.16167,1.12262,1.09091,1.06573,1.04621,1.03152,1.0208,1.01326,1.00815,1.00482,1.00274,1.0015,1.00078},
    {1.21439,1.15975,1.11567,1.08102,1.05466,1.03534,1.02181,1.0128,1.00712,1.00374,1.00185,1.00087,1.00038,1.00016,1.00006,1.00002},
    {1.24072,1.19535,1.15637,1.12326,1.09552,1.07265,1.05413,1.03945,1.02807,1.01947,1.01315,1.00864,1.00551,1.00341,1.00205,1.00119},
    {1.10797,1.08297,1.06231,1.04562,1.03248,1.02244,1.01501,1.0097,1.00605,1.00364,1.0021,1.00117,1.00063,1.00032,1.00016,1.00008},
    {1.07368,1.0591,1.04661,1.03609,1.02739,1.02035,1.01479,1.01049,1.00726,1.0049,1.00322,1.00206,1.00128,1.00077,1.00045,1.00026},
    {1.05768,1.04485,1.03417,1.02547,1.01854,1.01317,1.00911,1.00613,1.00401,1.00255,1.00157,1.00094,1.00055,1.00031,1.00017,1.00009},
    {1.15613,1.1213,1.09212,1.06819,1.04906,1.0342,1.02304,1.01495,1.00933,1.00559,1.00321,1.00176,1.00092,1.00046,1.00022,1.0001},
    {1.19914,1.1619,1.12966,1.1021,1.0789,1.05973,1.04421,1.03193,1.02246,1.01536,1.01021,1.00657,1.0041,1.00248,1.00145,1.00082},
    {1.22731,1.19828,1.17179,1.14775,1.12607,1.10665,1.08939,1.07418,1.06091,1.04945,1.03966,1.03141,1.02454,1.01891,1.01436,1.01074},
    {1.10888,1.09041,1.07411,1.05989,1.04766,1.03731,1.02869,1.02165,1.01601,1.0116,1.00822,1.00569,1.00385,1.00254,1.00164,1.00103},
    {1.35851,1.28493,1.22283,1.17106,1.12855,1.09432,1.06736,1.04669,1.03132,1.02027,1.01264,1.00757,1.00435,1.0024,1.00127,1.00064},
    {1.21774,1.175,1.13827,1.10714,1.08124,1.06013,1.04333,1.03032,1.02057,1.01349,1.00854,1.00521,1.00306,1.00173,1.00094,1.00049}
};

float corrFuncTop(Int_t pixelNum, Float_t ionvel){
    
    // defined over the range of ion velocities: 0.07 to 0.22
    static Float_t velArr[16] = {0.07,0.08,0.09,0.1,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.2,0.21,0.22};
    static Int_t theVelNum=0;
    for (Int_t i=0; i<15; i++) if (ionvel >= velArr[i]) theVelNum = i;
    
    static Float_t x0;
	x0 = velArr[theVelNum];
    static Float_t x1;
	x1 = velArr[theVelNum+1];
    
    static Int_t pixArr;
	pixArr = getArrayNum(pixelNum);
    static Float_t y0;
    y0	= corrArr[pixArr][theVelNum];
    static Float_t y1;
    y1	= corrArr[pixArr][theVelNum+1];
    
    static Float_t interpVal;
    interpVal	= y0 + ((y1-y0)*(ionvel-x0)/(x1-x0));
    
    return interpVal;
    
}

// ########################################################################################
// ########################################################################################
//                      RIGHT MCP Efficiency
// ########################################################################################
// ########################################################################################

// efficiency for charge state 2+
float getEfficiencyOutRight(Float_t ionVel, Int_t pixelNum)
{

    static Float_t ionVel, peak11;
    static Float_t theCentroid, theSigma;
    
    // this is for peak in pixel 11, sum of three charge states
    static Float_t centroidSlope = 27293.5;
    static Float_t centroidInt = 1729.81;
    static Float_t entryRatio = 0.124620409;
    
    static Float_t sigmaArr[16] = {1435.69,869.95,1665.94,1052.38,1362.6,1726.95,1728.23,2136.33,2665.99,1716.45,1844.26,1018.66,2469.06,2963.48,1589.89,1864.18};
    static Float_t theSigma;
	theSigma = sigmaArr[getArrayNum(pixelNum)]; // sigma for charge2
    static Float_t centroidArr[16] = {1.0,0.578590292,1.077494419,0.545464056,0.897426804,1.181067806,1.074953116,1.370652548,1.667109779,0.978827582,1.160923646,0.650473943,1.300840722,1.825249729,0.974112394,1.273399247};
    
    static Float_t corrVal;
    static Float_t theEfficiency = 0;
    
    peak11 =  ionVel*centroidSlope + centroidInt;
    // determine centroid for charge +2 from the centroid of sum of three charges
    theCentroid = (0.9461*peak11*centroidArr[getArrayNum(pixelNum)]) + 4.8786;

    theEfficiency = pixelFunctionRight(pixelNum, theCentroid, theSigma);
    corrVal = 1.0 + ((entryRatio*(1.0-theEfficiency))/theEfficiency);
    theEfficiency = theEfficiency*corrVal;
    
    return theEfficiency;
    
}

float pixelFunctionRight(Int_t pixelNum, Float_t theCentroid, Float_t theSigma)
{
    
    static Float_t trArr[16] = {945.0,945.0,845.0,775.0,875.0,925.0,705.0,785.0,795.0,755.0,975.0,915.0,705.0,775.0,865.0,925.0};
    static Float_t thresVal;
	thresVal = trArr[getArrayNum(pixelNum)];
    
    static Float_t fractionBelow;
	fractionBelow = (TMath::Erf((thresVal-theCentroid)/(sqrt(2.0)*theSigma)) - TMath::Erf(((-5000.0)-theCentroid)/(sqrt(2.0)*theSigma)))/2.0;
    
    static Float_t efficiencyVal;
	efficiencyVal = (1.0-fractionBelow);
    
    return efficiencyVal;
    
}

int getArrayNum(Int_t pixelNum){
    
    static Int_t arrNum;
    if (pixelNum == 11) arrNum = 0;
    if (pixelNum == 12) arrNum = 1;
    if (pixelNum == 13) arrNum = 2;
    if (pixelNum == 14) arrNum = 3;
    if (pixelNum == 21) arrNum = 4;
    if (pixelNum == 22) arrNum = 5;
    if (pixelNum == 23) arrNum = 6;
    if (pixelNum == 24) arrNum = 7;
    if (pixelNum == 31) arrNum = 8;
    if (pixelNum == 32) arrNum = 9;
    if (pixelNum == 33) arrNum = 10;
    if (pixelNum == 34) arrNum = 11;
    if (pixelNum == 41) arrNum = 12;
    if (pixelNum == 42) arrNum = 13;
    if (pixelNum == 43) arrNum = 14;
    if (pixelNum == 44) arrNum = 15;
    
    return arrNum;
    
}

int getPixelNum(Int_t inNum){
    
    static Int_t outPixel;
    if (inNum == 0) outPixel = 11;
    if (inNum == 1) outPixel = 12;
    if (inNum == 2) outPixel = 13;
    if (inNum == 3) outPixel = 14;
    if (inNum == 4) outPixel = 21;
    if (inNum == 5) outPixel = 22;
    if (inNum == 6) outPixel = 23;
    if (inNum == 7) outPixel = 24;
    if (inNum == 8) outPixel = 31;
    if (inNum == 9) outPixel = 32;
    if (inNum == 10) outPixel = 33;
    if (inNum == 11) outPixel = 34;
    if (inNum == 12) outPixel = 41;
    if (inNum == 13) outPixel = 42;
    if (inNum == 14) outPixel = 43;
    if (inNum == 15) outPixel = 44;
    
    return outPixel;
    
}
