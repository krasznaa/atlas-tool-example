# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Framework import(s).
from AnaAlgorithm.AlgSequence import AlgSequence
from AnaAlgorithm.DualUseConfig import createAlgorithm, addPrivateTool

def makeAnalysisDemoSequence():
    '''
    This function sets up an algorithm sequence with the ATE::AnalysisAlg
    algorithm. Making sure that it would be configured correctly.
    '''

    # Creat the sequence.
    seq = AlgSequence()

    # Create the algorithm, and set it up.
    alg = createAlgorithm('ATE::AnalysisAlg', 'AnalysisDemo')
    addPrivateTool(alg, 'MuonCalibratorTool', 'ATE::MuonCalibratorTool')
    alg.InputMuons = 'Muons'
    alg.OutputMuons = 'CalibratedMuons'

    # Add the algorithm to the sequence.
    seq += alg

    # Return the sequence.
    return seq
