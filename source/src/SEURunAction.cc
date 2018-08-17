#include "SEURunAction.hh"
#include "SEUPrimaryGeneratorAction.hh"
#include "SEUDetectorConstruction.hh"
#include "SEUAnalysis.hh"
#include "UserInput.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <ctime>
#include <fstream>
#include <iostream>


SEURunAction::SEURunAction()
: G4UserRunAction(),
  fEdep(0.)
{ 
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);

  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(100000);  

  //Random seeds
  long seeds[2];
  time_t systime = time(NULL);
  seeds[0] = (long) systime;
  seeds[1] = (long) (systime*G4UniformRand());
  G4Random::setTheSeeds(seeds);      

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in SEUAnalysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  analysisManager->CreateH1("dEdX","Dose Profile", 100, 0., 0.012);
  analysisManager->CreateNtuple("Event","Event");
  //ntuple0
  analysisManager->CreateNtupleDColumn("EventEDep");
  analysisManager->CreateNtupleDColumn("spreadX");
  analysisManager->CreateNtupleDColumn("spreadY");
  analysisManager->FinishNtuple(0);
  //ntuple1
  analysisManager->CreateNtuple("Step","Step");
  analysisManager->CreateNtupleDColumn("StepZ");
  analysisManager->CreateNtupleDColumn("StepEDep");
  analysisManager->CreateNtupleDColumn("kineticEnergy");
  analysisManager->FinishNtuple(1);

}

SEURunAction::~SEURunAction()
{  
  delete G4AnalysisManager::Instance();  
}


void SEURunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();


  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  UserInput input;
  std::string fileName = input.GetTreeFileName();


  // Open an output file
  analysisManager->OpenFile(fileName);
}


void SEURunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4double edep  = fEdep.GetValue();
        
 
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << "events"
     << G4endl
     << " Cumulated energy per run, in scoring volume: " 
     << G4BestUnit(edep,"Energy")
     << G4endl
     << "------------------------------------------------------------"
     << G4endl;



  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}


void SEURunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
}
