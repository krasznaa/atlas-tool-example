# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Set the name of the package.
atlas_subdir(MuonAnalysisTools)

# Component(s) in the package.
atlas_add_library(MuonAnalysisToolsLib
   MuonAnalysisTools/*.h Root/*.cxx
   PUBLIC_HEADERS MuonAnalysisTools
   LINK_LIBRARIES PATInterfaces AsgMessagingLib AsgTools xAODMuon)
