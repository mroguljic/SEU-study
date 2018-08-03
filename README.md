# SEU-study
Studying energy deposition in a sensitive area of an electronic chip

Simulations are performed using Geant (4.10.3) - https://geant4.web.cern.ch/.

To compile: mkdir SEU  
            copy /source directory into SEU  
            mkdir build  
            cd build  
            cmake -DGeant4_DIR=...../geantInstallation/lib/Geant4-10.3.3 ../source  
            make  
 
 To run:    enter build directory  
            edit configuration.txt according to your needs  
            edit run.mac to set the number of particles  
            ./SEU run.mac  
           
 It is recommended to use cmake3        - https://cmake.org/download/  
 Root is required to look at the output - https://root.cern.ch/  
