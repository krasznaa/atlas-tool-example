# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Set up the input file reading.
import os
import AthenaPoolCnvSvc.ReadAthenaPool
svcMgr.EventSelector.InputCollections = [os.getenv('ASG_TEST_FILE_MC')]

# Add the analysis sequence to the main algorithm sequence.
from AnalysisDemo.AnalysisDemoSequence import makeAnalysisDemoSequence
athAlgSeq += makeAnalysisDemoSequence()
print(athAlgSeq)

# Configure the level of details in the output.
include('AthAnalysisBaseComps/SuppressLogging.py')
