// Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#ifndef ANALYSISDEMO_ADDCALIBRATEDMUONPT_H
#define ANALYSISDEMO_ADDCALIBRATEDMUONPT_H

// Project include(s).
#include "MuonAnalysisTools/MuonCalibrator.h"

// EDM include(s).
#include <xAODMuon/MuonContainer.h>

// System include(s).
#include <vector>

namespace ATE {

/// Functor meant to simplify using the muon calibration tool in RDF
class AddCalibratedMuonPt {

public:
    /// Default constructor
    AddCalibratedMuonPt();
    /// Copy constructor
    AddCalibratedMuonPt(const AddCalibratedMuonPt&);
    /// Move constructor
    AddCalibratedMuonPt(AddCalibratedMuonPt&&);

    /// Operator creating a variable with the calibrated muon pts
    std::vector<float> operator()(const xAOD::MuonContainer& muons) const;

private:
    /// Tool performing the muon momentum calibration
    MuonCalibrator m_calibrator{"AddCalibratedMuuonPt"};

};  // class AddCalibratedMuonPt

}  // namespace ATE

#endif  // ANALYSISDEMO_ADDCALIBRATEDMUONPT_H
