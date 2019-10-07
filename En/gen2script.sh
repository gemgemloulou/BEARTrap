#!/bin/bash

~/BEARTrap/Gen2/BDN-build/BDN 137I_c2_a-0.3_0.1MeV_n_geant.txt
mv GEANT4_output.txt G4_137I_0.1MeV_n.txt
mv BDN.root BDN_137I_0.1MeV_n.root

~/BEARTrap/Gen2/BDN-build/BDN 137I_c2_a-0.3_1MeV_n_geant.txt
mv GEANT4_output.txt G4_137I_1.0MeV_n.txt
mv BDN.root BDN_137I_1.0MeV_n.root
