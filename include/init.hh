#ifndef INIT_HH
#define INIT_HH

#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include <iostream>
#include <fstream>

class Project
{
public:
    static void Initialize();
    static double emitterX;
    static double emitterY;
    static double emitterZ;
    static double aerogelThickness;
    static int autoRunNum;
};

#endif
