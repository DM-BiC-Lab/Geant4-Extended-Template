#include "init.hh"

double Project::emitterX;
double Project::emitterY;
double Project::emitterZ;
double Project::aerogelThickness;
int Project::autoRunNum;


using namespace std;

void Project::Initialize()
{
    Project::autoRunNum = 0;

    fstream file;
    string line;
    file.open("../project-variables.txt", ios::in);
    getline(file, line);
    getline(file, line);
    Project::emitterX = stod(line);
    getline(file, line);
    Project::emitterY = stod(line);
    getline(file, line);
    Project::emitterZ = stod(line);
    getline(file, line);
    getline(file, line);
    Project::aerogelThickness = stod(line) * mm;
    
    file.close();
}
