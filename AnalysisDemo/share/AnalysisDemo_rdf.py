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

# Create the muon calibrator object(s).
muCalibxAOD = ROOT.ATE.RDF.MuonCalibratorxAOD()
muCalibxAOD.initialize().ignore()
muCalib = ROOT.ATE.RDF.MuonCalibrator()
muCalib.initialize().ignore()

# Create the calibrated muon pt as a new column, from the xAOD container.
muon_pt_xaod = df.Define('muon_pt_calib', muCalibxAOD, ['Muons'])

# Create the calibrated muon pt as a new column, from primitive columns.
# For this, first set up the primitive columns from the xAOD container.
code = '''
   std::vector<float> result;
   result.reserve(Muons.size());
   for (const xAOD::Muon* muon : Muons) {
      result.push_back(muon->%s());
   }
   return result;
   '''
muon_primitive = df.Define('muon_eta', code % 'eta') \
                   .Define('muon_phi', code % 'phi') \
                   .Define('muon_pt',  code % 'pt')
# Now create the calibrated column.
muon_pt_primitive = muon_primitive.Define('muon_pt_calib', muCalib,            \
                                          ['muon_pt', 'muon_eta', 'muon_phi'])

# Make a histogram of the calibrated muon pts.
canvas = ROOT.TCanvas('canvas', 'canvas', 1600, 600)
canvas.Divide(2)
canvas.cd(1).SetLogy()
hist1 = muon_pt_xaod.Histo1D('muon_pt_calib')
hist1.Draw()
canvas.cd(2).SetLogy()
hist2 = muon_pt_primitive.Histo1D('muon_pt_calib')
hist2.Draw()
canvas.SaveAs('muon_pt.png')
