#!/usr/bin/env python
#
# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#

# Set up (Py)ROOT.
import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.EnableImplicitMT()
ROOT.xAOD.Init().ignore()

# Create a data frame object.
import os
from xAODDataSource.Helpers import MakexAODDataFrame
df = MakexAODDataFrame(os.getenv('ASG_TEST_FILE_MC'))

# Create the global muon calibrator object/tool.
ROOT.gROOT.ProcessLine(
   '''
   ATE::MuonCalibrator gCalibrator("RDFMuonCalibrator");
   gCalibrator.initialize().ignore();
   ''')

# Create the calibrated muon pt as a new column, using hand-written code.
muon_manual = \
   df.Define('muon_pt',
             '''
             std::vector<float> result;
             result.reserve(Muons.size());
             for(const xAOD::Muon* mu : Muons) {
                result.push_back(gCalibrator.getCalibratedPt(
                   mu->pt(), mu->eta(), mu->phi()));
             }
             return result;
             ''')

# Create the calibrated muon pt as a new column, using a helper functor.
muon_functor = \
   df.Define('muon_pt', ROOT.ATE.AddCalibratedMuonPt(), ['Muons'])

# Make a histogram of the calibrated muon pt.
canvas = ROOT.TCanvas('canvas', 'canvas', 1600, 600)
canvas.Divide(2)
canvas.cd(1).SetLogy()
hist1 = muon_manual.Histo1D('muon_pt')
hist1.Draw()
canvas.cd(2).SetLogy()
hist2 = muon_functor.Histo1D('muon_pt')
hist2.Draw()
canvas.SaveAs('muon_pt.png')
