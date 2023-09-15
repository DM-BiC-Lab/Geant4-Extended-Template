#include "construction.hh"
#include "init.hh"

// Empty constructor and destructor
MyDetectorConstruction::MyDetectorConstruction() { }
MyDetectorConstruction::~MyDetectorConstruction() { }

// 
G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    // Get the NIST manager (allows for access to prebuilt materials)
    G4NistManager *nist = G4NistManager::Instance();
    
    G4Material *SiO2 = new G4Material("SiliconDioxide", 2.201*g/cm3, 2);
    SiO2->AddElement(nist->FindOrBuildElement("Si"), 1);
    SiO2->AddElement(nist->FindOrBuildElement("O"), 2);
    
    G4Material *H2O = new G4Material("Water", 1.000*g/cm3, 2);
    H2O->AddElement(nist->FindOrBuildElement("H"), 2);
    H2O->AddElement(nist->FindOrBuildElement("O"), 1);
    
    G4Element *carbon = nist->FindOrBuildElement("C");
    
    G4Material *aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
    aerogel->AddMaterial(SiO2, 62.5*perCent);
    aerogel->AddMaterial(H2O, 37.4*perCent);
    aerogel->AddElement(carbon, 0.1*perCent);
    
    G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double rindexAerogel[2] = {1.1, 1.1};
    G4double rindexWorld[2] = {1.0, 1.0};
    
    G4MaterialPropertiesTable *mptAerogel = new G4MaterialPropertiesTable();
    mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
    
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
    
    aerogel->SetMaterialPropertiesTable(mptAerogel);
    
    // Retrieve and store a material from the NIST manager
    // (list of materials in ~/Tommy/Geant4/Reference Files/ NIST_materials.txt)
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    worldMat->SetMaterialPropertiesTable(mptWorld);
    
    // Define a volume for the simulation to take place within
    G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
    
    
    // Create a Logical Volume using the G4Box and G4Material
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    // Place the logical volume into the simulation by creating a physical volume
    // (I'm not sure what a lot of the parameters in the constructor are for. The most
    // important are the second, third, and fourth, which are the the position of the volume,
    // the logical volume to use when creating the physical volume, and a name for the volume)
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    G4Box *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, Project::aerogelThickness);
    G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, aerogel, "logicRadiator");
    G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0.0, 0.0, 0.25*m), logicRadiator, "phsyRadiator", logicWorld, false, 0, true);
    G4VisAttributes *radiatorAttributes = new G4VisAttributes();
    radiatorAttributes->SetColor(0, 1, 1, 1);
    logicRadiator->SetVisAttributes(radiatorAttributes);
    
    G4Box *solidDetector = new G4Box("solidDetector", 0.01*m, 0.01*m, 0.01*m);
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    G4VisAttributes *detectorAttributes = new G4VisAttributes();
    detectorAttributes->SetColor(1, 1, 1, 0.1);
    logicDetector->SetVisAttributes(detectorAttributes);
    for(G4int i = 0; i < 50; i++) {
        for(G4int j = 0; j < 50; j++) {
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m + (2*i + 0.50)*m/100, -0.5*m+(2*j + 0.5)*m/100, 0.49*m), logicDetector, "physDetector", logicWorld, false, 100*i + j, true);
        }
    }
    
    return physWorld;
    
}

void MyDetectorConstruction::ConstructSDandField() {
    MySensitiveDetector *sensDet = new MySensitiveDetector("sensitiveDetector");
    
    logicDetector->SetSensitiveDetector(sensDet);
}
