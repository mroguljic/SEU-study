#include "SEUPrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"
#include "UserInput.hh"
#include "G4IonTable.hh"


SEUPrimaryGeneratorAction::SEUPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  UserInput input;
  fParticleGun    = new G4ParticleGun();
  particleEnergy  = input.GetParticleEnergy();
  ionZ            = input.GetIonZ();
  ionA            = input.GetIonA();
  ionCharge       = input.GetIonCharge();

  std::cout<<G4BestUnit(particleEnergy,"Energy") <<"\n";

}


SEUPrimaryGeneratorAction::~SEUPrimaryGeneratorAction()
{
  delete fParticleGun;
}


void SEUPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //UserInput input;
  //G4String particleName;
  //G4ParticleDefinition* particle = particleTable->FindParticle(particleName=input.GetParticleType());
  G4IonTable* ionTable = particleTable->GetIonTable();
  G4ParticleDefinition*  particle = ionTable->GetIon(ionZ,ionA,0.); //third argument is excitation energy
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleCharge(ionCharge);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(particleEnergy);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-0.3*cm));
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
