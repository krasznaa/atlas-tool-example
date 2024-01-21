# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Set up the compiler:
source /opt/lcg/binutils/*/x86_64-*/setup.sh
source /opt/lcg/gcc/*/x86_64-*/setup.sh
echo "Configured GCC from: ${CC}"

# Configure Calibration via HTTP
export PATHRESOLVER_ALLOWHTTPDOWNLOAD=1

# Set up the analysis release:
source /usr/AnalysisBase/*/InstallArea/*/setup.sh
echo "Configured AnalysisBase from: ${AnalysisBase_DIR}"
