#include "SEUActionInitialization.hh"
#include "SEUPrimaryGeneratorAction.hh"
#include "SEURunAction.hh"
#include "SEUEventAction.hh"
#include "SEUSteppingAction.hh"


SEUActionInitialization::SEUActionInitialization()
 : G4VUserActionInitialization()
{}


SEUActionInitialization::~SEUActionInitialization()
{}


void SEUActionInitialization::BuildForMaster() const
{
  SEURunAction* runAction = new SEURunAction;
  SetUserAction(runAction);
}


void SEUActionInitialization::Build() const
{
  SetUserAction(new SEUPrimaryGeneratorAction);

  SEURunAction* runAction = new SEURunAction;
  SetUserAction(runAction);
  
  SEUEventAction* eventAction = new SEUEventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new SEUSteppingAction(eventAction));
}  
