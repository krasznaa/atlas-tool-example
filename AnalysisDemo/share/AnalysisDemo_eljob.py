#!/usr/bin/env python
#
# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#

# Set up (Py)ROOT.
import ROOT
ROOT.xAOD.Init().ignore()

# Set up the sample to run on.
import os
sh = ROOT.SH.SampleHandler()
sh.setMetaString('nc_tree', 'CollectionTree')
sample = ROOT.SH.SampleLocal('MC')
sample.add(os.getenv('ASG_TEST_FILE_MC'))
sh.add(sample)

# Create an EventLoop job.
job = ROOT.EL.Job()
job.sampleHandler(sh)

# Create the main algorithm sequence, and add the demo algorithm sequence to it.
from AnaAlgorithm.AlgSequence import AlgSequence
from AnalysisDemo.AnalysisDemoSequence import makeAnalysisDemoSequence
seq = AlgSequence()
seq += makeAnalysisDemoSequence()

# Add the sequence to the job.
print(seq)
seq.addSelfToJob(job)

# Run the job locally.
driver = ROOT.EL.LocalDriver()
driver.submit(job, 'AnalysisDemo')
