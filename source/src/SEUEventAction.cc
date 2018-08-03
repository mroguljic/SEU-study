

#include "SEUEventAction.hh"
#include "SEURunAction.hh"
#include "SEUAnalysis.hh"


#include "G4Event.hh"
#include "G4RunManager.hh"


SEUEventAction::SEUEventAction(SEURunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.)
{} 


SEUEventAction::~SEUEventAction()
{}


void SEUEventAction::BeginOfEventAction(const G4Event*)
{  
  fEdep = 0.;
}


void SEUEventAction::EndOfEventAction(const G4Event*)
{   

  auto analysisManager = G4AnalysisManager::Instance();

  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);

  if(fEdep>0.){
  analysisManager->FillNtupleDColumn(0,0, fEdep);
  analysisManager->AddNtupleRow(0);
  }

}