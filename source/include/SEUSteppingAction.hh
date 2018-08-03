#ifndef SEUSteppingAction_h
#define SEUSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SEUEventAction;

class G4LogicalVolume;
class G4Region;

class SEUSteppingAction : public G4UserSteppingAction
{
  public:
    SEUSteppingAction(SEUEventAction* eventAction);
    virtual ~SEUSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    SEUEventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
    G4Region* fScoringRegion;
};

#endif
