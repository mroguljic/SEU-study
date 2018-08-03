#ifndef SEUDetectorConstruction_h
#define SEUDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Region;
class G4UserLimits;


class SEUDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    SEUDetectorConstruction();
    virtual ~SEUDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    G4Region*        GetScoringRegion() const { return fScoringRegion; }


  private:
    G4UserLimits* fStepLimit;


  protected:
    G4LogicalVolume*  fScoringVolume;
    G4Region*  fScoringRegion;
};


#endif

