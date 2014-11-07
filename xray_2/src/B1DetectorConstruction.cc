#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 100*cm;
//  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  G4Material* vacuum =
     new G4Material("Vacuum",1,1.008*g/mole, 1.e-25*g/cm3,kStateGas,2.73*kelvin,1.e-25*g/cm3);

  //     
  // World
  //
  G4double world_sizeXY = 1.4*env_sizeXY;
  G4double world_sizeZ  = 1.4*env_sizeZ;
  //G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
//                        world_mat,           //its material
			world_mat,
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
//                        env_mat,             //its material
                        vacuum,
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //     
  // Shape 1
  //  
//  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_A-150_TISSUE");
  G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);
        
  // Conical section shape       
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = 1.*cm;
  G4double shape1_rminb =  0.*cm, shape1_rmaxb = 1.*cm;
  G4double shape1_hz = 1.*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Cons* solidShape1 =    
    new G4Cons("Shape1", 
    shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    shape1_phimin, shape1_phimax);
                      
  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        vacuum,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  //     
  // Shape 2
  //
  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
  G4ThreeVector pos2 = G4ThreeVector(0., 0., 0.*cm);
  G4ThreeVector pos3 = G4ThreeVector(-8.*cm,0.,2.*cm);
	
  G4ThreeVector pos4 = G4ThreeVector(8.*cm,0.,1.*cm);
  G4double shape2_size = 4.*cm;
  G4double shape2_depth = 2*cm;

  //     
  // Shape 2
  //  
  G4Box* solidShape2 =    
    new G4Box("Shape2",                    //its name
        shape2_size, shape2_size, shape2_depth); //its size
      
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,            //its solid
//                        shape2_mat,             //its material
                        shape2_mat,
                        "Shape2");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,         //at (0,0,0)
                    logicShape2,                //its logical volume
                    "Shape2",              //its name
                    logicEnv,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  //     
  // Shape 3
  //  
  G4Box* solidShape3 =    
    new G4Box("Shape3",                    //its name
        0.5*shape2_size, 0.5*shape2_size, 2*shape2_depth); //its size
      
  G4LogicalVolume* logicShape3 =                         
    new G4LogicalVolume(solidShape3,            //its solid
//                        shape2_mat,             //its material
                        shape2_mat,
                        "Shape3");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos3,         //at (0,0,0)
                    logicShape3,                //its logical volume
                    "Shape3",              //its name
                    logicEnv,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  //     
  // Shape 4
  //  
  G4Box* solidShape4 =    
    new G4Box("Shape4",                    //its name
        0.5*shape2_size, 0.5*shape2_size, 0.5*shape2_depth); //its size
      
  G4LogicalVolume* logicShape4 =                         
    new G4LogicalVolume(solidShape4,            //its solid
//                        shape2_mat,             //its material
                        shape2_mat,
                        "Shape4");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos4,         //at (0,0,0)
                    logicShape4,                //its logical volume
                    "Shape4",              //its name
                    logicEnv,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


                
  // Set Shape2 as scoring volume
  //
  fScoringVolume = logicShape2;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
