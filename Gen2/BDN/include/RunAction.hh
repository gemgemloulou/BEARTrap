//-----------------------------------------------------------------------
//Edits made by Barbara Wang:
//(Note: To view all lines edited, search for "bswang.")
//
//5/11/2015: Added statements to properly initialize the parameter EID
//           (Electron ID) 
//-----------------------------------------------------------------------

#ifndef RunAction_h
#define RunAction_h 1

#include "Analysis.hh"

#include "G4UserRunAction.hh"
#include "globals.hh"

class EventAction; //bswang (5/11/2015)

class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    RunAction(EventAction*);  //bswang(5/11/2015)
   ~RunAction();

  public:
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private: 
    EventAction* fEventAction;  //bswang(5/11/2015)
};

#endif

