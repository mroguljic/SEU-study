#include "SEUDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4Region.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4SubtractionSolid.hh"
#include "UserInput.hh"
#include "G4UserLimits.hh"



SEUDetectorConstruction::SEUDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{}


SEUDetectorConstruction::~SEUDetectorConstruction()
{ }


G4VPhysicalVolume* SEUDetectorConstruction::Construct()
{  
  UserInput input;
  G4double mu             = 0.001*mm;
  G4NistManager* nist     = G4NistManager::Instance();
  G4double detHz          = input.GetDetThickness()/2.0;
  G4bool checkOverlaps    = true;
  G4double world_sizeXY   = 1.0*cm;
  G4double world_sizeZ    = 1.0*cm;
  G4Material* world_mat   = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* silicon     = nist->FindOrBuildMaterial("G4_Si");
  G4Material* aluminum    = nist->FindOrBuildMaterial("G4_Al");
  G4Material* SiO2        = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");

  G4Element* SiElement    = new G4Element("Silicon", "Si", 14, 28.0855*g/mole);
  G4Element* NElement     = new G4Element("Nitrogen", "N", 7, 14.0067*g/mole);

  G4Material* SiNitride   = new G4Material("Silicon Nitride", 3.17*g/cm3,2);
  SiNitride->AddElement(SiElement, 3);
  SiNitride->AddElement(NElement, 4);

  G4Material* TBMSurfaceMat  = new G4Material("TBMSurfaceMat",2.909,2);
  TBMSurfaceMat->AddMaterial(SiNitride,0.5448);
  TBMSurfaceMat->AddMaterial(SiO2 ,0.4552);


  G4ThreeVector origin   = G4ThreeVector(0.*cm, 0.*cm, 0.*cm);

  G4Box* solidWorld               = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ); 
  G4LogicalVolume* logicWorld     = new G4LogicalVolume(solidWorld, world_mat, "World");  
  G4VPhysicalVolume* physWorld    = new G4PVPlacement(0, origin, logicWorld, "World", 0, false, 0, checkOverlaps);
                

  G4double TBMhx                  = 0.5*mm;
  G4double SurfaceHz              = 0.572*mu;


  G4Box* surfaceSolid             = new G4Box("Surface", TBMhx, TBMhx,SurfaceHz); 
  G4LogicalVolume* surfaceLogic   = new G4LogicalVolume(surfaceSolid, TBMSurfaceMat, "Surface");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,SurfaceHz), surfaceLogic, "Surface", logicWorld, false, 0, checkOverlaps);

  G4double aluminum1Hz            = 0.5*mu;
  G4double aluminum1Position      = 2*SurfaceHz+aluminum1Hz;
  G4Box* aluminum1Solid           = new G4Box("aluminum1", TBMhx, TBMhx, aluminum1Hz); 
  G4LogicalVolume* aluminum1Logic = new G4LogicalVolume(aluminum1Solid, aluminum, "aluminum1");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,aluminum1Position), aluminum1Logic, "aluminum1", logicWorld, false, 0, checkOverlaps);

  G4double quartz1Hz              = 1.2*mu;
  G4double quartz1Position        = 2*SurfaceHz+2*aluminum1Hz+quartz1Hz;
  G4Box* quartz1Solid             = new G4Box("quartz1", TBMhx, TBMhx, quartz1Hz); 
  G4LogicalVolume* quartz1Logic   = new G4LogicalVolume(quartz1Solid, SiO2, "quartz1");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,quartz1Position), quartz1Logic, "quartz1", logicWorld, false, 0, checkOverlaps);

  G4double aluminum2Hz            = 0.81*mu;
  G4double aluminum2Position      = 2*SurfaceHz+2*aluminum1Hz+2*quartz1Hz+aluminum2Hz;
  G4Box* aluminum2Solid           = new G4Box("aluminum2", TBMhx, TBMhx, aluminum2Hz); 
  G4LogicalVolume* aluminum2Logic = new G4LogicalVolume(aluminum2Solid, aluminum, "aluminum2");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,aluminum2Position), aluminum2Logic, "aluminum2", logicWorld, false, 0, checkOverlaps);

  G4double quartz2Hz              = 1.0375*mu;
  G4double quartz2Position        = 2*SurfaceHz+2*aluminum1Hz+2*quartz1Hz+2*aluminum2Hz+quartz2Hz;
  G4Box* quartz2Solid             = new G4Box("quartz2", TBMhx, TBMhx, quartz2Hz); 
  G4LogicalVolume* quartz2Logic   = new G4LogicalVolume(quartz2Solid, SiO2, "quartz2");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,quartz2Position), quartz2Logic, "quartz2", logicWorld, false, 0, checkOverlaps);

  G4double aluminum3Hz            = 0.57*mu;
  G4double aluminum3Position      = 2*SurfaceHz+2*aluminum1Hz+2*quartz1Hz+2*aluminum2Hz+2*quartz2Hz+aluminum3Hz;
  G4Box* aluminum3Solid           = new G4Box("aluminum3", TBMhx, TBMhx, aluminum3Hz); 
  G4LogicalVolume* aluminum3Logic = new G4LogicalVolume(aluminum3Solid, aluminum, "aluminum3");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,aluminum3Position), aluminum3Logic, "aluminum3", logicWorld, false, 0, checkOverlaps);

  G4double detPosition            = 2*SurfaceHz+2*aluminum1Hz+2*quartz1Hz+2*aluminum2Hz+2*quartz2Hz+2*aluminum3Hz+detHz;
  
  G4VSolid* siliconLayer          = new G4Box("siliconLayer", TBMhx, TBMhx, detHz); 
  G4VSolid* sensitiveArea         = new G4Box("sensitiveArea", 7.5*mu, 22.5*mu, detHz);
  G4VSolid *siliconSolid          = new G4SubtractionSolid("siliconSolid", siliconLayer, sensitiveArea); 
  G4LogicalVolume* siliconLogic   = new G4LogicalVolume(siliconSolid, silicon, "siliconLayer");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,detPosition), siliconLogic, "siliconLayer", logicWorld, false, 0, checkOverlaps);

  G4LogicalVolume* sensitiveLogic = new G4LogicalVolume(sensitiveArea, silicon, "sensitiveArea");  
  new G4PVPlacement(0, G4ThreeVector(0.,0.,detPosition), sensitiveLogic, "sensitiveArea", logicWorld, false, 0, checkOverlaps);



  G4Region* TBM  = new G4Region("TBM");
  aluminum1Logic->SetRegion(TBM);
  TBM->AddRootLogicalVolume(aluminum1Logic);
  aluminum2Logic->SetRegion(TBM);
  TBM->AddRootLogicalVolume(aluminum2Logic);
  aluminum3Logic->SetRegion(TBM);
  TBM->AddRootLogicalVolume(aluminum3Logic);
  quartz1Logic->SetRegion(TBM);
  TBM->AddRootLogicalVolume(quartz1Logic);
  quartz2Logic->SetRegion(TBM);
  TBM->AddRootLogicalVolume(quartz2Logic);
  siliconLogic->SetRegion(TBM);
  TBM->AddRootLogicalVolume(siliconLogic);
  sensitiveLogic->SetRegion(TBM);
  TBM->AddRootLogicalVolume(sensitiveLogic);

  G4double maxStep = 0.03*mu;
  fStepLimit = new G4UserLimits(maxStep);
  TBM->SetUserLimits(fStepLimit);

  fScoringVolume = sensitiveLogic;
  fScoringRegion = TBM;
  //
  //always return the physical World
  //
  return physWorld;
}