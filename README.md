# SEU-study
Studying energy deposition in a sensitive area of an electronic chip. Tested on ubuntu 14.04. LTS  
Simulations are performed using Geant (4.10.3)            - https://geant4.web.cern.ch/.
To install geant4 and compile the code, cmake 3 is needed -https://cmake.org/download/  
Root is required to look at the output                   - https://root.cern.ch/  
 
To compile:  
            mkdir SEU  
            copy /source directory into SEU  
            mkdir build  
            cd build  
            cmake -DGeant4_DIR=...../geantInstallation/lib/Geant4-10.3.3 ../source  
            make  
 
 To run:    
            source ..../geantInstallation/bin/geant4.sh (or .csh)
            cd build
            edit configuration.txt according to your needs  
            edit run.mac to set the number of particles  
            ./SEU run.mac  
           

