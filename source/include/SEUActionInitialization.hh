#ifndef SEUActionInitialization_h
#define SEUActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class SEUActionInitialization : public G4VUserActionInitialization
{
  public:
    SEUActionInitialization();
    virtual ~SEUActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif

    
