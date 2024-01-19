# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Set the name of the package.
atlas_subdir(AnalysisDemo)

# Component(s) in the package.
atlas_add_library(AnalysisDemoLib
   AnalysisDemo/*.h Root/*.cxx
   PUBLIC_HEADERS AnalysisDemo
   LINK_LIBRARIES AnaAlgorithmLib AsgTools AsgDataHandlesLib xAODMuon
                  MuonAnalysisToolsLib
   PRIVATE_LINK_LIBRARIES AsgMessagingLib)

atlas_add_dictionary(AnalysisDemoDict
   AnalysisDemo/AnalysisDemoDict.h
   AnalysisDemo/selection.xml
   LINK_LIBRARIES AnalysisDemoLib)

# Install files from the package.
atlas_install_python_modules(python/*.py)
atlas_install_scripts(share/*_eljob.py)
