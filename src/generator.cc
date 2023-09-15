#include "generator.hh"
#include "init.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    // When constructed, created a particle gun
    // that emits one particle
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    // When destroys, deletes the particle gun
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("proton");
    
    G4ThreeVector pos(0.0, 0.0, 0.0);
    G4ThreeVector mom(Project::emitterX, Project::emitterY, Project::emitterZ);
    
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(100.0*GeV);
    fParticleGun->SetParticleDefinition(particle);
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}
