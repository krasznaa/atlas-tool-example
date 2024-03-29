# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Set the name of the package.
atlas_subdir(MuonAnalysisTools)

# Find the needed external(s).
find_package(ROOT COMPONENTS Core ROOTVecOps)
find_package(VDT)

# Component(s) in the package.
atlas_add_library(MuonAnalysisToolsLib
   MuonAnalysisTools/*.h Root/*.cxx
   PUBLIC_HEADERS MuonAnalysisTools
   INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${VDT_INCLUDE_DIRS}
   LINK_LIBRARIES ${ROOT_LIBRARIES} ${VDT_LIBRARIES} PATInterfaces
                  AsgMessagingLib AsgTools xAODMuon)

atlas_add_dictionary(MuonAnalysisToolsDict
   Root/MuonAnalysisToolsDict.h
   Root/selection.xml
   LINK_LIBRARIES MuonAnalysisToolsLib)

if (NOT XAOD_STANDALONE)
   atlas_add_component(MuonAnalysisTools
      src/components/*.cxx
      LINK_LIBRARIES MuonAnalysisToolsLib)
endif()
