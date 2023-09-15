#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{
    // Registers which types of physics systems to use in the
    // simulation. These two are pretty basic and standard
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4OpticalPhysics());
}

// Empty Destructor
MyPhysicsList::~MyPhysicsList() { }
