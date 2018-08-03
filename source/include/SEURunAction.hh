#ifndef SEURunAction_h
#define SEURunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

class SEURunAction : public G4UserRunAction
{
  public:
    SEURunAction();
    virtual ~SEURunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep); 

  private:
    G4Accumulable<G4double> fEdep;
};

#endif

