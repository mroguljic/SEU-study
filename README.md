# SEU-study
Studying energy deposition in a sensitive area of an electronic chip. If a large enough deposition occurs in this thin layer, the chip (TBM) can undergo a Single Event Upset. Layout of the chip can be changed in SEUDetectorConstruction.cc


Tested on ubuntu 14.04. LTS  
Simulations are performed using Geant (4.10.3)            - https://geant4.web.cern.ch/  
To install geant4 and compile the code, cmake 3 is needed -https://cmake.org/download/    
Root is required to look at the output                   - https://root.cern.ch/  
 
To compile, create a directory (SEU) and copy the source directory in it. From SEU directory, do:
```
mkdir build  
cd build  
cmake -DGeant4_DIR=...../geantInstallation/lib/Geant4-10.3.3 ../source  
make  
```
 
To run, edit configuration.txt according to your needs (particleType can be ignored, just set Z and A),edit run.mac to set the number of particles:
 ```
source ..../geantInstallation/bin/geant4.sh (or .csh)
cd build
./SEU run.mac  
  ```
         

