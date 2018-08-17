#include "UserInput.hh" 
#include "G4SystemOfUnits.hh"

//Sampling options
//const long long UserInput::events=1e3; //events to be generated


UserInput::UserInput(){
  std::ifstream cfgFile; 
  cfgFile.open(cfgFileName);
  std::string line;
  char * key, * value;
  while(cfgFile >> line){
    char *cstr   = &line[0u];
    key          = std::strtok (cstr,"=");
    value        = std::strtok (NULL,"=");
    cfgParams.insert(std::make_pair(key,value));
    }
  particleEnergy = stod(cfgParams["particleEnergy"])*MeV;
  detThickness   = stod(cfgParams["detectorThickness"])*mm;
  treeFile       = cfgParams["outputTree"];
  particleType   = cfgParams["particleType"];
  ionZ           = stoi(cfgParams["ionZ"]);
  ionA           = stoi(cfgParams["ionA"]);
  ionCharge      = stod(cfgParams["ionCharge"])*eplus;
  maxStepLength  = stod(cfgParams["maxStep"])*um;

}

UserInput::~UserInput(){}

