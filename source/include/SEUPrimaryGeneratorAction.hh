#ifndef SEUPrimaryGeneratorAction_h
#define SEUPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;


class SEUPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    SEUPrimaryGeneratorAction();    
    virtual ~SEUPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         
  
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
  	G4double		particleEnergy;
  	G4double		ionZ;
  	G4double		ionA;
  	G4double		ionCharge;
    G4ParticleGun*  fParticleGun;
};

#endif
