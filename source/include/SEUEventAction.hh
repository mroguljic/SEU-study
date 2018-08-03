#ifndef SEUEventAction_h
#define SEUEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class SEURunAction;

class SEUEventAction : public G4UserEventAction
{
  public:
    SEUEventAction(SEURunAction* runAction);
    virtual ~SEUEventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep){ fEdep += edep; }
  private:
    SEURunAction* fRunAction;
    G4double      fEdep;
};


#endif

    
