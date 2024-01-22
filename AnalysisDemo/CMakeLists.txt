# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Set the name of the package.
atlas_subdir(AnalysisDemo)

# Find the needed external(s).
find_package(ROOT COMPONENTS Core Gpad ROOTVecOps ROOTDataFrame)
find_package(VDT)

# Component(s) in the package.
atlas_add_library(AnalysisDemoLib
   AnalysisDemo/*.h Root/*.cxx
   PUBLIC_HEADERS AnalysisDemo
   LINK_LIBRARIES AnaAlgorithmLib AsgTools AsgDataHandlesLib xAODMuon
                  MuonAnalysisToolsLib
   PRIVATE_LINK_LIBRARIES AsgMessagingLib)

atlas_add_dictionary(AnalysisDemoDict
   Root/AnalysisDemoDict.h
   Root/selection.xml
   LINK_LIBRARIES AnalysisDemoLib)

if(NOT XAOD_STANDALONE)
   atlas_add_component(AnalysisDemo
      src/components/*.cxx
      LINK_LIBRARIES AnalysisDemoLib)
endif()

# Executable(s) in the package.
if(XAOD_STANDALONE)
   atlas_add_executable(AnalysisDemo_rdf
      utils/AnalysisDemo_rdf.cxx
      INCLUDE_DIRS ${ROOT_INCLUDE_DIRS} ${VDT_INCLUDE_DIRS}
      LINK_LIBRARIES ${ROOT_LIBRARIES} ${VDT_LIBRARIES}
                     xAODRootAccess xAODDataSourceLib AsgMessagingLib
                     MuonAnalysisToolsLib xAODMuon)
endif()

# Install files from the package.
atlas_install_python_modules(python/*.py)
if(XAOD_STANDALONE)
   atlas_install_scripts(share/*_eljob.py share/*_rdf.py)
else()
   atlas_install_joboptions(share/*_jobOptions.py)
endif()
