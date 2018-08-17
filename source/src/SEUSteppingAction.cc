#include "SEUSteppingAction.hh"
#include "SEUEventAction.hh"
#include "SEUDetectorConstruction.hh"
#include "g4root.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Region.hh"


SEUSteppingAction::SEUSteppingAction(SEUEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0),
  fScoringRegion(0)
{}


SEUSteppingAction::~SEUSteppingAction()
{}


void SEUSteppingAction::UserSteppingAction(const G4Step* step)
{
  auto analysisManager = G4AnalysisManager::Instance();
  
  if (!fScoringVolume) { 
    const SEUDetectorConstruction* detectorConstruction
      = static_cast<const SEUDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    //ScoringVolume is the region in which we want to know energy deposition
    //ScoringRegion is the whole TBM, we just want to limit step length there
    //Keeping track of some variables in the region as a sanity check
    fScoringVolume = detectorConstruction->GetScoringVolume();   
    fScoringRegion = detectorConstruction->GetScoringRegion();   
  }

  // get volume of the current step
  G4LogicalVolume* preStepVolume  = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  G4LogicalVolume* postStepVolume;
  G4Region* region                = preStepVolume->GetRegion();

  G4double kinEnergy              = step->GetTrack()->GetDynamicParticle()->GetKineticEnergy();
  G4double edepStep               = step->GetTotalEnergyDeposit();
  G4double z                      = step->GetPostStepPoint()->GetPosition().z();
  G4String pName                  = step->GetTrack()->GetDefinition()->GetParticleName();
  G4double spreadX, spreadY;

  // check if we are in region of interest
  if (region != fScoringRegion) return;

/*  if(pName!="proton" && pName!="e-" && pName!="C12")
  	std::cout<<pName<<"\n";*/


  if(preStepVolume->GetName()!="World"){  
    //We get a seg fault if we access postStep at the last step of the event, last step means
    //exiting the "World", so this is a safety measure not to access postStep when it doesn't exist
    postStepVolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
    if(pName!="e-"  && postStepVolume==fScoringVolume && postStepVolume!=preStepVolume ){
      spreadX = step->GetPostStepPoint()->GetPosition().x();
      spreadY = step->GetPostStepPoint()->GetPosition().y();
      analysisManager->FillNtupleDColumn(0,1,spreadX);
      analysisManager->FillNtupleDColumn(0,2,spreadY);
    }
  }
  if(preStepVolume == fScoringVolume){
    fEventAction->AddEdep(edepStep);
  }

  if(edepStep>0.){
    analysisManager->FillH1(0,z,edepStep);
    analysisManager->FillNtupleDColumn(1,0,z);
    analysisManager->FillNtupleDColumn(1,1,edepStep);
    analysisManager->FillNtupleDColumn(1,2,kinEnergy);
    analysisManager->AddNtupleRow(1);
  }

}
